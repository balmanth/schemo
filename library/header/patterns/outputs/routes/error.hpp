/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../error.hpp"

namespace Schemo::Patterns::Outputs::Routes {
  /// <summary>
  /// Error route.
  /// </summary>
  /// <typeparam name="E">Error code.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto E, auto ...V>
  class Error {
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
    using Pattern = Outputs::Error<U, E>;
  };
}
