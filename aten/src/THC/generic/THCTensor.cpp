#ifndef THC_GENERIC_FILE
#define THC_GENERIC_FILE "THC/generic/THCTensor.cpp"
#else

#include <ATen/InferSize.h>
#include <ATen/NativeFunctions.h>
#include <c10/util/irange.h>

/**** creation methods ****/

THCTensor *THCTensor_(newWithStorage1d)(THCState *state, THCStorage *storage, ptrdiff_t storageOffset,
                               int64_t size0, int64_t stride0)
{
  c10::raw::intrusive_ptr::incref(storage);
  THTensor* self = c10::make_intrusive<at::TensorImpl, at::UndefinedTensorImpl>(
                       c10::intrusive_ptr<at::StorageImpl>::reclaim(storage),
                       at::DispatchKey::CUDA,
                       caffe2::TypeMeta::Make<scalar_t>())
                       .release();
  THCTensor_setStorage(state, self, storage, storageOffset, {size0}, {stride0});

  return self;
}

void THCTensor_(free)(THCState *state, THCTensor *self)
{
  THCTensor_free(state, self);
}
#endif
