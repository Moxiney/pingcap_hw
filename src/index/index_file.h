#pragma once

#include <iostream>


#include "common/def.h"
#include "common/config.h"
#include "util/file.h"
#include "index/data_entry.h"
#include "filter/filter.h"

const char data_path[] = "data";

namespace hash_index {
    class IndexFile {
    public:
        IndexFile(u32 partition, u32 seq) : _partition(partition), _seq(seq), _cur(0) {
            // Create file.
            char file_path[64];

            sprintf(file_path, "%s/p_%u/s_%u", data_path, _partition, _seq);
            assert(util::create_file(file_path, Config::index_file_size));

            std::cout << "create index file " << file_path << std::endl;

            // Mmap file.
            _entries = (DataEntry*)util::mmap_file(file_path, _fd);
            assert(_entries != nullptr);

            _max = Config::index_file_size / sizeof(DataEntry);
        }

        ~IndexFile() {
            util::mumap_and_close(_fd, _entries, Config::index_file_size);
        };

        bool insert(common::RawData* key, common::RawData* value) {
            if (_cur >= _max) {
                return false;
            }
            _entries[_cur++].init(key, value);
            return true;
        }

        common::RawData* find(common::RawData* key) {
            // filter
            if (!_filter(*key)) {
                return nullptr;
            }
            for (u32 i = 0; i < _cur; i++) {
                if (_entries[i].match(key) != MatchResult::UNMATCHED && _entries[i].inderict_match(key) == MatchResult::MATCHED) {
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

        filter::Filter _filter;
    };
} // namespace hash_index
