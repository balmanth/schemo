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
  TEST_CLASS(RouterTests)
  {
  private:
    // Range pattern.
    template<typename T>
    using RangePattern = RangeUnit<T, '0', '5'>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = SymbolOutput<T, -1, RangePattern>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("abc0def1ghi2jkl3mno4pqr5s");
      Context<char> context;
      TextSource<char> source(input, context);
      Router<char,
        StateScopeRoute<RangePattern, 'a', 'b', 'c'>,
        CodeScopeRoute<0x01, SymbolPattern, 'd', 'e', 'f'>,
        FlagScopeRoute<0x02, SymbolPattern, 'g', 'h', 'i'>,
        RecordScopeRoute<0x03, SymbolPattern, 'j', 'k', 'l'>,
        SymbolScopeRoute<0x04, RangePattern, 'm', 'n', 'o'>,
        NodeScopeRoute<Direction::Next, SymbolPattern, 'p', 'q', 'r'>> rule;
      auto& symbols = context.getSymbols();
      // Consume 'abc0'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(4U, source.getOffset());
      // Consume 'def1' (using the fragment after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(8U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("g"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual<Id>(0x01, symbols.get("g")[0].getType());
      // Consume 'ghi2' (using the fragment after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(12U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("j"));
      Assert::AreEqual(2U, symbols.getSize());
      Assert::AreEqual<Id>(0x02, symbols.get("j")[0].getFlags());
      // Consume 'jkl3' (using the fragment after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(16U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("m"));
      Assert::AreEqual(3U, symbols.getSize());
      Assert::AreEqual(1U, symbols.get("m")[0].getRecords().get(0x03).getLength());
      Assert::AreEqual(0, Identifier<char>(symbols.get("m")[0].getRecords().get(0x03)[0]).compare("3"));
      // Consume 'mno4' (using the fragment after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(20U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("4"));
      Assert::AreEqual(4U, symbols.getSize());
      Assert::AreEqual(1U, symbols.get("4").getLength());
      // Consume 'pqr5'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(24U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(24U, source.getOffset());
      Assert::AreEqual<Id>('s', source.getValue());
    }
  };
}
