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
  const char file_path[] = "test_data";

  bool success = util::create_file(file_path, 1024);

  assert(success);

  int fd = 0;
  void* addr = util::mmap_file(file_path, fd);

  assert(addr != nullptr);

  string test_strs[] = { "Hello", " ", "World", "!" };

  common::RawData* ptr = (common::RawData*)addr;

  for (int i = 0; i < 4; i++) {
    ptr->store(test_strs[i].c_str(), test_strs[i].size());
    ptr = ptr->next();
  }

  cout << (u64)ptr - (u64)addr << endl;

  auto key = (common::RawData*)addr;
  auto value = key->next();
  auto key2 = value->next();
  auto value2 = key2->next();

  hash_index::DataEntry de;
  de.init(key, value);

  cout << de.match(key) << endl;
  cout << de.inderict_match(key) << endl;

  std::hash<common::RawData> hash_fn;
  cout << "hash() = " << hash_fn(*key) << endl;
  cout << "hash() = " << hash_fn(*value) << endl;
  cout << "hash() = " << hash_fn(*key2) << endl;
  cout << "hash() = " << hash_fn(*value2) << endl;

  filter::BloomFilter bf;
  cout << "filter() = " << bf(*key) << endl;


  hash_index::set_up();

  hash_index::IndexFile file(0, 0);

  file.insert(key, value);
  file.insert(key2, value2);

  assert(file.find(key) == value);
  assert(file.find(key2) == value2);



  return 0;
}