/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Symbols {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(RouterTests)
  {
  private:
    // Range pattern.
    template<typename T>
    using RangePattern = RangeUnit<T, '1', '3'>;
    // Node pattern.
    template<typename T>
    using NodePattern = ConnectNode<T, 0x03, Direction::Right, Direction::Right, RangePattern>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("abc1def2ghi3j");
      Context<char> context;
      TextSource<char> source(input, context);
      Router<char,
        SymbolFlagRoute<0x01, RangePattern, 'a', 'b', 'c'>,
        SymbolRecordRoute<0x02, RangePattern, 'd', 'e', 'f'>,
        SymbolNodeRoute<Direction::Next, NodePattern, 'g', 'h', 'i'>> rule;
      auto& symbol = context.getSymbol();
      auto& records = context.getRecords();
      // Consume 'abc1'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(4U, source.getOffset());
      Assert::AreEqual<Id>(0x01, symbol.getFlags());
      // Consume 'def2' (recording after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(8U, source.getOffset());
      Assert::AreEqual(1U, records.get(0x02).getLength());
      Assert::AreEqual(0, Identifier<char>(records.get(0x02)[0]).compare("g"));
      // Consume 'ghi3'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(12U, source.getOffset());
      Assert::IsNotNull(symbol.getNode());
      Assert::AreEqual<Id>(0x03, symbol.getNode()->getType());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(12U, source.getOffset());
      Assert::AreEqual<Id>('j', source.getValue());
    }
  };
}
