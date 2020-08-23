/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../flag.hpp"

namespace Schemo::Patterns::Scopes::Routes {
  /// <summary>
  /// Flag route.
  /// </summary>
  /// <typeparam name="F">Flag value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto F, template<typename> class P, auto ...V>
  class Flag {
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
    using Pattern = Scopes::Flag<U, F, P>;
  };
}
