#version 310 es

layout(binding = 0, std430) buffer Matrix_ssbo {
  float numbers[];
} firstMatrix;

layout(binding = 1, std430) buffer Matrix_ssbo_1 {
  float numbers[];
} secondMatrix;

layout(binding = 2, std430) buffer Matrix_ssbo_2 {
  float numbers[];
} resultMatrix;

layout(binding = 3) uniform Uniforms_ubo {
  uint dimAOuter;
  uint dimInner;
  uint dimBOuter;
} uniforms;

float mm_readA(uint row, uint col) {
  bool tint_tmp = (row < uniforms.dimAOuter);
  if (tint_tmp) {
    tint_tmp = (col < uniforms.dimInner);
  }
  if ((tint_tmp)) {
    float result = firstMatrix.numbers[((row * uniforms.dimInner) + col)];
    return result;
  }
  return 0.0f;
}

float mm_readB(uint row, uint col) {
  bool tint_tmp_1 = (row < uniforms.dimInner);
  if (tint_tmp_1) {
    tint_tmp_1 = (col < uniforms.dimBOuter);
  }
  if ((tint_tmp_1)) {
    float result = secondMatrix.numbers[((row * uniforms.dimBOuter) + col)];
    return result;
  }
  return 0.0f;
}

void mm_write(uint row, uint col, float value) {
  bool tint_tmp_2 = (row < uniforms.dimAOuter);
  if (tint_tmp_2) {
    tint_tmp_2 = (col < uniforms.dimBOuter);
  }
  if ((tint_tmp_2)) {
    uint index = (col + (row * uniforms.dimBOuter));
    resultMatrix.numbers[index] = value;
  }
}

shared float mm_Asub[64][64];
shared float mm_Bsub[64][64];
void tint_symbol(uvec3 local_id, uvec3 global_id, uint local_invocation_index) {
  {
    for(uint idx = local_invocation_index; (idx < 4096u); idx = (idx + 256u)) {
      uint i = (idx / 64u);
      uint i_1 = (idx % 64u);
      mm_Asub[i][i_1] = 0.0f;
      mm_Bsub[i][i_1] = 0.0f;
    }
  }
  barrier();
  uint tileRow = (local_id.y * 4u);
  uint tileCol = (local_id.x * 4u);
  uint globalRow = (global_id.y * 4u);
  uint globalCol = (global_id.x * 4u);
  uint numTiles = (((uniforms.dimInner - 1u) / 64u) + 1u);
  float acc[16] = float[16](0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  float ACached = 0.0f;
  float BCached[4] = float[4](0.0f, 0.0f, 0.0f, 0.0f);
  {
    for(uint index = 0u; (index < 16u); index = (index + 1u)) {
      acc[index] = 0.0f;
    }
  }
  uint ColPerThreadA = (64u / 16u);
  uint tileColA = (local_id.x * ColPerThreadA);
  uint RowPerThreadB = (64u / 16u);
  uint tileRowB = (local_id.y * RowPerThreadB);
  {
    for(uint t = 0u; (t < numTiles); t = (t + 1u)) {
      {
        for(uint innerRow = 0u; (innerRow < 4u); innerRow = (innerRow + 1u)) {
          {
            for(uint innerCol = 0u; (innerCol < ColPerThreadA); innerCol = (innerCol + 1u)) {
              uint inputRow = (tileRow + innerRow);
              uint inputCol = (tileColA + innerCol);
              float tint_symbol_1 = mm_readA((globalRow + innerRow), ((t * 64u) + inputCol));
              mm_Asub[inputRow][inputCol] = tint_symbol_1;
            }
          }
        }
      }
      {
        for(uint innerRow = 0u; (innerRow < RowPerThreadB); innerRow = (innerRow + 1u)) {
          {
            for(uint innerCol = 0u; (innerCol < 4u); innerCol = (innerCol + 1u)) {
              uint inputRow = (tileRowB + innerRow);
              uint inputCol = (tileCol + innerCol);
              float tint_symbol_2 = mm_readB(((t * 64u) + inputRow), (globalCol + innerCol));
              mm_Bsub[innerCol][inputCol] = tint_symbol_2;
            }
          }
        }
      }
      barrier();
      {
        for(uint k = 0u; (k < 64u); k = (k + 1u)) {
          {
            for(uint inner = 0u; (inner < 4u); inner = (inner + 1u)) {
              BCached[inner] = mm_Bsub[k][(tileCol + inner)];
            }
          }
          {
            for(uint innerRow = 0u; (innerRow < 4u); innerRow = (innerRow + 1u)) {
              ACached = mm_Asub[(tileRow + innerRow)][k];
              {
                for(uint innerCol = 0u; (innerCol < 4u); innerCol = (innerCol + 1u)) {
                  uint index = ((innerRow * 4u) + innerCol);
                  acc[index] = (acc[index] + (ACached * BCached[innerCol]));
                }
              }
            }
          }
        }
      }
      barrier();
    }
  }
  {
    for(uint innerRow = 0u; (innerRow < 4u); innerRow = (innerRow + 1u)) {
      {
        for(uint innerCol = 0u; (innerCol < 4u); innerCol = (innerCol + 1u)) {
          uint index = ((innerRow * 4u) + innerCol);
          mm_write((globalRow + innerRow), (globalCol + innerCol), acc[index]);
        }
      }
    }
  }
}

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
void main() {
  tint_symbol(gl_LocalInvocationID, gl_GlobalInvocationID, gl_LocalInvocationIndex);
  return;
}
