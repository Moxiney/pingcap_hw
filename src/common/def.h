/**
 * @file def.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 全局的一些类型定义
 */
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

  /**
   * @brief RawData 代表一个不定长的数据，size 代表 data 的长度
   *
   */
  struct RawData {
    i32 _size;
    Byte _data[];

    RawData() : _size(0) {};

    /**
     * @brief 判断两个 RawData 是否相等
     *
     * @param that
     * @return true
     * @return false
     */
    bool operator==(RawData& that) {
      return memcmp(this, &that, sizeof(_size) + _size) == 0;
    }

    /**
     * @brief 将一个数据存储成 RawData 的格式。
     *
     * @param data
     * @param size
     */
    void store(const Byte* data, i32 size) {
      _size = size;
      memcpy(_data, data, _size);
    }

    /**
     * @brief 指向 RawData 的末端。如果 RawData 是连续存储的，则代表下一个 RawData 的地址。
     *
     * @return RawData*
     */
    RawData* next() {
      return reinterpret_cast<RawData*>((Byte*)this + sizeof(i32) + _size);
    }
  };
} // namespace common
