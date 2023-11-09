#include <android/log.h>
#include <jni.h>

#include <string>
#include <dlfcn.h>

#define log(...) __android_log_print(ANDROID_LOG_INFO, "TRACKERS", __VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "stringFromJNI: %d", 0);

    void* handle = dlopen("libtest_runner.so", RTLD_NOW);
    if (handle == nullptr) {
        auto error_msg = "failed to open lib";
        log("%s\n", error_msg);
        return env->NewStringUTF(error_msg);
    }

    typedef bool (*RunTests)(int argc, char** argv);
    RunTests runTests = nullptr;
    runTests = reinterpret_cast<RunTests>(dlsym(handle, "RunTests"));
    if (runTests == nullptr) {
        auto error_msg = "failed to load runtests";
        log("%s\n", error_msg);
        return env->NewStringUTF(error_msg);
    }

    __android_log_write( ANDROID_LOG_DEBUG, "Catch", "stringFromJNI()" );

    runTests(0, nullptr);

    return env->NewStringUTF("test success");
}
