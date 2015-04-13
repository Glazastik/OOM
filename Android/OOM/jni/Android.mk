LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := Messenger
LOCAL_SRC_FILES := Messenger.cpp
LOCAL_EXPORT_LDLIBS := -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ManagedCode
LOCAL_SRC_FILES := ManagedCode.cpp
LOCAL_STATIC_LIBRARIES := Messenger
include $(BUILD_SHARED_LIBRARY)