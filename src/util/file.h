#pragma once

#include "common/def.h"

namespace util {

    bool create_file(const char* file_path, u64 file_size);

    void* mmap_file(const char* file_path, int& fd);

    void mumap_and_close(int fd, void* addr, u64 size);

} // namespace util