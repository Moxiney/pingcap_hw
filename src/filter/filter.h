#include "common/def.h"

namespace filter {
    class Filter {
    public:
        Filter() = default;
        virtual ~Filter() = default;

        virtual bool is_contain(common::RawData& key)     {
            return true;
        }
    };

    class BloomFilter : public Filter {
        BloomFilter() = default;
        ~BloomFilter() = default;

        bool is_contain(common::RawData& key)     {
            return true;
        }
    };
} // namespace filter
