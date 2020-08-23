/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"

namespace Schemo::Patterns::Flows {
  /// <summary>
  /// Expect pattern declaration.
  /// </summary>
  template<typename, template<typename> class...>
  class Expect;
  /// <summary>
  /// Expect pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Expect<T> final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      return true;
    }
  };
  /// <summary>
  /// Expect pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  template<typename T, template<typename> class P>
  class Expect<T, P> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, P<T>>, "P<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      return P<T>().consume(source);
    }
  };
  /// <summary>
  /// Expect pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...N">Next pattern types.</typeparam>
  template<typename T, template<typename> class P, template<typename> class ...N>
  class Expect<T, P, N...> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, P<T>>, "P<T> and ...N<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      return P<T>().consume(source) && Expect<T, N...>().consume(source);
    }
  };
}
