#pragma once

#include <map>
#include <string>

namespace index {
    template <class Hasher, class Filter>
    class Index {
    public:
        Index() = default;
        ~Index() = default;

        bool build(const char* file_path);

        bool find(RawData& key, RawData* value);

    private:
        Hasher hasher;

        std::map<std::string, Filter> index_file_filters;

        std::map<std::string, void*> index_file_addrs;

        void* file_addr;
    };
} // namespace index
