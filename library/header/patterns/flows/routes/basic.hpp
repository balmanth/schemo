/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../../types.hpp"

namespace Schemo::Patterns::Flows::Routes {
  /// <summary>
  /// Basic route.
  /// </summary>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...V">Expected values.</typeparam>
  template<template<typename> class P, auto ...V>
  class Basic {
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
    using Pattern = P<U>;
  };
}
