#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "action bronson says hi";
    return env->NewStringUTF(hello.c_str());
}

#include <catch2/catch_all.hpp>

TEST_CASE("Simple Test") {
    REQUIRE(1 + 1 == 7);
}


