cmake -B build -S . `
-DCMAKE_TOOLCHAIN_FILE="C:/Users/barry/AppData/Local/Android/Sdk/ndk/27.0.12077973/build/cmake/android.toolchain.cmake" `
-DANDROID_ABI=armeabi-v7a `
-DANDROID_PLATFORM=android-21 `
-DCMAKE_BUILD_TYPE=Release


cmake --build build