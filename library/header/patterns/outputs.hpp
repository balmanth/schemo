/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./outputs/routes/code.hpp"
#include "./outputs/routes/flag.hpp"
#include "./outputs/routes/record.hpp"
#include "./outputs/routes/token.hpp"
#include "./outputs/routes/symbol.hpp"
#include "./outputs/routes/error.hpp"
#include "./outputs/code.hpp"
#include "./outputs/flag.hpp"
#include "./outputs/record.hpp"
#include "./outputs/token.hpp"
#include "./outputs/symbol.hpp"
#include "./outputs/error.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Flag output route.
  /// </summary>
  /// <typeparam name="F">Flag value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto F, auto ...V>
  using FlagOutputRoute = Outputs::Routes::Flag<F, V...>;
  /// <summary>
  /// Code output route.
  /// </summary>
  /// <typeparam name="C">Code value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto C, auto ...V>
  using CodeOutputRoute = Outputs::Routes::Code<C, V...>;
  /// <summary>
  /// Record output route.
  /// </summary>
  /// <typeparam name="R">Record value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto R, auto ...V>
  using RecordOutputRoute = Outputs::Routes::Record<R, V...>;
  /// <summary>
  /// Token output route.
  /// </summary>
  /// <typeparam name="T">Token value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto T, auto ...V>
  using TokenOutputRoute = Outputs::Routes::Token<T, V...>;
  /// <summary>
  /// Symbol output route.
  /// </summary>
  /// <typeparam name="S">Symbol value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto S, auto ...V>
  using SymbolOutputRoute = Outputs::Routes::Symbol<S, V...>;
  /// <summary>
  /// Error output route.
  /// </summary>
  /// <typeparam name="E">Error value.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto E, auto ...V>
  using ErrorOutputRoute = Outputs::Routes::Error<E, V...>;
  /// <summary>
  /// Code output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Code value.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  using CodeOutput = Outputs::Code<T, C, P...>;
  /// <summary>
  /// Flag output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="F">Flags code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto F, template<typename> class ...P>
  using FlagOutput = Outputs::Flag<T, F, P...>;
  /// <summary>
  /// Record output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="R">Record code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto R, template<typename> class ...P>
  using RecordOutput = Outputs::Record<T, R, P...>;
  /// <summary>
  /// Token output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Token code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  using TokenOutput = Outputs::Token<T, C, P...>;
  /// <summary>
  /// Symbol output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="S">Symbol type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto S, template<typename> class ...P>
  using SymbolOutput = Outputs::Symbol<T, S, P...>;
  /// <summary>
  /// Error output pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="E">Error code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto E, template<typename> class ...P>
  using ErrorOutput = Outputs::Error<T, E, P...>;
}
