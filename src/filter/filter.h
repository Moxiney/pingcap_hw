#include "common/def.h"

namespace filter {
    class Filter {
    public:
        Filter() = default;
        ~Filter() = default;

        bool is_contain(common::RawData& elem) {
            return true;
        }
    };
} // namespace filter
