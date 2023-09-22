#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <type_traits>
#include <vector>

#include "math/basic_arithmetic.h"
// normal lib
#include "normal/str/string_utility.h"

// zlib
#include "spdlog/spdlog.h"
#include "zlib.h"

// nlohmann_json
#include <ranges>

#include "nlohmann/json.hpp"

int main(int argc, char** argv) {
  using nlohmann::json;

  json value;
  value["love"] = "you";
  value["haha"] = "f";
  value["the_number"] = 42;
  value["C++"] = "is bad";

  auto json_str = value.dump();

  printf("json str = %s\n", json_str.c_str());
  spdlog::error("this {}", json_str);

  printf("add(3, 5) == %d\n", add(3, 5));

  auto str = string_utility_test();
  printf("%s\n", str.c_str());

  char buffer_in[256] = {
      "Conan is a MIT-licensed, Open Source package manager "
      "for C and C++ development "
      "for C and C++ development, allowing development "
      "teams to easily and efficiently "
      "manage their packages and dependencies across "
      "platforms and build systems."};
  char buffer_out[256] = {0};

  z_stream defstream;
  defstream.zalloc = Z_NULL;
  defstream.zfree = Z_NULL;
  defstream.opaque = Z_NULL;
  defstream.avail_in = (uInt)strlen(buffer_in);
  defstream.next_in = (Bytef*)buffer_in;
  defstream.avail_out = (uInt)sizeof(buffer_out);
  defstream.next_out = (Bytef*)buffer_out;

  deflateInit(&defstream, Z_BEST_COMPRESSION);
  deflate(&defstream, Z_FINISH);
  deflateEnd(&defstream);

  printf("Uncompressed size is: %lu\n", strlen(buffer_in));
  printf("Compressed size is: %lu\n", strlen(buffer_out));

  return EXIT_SUCCESS;
}
