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

            /**
             * https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
             */
            static constexpr unsigned int str2int(const std::string &str, const int h = 0) {
                return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
            }
    };
}  // namespace funkin
