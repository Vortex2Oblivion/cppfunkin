#include "coolutil.hpp"

#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <raylib-cpp.hpp>

int *funkin::CoolUtil::codepointRemoveDuplicates(const int *codepoints, const int codepointCount, int *codepointsResultCount)
{
    int codepointsNoDupsCount = codepointCount;
    const auto codepointsNoDups = static_cast<int *>(calloc(codepointCount, sizeof(int)));
    memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++)
    {
        for (int j = i + 1; j < codepointsNoDupsCount; j++)
        {
            if (codepointsNoDups[i] == codepointsNoDups[j])
            {
                for (int k = j; k < codepointsNoDupsCount; k++)
                    codepointsNoDups[k] = codepointsNoDups[k + 1];

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

std::string funkin::CoolUtil::formatBytes(size_t bytes)
{
	std::string suffix[] = {"B", "KB", "MB", "GB", "TB"};
	char length = sizeof(suffix) / sizeof(suffix[0]);

	int i = 0;
	double dblBytes = static_cast<double>(bytes);

	if (bytes > 1024) {
		for (i = 0; (bytes / 1024) > 0 && i<length-1; i++, bytes /= 1024)
			dblBytes = bytes / 1024.0;
	}

    static char output[200];
	return TextFormat("%.02lf %s", dblBytes, suffix[i]);
}