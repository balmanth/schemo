/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"

namespace Schemo::Patterns::Units {
  /// <summary>
  /// Range pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="S">Start range value.</typeparam>
  /// <typeparam name="E">End range value.</typeparam>
  template<typename T, auto S, auto E>
  class Range final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (source.hasValue()) {
        const Id& value = source.getValue();
        if (SPL::Compare(value, static_cast<Id>(S)) >= 0 && SPL::Compare(value, static_cast<Id>(E)) <= 0) {
          source.nextState();
          return true;
        }
      }
      return false;
    }
  };
}
