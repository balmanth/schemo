/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "patterns.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Patterns::Tests::Flows {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(NegateTests)
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
      NegateFlow<char, ExpectPattern> rule;
      // Consume 'a' but returns false.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Doesn't consume 'b' but returns true.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
