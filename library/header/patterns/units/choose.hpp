/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"

namespace Schemo::Patterns::Units {
  /// <summary>
  /// Choose pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...O">Options list.</typeparam>
  template<typename T, auto ...O>
  class Choose final : public Pattern<T> {
  private:
    /// <summary>
    /// HashSet type.
    /// </summary>
    using HashSet = SPL::HashSet<const Id>;
  private:
    /// <summary>
    /// Options set.
    /// </summary>
    static const HashSet options;
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (source.hasValue()) {
        if (Choose<T, O...>::options.has(source.getValue())) {
          source.nextState();
          return true;
        }
      }
      return false;
    }
  };
  /// <summary>
  /// Initializes all options.
  /// </summary>
  template<typename T, auto ...O>
  const typename Choose<T, O...>::HashSet Choose<T, O...>::options = Choose<T, O...>::HashSet({ static_cast<Id>(O)... });
}
