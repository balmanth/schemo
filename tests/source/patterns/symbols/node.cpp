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
  TEST_CLASS(NodeTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Node pattern.
    template<typename T>
    using NodePattern = ConnectNode<T, 0x01, Direction::Right, Direction::Right, ExpectPattern>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("aaab");
      Context<char> context;
      TextSource<char> source(input, context);
      SymbolNode<char, Direction::Next, NodePattern> rule;
      auto& symbol = context.getSymbol();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(symbol.getNode());
      Assert::AreEqual<Id>(0x01, symbol.getNode()->getType());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(symbol.getNode());
      Assert::IsNotNull(symbol.getNode()->getNext());
      Assert::AreEqual<Id>(0x01, symbol.getNode()->getNext()->getType());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsNotNull(symbol.getNode());
      Assert::IsNotNull(symbol.getNode()->getNext());
      Assert::IsNotNull(symbol.getNode()->getNext()->getNext());
      Assert::AreEqual<Id>(0x01, symbol.getNode()->getNext()->getNext()->getType());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
