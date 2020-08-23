/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Symbols {
  /// <summary>
  /// Flag pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Flags code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  class Flag final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (Flows::Expect<T, P...>().consume(source)) {
        Flags& flags = source.getSymbolFlags();
        flags.enable(static_cast<Id>(C));
        return true;
      }
      return false;
    }
  };
}
