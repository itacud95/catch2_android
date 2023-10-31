// #define CATCH_CONFIG_RUNNER
#include "catch2/catch_session.hpp"
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <dlfcn.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

class TestRunner {
public:
  TestRunner(const TestRunner &) = delete;
  TestRunner(TestRunner &&) = delete;
  TestRunner &operator=(const TestRunner &) = delete;
  TestRunner &operator=(TestRunner &&) = delete;

  TestRunner(std::string);
  ~TestRunner();
  bool IsLoaded() const;

private:
  void *_handle;
};

TestRunner::TestRunner(std::string library)
    : _handle(dlopen(library.c_str(), RTLD_NOW)) {
}

TestRunner::~TestRunner() {
  if (!_handle) {
    return;
  }
  dlclose(_handle);
}

bool TestRunner::IsLoaded() const { return _handle != nullptr; }

class testRunListener : public Catch::EventListenerBase {
public:
  using Catch::EventListenerBase::EventListenerBase;

  void testCaseEnded(Catch::TestCaseStats const &testCaseStats) final {
    if (testCaseStats.totals.assertions.failed > 0) {
      // store failed test
      auto str = testCaseStats.stdOut;
      auto foo = testCaseStats.testInfo;
    }
  }

  void testRunEnded(Catch::TestRunStats const &) final {
    // print summary
  }
};

CATCH_REGISTER_LISTENER(testRunListener)

int main(int argc, char *argv[]) {

  const std::string path = "/home/jk/dev/catch2_android/app/src/main/cpp/build/"
                           "shared_modules/";
  auto tests = {
      "foo/libfoo_tests.so", //
      "bar/libbar_tests.so"  //
  };

  static auto session = Catch::Session();
  auto &config = session.configData();
  config.filenamesAsTags = true;

  std::list<TestRunner> testLibs;
  for (const auto &test : tests) {
    testLibs.emplace_back(path + test);
    if (!testLibs.back().IsLoaded()){
      std::cout << "Failed to load test\n";
    }
  }
  return session.run(argc, argv);
}
