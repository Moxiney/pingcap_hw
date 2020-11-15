#pragma once

#include <string>

#include "common/def.h"
#include "util/file.h"
#include "index/data_entry.h"
#include "filter/filter.h"

namespace hash_index {
    class IndexFile {
    public:
        IndexFile(u32 partition, u32 seq) : _partition(partition), _seq(seq) {
            // Create file.
            std::string file_path = "";

            // Mmap file.

        }
        ~IndexFile() = default;
    private:
        u32 _partition;
        u32 _seq;

        void* _addr;
        filter::Filter _filter;
    };
} // namespace hash_index
