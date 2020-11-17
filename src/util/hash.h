/**
 * @file hash.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 哈希函数的辅助函数。
 *
 */
#pragma once

#include <functional>

#include "common/def.h"

namespace std {
    template<>
    class hash<common::RawData> {
    public:
        size_t operator()(const common::RawData& data) const {
            std::string s(data._data, data._size);
            return std::hash<std::string>()(s);
        }

        size_t operator()(const common::RawData& data, i32 n) {
            std::string s(data._data, data._size);
            s += std::to_string(n);
            return std::hash<std::string>()(s);

        }
    };
} // namespace std



namespace util {
    class Hasher {
    public:
        virtual u64 hash(Byte* data, i32 size) {
            return (u64)size;
        };
    };
} // namespace util
