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
  TEST_CLASS(TryTests)
  {
  private:
    // Expect pattern B.
    template<typename T>
    using ExpectPatternB = ExpectUnit<T, 'b'>;
    // Expect pattern A.
    template<typename T>
    using ExpectPatternA = ExpectUnit<T, 'a'>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("abac");
      Context<char> context;
      TextSource<char> source(input, context);
      TryFlow<char, ExpectPatternA, ExpectPatternB> rule;
      // Consume 'ab'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(2U, source.getOffset());
      Assert::AreEqual<Id>('a', source.getValue());
    }
  };
}
