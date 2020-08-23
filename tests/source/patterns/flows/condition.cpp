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
  TEST_CLASS(ConditionTests)
  {
  private:
    // Expect pattern F.
    template<typename T>
    using ExpectPatternF = ExpectUnit<T, 'b'>;
    // Expect pattern S.
    template<typename T>
    using ExpectPatternS = ExpectUnit<T, 'a'>;
    // Expect pattern C.
    template<typename T>
    using ExpectPatternC = ExpectUnit<T, '@'>;
  public:
    /// <summary>
    /// Test the consume method (with success and failure).
    /// </summary>
    TEST_METHOD(MethodConsumeBinary) {
      AnsiString input("@abc");
      Context<char> context;
      TextSource<char> source(input, context);
      ConditionFlow<char, ExpectPatternC, ExpectPatternS, ExpectPatternF> rule;
      // Consume '@a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume 'b'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('c', source.getValue());
    }
    /// <summary>
    /// Test the consume method (with success only).
    /// </summary>
    TEST_METHOD(MethodConsumeUnary) {
      AnsiString input("@ab");
      Context<char> context;
      TextSource<char> source(input, context);
      ConditionFlow<char, ExpectPatternC, ExpectPatternS> rule;
      // Consume '@a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
