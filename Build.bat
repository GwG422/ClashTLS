@echo off
set PATH=%PATH%;D:\Android\build-tools\29.0.0\;D:\Android\platform-tools\;D:\Android\ndk\20.0.5594570
set NDK_PROJECT_PATH=P:\COSHack
ndk-build.cmd -C .
@echo on
