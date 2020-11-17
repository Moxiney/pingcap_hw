/**
 * @file config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 * 全局的一些设置
 */
#pragma once

#include "def.h"

struct Config {
    // 分区数量
    static const u64 num_partitions = 16;
    // Index 文件的大小
    static const u64 index_file_size = 16 * 1024;
};