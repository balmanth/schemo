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
  TEST_CLASS(ChooseTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeText) {
      AnsiString input("aceg");
      Context<char> context;
      TextSource<char> source(input, context);
      ChooseUnit<char, 'a', 'c', 'e'> rule;
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume 'c'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume 'e'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Fails.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('g', source.getValue());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeTokens) {
      TokenList<char> input({ Token<char>(0xD0), Token<char>(0xE6), Token<char>(0xFF), Token<char>(0x00) });
      Context<char> context;
      TokenSource<char> source(input, context);
      ChooseUnit<char, 0xD0, 0xE6, 0xFF> rule;
      // Consume '0xD0'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume '0xE6'.
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
