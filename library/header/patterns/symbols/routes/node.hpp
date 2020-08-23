/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"
#include "../node.hpp"

namespace Schemo::Patterns::Symbols::Routes {
  /// <summary>
  /// Node route.
  /// </summary>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<Direction A, template<typename> class P, auto ...V>
  class Node {
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
    using Pattern = Symbols::Node<U, A, P>;
  };
}
