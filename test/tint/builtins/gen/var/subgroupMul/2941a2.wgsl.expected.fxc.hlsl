SKIP: FAILED


enable f16;

@group(0) @binding(0) var<storage, read_write> prevent_dce : f16;

fn subgroupMul_2941a2() -> f16 {
  var arg_0 = 1.0h;
  var res : f16 = subgroupMul(arg_0);
  return res;
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = subgroupMul_2941a2();
}

Failed to generate: error: Unknown builtin method: subgroupMul
