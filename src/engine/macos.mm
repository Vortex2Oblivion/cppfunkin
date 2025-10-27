#include "macos.hpp"

#include <cstddef>
#include <raylib.h>
#include <Cocoa/Cocoa.h>

namespace MacOSUtil {
    void fixWindowColorSpace(void) {
        NSWindow* nativeWindow = (NSWindow*)GetWindowHandle();
        if (nativeWindow == NULL) {
            return;
        }

        [nativeWindow setColorSpace: [NSColorSpace sRGBColorSpace]];
    }
}