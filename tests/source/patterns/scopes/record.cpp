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
  TEST_CLASS(RecordTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = SymbolOutput<T, -1, ExpectPattern>;
    // Record pattern.
    template<typename T>
    using RecordPattern = RecordScope<T, 0x01, SymbolPattern>;
  public:
    /// <summary>
    /// Test the consume method (emitting the symbol before).
    /// </summary>
    TEST_METHOD(MethodConsumeBefore) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StateScope<char, RecordPattern> rule;
      auto& symbols = context.getSymbols();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, symbols.getSize());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a"));
      Assert::AreEqual(1U, symbols.get("a")[0].getRecords().get(0x01).getLength());
      Assert::AreEqual(0, Identifier<char>(symbols.get("a")[0].getRecords().get(0x01)[0]).compare("a"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (emitting the symbol after).
    /// </summary>
    TEST_METHOD(MethodConsumeAfter) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      RecordPattern<char> rule;
      auto& symbols = context.getSymbols();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("b"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual(1U, symbols.get("b")[0].getRecords().get(0x01).getLength());
      Assert::AreEqual(0, Identifier<char>(symbols.get("b")[0].getRecords().get(0x01)[0]).compare("a"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
