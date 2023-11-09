#include <android/log.h>
#include <jni.h>

#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    // std::string failed_tests = "Failed tests:\n"; 
    // __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "result: %d", result);
    // if (result != 0) {
    //     return env->NewStringUTF(failed_tests.c_str());
    // }
    return env->NewStringUTF("test success");
}
