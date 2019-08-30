# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set (CMAKE_BUILD_TYPE DEBUG)

include_directories(${ANDROID_NDK}/sources/android/cpufeatures)
add_library(cpufeatures STATIC
        ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
        # make a list of neon files and add neon compiling flags to them
        set(native-lib-srcs
             src/main/cpp/FirstNeonTest.cpp
             src/main/cpp/native-lib.cpp)

        set_property(SOURCE ${native-lib-srcs}
                APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon")
        add_definitions("-DHAVE_NEON=1")
        add_definitions("-DANDROID_ARM_NEON=on")
elseif (${ANDROID_ABI} STREQUAL "x86")
        set(native-lib-srcs
             src/main/cpp/native-lib.cpp)

        set_property(SOURCE ${native-lib-srcs} APPEND_STRING PROPERTY COMPILE_FLAGS
                " -mssse3  -Wno-unknown-attributes \
                   -Wno-deprecated-declarations \
                   -Wno-constant-conversion \
                   -Wno-static-in-inline")
        add_definitions(-DHAVE_NEON_X86=1 )#-DHAVE_NEON=1)
        #add_definitions("-DLOCAL_ARM_NEON=1")
else ()
        set(native-lib-srcs
             src/main/cpp/FirstNeonTest.cpp
             src/main/cpp/native-lib.cpp)
endif ()

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${native-lib-srcs})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       cpufeatures
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )