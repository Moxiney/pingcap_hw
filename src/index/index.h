#pragma once

#include <map>
#include <string>
#include <string.h>
#include <algorithm>
#include <assert.h>

#include "common/def.h"


namespace hash_index {

    enum MatchResult {
        MATCHED = 0,
        PARTCIALMACHED,
        UNMATCHED
    };

    struct DataEntry {
        i32 _key_size;
        Byte _prefix[4];
        common::RawData* _kv_pos;

        void init(common::RawData* key, common::RawData* value) {
            assert(key->next() == value);
            _key_size = key->_size;
            memcpy(_prefix, key->_data, std::min(_key_size, 4));
            _kv_pos = key;
        }

        MatchResult match(common::RawData* key) {
            if (memcmp(this, key, sizeof(i32) + std::min(key->_size, 4)) == 0) {
                return (key->_size <= 4) ? MatchResult::MATCHED : MatchResult::PARTCIALMACHED;
            }
            else {
                return MatchResult::UNMATCHED;
            }
        }

        MatchResult inderict_match(common::RawData* key) {
            return (*key == *_kv_pos) ? MatchResult::MATCHED : MatchResult::UNMATCHED;
        }

        common::RawData* get_value() {
            return _kv_pos->next();
        }
    };

    template <class Hasher, class Filter>
    class Index {
    public:
        Index() = default;
        ~Index() = default;

        bool build(const char* file_path);

        MatchResult find(common::RawData& key, common::RawData* value);

    private:
        Hasher hasher;

        std::map<std::string, Filter> index_file_filters;

        std::map<std::string, void*> index_file_addrs;

        void* file_addr;
    };
} // namespace index
