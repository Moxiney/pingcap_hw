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
