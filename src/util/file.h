/**
 * @file file.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 一些文件的辅助函数。
 *
 */
#pragma once

#include "common/def.h"

namespace util {

    bool create_file(const char* file_path, u64 file_size);

    void* mmap_file(const char* file_path, int& fd, u64& file_size);

    void mumap(void* addr, u64 size);

    void mumap_and_close(int fd, void* addr, u64 size);

} // namespace util