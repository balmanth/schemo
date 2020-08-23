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
  TEST_CLASS(SymbolTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = SymbolOutput<T, 0x01, ExpectPattern>;
  public:
    /// <summary>
    /// Test the consume method (using the fragment before).
    /// </summary>
    TEST_METHOD(MethodConsumeBefore) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StateScope<char, SymbolPattern> rule;
      auto& symbols = context.getSymbols();
      // Set the output flags.
      source.getOutput().getFlags().set(0x02);
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a"));
      Assert::AreEqual<Id>(0x01, symbols.get("a")[0].getType());
      Assert::AreEqual<Id>(0x02, symbols.get("a")[0].getFlags());
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
      SymbolPattern<char> rule;
      auto& symbols = context.getSymbols();
      // Set the output flags.
      source.getOutput().getFlags().set(0x02);
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("b"));
      Assert::AreEqual<Id>(0x01, symbols.get("b")[0].getType());
      Assert::AreEqual<Id>(0x02, symbols.get("b")[0].getFlags());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
