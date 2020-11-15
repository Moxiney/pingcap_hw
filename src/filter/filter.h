#pragma once

#include "common/def.h"

namespace filter {
    class Filter {
    public:
        Filter() = default;
        virtual ~Filter() = default;

        virtual bool operator()(const common::RawData& key) {
            return true;
        }


    };

    class BloomFilter : public Filter {
    public:
        BloomFilter() = default;
        ~BloomFilter() = default;


        bool operator()(const common::RawData& key) {
            return true;
        }
    private:

        // Byte array control by variable M

    };
} // namespace filter
