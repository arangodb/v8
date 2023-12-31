// Copyright 2018 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_OBJECTS_MAYBE_OBJECT_H_
#define V8_OBJECTS_MAYBE_OBJECT_H_

#include "src/objects/tagged-impl.h"

namespace v8 {
namespace internal {

// A MaybeObject is either a SMI, a strong reference to a HeapObject, a weak
// reference to a HeapObject, or a cleared weak reference. It's used for
// implementing in-place weak references (see design doc: goo.gl/j6SdcK )
class MaybeObject : public TaggedImpl<HeapObjectReferenceType::WEAK, Address> {
 public:
  constexpr MaybeObject() : TaggedImpl(kNullAddress) {}
  constexpr explicit MaybeObject(Address ptr) : TaggedImpl(ptr) {}

  // These operator->() overloads are required for handlified code.
  constexpr const MaybeObject* operator->() const { return this; }

  V8_INLINE static MaybeObject FromSmi(Tagged<Smi> smi);

  V8_INLINE static MaybeObject FromObject(Tagged<Object> object);

  V8_INLINE static MaybeObject MakeWeak(MaybeObject object);

  V8_INLINE static MaybeObject Create(MaybeObject o);
  V8_INLINE static MaybeObject Create(Tagged<Object> o);
  V8_INLINE static MaybeObject Create(Tagged<Smi> smi);

#ifdef VERIFY_HEAP
  static void VerifyMaybeObjectPointer(Isolate* isolate, MaybeObject p);
#endif

 private:
  template <typename TFieldType, int kFieldOffset, typename CompressionScheme>
  friend class TaggedField;
};

// A HeapObjectReference is either a strong reference to a HeapObject, a weak
// reference to a HeapObject, or a cleared weak reference.
class HeapObjectReference : public MaybeObject {
 public:
  explicit HeapObjectReference(Address address) : MaybeObject(address) {}
  V8_INLINE explicit HeapObjectReference(Tagged<Object> object);

  V8_INLINE static HeapObjectReference Strong(Tagged<Object> object);

  V8_INLINE static HeapObjectReference Weak(Tagged<Object> object);

  V8_INLINE static HeapObjectReference From(Tagged<Object> object,
                                            HeapObjectReferenceType type);

  V8_INLINE static HeapObjectReference ClearedValue(PtrComprCageBase cage_base);

  template <typename THeapObjectSlot>
  V8_INLINE static void Update(THeapObjectSlot slot, Tagged<HeapObject> value);
};

}  // namespace internal
}  // namespace v8

#endif  // V8_OBJECTS_MAYBE_OBJECT_H_
