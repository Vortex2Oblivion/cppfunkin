#pragma once

#include <string>

namespace funkin {
class CoolUtil {
   public:
    /**
     * https://www.raylib.com/examples/text/loader.html?name=text_codepoints_loading
     */
    static int* codepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount);
    static std::string formatBytes(size_t bytes);
};

}  // namespace funkin
