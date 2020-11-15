#pragma once

#include <map>
#include <string>
#include <string.h>
#include <algorithm>
#include <assert.h>

#include "common/def.h"
#include "common/config.h"
#include "util/hash.h"
#include "index/data_entry.h"
#include "index/index_file.h"

namespace hash_index {

    class Index {
    public:
        Index() = default;
        ~Index() = default;

        bool build(const char* file_path) {
            bool result = true;

            // open file
            void* addr = util::mmap_file(file_path);

            // for all kv pair, build index.


            return result;
        }

        MatchResult find(common::RawData& key, common::RawData* value);

    private:

        void* file_addr;
    };
} // namespace index
