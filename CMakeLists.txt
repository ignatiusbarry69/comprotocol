cmake_minimum_required(VERSION 3.10)
project(BufferProtocol VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for each module
add_subdirectory(src/comprotocol)
add_subdirectory(src/app)


# cmake -DCMAKE_TOOLCHAIN_FILE="C:/Users/barry/AppData/Local/Android/Sdk/ndk/27.0.12077973/build/cmake/android.toolchain.cmake" \
#       -DANDROID_ABI=armeabi-v7a \
#       -DANDROID_PLATFORM=android-21 \
#       -B build/armeabi-v7a
# cmake --build build/armeabi-v7a