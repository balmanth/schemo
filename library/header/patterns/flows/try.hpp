/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "./expect.hpp"

namespace Schemo::Patterns::Flows {
  /// <summary>
  /// Try pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  class Try final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      source.pushState();
      const bool result = Expect<T, P...>().consume(source);
      if (!result) {
        source.restoreState();
      }
      source.popState();
      return result;
    }
  };
}
