/**
 * @file index_file.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 定义了 index file 数据结构
 */
#pragma once

#include <iostream>


#include "common/def.h"
#include "common/config.h"
#include "util/file.h"
#include "index/data_entry.h"
#include "filter/filter.h"

const char data_path[] = "data";

namespace hash_index {
    /**
     * @brief IndexFile 对应着一个定长的文件，其内容都是 DataEntry。
     * 需要负责管理该文件。
     *
     */
    class IndexFile {
    public:

        /**
         * @brief Construct a new Index File object
         * 新建一个 IndexFile，同时需要创建一个对应的文件用于存放 DataEntry，文件大小由 Config 决定。
         *
         * @param partition
         * @param seq
         */
        IndexFile(u32 partition, u32 seq) : _partition(partition), _seq(seq), _cur(0) {
            // Create file.
            char file_path[64];

            sprintf(file_path, "%s/p_%u/s_%u", data_path, _partition, _seq);
            assert(util::create_file(file_path, Config::index_file_size));

            std::cout << "create index file " << file_path << std::endl;

            // Mmap file.
            u64 size;
            _entries = (DataEntry*)util::mmap_file(file_path, _fd, size);
            assert(_entries != nullptr);

            _max = Config::index_file_size / sizeof(DataEntry);
        }

        ~IndexFile() {
            util::mumap_and_close(_fd, _entries, Config::index_file_size);
        };

        /**
         * @brief 在 IndexFile 的 _entries 中加入一个新的 kv 对所对应的 DataEntry。
         *
         * @param key
         * @param value
         * @return true
         * @return false
         */
        bool insert(common::RawData* key, common::RawData* value) {
            if (full()) {
                return false;
            }

            _filter.insert(key);

            _entries[_cur++].init(key, value);
            return true;
        }

        bool full() {
            return _cur >= _max;
        }

        /**
         * @brief 查询该 IndexFile 中是否存在 key 对应的 kv 对。
         * 先通过 filter 判断一次，如果 filter 认为是不存在，则直接结束查询。
         * 如果认为存在，则遍历查询。
         * 遍历查询时先通过 match 来原地查询，如果是部分匹配成功才 indirect_match。
         *
         * @param key
         * @return common::RawData*
         */
        common::RawData* find(common::RawData* key) {
            // filter
            if (!_filter(*key)) {
                return nullptr;
            }
            for (u32 i = 0; i < _cur; i++) {
                auto res = _entries[i].match(key);

                if (res == MatchResult::MATCHED || (res == MatchResult::PARTICALMATCHED && _entries[i].indirect_match(key) == MatchResult::MATCHED)) {
                    return _entries[i].get_value();
                }
            }
            return nullptr;
        }
    private:
        u32 _partition;
        u32 _seq;

        int _fd;
        DataEntry* _entries;

        u32 _max;
        u32 _cur;

        filter::BloomFilter _filter;
    };
} // namespace hash_index
