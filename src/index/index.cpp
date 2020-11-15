#include "index.h"

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

    Index::Index(const char* file_path) {
        // create and map file.
        file_addr = util::mmap_file(file_path, _fd, _file_size);
        index_files.resize(Config::num_partitions);

        std::cout << " file size " << _file_size << std::endl;
    };

    bool Index::build() {
        bool result = true;

        // for all kv pair, build index.
        for (auto ptr = (common::RawData*)file_addr; (u64)ptr - (u64)file_addr < _file_size; ptr = ptr->next()) {
            auto key = ptr; ptr = ptr->next();
            auto value = ptr;

            // insert kv pair
            insert(key, value);
        }

        return result;
    }

    void Index::insert(common::RawData* key, common::RawData* value) {
        // find partition
        auto p = data_hash(*key) % Config::num_partitions;
        i32 s = index_files[p].size() - 1;
        // find index_file
        if (s < 0 || index_files[p][s].full()) {
            s++;
            index_files[p].emplace_back(p, s);
        }
        index_files[p][s].insert(key, value);
    }

    common::RawData* Index::find(common::RawData* key) {
        auto p = data_hash(*key) % Config::num_partitions;
        common::RawData* value = nullptr;

        for (auto& idx_file : index_files[p]) {
            value = idx_file.find(key);
            if (value) {
                return value;
            }
        }
        return value;
    }


} // namespace hash_index
