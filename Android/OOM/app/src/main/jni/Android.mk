# Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := NetworkCode
LOCAL_SRC_FILES := AndroidInterface.cpp TokenHandler.cpp XmppConnection.cpp Person.cpp MessageBuffer.cpp Message.cpp GoogleHangoutConnection.cpp GoogleHangout.cpp ChatService.cpp ChatModel.cpp Base64.cpp Account.cpp ChatInterface.cpp
LOCAL_SHARED_LIBRARIES := boost_system_shared boost_thread_shared
LOCAL_STATIC_LIBRARIES := ssl_static crypto_static
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module,boost/1.57.0)

# PREBUILT SSL

include $(CLEAR_VARS)
LOCAL_MODULE := ssl_static
LOCAL_SRC_FILES := openssl-libs/$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto_static
LOCAL_SRC_FILES := openssl-libs/$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)