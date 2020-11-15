#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>
#include <string>
#include <functional>


#include "common/def.h"
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

  void* addr = util::mmap_file(file_path);

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

  hash_index::DataEntry de;
  de.init(key, value);

  cout << de.match(key) << endl;
  cout << de.inderict_match(key) << endl;

  auto key2 = value->next();

  std::hash<common::RawData> hash_fn;
  cout << "hash() = " << hash_fn(*key) << endl;
  cout << "hash() = " << hash_fn(*value) << endl;
  cout << "hash() = " << hash_fn(*key2) << endl;
  cout << "hash() = " << hash_fn(*(key2->next())) << endl;

  filter::BloomFilter bf;
  cout << "filter() = " << bf(*key) << endl;


  hash_index::IndexFile index_file(0, 0);

  return 0;
}