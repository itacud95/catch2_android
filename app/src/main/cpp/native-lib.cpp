#if ANDROID
#include <android/log.h>
#include <jni.h>
#endif
#include <string>


#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"

#if ANDROID
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    int result = Catch::Session().run( );
    __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "result: %d", result);
    if (result != 0){
        return env->NewStringUTF("test failure");
    }
    return env->NewStringUTF("test success");
}
#endif

TEST_CASE("Simple Test") {
    // __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "%s", "Running test!");
    REQUIRE(1 + 1 == 2);
}
/**
 * Each module becomes a library with a entry point function.
 *  - Add ability to add filter through the function (which test to run).
 * */
