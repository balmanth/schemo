/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../code.hpp"

namespace Schemo::Patterns::Outputs::Routes {
  /// <summary>
  /// Code route.
  /// </summary>
  /// <typeparam name="C">Code value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto C, auto ...V>
  class Code {
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
    using Pattern = Outputs::Code<U, C>;
  };
}
