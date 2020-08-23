/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../../flows/static.hpp"

namespace Schemo::Patterns::Units::Routes {
  /// <summary>
  /// Basic route.
  /// </summary>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto ...V>
  class Basic {
  public:
    /// <summary>
    /// Route values.
    /// </summary>
    constexpr static const Id values[] = { static_cast<Id>(V)..., Id() };
    /// <summary>
    /// Route pattern.
    /// </summary>
    /// <typeparam name="T">Character type.</typeparam>
    template<typename T>
    using Pattern = Flows::Static<T, true>;
  };
}
