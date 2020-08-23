/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Scopes {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(CodeTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = SymbolOutput<T, -1, ExpectPattern>;
    // Code pattern.
    template<typename T>
    using CodePattern = CodeScope<T, 0x01, SymbolPattern>;
  public:
    /// <summary>
    /// Test the consume method (using the fragment before)
    /// </summary>
    TEST_METHOD(MethodConsumeBefore) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StateScope<char, CodePattern> rule;
      auto& symbols = context.getSymbols();
      // Check the environment code.
      Assert::AreEqual<Id>(0x00, source.getOutput().getCode());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual<Id>(0x01, symbols.get("a")[0].getType());
      // Check the environment code.
      Assert::AreEqual<Id>(0x00, source.getOutput().getCode());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (using the fragment after)
    /// </summary>
    TEST_METHOD(MethodConsumeAfter) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      CodePattern<char> rule;
      auto& symbols = context.getSymbols();
      // Check the environment code.
      Assert::AreEqual<Id>(0x00, source.getOutput().getCode());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("b"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual<Id>(0x01, symbols.get("b")[0].getType());
      // Check the environment code.
      Assert::AreEqual<Id>(0x00, source.getOutput().getCode());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
