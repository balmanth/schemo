/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "./try.hpp"

namespace Schemo::Patterns::Flows {
  /// <summary>
  /// Condition pattern declaration.
  /// </summary>
  template<typename, template<typename> class, template<typename> class...>
  class Condition;
  /// <summary>
  /// Condition pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Condition pattern type.</typeparam>
  /// <typeparam name="S">Success pattern type.</typeparam>
  template<typename T, template<typename> class C, template<typename> class S>
  class Condition<T, C, S> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, C<T>, S<T>>, "C<T> and S<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (Try<T, C>().consume(source)) {
        return S<T>().consume(source);
      }
      return false;
    }
  };
  /// <summary>
  /// Condition pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="C">Condition pattern type.</typeparam>
  /// <typeparam name="S">Success pattern type.</typeparam>
  /// <typeparam name="F">Failure pattern type.</typeparam>
  template<typename T, template<typename> class C, template<typename> class S, template<typename> class F>
  class Condition<T, C, S, F> final : public Pattern<T> {
    static_assert(SPL::Types::IsBaseOf<Pattern<T>, C<T>, S<T>, F<T>>, "C<T>, S<T> and F<T> must derive from Pattern<T>");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (Try<T, C>().consume(source)) {
        return S<T>().consume(source);
      }
      return F<T>().consume(source);
    }
  };
}
