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
  TEST_CLASS(EndTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("a");
      Context<char> context;
      TextSource<char> source(input, context);
      EndFlow<char> rule;
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(0U, source.getOffset());
      // Move to the end.
      source.nextState();
      // Check success.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
    }
  };
}
