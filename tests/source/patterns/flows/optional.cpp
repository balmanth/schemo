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
  TEST_CLASS(OptionalTests)
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
      OptionalFlow<char, ExpectPattern> rule;
      // Consume 'a'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(1U, source.getOffset());
      // Check failure.
      Assert::IsTrue(rule.consume(source)); // <~ Doesn't returns false on purpose.
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
    }
  };
}
