#ifndef CPR_MULTIPART_H
#define CPR_MULTIPART_H

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

#include "defines.h"

namespace cpr {

struct File {
    template <typename StringType>
    explicit File(StringType&& filepath) : filepath{CPR_FWD(filepath)} {}
    std::string filepath;
};

struct Part {
    Part(const std::string& name, const std::string& value, const std::string& content_type = {})
            : name{name}, value{value}, content_type{content_type}, is_file{false} {}
    Part(const std::string& name, const std::int32_t& value, const std::string& content_type = {})
            : name{name}, value{std::to_string(value)}, content_type{content_type}, is_file{false} {
    }
    Part(const std::string& name, const File& file, const std::string& content_type = {})
            : name{name}, value{file.filepath}, content_type{content_type}, is_file{true} {}

    std::string name;
    std::string value;
    std::string content_type;
    bool is_file;
};

class Multipart {
  public:
    Multipart(const std::initializer_list<Part>& parts);

    std::vector<Part> parts;
};

} // namespace cpr

#endif
