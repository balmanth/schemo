/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Units {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(RangeTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeText) {
      AnsiString input("amz1");
      Context<char> context;
      TextSource<char> source(input, context);
      RangeUnit<char, 'a', 'z'> rule;
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume 'm'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume 'z'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Fails.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('1', source.getValue());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeTokens) {
      TokenList<char> input({ Token<char>(0xF0), Token<char>(0xF6), Token<char>(0xFF), Token<char>(0x00) });
      Context<char> context;
      TokenSource<char> source(input, context);
      RangeUnit<char, 0xF0, 0xFF> rule;
      // Consume '0xF0'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume '0xF6'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume '0xFF'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>(0x00, source.getValue());
    }
  };
}
