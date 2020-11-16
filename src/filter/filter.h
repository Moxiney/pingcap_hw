#pragma once

#include "common/def.h"
#include "util/hash.h"

#define BIT_ARRAY_SIZE 32
#define HASH_RANGE (BIT_ARRAY_SIZE * 8)
#define NUM_HASH 4

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
        BloomFilter() {
            memset(_bit_array, 0, BIT_ARRAY_SIZE);
        };
        ~BloomFilter() = default;


        bool operator()(const common::RawData& key) {
            std::hash<common::RawData> hash_fn;
            for (int i = 0; i < NUM_HASH;i++) {
                i32 v = hash_fn(key, i) % HASH_RANGE;

                Byte b = 1 << (v & 0x3);

                if ((_bit_array[v >> 3] & b) != b) {
                    return false;
                }
            }
            return true;
        }

        bool insert(common::RawData* key) {
            // generate k hash value.
            std::hash<common::RawData> hash_fn;
            for (int i = 0; i < NUM_HASH; i++) {
                i32 v = hash_fn(*key, i) % HASH_RANGE;

                // set bit.
                _bit_array[v >> 3] |= 1 << (v & 0x3);
            }
        }

    private:
        // Byte array control by variable M
        Byte _bit_array[BIT_ARRAY_SIZE];

    };
} // namespace filter
