/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"

namespace Schemo::Patterns::Units {
  /// <summary>
  /// Any pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Any final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (source.hasValue()) {
        source.nextState();
        return true;
      }
      return false;
    }
  };
}
