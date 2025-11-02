#include "coolutil.hpp"

#include <cstdlib>
#include <cstring>

int* funkin::CoolUtil::codepointRemoveDuplicates(const int* codepoints, const int codepointCount, int* codepointsResultCount) {
    int codepointsNoDupsCount = codepointCount;
    const auto codepointsNoDups = static_cast<int *>(calloc(codepointCount, sizeof(int)));
    memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++) {
        for (int j = i + 1; j < codepointsNoDupsCount; j++) {
            if (codepointsNoDups[i] == codepointsNoDups[j]) {
                for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    *codepointsResultCount = codepointsNoDupsCount;
    return codepointsNoDups;
}