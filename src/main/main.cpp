#include <iostream>
#include <vector>
#include <assert.h>


#include "common/def.h"
#include "filter/filter.h"
#include "util/file.h"

using namespace std;

int main() {
  const char file_path[] = "test_data";

  bool success = util::create_file(file_path, 1024);

  assert(success);

  void* addr = util::mmap_file(file_path);

  assert(addr != nullptr);

  return 0;

}