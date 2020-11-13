#pragma once

using Byte = char;
using i32 = int;
using i64 = long;

namespace common
{

  struct Elem
  {
    i32 size;
    Byte data[];
  };
} // namespace common
