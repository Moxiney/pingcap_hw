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


/**
 * @brief Todo: 完成 find 函数
 *
 */

namespace hash_index {

    void set_up();
    void tear_down();

    class Index {
    public:
        Index(const char* file_path);
        ~Index() = default;

        bool build();

        common::RawData* find(common::RawData* key);

        void* addr() {
            return file_addr;
        }

    private:

        void insert(common::RawData* key, common::RawData* value);

        int _fd;
        void* file_addr;
        u64 _file_size;

        std::hash<common::RawData> data_hash;

        std::vector<std::vector<IndexFile>> index_files;
    };
} // namespace index
