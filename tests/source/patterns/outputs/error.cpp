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
  TEST_CLASS(ErrorTests)
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
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      ErrorOutput<char, 0x01, ExpectPattern> rule;
      auto& errors = context.getErrors();
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual(1U, errors.getLength());
      Assert::AreEqual<Id>(0x01, errors[0].getCode());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
