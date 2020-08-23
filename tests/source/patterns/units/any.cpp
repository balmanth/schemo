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
  TEST_CLASS(AnyTests)
  {
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeText) {
      AnsiString input("a1@");
      Context<char> context;
      TextSource<char> source(input, context);
      AnyUnit<char> rule;
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume '1'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume '@'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsFalse(source.hasValue());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeTokens) {
      TokenList<char> input({ Token<char>(0xFF), Token<char>(0x6A), Token<char>(0x00) });
      Context<char> context;
      TokenSource<char> source(input, context);
      AnyUnit<char> rule;
      // Consume '0xFF'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Consume '0x6A'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Consume '0x00'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsFalse(source.hasValue());
    }
  };
}
