#pragma once

namespace funkin
{
    class CoolUtil
    {
    public:
        /**
         * https://www.raylib.com/examples/text/loader.html?name=text_codepoints_loading
         */
        static int *codepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount);
    };

} // namespace funkin
