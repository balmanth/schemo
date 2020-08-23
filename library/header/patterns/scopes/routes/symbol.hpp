/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../symbol.hpp"

namespace Schemo::Patterns::Scopes::Routes {
  /// <summary>
  /// Symbol route.
  /// </summary>
  /// <typeparam name="S">Symbol type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto S, template<typename> class P, auto ...V>
  class Symbol {
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
    using Pattern = Scopes::Symbol<U, S, P>;
  };
}
