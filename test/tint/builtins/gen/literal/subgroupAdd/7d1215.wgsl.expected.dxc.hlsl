SKIP: FAILED


@group(0) @binding(0) var<storage, read_write> prevent_dce : vec3<f32>;

fn subgroupAdd_7d1215() -> vec3<f32> {
  var res : vec3<f32> = subgroupAdd(vec3<f32>(1.0f));
  return res;
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = subgroupAdd_7d1215();
}

Failed to generate: error: Unknown builtin method: subgroupAdd
