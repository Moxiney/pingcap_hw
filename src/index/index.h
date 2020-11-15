#pragma once

#include <vector>
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

    void set_up() {
        std::string folder_path = "data";

        std::string command = "mkdir -p " + folder_path;
        system(command.c_str());

        for (int i = 0; i < Config::num_partitions; i++) {
            std::string s = command + "/" + "p_" + std::to_string(i);
            system(s.c_str());
        }
    }

    void tear_down() {
        system("rm -rf data/");
    }

    class Index {
    public:
        Index(const char file_path) {
            // create and map file.


            index_files.resize(Config::num_partitions);
        };
        ~Index() = default;

        bool build(const char* file_path) {
            bool result = true;

            // open file
            void* addr = util::mmap_file(file_path, _fd);

            // for all kv pair, build index.


            return result;
        }

        common::RawData* find(common::RawData& key, common::RawData* value);

    private:
        int _fd;
        void* file_addr;

        std::vector<std::vector<IndexFile>> index_files;
    };
} // namespace index
