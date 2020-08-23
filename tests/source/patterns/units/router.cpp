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
  TEST_CLASS(RouterTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeText) {
      AnsiString input("abcdefg");
      Context<char> context;
      TextSource<char> source(input, context);
      Router<char,
        BasicUnitRoute<'a', 'b', 'c'>,
        BasicUnitRoute<'d', 'e', 'f'>> rule;
      // Consume 'abc'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Consume 'def'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(6U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(6U, source.getOffset());
      Assert::AreEqual<Id>('g', source.getValue());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeTokens) {
      TokenList<char> input({ Token<char>(0xE0), Token<char>(0xE1), Token<char>(0xF0), Token<char>(0xF1) });
      Context<char> context;
      TokenSource<char> source(input, context);
      Router<char,
        BasicUnitRoute<0xE0, 0xE1>,
        BasicUnitRoute<0xF0, 0xF1>> rule;
      // Consume '0xE0E1'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume '0xF0F1'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(4U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::IsFalse(source.hasValue());
      Assert::AreEqual(4U, source.getOffset());
    }
  };
}
