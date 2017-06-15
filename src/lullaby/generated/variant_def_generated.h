// Autogenerated code.  Do not edit.
#ifndef _SRC_LULLABY_GENERATED_VARIANT_DEF_GENERATED_H_
#define _SRC_LULLABY_GENERATED_VARIANT_DEF_GENERATED_H_

#include <type_traits>
#include <memory>
#include "flatbuffers/variant_def_generated.h"
#include "lullaby/base/common_types.h"
#include "lullaby/base/typeid.h"
#include "lullaby/util/color.h"
#include "lullaby/util/math.h"
#include "lullaby/util/optional.h"
#include "common_generated.h"

namespace lull {
class DataBoolT;
class DataIntT;
class DataFloatT;
class DataHashValueT;
class DataStringT;
class DataVec2T;
class DataVec3T;
class DataVec4T;
class DataQuatT;
class VariantDefT;
class KeyVariantPairDefT;
class DataBoolT {
 public:
  using FlatBufferType = DataBool;

  bool value = 0;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataIntT {
 public:
  using FlatBufferType = DataInt;

  int32_t value = 0;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataFloatT {
 public:
  using FlatBufferType = DataFloat;

  float value = 0.0f;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataHashValueT {
 public:
  using FlatBufferType = DataHashValue;

  std::string value;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataStringT {
 public:
  using FlatBufferType = DataString;

  std::string value;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataVec2T {
 public:
  using FlatBufferType = DataVec2;

  mathfu::vec2 value = {0.f, 0.f};

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataVec3T {
 public:
  using FlatBufferType = DataVec3;

  mathfu::vec3 value = {0.f, 0.f, 0.f};

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataVec4T {
 public:
  using FlatBufferType = DataVec4;

  mathfu::vec4 value = {0.f, 0.f, 0.f, 0.f};

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class DataQuatT {
 public:
  using FlatBufferType = DataQuat;

  mathfu::quat value = {0.f, 0.f, 0.f, 1.f};

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

class VariantDefT {
 public:
  using FlatBufferType = VariantDef;
  static const uint8_t kNone = VariantDef_NONE;

  VariantDefT() {}
  ~VariantDefT() { reset(); }

  VariantDefT(const VariantDefT& rhs) { assign(rhs); }
  VariantDefT& operator=(const VariantDefT& rhs) {
    assign(rhs);
    return *this;
  }

  void reset();

  FlatBufferType type() const {
    return type_;
  }

  template <typename T>
  T* get() {
    return type_ == get_type<T>() ?
        reinterpret_cast<T*>(&data_) : nullptr;
  }

  template <typename T>
  const T* get() const {
    return type_ == get_type<T>() ?
        reinterpret_cast<const T*>(&data_) : nullptr;
  }

  template <typename T>
  T* set();

  template <typename Archive>
  void SerializeFlatbuffer(FlatBufferType type, Archive archive);

 private:
  void assign(const VariantDefT& rhs);

  template <typename T>
  void destroy() {
    reinterpret_cast<T*>(&data_)->~T();
  }

  template <typename T>
  static FlatBufferType get_type() {
    return VariantDef_NONE;
  }

  template <typename T>
  using Store = std::aligned_storage<sizeof(T), alignof(T)>;
  union Buffer {
    Store<lull::DataBoolT>::type DataBool_;
    Store<lull::DataIntT>::type DataInt_;
    Store<lull::DataFloatT>::type DataFloat_;
    Store<lull::DataStringT>::type DataString_;
    Store<lull::DataHashValueT>::type DataHashValue_;
    Store<lull::DataVec2T>::type DataVec2_;
    Store<lull::DataVec3T>::type DataVec3_;
    Store<lull::DataVec4T>::type DataVec4_;
    Store<lull::DataQuatT>::type DataQuat_;
  };
  Buffer data_;
  FlatBufferType type_ = VariantDef_NONE;
};

class KeyVariantPairDefT {
 public:
  using FlatBufferType = KeyVariantPairDef;

  std::string key;
  lull::VariantDefT value;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

template <typename Archive>
void DataBoolT::SerializeFlatbuffer(Archive archive) {
  archive.Scalar(&value, 4, 0);
}

template <typename Archive>
void DataIntT::SerializeFlatbuffer(Archive archive) {
  archive.Scalar(&value, 4, 0);
}

template <typename Archive>
void DataFloatT::SerializeFlatbuffer(Archive archive) {
  archive.Scalar(&value, 4, 0.0f);
}

template <typename Archive>
void DataHashValueT::SerializeFlatbuffer(Archive archive) {
  archive.String(&value, 4);
}

template <typename Archive>
void DataStringT::SerializeFlatbuffer(Archive archive) {
  archive.String(&value, 4);
}

template <typename Archive>
void DataVec2T::SerializeFlatbuffer(Archive archive) {
  archive.NativeStruct(&value, 4);
}

template <typename Archive>
void DataVec3T::SerializeFlatbuffer(Archive archive) {
  archive.NativeStruct(&value, 4);
}

template <typename Archive>
void DataVec4T::SerializeFlatbuffer(Archive archive) {
  archive.NativeStruct(&value, 4);
}

template <typename Archive>
void DataQuatT::SerializeFlatbuffer(Archive archive) {
  archive.NativeStruct(&value, 4);
}

inline void VariantDefT::reset() {
  switch (type_) {
    case VariantDef_DataBool: {
      destroy<lull::DataBoolT>();
      break;
    }
    case VariantDef_DataInt: {
      destroy<lull::DataIntT>();
      break;
    }
    case VariantDef_DataFloat: {
      destroy<lull::DataFloatT>();
      break;
    }
    case VariantDef_DataString: {
      destroy<lull::DataStringT>();
      break;
    }
    case VariantDef_DataHashValue: {
      destroy<lull::DataHashValueT>();
      break;
    }
    case VariantDef_DataVec2: {
      destroy<lull::DataVec2T>();
      break;
    }
    case VariantDef_DataVec3: {
      destroy<lull::DataVec3T>();
      break;
    }
    case VariantDef_DataVec4: {
      destroy<lull::DataVec4T>();
      break;
    }
    case VariantDef_DataQuat: {
      destroy<lull::DataQuatT>();
      break;
    }
    default:
      break;
  }
  type_ = VariantDef_NONE;
}

inline void VariantDefT::assign(const VariantDefT& rhs) {
  reset();
  switch (rhs.type_) {
    case VariantDef_DataBool: {
      *set<lull::DataBoolT>() = *rhs.get<lull::DataBoolT>();
      break;
    }
    case VariantDef_DataInt: {
      *set<lull::DataIntT>() = *rhs.get<lull::DataIntT>();
      break;
    }
    case VariantDef_DataFloat: {
      *set<lull::DataFloatT>() = *rhs.get<lull::DataFloatT>();
      break;
    }
    case VariantDef_DataString: {
      *set<lull::DataStringT>() = *rhs.get<lull::DataStringT>();
      break;
    }
    case VariantDef_DataHashValue: {
      *set<lull::DataHashValueT>() = *rhs.get<lull::DataHashValueT>();
      break;
    }
    case VariantDef_DataVec2: {
      *set<lull::DataVec2T>() = *rhs.get<lull::DataVec2T>();
      break;
    }
    case VariantDef_DataVec3: {
      *set<lull::DataVec3T>() = *rhs.get<lull::DataVec3T>();
      break;
    }
    case VariantDef_DataVec4: {
      *set<lull::DataVec4T>() = *rhs.get<lull::DataVec4T>();
      break;
    }
    case VariantDef_DataQuat: {
      *set<lull::DataQuatT>() = *rhs.get<lull::DataQuatT>();
      break;
    }
    default:
      break;
  }
}

template <typename T>
T* VariantDefT::set() {
  reset();
  type_ = get_type<T>();
  if (type_ != kNone) {
    return new (&data_) T();
  }
  return nullptr;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataBoolT>() {
  return VariantDef_DataBool;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataIntT>() {
  return VariantDef_DataInt;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataFloatT>() {
  return VariantDef_DataFloat;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataStringT>() {
  return VariantDef_DataString;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataHashValueT>() {
  return VariantDef_DataHashValue;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataVec2T>() {
  return VariantDef_DataVec2;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataVec3T>() {
  return VariantDef_DataVec3;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataVec4T>() {
  return VariantDef_DataVec4;
}

template <>
inline VariantDef VariantDefT::get_type<lull::DataQuatT>() {
  return VariantDef_DataQuat;
}


template <typename Archive>
void VariantDefT::SerializeFlatbuffer(FlatBufferType type, Archive archive) {
  switch (type) {
    case VariantDef_DataBool: {
      if (archive.IsDestructive()) {
        set<lull::DataBoolT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataBoolT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataInt: {
      if (archive.IsDestructive()) {
        set<lull::DataIntT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataIntT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataFloat: {
      if (archive.IsDestructive()) {
        set<lull::DataFloatT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataFloatT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataString: {
      if (archive.IsDestructive()) {
        set<lull::DataStringT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataStringT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataHashValue: {
      if (archive.IsDestructive()) {
        set<lull::DataHashValueT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataHashValueT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataVec2: {
      if (archive.IsDestructive()) {
        set<lull::DataVec2T>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataVec2T>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataVec3: {
      if (archive.IsDestructive()) {
        set<lull::DataVec3T>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataVec3T>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataVec4: {
      if (archive.IsDestructive()) {
        set<lull::DataVec4T>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataVec4T>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    case VariantDef_DataQuat: {
      if (archive.IsDestructive()) {
        set<lull::DataQuatT>()->SerializeFlatbuffer(archive);
      } else {
        get<lull::DataQuatT>()->SerializeFlatbuffer(archive);
      }
      break;
    }
    default:
      if (archive.IsDestructive()) {
        reset();
      }
      break;
  }
}

template <typename Archive>
void KeyVariantPairDefT::SerializeFlatbuffer(Archive archive) {
  archive.String(&key, 4);
  archive.Union(&value, 8, lull::VariantDefT::kNone);
}

}  // namespace lull

LULLABY_SETUP_TYPEID(lull::DataBoolT);
LULLABY_SETUP_TYPEID(lull::DataIntT);
LULLABY_SETUP_TYPEID(lull::DataFloatT);
LULLABY_SETUP_TYPEID(lull::DataHashValueT);
LULLABY_SETUP_TYPEID(lull::DataStringT);
LULLABY_SETUP_TYPEID(lull::DataVec2T);
LULLABY_SETUP_TYPEID(lull::DataVec3T);
LULLABY_SETUP_TYPEID(lull::DataVec4T);
LULLABY_SETUP_TYPEID(lull::DataQuatT);
LULLABY_SETUP_TYPEID(lull::VariantDefT);
LULLABY_SETUP_TYPEID(lull::KeyVariantPairDefT);

#endif  // _SRC_LULLABY_GENERATED_VARIANT_DEF_GENERATED_H_
