@echo off
cd "P:\Clash Of Streamers\new"
xcopy /Y "P:\COSHack\libs\arm64-v8a\libfun.so" "P:\Clash Of Streamers\new\Patched\lib\arm64-v8a\libfun.so"
start /wait cmd /c build.bat
adb install runnable.apk
cd "P:\COSHack"
@echo on