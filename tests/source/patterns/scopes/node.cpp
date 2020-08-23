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
  TEST_CLASS(NodeTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Replace pattern.
    template<typename T>
    using ReplacePattern = ConnectNode<T, 0x01, Direction::Right, Direction::Right, ExpectPattern>;
    // Node pattern.
    template<typename T>
    using NodePattern = SymbolNode<T, Direction::Next, ReplacePattern>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = SymbolScope<T, 0x01, NodePattern>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      NodeScope<char, Direction::Next, SymbolPattern> rule;
      auto& symbols = context.getSymbols();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("a")); // <~ using the fragment before.
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual<Id>(0x01, symbols.get("a")[0].getType());
      Assert::IsNotNull(symbols.get("a")[0].getNode());
      Assert::AreEqual<Id>(0x01, symbols.get("a")[0].getNode()->getType());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
