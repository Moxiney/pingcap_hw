#pragma once

#include "def.h"

struct Config {
    static const u64 num_partitions = 16;
    static const u64 index_file_size = 256 * 1024 * 1024;
};