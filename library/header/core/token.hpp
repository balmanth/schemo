/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./fragment.hpp"

namespace Schemo {
  /// <summary>
  /// Token list type.
  /// </summary>
  /// <typeparam name="T">Value type</typeparam>
  template<typename T>
  using TokenList = SPL::ArrayList<Token<T>>;
  /// <summary>
  /// Token class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Token final : public SPL::Comparable<Token<T>> {
  private:
    /// <summary>
    /// Token code.
    /// </summary>
    Id code;
    /// <summary>
    /// Token fragment.
    /// </summary>
    Fragment<T> fragment;
  public:
    /// <summary>
    /// Default initialized constructor.
    /// </summary>
    /// <param name="code">Initial code.</param>
    /// <param name="fragment">Initial fragment.</param>
    Token(const Id code = 0, const Fragment<T>& fragment = {}) :
      code(code), fragment(fragment) {}
  public:
    /// <summary>
    /// Get the token code.
    /// </summary>
    /// <returns>Returns the token code.</returns>
    Id getCode() const {
      return this->code;
    }
    /// <summary>
    /// Get the token fragment.
    /// </summary>
    /// <returns>Returns the token fragment.</returns>
    const Fragment<T>& getFragment() const {
      return this->fragment;
    }
    /// <summary>
    /// Compare both tokens.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>
    /// Returns -1 when this token is less than the other one.
    /// Returns  0 when this token is equals to the other one.
    /// Returns  1 when this token is greater than the other one.
    /// </returns>
    int compare(const Token<T>& other) const {
      const auto& target = this->fragment.getLocation();
      const auto& source = other.fragment.getLocation();
      int result;
      if ((result = SPL::Compare(this->code, other.code)) != 0) {
        return result;
      }
      else if ((result = SPL::Compare(target.getLine(), source.getLine())) != 0) {
        return result;
      }
      else if ((result = SPL::Compare(target.getColumn(), source.getColumn())) != 0) {
        return result;
      }
      return 0;
    }
  };
}
