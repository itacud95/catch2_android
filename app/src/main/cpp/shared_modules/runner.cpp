#define CATCH_CONFIG_RUNNER
#include "catch2/catch_session.hpp"
#include <dlfcn.h>
#include <iostream>

class TestRunner {
public:
  TestRunner(std::string);
  ~TestRunner();
  bool RunTest(Catch::Session &session);
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
  using RunTestsEntry = int (*)(Catch::Session &session);
  std::string _library;
  void *_handle;
  RunTestsEntry _runTests;
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

bool TestRunner::RunTest(Catch::Session &session) {
  if (!Initialize()) {
    return false;
  }
  std::cout << "Running test for " << _library << '\n';
  return _runTests(session);
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
  if (!_runTests) {
    std::cout << "failed to load symbol\n";
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {

  const std::string path = "/home/jk/dev/catch2_android/app/src/main/cpp/build/"
                           "shared_modules/";
  auto tests = {"foo/libfoo_tests.so", "bar/libbar_tests.so"};

  static auto session = Catch::Session();

  for (const auto &test : tests) {
    std::cout << "\ntest: " << test << '\n';
    TestRunner runner(path + test);
    runner.RunTest(session);
  }

  return 0;
}
