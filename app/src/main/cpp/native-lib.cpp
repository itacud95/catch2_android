#include <vector>
#if ANDROID
#include <android/log.h>
#include <jni.h>
#endif
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <string>

#include "catch2/catch_all.hpp"

std::string failed_tests = "Failed tests:\n";
#if ANDROID
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    auto session = Catch::Session();
    auto &config = session.configData();
    config.filenamesAsTags = true;
    int result = session.run();
    __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "result: %d", result);
    if (result != 0) {
        return env->NewStringUTF(failed_tests.c_str());
    }
    return env->NewStringUTF("test success");
}
#else
#define ANDROID_LOG_INFO 0
#define __android_log_print(...)
#endif

class testRunListener : public Catch::EventListenerBase {
   public:
    using Catch::EventListenerBase::EventListenerBase;

    void testCaseEnded(Catch::TestCaseStats const &testCaseStats) final {
        if (testCaseStats.totals.assertions.failed > 0) {
            failed_tests += " - ";
            failed_tests += testCaseStats.testInfo->name;
            failed_tests += '\n';
            __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "failed test: %s",
                                testCaseStats.testInfo->name.c_str());
        }
    }

    void testRunEnded(Catch::TestRunStats const &testRunStats) final {
        __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "test run ended: %d",
                            testRunStats.totals.assertions.failed);
        if (testRunStats.totals.assertions.failed > 0) {
        }
    }
};
CATCH_REGISTER_LISTENER(testRunListener)

#include <dlfcn.h>

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_test_case_registry_impl.hpp"

class TestRunner {
   public:
    TestRunner(const TestRunner &) = delete;
    TestRunner(TestRunner &&) = delete;
    TestRunner &operator=(const TestRunner &) = delete;
    TestRunner &operator=(TestRunner &&) = delete;

    TestRunner(std::string library) : _handle(dlopen(library.c_str(), RTLD_NOW)) {}
    ~TestRunner() {
        if (!_handle) {
            return;
        }
        // dlclose(_handle);
    }
    
    bool IsLoaded() const { return _handle != nullptr; }

   private:
    void *_handle;
};

extern "C" bool RunTests() {
    auto session = Catch::Session();
    auto &config = session.configData();
    config.filenamesAsTags = true;

    std::list<TestRunner> testLibs;
    const std::string kPath =
        "/home/jk/dev/catch2_android/app/src/main/cpp/build/"
        "shared_modules/";
    auto tests = {
        "foo/libfoo_tests.so",  //
        "bar/libbar_tests.so"   //
    };

    for (const auto &test : tests) {
        testLibs.emplace_back(kPath + test);
        if (!testLibs.back().IsLoaded()) {
            std::cout << "Failed to load test: " << kPath + test << '\n';
            return false;
        }
    }

    int result = session.run();
    std::cout << "result: " << result << '\n';

    return true;
}
