/**
 * @file filter.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 定义了 Filter 数据结构，用于判断一个 RawData 是否存在。
 *
 */
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

    /**
     * @brief BloomFilter 用于判断一个 Key 是否存在。
     *
     */
    class BloomFilter : public Filter {
    public:
        BloomFilter() {
            memset(_bit_array, 0, BIT_ARRAY_SIZE);
        };
        ~BloomFilter() = default;

        /**
         * @brief 判断一个 key 是否存在，有可能假阳性
         *
         * @param key
         * @return true
         * @return false
         */
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

        /**
         * @brief 插入一个新的 key，会根据 key 的哈希值更新内部的 bit array。
         *
         * @param key
         * @return true
         * @return false
         */
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
