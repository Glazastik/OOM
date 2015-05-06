#include <jni.h>

#include <string.h>
#include <stdlib.h>

#include <string>
#include <exception>
#include <sstream>

#include <android/log.h>

#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "TEST-BOOST", fmt, ##__VA_ARGS__)

#include "gps.hpp"
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/thread.hpp"
#include "boost/lexical_cast.hpp"
//#include "boost\log\trivial.hpp"
#include "boost/bind.hpp"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/array.hpp>

std::string gps(std::string const &root)
{
    const gps_position g(35, 59, 24.567f);
    save(root, g);

    gps_position newg;
    load(root, newg);

    std::ostringstream ostr;

    if (g != newg)
        return std::string();

    ostr << "GPS coordinates: " << newg;
    return ostr.str();
}

extern "C"
jstring
Java_com_alexander_test_MainActivity_getGPSCoordinates( JNIEnv* env,
                                                                    jobject thiz,
                                                                    jstring rootPath )
{
    const char *s = env->GetStringUTFChars(rootPath, 0);
    std::string root(s);
    env->ReleaseStringUTFChars(rootPath, s);
    LOG("root: %s", root.c_str());

    try {
        std::string ret = gps(root);
        return env->NewStringUTF(ret.c_str());
    }
    catch (std::exception &e) {
        LOG("ERROR: %s", e.what());
        abort();
    }
    catch (...) {
        LOG("Unknown error");
        abort();
    }
}