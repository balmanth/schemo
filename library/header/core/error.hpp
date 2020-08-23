/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./fragment.hpp"

namespace Schemo {
  /// <summary>
  /// Error list type.
  /// </summary>
  /// <typeparam name="T">Value type</typeparam>
  template<typename T>
  using ErrorList = SPL::ArrayList<Error<T>>;
  /// <summary>
  /// Error class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Error final : public SPL::Comparable<Error<T>> {
  private:
    /// <summary>
    /// Error code.
    /// </summary>
    Id code;
    /// <summary>
    /// Error fragment.
    /// </summary>
    Fragment<T> fragment;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Error() :
      code(), fragment() {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="code">Error code.</param>
    /// <param name="fragment">Error fragment.</param>
    template<typename V>
    Error(const V& code, const Fragment<T>& fragment = {}) :
      code(static_cast<Id>(code)), fragment(fragment) {}
  public:
    /// <summary>
    /// Get the error code.
    /// </summary>
    /// <returns>Returns the error code.</returns>
    Id getCode() const {
      return this->code;
    }
    /// <summary>
    /// Get the error code as the specified value type.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <returns>Returns the error code.</returns>
    template<typename V>
    const V getCode() const {
      return static_cast<V>(this->getCode());
    }
    /// <summary>
    /// Get the error fragment.
    /// </summary>
    /// <returns>Returns the error fragment.</returns>
    const Fragment<T>& getFragment() const {
      return this->fragment;
    }
    /// <summary>
    /// Compare both errors.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>
    /// Returns -1 when this error is less than the other one.
    /// Returns  0 when this error is equals to the other one.
    /// Returns  1 when this error is greater than the other one.
    /// </returns>
    int compare(const Error<T>& other) const {
      const auto& target = this->fragment.getLocation();
      const auto& source = other.fragment.getLocation();
      int result;
      if ((result = SPL::Compare(this->code, other.code)) != 0) {
        return result;
      }
      else  if ((result = SPL::Compare(target.getLine(), source.getLine())) != 0) {
        return result;
      }
      else  if ((result = SPL::Compare(target.getColumn(), source.getColumn())) != 0) {
        return result;
      }
      return 0;
    }
  };
}
