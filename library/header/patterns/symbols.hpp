/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./symbols/routes/flag.hpp"
#include "./symbols/routes/record.hpp"
#include "./symbols/routes/node.hpp"
#include "./symbols/flag.hpp"
#include "./symbols/record.hpp"
#include "./symbols/node.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Symbol flag route.
  /// </summary>
  /// <typeparam name="F">Flag value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto F, template<typename> class P, auto ...V>
  using SymbolFlagRoute = Symbols::Routes::Flag<F, P, V...>;
  /// <summary>
  /// Symbol record route.
  /// </summary>
  /// <typeparam name="R">Record value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto R, template<typename> class P, auto ...V>
  using SymbolRecordRoute = Symbols::Routes::Record<R, P, V...>;
  /// <summary>
  /// Symbol node route.
  /// </summary>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<Direction A, template<typename> class P, auto ...V>
  using SymbolNodeRoute = Symbols::Routes::Node<A, P, V...>;
  /// <summary>
  /// Symbol flag pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Flags code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  using SymbolFlag = Symbols::Flag<T, C, P...>;
  /// <summary>
  /// Symbol record pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Record code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  using SymbolRecord = Symbols::Record<T, C, P...>;
  /// <summary>
  /// Symbol node pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, Direction A, template<typename> class ...P>
  using SymbolNode = Symbols::Node<T, A, P...>;
}
