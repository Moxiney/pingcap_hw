#pragma once

#include <cstdint>
#include <string.h>

using Byte = char;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

namespace common {

  struct RawData {
    i32 size;
    Byte data[];

    RawData() : size(0) {};

    bool operator==(RawData& that) {
      return memcmp(this, &that, sizeof(size) + size) == 0;
    }

    Byte* get_data() {
      return data;
    }

    RawData* next() {
      return reinterpret_cast<RawData*>(this + sizeof(i32) + size);
    }
  };
} // namespace common
