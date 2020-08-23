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
  TEST_CLASS(RouterTests)
  {
  public:
    // Test the consume method.
    TEST_METHOD(MethodConsume) {
      AnsiString input("abcdefghijklmnopqrs");
      Context<char> context;
      TextSource<char> source(input, context);
      Router<char,
        CodeOutputRoute<0x01, 'a', 'b', 'c'>,
        FlagOutputRoute<0x02, 'd', 'e', 'f'>,
        RecordOutputRoute<0x03, 'g', 'h', 'i'>,
        TokenOutputRoute<0x04, 'j', 'k', 'l'>,
        SymbolOutputRoute<0x05, 'm', 'n', 'o'>,
        ErrorOutputRoute<0x06, 'p', 'q', 'r'>> rule;
      auto& output = source.getOutput();
      auto& records = output.getRecords();
      auto& tokens = context.getTokens();
      auto& symbols = context.getSymbols();
      auto& errors = context.getErrors();
      // Consume 'abc'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(3U, source.getOffset());
      Assert::AreEqual<Id>(0x01, output.getCode());
      // Consume 'def'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(6U, source.getOffset());
      Assert::AreEqual<Id>(0x02, output.getFlags());
      // Consume 'ghi'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(9U, source.getOffset());
      Assert::AreEqual(1U, records.get(0x03).getLength());
      Assert::AreEqual(0, Identifier<char>(records.get(0x03)[0]).compare("j")); // <~ Using the fragment after.
      // Consume 'jkl'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(12U, source.getOffset());
      Assert::AreEqual(1U, tokens.getLength());
      Assert::AreEqual<Id>(0x04, tokens[0].getCode());
      // Consume 'mno' (using the fragment after).
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(15U, source.getOffset());
      Assert::IsFalse(symbols.isEmpty());
      Assert::IsTrue(symbols.has("p"));
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual(1U, symbols.get("p").getLength());
      Assert::AreEqual<Id>(0x05, symbols.get("p")[0].getType());
      // Consume 'pqr'.
      Assert::IsTrue(rule.consume(source));
      Assert::AreEqual(18U, source.getOffset());
      Assert::AreEqual(1U, errors.getLength());
      Assert::AreEqual<Id>(0x06, errors[0].getCode());
      // Check failure.
      Assert::IsFalse(rule.consume(source));
      Assert::AreEqual(18U, source.getOffset());
      Assert::AreEqual<Id>('s', source.getValue());
    }
  };
}
