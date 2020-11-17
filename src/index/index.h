/**
 * @file index.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 定义了 Index 数据结构以及相关的辅助函数。
 */
#pragma once

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <functional>

#include "common/def.h"
#include "common/config.h"
#include "util/hash.h"
#include "index/data_entry.h"
#include "index/index_file.h"


namespace hash_index {

    /**
     * @brief 为 IndexFile 创建文件夹
     *
     */
    void set_up();
    void tear_down();

    class Index {
    public:

        /**
         * @brief Construct a new Index object
         * 将一个 data 文件打开并且 mmap 到内存中。
         *
         * @param file_path
         */
        Index(const char* file_path);
        ~Index() = default;

        /**
         * @brief 根据打开的文件创建索引。
         *
         * @return true
         * @return false
         */
        bool build();

        /**
         * @brief 查找一个 key。
         *
         * @param key
         * @return common::RawData*
         */
        common::RawData* find(common::RawData* key);

        void* addr() {
            return file_addr;
        }

    private:

        /**
         * @brief 插入一个 kv 对。
         *
         * @param key
         * @param value
         */
        void insert(common::RawData* key, common::RawData* value);

        int _fd;
        void* file_addr;
        u64 _file_size;

        // RawData 对应的哈希函数
        std::hash<common::RawData> data_hash;

        // IndexFile 的二维数组，第一级索引为分区 p，第二级索引是序列号 s。
        std::vector<std::vector<IndexFile>> index_files;
    };
} // namespace index
