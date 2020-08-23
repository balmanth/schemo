/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./scopes/routes/state.hpp"
#include "./scopes/routes/code.hpp"
#include "./scopes/routes/flag.hpp"
#include "./scopes/routes/record.hpp"
#include "./scopes/routes/node.hpp"
#include "./scopes/routes/symbol.hpp"
#include "./scopes/state.hpp"
#include "./scopes/code.hpp"
#include "./scopes/flag.hpp"
#include "./scopes/record.hpp"
#include "./scopes/node.hpp"
#include "./scopes/symbol.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// State scope route.
  /// </summary>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<template<typename> class P, auto ...V>
  using StateScopeRoute = Scopes::Routes::State<P, V...>;
  /// <summary>
  /// Code scope route.
  /// </summary>
  /// <typeparam name="C">Code value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto C, template<typename> class P, auto ...V>
  using CodeScopeRoute = Scopes::Routes::Code<C, P, V...>;
  /// <summary>
  /// Flag scope route.
  /// </summary>
  /// <typeparam name="F">Flag value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto F, template<typename> class P, auto ...V>
  using FlagScopeRoute = Scopes::Routes::Flag<F, P, V...>;
  /// <summary>
  /// Record scope route.
  /// </summary>
  /// <typeparam name="R">Record value.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto R, template<typename> class P, auto ...V>
  using RecordScopeRoute = Scopes::Routes::Record<R, P, V...>;
  /// <summary>
  /// Node scope route.
  /// </summary>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<Direction A, template<typename> class P, auto ...V>
  using NodeScopeRoute = Scopes::Routes::Node<A, P, V...>;
  /// <summary>
  /// Symbol scope route.
  /// </summary>
  /// <typeparam name="S">Symbol type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto S, template<typename> class P, auto ...V>
  using SymbolScopeRoute = Scopes::Routes::Symbol<S, P, V...>;
  /// <summary>
  /// State scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using StateScope = Scopes::State<T, P...>;
  /// <summary>
  /// Code scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Code value.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto C, template<typename> class ...P>
  using CodeScope = Scopes::Code<T, C, P...>;
  /// <summary>
  /// Flag scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="F">Flags code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto F, template<typename> class ...P>
  using FlagScope = Scopes::Flag<T, F, P...>;
  /// <summary>
  /// Record scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="R">Record code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto R, template<typename> class ...P>
  using RecordScope = Scopes::Record<T, R, P...>;
  /// <summary>
  /// Node scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, Direction A, template<typename> class ...P>
  using NodeScope = Scopes::Node<T, A, P...>;
  /// <summary>
  /// Symbol scope pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="S">Symbol type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto S, template<typename> class ...P>
  using SymbolScope = Scopes::Symbol<T, S, P...>;
}
