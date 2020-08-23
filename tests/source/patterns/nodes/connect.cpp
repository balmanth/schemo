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
  TEST_CLASS(ConnectTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Replace pattern.
    template<typename T>
    using ReplacePattern = ReplaceNode<T, 0x02, Direction::Left, Direction::Left, ExpectPattern>;
  public:
    /// <summary>
    /// Test the consume method (with left direction).
    /// </summary>
    TEST_METHOD(MethodConsumeLeft) {
      AnsiString input("aaab");
      Context<char> context;
      TextSource<char> source(input, context);
      ConnectNode<char, 0x01, Direction::Left, Direction::Next, ReplacePattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNotNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getLeft());
      Assert::AreEqual<Id>(0x01, output.getNode()->getLeft()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getLeft()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft()->getLeft());
      Assert::IsNull(output.getNode()->getLeft()->getRight());
      Assert::IsNotNull(output.getNode()->getLeft()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getLeft()->getLeft());
      Assert::AreEqual<Id>(0x01, output.getNode()->getLeft()->getLeft()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getLeft()->getLeft()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft()->getLeft()->getLeft());
      Assert::IsNull(output.getNode()->getLeft()->getLeft()->getRight());
      Assert::IsNotNull(output.getNode()->getLeft()->getLeft()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (with right direction).
    /// </summary>
    TEST_METHOD(MethodConsumeRight) {
      AnsiString input("aaab");
      Context<char> context;
      TextSource<char> source(input, context);
      ConnectNode<char, 0x01, Direction::Right, Direction::Left, ReplacePattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNotNull(output.getNode()->getLeft());
      Assert::IsNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getRight());
      Assert::AreEqual<Id>(0x01, output.getNode()->getRight()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getRight()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNotNull(output.getNode()->getRight()->getLeft());
      Assert::IsNull(output.getNode()->getRight()->getRight());
      Assert::IsNull(output.getNode()->getRight()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getRight()->getRight());
      Assert::AreEqual<Id>(0x01, output.getNode()->getRight()->getRight()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getRight()->getRight()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNotNull(output.getNode()->getRight()->getRight()->getLeft());
      Assert::IsNull(output.getNode()->getRight()->getRight()->getRight());
      Assert::IsNull(output.getNode()->getRight()->getRight()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (with the direction).
    /// </summary>
    TEST_METHOD(MethodConsumeNext) {
      AnsiString input("aaab");
      Context<char> context;
      TextSource<char> source(input, context);
      ConnectNode<char, 0x01, Direction::Next, Direction::Right, ReplacePattern> rule;
      auto& output = source.getOutput();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::IsNotNull(output.getNode());
      Assert::AreEqual<Id>(0x01, output.getNode()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getLeft());
      Assert::IsNotNull(output.getNode()->getRight());
      Assert::IsNull(output.getNode()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getNext());
      Assert::AreEqual<Id>(0x01, output.getNode()->getNext()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getNext()->getFragment()).compare("a")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getNext()->getLeft());
      Assert::IsNotNull(output.getNode()->getNext()->getRight());
      Assert::IsNull(output.getNode()->getNext()->getNext());
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::IsNotNull(output.getNode()->getNext()->getNext());
      Assert::AreEqual<Id>(0x01, output.getNode()->getNext()->getNext()->getType());
      Assert::AreEqual(0, Identifier<char>(output.getNode()->getNext()->getNext()->getFragment()).compare("b")); // <~ Using the fragment after.
      Assert::IsNull(output.getNode()->getNext()->getNext()->getLeft());
      Assert::IsNotNull(output.getNode()->getNext()->getNext()->getRight());
      Assert::IsNull(output.getNode()->getNext()->getNext()->getNext());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
