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
  TEST_CLASS(RouterTests)
  {
  private:
    // Range pattern.
    template<typename T>
    using RangePattern = RangeUnit<T, '0', '3'>;
  public:
    /// <summary>
    /// Test the consume method.
    /// </summary>
    TEST_METHOD(MethodConsume) {
      AnsiString input("abc0d");
      Context<char> context;
      TextSource<char> source(input, context);
      Router<char, BasicFlowRoute<RangePattern, 'a', 'b', 'c'>> rule;
      // Consume 'abc0'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(4U, source.getOffset());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(4U, source.getOffset());
      Assert::AreEqual<Id>('d', source.getValue());
    }
  };
}
