/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Outputs {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(TokenTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Token pattern.
    template<typename T>
    using TokenPattern = TokenOutput<T, 0x01, ExpectPattern>;
  public:
    /// <summary>
    /// Test the consume method (using the fragment before).
    /// </summary>
    TEST_METHOD(MethodConsumeBefore) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StateScope<char, TokenPattern> rule;
      auto& tokens = context.getTokens();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, tokens.getLength());
      Assert::AreEqual<Id>(0x01, tokens[0].getCode());
      Assert::AreEqual(0, Identifier<char>(tokens[0].getFragment()).compare("a"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (using the fragment after).
    /// </summary>
    TEST_METHOD(MethodConsumeAfter) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      TokenPattern<char> rule;
      auto& tokens = context.getTokens();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, tokens.getLength());
      Assert::AreEqual<Id>(0x01, tokens[0].getCode());
      Assert::AreEqual(0, Identifier<char>(tokens[0].getFragment()).compare("b"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
