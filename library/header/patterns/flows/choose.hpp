/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "./try.hpp"

namespace Schemo::Patterns::Flows {
  /// <summary>
  /// Choose pattern declaration.
  /// </summary>
  template<typename, template<typename> class...>
  class Choose;
  /// <summary>
  /// Choose pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Choose<T> final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      return false;
    }
  };
  /// <summary>
  /// Choose pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  template<typename T, template<typename> class P>
  class Choose<T, P> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, P<T>>, "P<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      return Try<T, P>().consume(source);
    }
  };
  /// <summary>
  /// Combine pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="P">Pattern type.</typeparam>
  /// <typeparam name="...N">Next pattern types.</typeparam>
  template<typename T, template<typename> class P, template<typename> class ...N>
  class Choose<T, P, N...> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, P<T>>, "P<T> and ...N<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (!Try<T, P>().consume(source)) {
        return Choose<T, N...>().consume(source);
      }
      return true;
    }
  };
}
