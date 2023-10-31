#include <vector>
#if ANDROID
#include <android/log.h>
#include <jni.h>
#endif
#include <string>

#include "catch2/catch_all.hpp"
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

std::string failed_tests = "Failed tests:\n";
#if ANDROID
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1tests_MainActivity_stringFromJNI(JNIEnv *env,
                                                        jobject /* this */) {
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
    __android_log_print(ANDROID_LOG_INFO, "TRACKERS", "test run ended");
    if (testRunStats.totals.assertions.failed > 0) {
    }
  }
};
CATCH_REGISTER_LISTENER(testRunListener)
