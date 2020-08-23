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
  TEST_CLASS(ExpectTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeText) {
      AnsiString input("abc1");
      Context<char> context;
      TextSource<char> source(input, context);
      ExpectUnit<char, 'a', 'b', 'c'> rule;
      // Consume 'abc'.
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
      TokenList<char> input({ Token<char>(0xF0), Token<char>(0xF1), Token<char>(0xFA), Token<char>(0x00) });
      Context<char> context;
      TokenSource<char> source(input, context);
      ExpectUnit<char, 0xF0, 0xF1, 0xFA> rule;
      // Consume '0xF0F1FA'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>(0x00, source.getValue());
    }
  };
}
