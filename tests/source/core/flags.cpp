/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#include "CppUnitTest.h"
#include "core.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Schemo::Tests {
  /// <summary>
  /// Test class.
  /// </summary>
  TEST_CLASS(FlagsTests)
  {
  public:
    /// <summary>
    /// Test the empty constructor.
    /// </summary>
    TEST_METHOD(ConstructEmpty) {
      Flags flags;
      // Check state.
      Assert::IsFalse(flags.has(0b00000000));
      Assert::IsFalse(flags.has(0b10000000));
    }
    /// <summary>
    /// Test the initialized constructor.
    /// </summary>
    TEST_METHOD(ConstructInitialized) {
      Flags flags(0b10010010);
      // Check state.
      Assert::IsFalse(flags.has(0b00000000));
      Assert::IsTrue(flags.has(0b10000000));
      Assert::IsTrue(flags.has(0b00010000));
      Assert::IsTrue(flags.has(0b00000010));
      Assert::IsTrue(flags.has(0b10010010));
    }
    /// <summary>
    /// Test the enable method.
    /// </summary>
    TEST_METHOD(MethodEnable) {
      Flags flags;
      // Set flags.
      flags.enable(0b10010010);
      // Check state.
      Assert::IsFalse(flags.has(0b00000000));
      Assert::IsTrue(flags.has(0b10000000));
      Assert::IsTrue(flags.has(0b00010000));
      Assert::IsTrue(flags.has(0b00000010));
      Assert::IsTrue(flags.has(0b00010010));
    }
    /// <summary>
    /// Test the disable method.
    /// </summary>
    TEST_METHOD(MethodDisable) {
      Flags flags(0b10010010);
      // Disable flags.
      flags.disable(0b10010000);
      // Check state.
      Assert::IsFalse(flags.has(0b00000000));
      Assert::IsFalse(flags.has(0b10000000));
      Assert::IsFalse(flags.has(0b00010000));
      Assert::IsTrue(flags.has(0b00010010));
      Assert::IsTrue(flags.has(0b00000010));
    }
  };
}
