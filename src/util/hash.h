#pragma once

#include "common/def.h"

namespace util {
    class Hasher {
    public:
        virtual u64 hash(Byte* data, i32 size) {
            return (u64)size;
        };
    };
} // namespace util
