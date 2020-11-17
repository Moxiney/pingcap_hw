/**
 * @file data_entry.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 定义了 DataEntry 数据结构
 *
 */
#pragma once

#include "common/def.h"

namespace hash_index {
    enum MatchResult {
        MATCHED = 0,
        PARTICALMATCHED,
        UNMATCHED
    };

    /**
     * @brief DataEntry 是一个定长的数据结构，用于存储 kv 对的位置，并且可以 in-place 比对。
     *
     */
    struct DataEntry {
        // kv 对的 key 的 size。
        i32 _key_size;
        // key 的前四位
        Byte _prefix[4];
        // kv 对的地址。
        common::RawData* _kv_pos;

        /**
         * @brief 根据一个 kv 对进行初始化
         *
         * @param key
         * @param value
         */
        void init(common::RawData* key, common::RawData* value) {
            assert(key->next() == value);
            _key_size = key->_size;
            memcpy(_prefix, key->_data, std::min(_key_size, 4));
            _kv_pos = key;
        }

        /**
         * @brief 判断输入的 key 值是否和存储的 key 值相等。
         * 如果 key size 小于等于 4。则可以立刻比对出结果。
         * 如果 key size 等于 4，即使 key size 和 prefix 都一致，也只是部分比对成功。
         * 该函数不间址，只利用 DataEntry 本身记录的信息比对。
         *
         * @param key
         * @return MatchResult
         */
        MatchResult match(common::RawData* key) {
            if (memcmp(this, key, sizeof(i32) + std::min(key->_size, 4)) == 0) {
                return (key->_size <= 4) ? MatchResult::MATCHED : MatchResult::PARTICALMATCHED;
            }
            else {
                return MatchResult::UNMATCHED;
            }
        }

        /**
         * @brief 当 match 结果是 partical matched，则需要间址比对。此函数起到此作用。
         *
         * @param key
         * @return MatchResult
         */
        MatchResult indirect_match(common::RawData* key) {
            return (*key == *_kv_pos) ? MatchResult::MATCHED : MatchResult::UNMATCHED;
        }

        common::RawData* get_value() {
            return _kv_pos->next();
        }
    };
} // namespace hash_index
