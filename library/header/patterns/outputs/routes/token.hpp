/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../token.hpp"

namespace Schemo::Patterns::Outputs::Routes {
  /// <summary>
  /// Token route.
  /// </summary>
  /// <typeparam name="T">Token value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto T, auto ...V>
  class Token {
  public:
    /// <summary>
    /// Route values.
    /// </summary>
    constexpr static const Id values[] = { static_cast<Id>(V)..., Id() };
    /// <summary>
    /// Route pattern.
    /// </summary>
    /// <typeparam name="U">Character type.</typeparam>
    template<typename U>
    using Pattern = Outputs::Token<U, T>;
  };
}
