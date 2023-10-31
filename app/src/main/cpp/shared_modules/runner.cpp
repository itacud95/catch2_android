// #define CATCH_CONFIG_RUNNER
#include "catch2/catch_session.hpp"
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <dlfcn.h>
#include <iostream>

class TestRunner {
public:
  TestRunner(std::string);
  ~TestRunner();
  bool RunTest(int argc, char *argv[], Catch::Session &session);
  bool RunTestv2();
  void Close() {
    if (!_handle) {
      std::cout << "Failed to close handle\n";
      return;
    }
    std::cout << "Closing handle\n";
    dlclose(_handle);
  }

private:
  bool Initialize();
  using RunTestsEntry = int (*)(int argc, char *argv[],
                                Catch::Session &session);
  using RunTestsEntryv2 = int (*)();
  std::string _library;
  void *_handle;
  RunTestsEntry _runTests;
  RunTestsEntryv2 _runTestsv2;
};

TestRunner::TestRunner(std::string library)
    : _library(library), _handle(nullptr) {
  Initialize();
}

TestRunner::~TestRunner() {
  if (!_handle) {
    return;
  }
  dlclose(_handle);
}

bool TestRunner::RunTest(int argc, char *argv[], Catch::Session &session) {
  if (!Initialize()) {
    return false;
  }
  return _runTests(argc, argv, session);
}

bool TestRunner::RunTestv2() {
  if (!Initialize()) {
    return false;
  }
  return _runTestsv2();
}

bool TestRunner::Initialize() {
  if (_handle) {
    return true;
  }

  _handle = dlopen(_library.c_str(), RTLD_NOW);
  if (!_handle) {
    std::cout << "failed to load library\n";
    return false;
  }

  dlerror();

  _runTests = (RunTestsEntry)dlsym(_handle, "RunTests");
  _runTestsv2 = (RunTestsEntryv2)dlsym(_handle, "RunTests");
  if (!_runTestsv2) {
    std::cout << "failed to load symbol\n";
    return false;
  }
  return true;
}

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
  auto& config = session.configData();
  config.filenamesAsTags = true;
  return session.run(argc, argv);

  for (const auto &test : tests) {
    TestRunner runner(path + test);
    // runner.RunTestv2();
    runner.RunTest(argc, argv, session);
  }

  return 0;
}
