/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./source.hpp"

namespace Schemo {
  /// <summary>
  /// Pattern interface.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Pattern {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Pattern() = default;
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    virtual bool consume(Source<T>& source) = 0;
  };
}
