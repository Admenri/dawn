SKIP: FAILED


enable f16;

@group(0) @binding(0) var<storage, read_write> prevent_dce : vec3<f16>;

fn subgroupExclusiveAdd_e58e23() -> vec3<f16> {
  var arg_0 = vec3<f16>(1.0h);
  var res : vec3<f16> = subgroupExclusiveAdd(arg_0);
  return res;
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = subgroupExclusiveAdd_e58e23();
}

Failed to generate: error: Unknown builtin method: 0x558ff6290498
