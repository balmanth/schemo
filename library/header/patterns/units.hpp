/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./units/routes/basic.hpp"
#include "./units/any.hpp"
#include "./units/expect.hpp"
#include "./units/choose.hpp"
#include "./units/range.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Basic unit route.
  /// </summary>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<auto ...V>
  using BasicUnitRoute = Units::Routes::Basic<V...>;
  /// <summary>
  /// Any unit pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using AnyUnit = Units::Any<T>;
  /// <summary>
  /// Expect unit pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<typename T, auto ...V>
  using ExpectUnit = Units::Expect<T, V...>;
  /// <summary>
  /// Choose unit pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...O">Options list.</typeparam>
  template<typename T, auto ...O>
  using ChooseUnit = Units::Choose<T, O...>;
  /// <summary>
  /// Range unit pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="S">Start value.</typeparam>
  /// <typeparam name="E">End value.</typeparam>
  template<typename T, auto S, auto E>
  using RangeUnit = Units::Range<T, S, E>;
}
