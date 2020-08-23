/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Flows {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(StaticTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeSuccess) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StaticFlow<char, true> rule;
      // Doesn't consume but return true (the same status as given)
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(0U, source.getOffset());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeFailure) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StaticFlow<char, false> rule;
      // Doesn't consume but return false (the same status as given)
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(0U, source.getOffset());
    }
  };
}
