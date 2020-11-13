#include <iostream>
#include <vector>
#include <assert.h>

#include "common/def.h"
#include "filter/filter.h"
#include "util/file.h"
#include "util/hash.h"

using namespace std;

int main() {
  const char file_path[] = "test_data";

  bool success = util::create_file(file_path, 1024);

  assert(success);

  void* addr = util::mmap_file(file_path);

  assert(addr != nullptr);

  util::Hasher hasher;

  common::RawData data;

  cout << data.size << endl;
  cout << hasher.hash((Byte*)data.data, data.size) << endl;

  return 0;
}