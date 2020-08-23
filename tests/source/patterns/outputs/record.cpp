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
  TEST_CLASS(RecordTests)
  {
  private:
    // Expect pattern.
    template<typename T>
    using ExpectPattern = ExpectUnit<T, 'a'>;
    // Record pattern.
    template<typename T>
    using RecordPattern = RecordOutput<T, 0x01, ExpectPattern>;
  public:
    /// <summary>
    /// Test the consume method (recording the fragment before).
    /// </summary>
    TEST_METHOD(MethodConsumeBefore) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      StateScope<char, RecordPattern> rule;
      auto& output = source.getOutput();
      auto& records = output.getRecords();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, records.get(0x01).getLength());
      Assert::AreEqual(0, Identifier<char>(records.get(0x01)[0]).compare("a"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
    /// <summary>
    /// Test the consume method (recording the fragment after).
    /// </summary>
    TEST_METHOD(MethodConsumeAfter) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      RecordPattern<char> rule;
      auto& output = source.getOutput();
      auto& records = output.getRecords();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, records.get(0x01).getLength());
      Assert::AreEqual(0, Identifier<char>(records.get(0x01)[0]).compare("b"));
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
