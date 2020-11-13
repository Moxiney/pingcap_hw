#pragma once

#include "common/def.h"

namespace util {

    bool create_file(const char* file_path, u64 file_size);

    void* mmap_file(const char* file_path);

} // namespace util