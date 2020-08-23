/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "interfaces.hpp"
#include "sources.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Sources::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(TextTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      AnsiString input;
      Context<char> context;
      TextSource<char> source(input, context);
      // Check state.
      Assert::IsFalse(source.hasValue());
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      // Check state.
      Assert::IsTrue(source.hasValue());
    }
    /// <summary>
    /// Test the emitToken method.
    /// </summary>
    TEST_METHOD(MethodEmitToken) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      TokenList<char>& tokens = context.getTokens();
      // Emit by output value.
      source.getOutput().setCode(0x0C);
      source.emitToken();
      // Emit by direct value.
      source.emitToken(0x0D);
      // Check state.
      Assert::AreEqual(2U, tokens.getLength());
      Assert::AreEqual<Id>(0x0C, tokens[0].getCode());
      Assert::AreEqual<Id>(0x0D, tokens[1].getCode());
    }
    /// <summary>
    /// Test the emitToken method.
    /// </summary>
    TEST_METHOD(MethodEmitError) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      ErrorList<char>& errors = context.getErrors();
      // Emit by output value.
      source.getOutput().setCode(0x0C);
      source.emitError();
      // Emit by direct value.
      source.emitError(0x0D);
      // Check state.
      Assert::AreEqual(2U, errors.getLength());
      Assert::AreEqual<Id>(0x0C, errors[0].getCode());
      Assert::AreEqual<Id>(0x0D, errors[1].getCode());
    }
    /// <summary>
    /// Test the emitSymbol method.
    /// </summary>
    TEST_METHOD(MethodEmitSymbol) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      auto& symbols = context.getSymbol().getSymbols();
      // Emit by output value.
      source.getOutput().setCode(0x0C);
      source.emitSymbol();
      Assert::IsFalse(symbols.isEmpty());
      Assert::AreEqual(1U, symbols.getSize());
      Assert::AreEqual<Id>(0x0C, symbols.get("a")[0].getType());
      // Go to the next state.
      source.nextState();
      // Emit by direct value.
      source.emitSymbol(0x0D);
      Assert::IsFalse(symbols.isEmpty());
      Assert::AreEqual(2U, symbols.getSize());
      // Get by direct name.
      Assert::AreEqual<Id>(0x0D, symbols.get("b")[0].getType());
    }
    /// <summary>
    /// Test the next method.
    /// </summary>
    TEST_METHOD(MethodNext) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      // Check the first state.
      Assert::IsTrue(source.hasValue());
      Assert::AreEqual(0U, source.getOffset());
      Assert::AreEqual<Id>('a', source.getValue());
      // Move forward.
      source.nextState();
      // Check the second state.
      Assert::IsTrue(source.hasValue());
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
      // Move forward.
      source.nextState();
      // Check the third state.
      Assert::IsFalse(source.hasValue());
      Assert::AreEqual(2U, source.getOffset());
    }
    /// <summary>
    /// Test the state feature.
    /// </summary>
    TEST_METHOD(FeatureState) {
      AnsiString input("ab");
      Context<char> context;
      TextSource<char> source(input, context);
      // Save the current state.
      source.pushState();
      Assert::IsTrue(source.hasValue());
      Assert::AreEqual(0U, source.getOffset());
      Assert::AreEqual<Id>('a', source.getValue());
      // Change the current state.
      source.nextState();
      Assert::IsTrue(source.hasValue());
      Assert::AreEqual(1U, source.getOffset());
      Assert::AreEqual<Id>('b', source.getValue());
      // Restore the previous state.
      source.restoreState();
      Assert::IsTrue(source.hasValue());
      Assert::AreEqual(0U, source.getOffset());
      Assert::AreEqual<Id>('a', source.getValue());
      // Discard the previous state.
      source.popState();
    }
  };
}
