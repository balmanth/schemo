/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./nodes/connect.hpp"
#include "./nodes/replace.hpp"
#include "./nodes/pivot.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Connect node pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="L">Link direction.</typeparam>
  /// <typeparam name="...E">Expected pattern types.</typeparam>
  template<typename T, auto N, Direction A, Direction L, template<typename> class ...E>
  using ConnectNode = Nodes::Connect<T, N, A, L, E...>;
  /// <summary>
  /// Replace node pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="R">Replacement direction.</typeparam>
  /// <typeparam name="L">Link direction.</typeparam>
  /// <typeparam name="...E">Expected pattern types.</typeparam>
  template<typename T, auto N, Direction R, Direction L, template<typename> class ...E>
  using ReplaceNode = Nodes::Replace<T, N, R, L, E...>;
  /// <summary>
  /// Pivot node pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="A">Active direction.</typeparam>
  /// <typeparam name="L">Link direction.</typeparam>
  /// <typeparam name="P">Pivot pattern type.</typeparam>
  /// <typeparam name="...E">Expected pattern types.</typeparam>
  template<typename T, auto N, Direction A, Direction L, template<typename> class P, template<typename> class ...E>
  using PivotNode = Nodes::Pivot<T, N, A, L, P, E...>;
}
