#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>
#include <string>
#include <functional>


#include "common/def.h"
#include "common/config.h"
#include "filter/filter.h"
#include "util/file.h"
#include "util/hash.h"
#include "index/index.h"
#include "filter/filter.h"
#include "index/index_file.h"

using namespace std;


int main() {
  // 1. 创建测试文件
  const char file_path[] = "test_data";
  hash_index::set_up();

  bool success = util::create_file(file_path, 1024);

  assert(success);

  int fd = 0;
  u64 file_size;
  void* addr = util::mmap_file(file_path, fd, file_size);
  assert(addr != nullptr);


  // 2. 插入测试数据
  vector<string> test_strs = { "Hello", " ", "World", "!" , "test1", "happy", "tree", "friend" };

  common::RawData* ptr = (common::RawData*)addr;

  for (int i = 0; i < test_strs.size(); i++) {
    ptr->store(test_strs[i].c_str(), test_strs[i].size());
    ptr = ptr->next();
  }
  util::mumap_and_close(fd, addr, file_size);

  // 3. 建立索引
  hash_index::Index idx(file_path);
  idx.build();

  auto key = (common::RawData*)idx.addr();
  auto value = key->next();
  auto key2 = value->next();
  auto value2 = key2->next();

  assert(idx.find(key) == value);
  assert(idx.find(key2) == value2);


  util::mumap_and_close(fd, addr, file_size);

  return 0;
}