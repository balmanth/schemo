/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./flows/routes/basic.hpp"
#include "./flows/try.hpp"
#include "./flows/repeat.hpp"
#include "./flows/optional.hpp"
#include "./flows/negate.hpp"
#include "./flows/condition.hpp"
#include "./flows/expect.hpp"
#include "./flows/choose.hpp"
#include "./flows/static.hpp"
#include "./flows/end.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Basic flow route.
  /// </summary>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<template<typename> class P, auto ...V>
  using BasicFlowRoute = Flows::Routes::Basic<P, V...>;
  /// <summary>
  /// Try flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using TryFlow = Flows::Try<T, P...>;
  /// <summary>
  /// Repeat flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using RepeatFlow = Flows::Repeat<T, P...>;
  /// <summary>
  /// Optional flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using OptionalFlow = Flows::Optional<T, P...>;
  /// <summary>
  /// Negate flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using NegateFlow = Flows::Negate<T, P...>;
  /// <summary>
  /// Condition flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Condition pattern type.</typeparam>
  /// <typeparam name="...N">Next pattern types.</typeparam>
  template<typename T, template<typename> class C, template<typename> class ...N>
  using ConditionFlow = Flows::Condition<T, C, N...>;
  /// <summary>
  /// Expect flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using ExpectFlow = Flows::Expect<T, P...>;
  /// <summary>
  /// Choose flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, template<typename> class ...P>
  using ChooseFlow = Flows::Choose<T, P...>;
  /// <summary>
  /// Static flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="S">Pattern status.</typeparam>
  template<typename T, bool S>
  using StaticFlow = Flows::Static<T, S>;
  /// <summary>
  /// End flow pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using EndFlow = Flows::End<T>;
}
