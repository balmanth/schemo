/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"

namespace Schemo::Patterns::Units {
  /// <summary>
  /// Expect pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<typename T, auto ...V>
  class Expect final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      for (const Id& value : { static_cast<Id>(V)... }) {
        if (!source.hasValue() || SPL::Compare(source.getValue(), value) != 0) {
          return false;
        }
        source.nextState();
      }
      return true;
    }
  };
}
