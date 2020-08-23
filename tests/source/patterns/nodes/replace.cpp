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
  TEST_CLASS(ReplaceTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
  public:
    /// <summary>
    /// Test the consume method (with left direction).
    /// </summary>
    TEST_METHOD(MethodConsumeLeft) {
      AnsiString input("aab");
      Context<char> context;
      TextSource<char> source(input, context);
      ReplaceNode<char, 0x01, Direction::Left, Direction::Left, ExpectPattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNotNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (with right direction).
    /// </summary>
    TEST_METHOD(MethodConsumeRight) {
      AnsiString input("aab");
      Context<char> context;
      TextSource<char> source(input, context);
      ReplaceNode<char, 0x01, Direction::Right, Direction::Right, ExpectPattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNotNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (with the direction).
    /// </summary>
    TEST_METHOD(MethodConsumeNext) {
      AnsiString input("aab");
      Context<char> context;
      TextSource<char> source(input, context);
      ReplaceNode<char, 0x01, Direction::Next, Direction::Next, ExpectPattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNotNull(output.getNode()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
