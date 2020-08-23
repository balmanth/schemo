/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Nodes {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(PivotTests)
  {
  private:
    // Range pattern.
    template<typename T>
    using RangePattern = RangeUnit<T, 'a', 'b'>;
    // Replace pattern.
    template<typename T>
    using ReplacePattern = ConnectNode<T, 0x02, Direction::Right, Direction::Right, RangePattern>;
    // Operand pattern.
    template<typename T>
    using OperandPattern = StateScope<T, ReplacePattern>;
    // Symbol pattern.
    template<typename T>
    using SymbolPattern = ExpectUnit<T, '+'>;
    // Pivot pattern.
    template<typename T>
    using PivotPattern = PivotNode<T, 0x01, Direction::Left, Direction::Right, SymbolPattern, OperandPattern>;
    // Operation pattern.
    template<typename T>
    using OperationPattern = StateScope<T, PivotPattern>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeSuccess) {
      AnsiString input("a+bc");
      Context<char> context;
      TextSource<char> source(input, context);
      ExpectFlow<char, OperandPattern, OperationPattern> rule;
      auto& output = source.getOutput();
      // Consume 'a+a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("+")); // <~ Using the fragment after.
      Assert::IsNotNull(output.getNode()->getLeft());
      Assert::IsNotNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      Assert::AreEqual<Id>(0x02, output.getNode()->getLeft()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getLeft()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft()->getLeft());
      Assert::IsNull(output.getNode()->getLeft()->getRight());
      Assert::IsNull(output.getNode()->getLeft()->getNext());
      Assert::AreEqual<Id>(0x02, output.getNode()->getRight()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getRight()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getRight()->getLeft());
      Assert::IsNull(output.getNode()->getRight()->getRight());
      Assert::IsNull(output.getNode()->getRight()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('c', source.getValue());
    }
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsumeFailure) {
      AnsiString input("a+c");
      Context<char> context;
      TextSource<char> source(input, context);
      ExpectFlow<char, ReplacePattern, PivotPattern> rule;
      auto& output = source.getOutput();
      // Consume 'a' but fails on consuming '+c'.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x02, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("+")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
    }
  };
}
