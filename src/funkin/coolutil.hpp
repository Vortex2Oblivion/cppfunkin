#pragma once

#include <string>

namespace funkin {
    class CoolUtil {
        public:
            /**
             * https://www.raylib.com/examples/text/loader.html?name=text_codepoints_loading
             */
            static int* codepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount);
            /**
             * https://gist.github.com/dgoguerra/7194777
             */
            static std::string formatBytes(size_t bytes);
    };
}  // namespace funkin
