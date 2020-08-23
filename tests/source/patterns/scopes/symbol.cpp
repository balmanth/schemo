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
  TEST_CLASS(SymbolTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("aab");
      Context<char> context;
      TextSource<char> source(input, context);
      SymbolScope<char, 0x01, ExpectPattern> rule;
      auto& symbols = context.getSymbols();
      // Consume 'a' (using the fragment before).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual(1U, symbols.get("a").getLength());
      Assert::AreEqual<Id>(0x01, symbols.get("a")[0].getType());
      // Consume 'a' (using the fragment before).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual(2U, symbols.get("a").getLength());
      Assert::AreEqual<Id>(0x01, symbols.get("a")[1].getType());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
