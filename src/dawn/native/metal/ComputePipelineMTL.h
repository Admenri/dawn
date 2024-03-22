// Copyright 2017 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef SRC_DAWN_NATIVE_METAL_COMPUTEPIPELINEMTL_H_
#define SRC_DAWN_NATIVE_METAL_COMPUTEPIPELINEMTL_H_

#include <vector>

#include "dawn/native/ComputePipeline.h"
#include "dawn/native/CreatePipelineAsyncEvent.h"

#include "dawn/common/NSRef.h"

#import <Metal/Metal.h>

namespace dawn::native::metal {

class Device;

class ComputePipeline final : public ComputePipelineBase {
  public:
    static Ref<ComputePipeline> CreateUninitialized(
        Device* device,
        const UnpackedPtr<ComputePipelineDescriptor>& descriptor);
    static Ref<CreateComputePipelineAsyncEvent> InitializeAsync(
        Device* device,
        Ref<ComputePipelineBase> computePipeline,
        const CreateComputePipelineAsyncCallbackInfo& callbackInfo);

    ComputePipeline(DeviceBase* device, const UnpackedPtr<ComputePipelineDescriptor>& descriptor);
    ~ComputePipeline() override;

    void Encode(id<MTLComputeCommandEncoder> encoder);
    MTLSize GetLocalWorkGroupSize() const;
    bool RequiresStorageBufferLength() const;

  private:
    using ComputePipelineBase::ComputePipelineBase;
    MaybeError InitializeImpl() override;

    NSPRef<id<MTLComputePipelineState>> mMtlComputePipelineState;
    MTLSize mLocalWorkgroupSize;
    bool mRequiresStorageBufferLength;
    std::vector<uint32_t> mWorkgroupAllocations;
};

}  // namespace dawn::native::metal

#endif  // SRC_DAWN_NATIVE_METAL_COMPUTEPIPELINEMTL_H_
