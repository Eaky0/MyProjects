/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   lock_closed_png;
    const int            lock_closed_pngSize = 13593;

    extern const char*   lock_open_png;
    const int            lock_open_pngSize = 12340;

    extern const char*   logo_png;
    const int            logo_pngSize = 3432;

    extern const char*   pause_png;
    const int            pause_pngSize = 11352;

    extern const char*   play_png;
    const int            play_pngSize = 1900;

    extern const char*   recording_jpg;
    const int            recording_jpgSize = 19605;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
