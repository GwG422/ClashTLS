LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.c log.c proxy.c syms.c net.c init_hook.c heaps.c

LOCAL_MODULE := libfun
LOCAL_CFLAGS += -std=c11 -Wl,--hash-style=both


include $(BUILD_SHARED_LIBRARY)