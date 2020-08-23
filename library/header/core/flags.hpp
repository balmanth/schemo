/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace Schemo {
  /// <summary>
  /// Flags class.
  /// </summary>
  class Flags final {
  private:
    /// <summary>
    /// Current value.
    /// </summary>
    Id value;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Flags() :
      value(0) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="value">Initial value.</param>
    template<typename V>
    Flags(const V& value) :
      value(static_cast<Id>(value)) {}
  public:
    /// <summary>
    /// Get the current value.
    /// </summary>
    /// <returns>Returns the value.</returns>
    Id get() const {
      return this->value;
    }
    /// <summary>
    /// Get the current value as the specified value type.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <returns>Returns the value.</returns>
    template<typename V>
    const V get() const {
      return static_cast<V>(this->get());
    }
    /// <summary>
    /// Determines whether or not one of the given flags are active.
    /// </summary>
    /// <param name="flags">Flags to check.</param>
    /// <returns>Returns true when one or more flags are active, false otherwise.</returns>
    bool has(const Id flags) const {
      return this->value & flags;
    }
    /// <summary>
    /// Determines whether or not one of the given flags are active.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="flags">Flags to check.</param>
    /// <returns>Returns true when one or more flags are active, false otherwise.</returns>
    template<typename V>
    bool has(const V& flags) const {
      return this->has(static_cast<Id>(flags));
    }
    /// <summary>
    /// Set the specified flags.
    /// </summary>
    /// <param name="flags">New flags.</param>
    void set(const Id flags) {
      this->value = flags;
    }
    /// <summary>
    /// Set the specified flags.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="flags">New flags.</param>
    template<typename V>
    void set(const V& flags) {
      this->set(static_cast<Id>(flags));
    }
    /// <summary>
    /// Enable the specified flags.
    /// </summary>
    /// <param name="flags">Flags to enable.</param>
    void enable(const Id flags) {
      this->value |= flags;
    }
    /// <summary>
    /// Enable the specified flags.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="flags">Flags to enable.</param>
    template<typename V>
    void enable(const V& flags) {
      this->enable(static_cast<Id>(flags));
    }
    /// <summary>
    /// Disable the specified flags.
    /// </summary>
    /// <param name="flags">Flags to disable.</param>
    void disable(const Id flags) {
      this->value &= ~flags;
    }
    /// <summary>
    /// Disable the specified flags.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="flags">Flags to disable.</param>
    template<typename V>
    void disable(const V& flags) {
      this->disable(static_cast<Id>(flags));
    }
  public:
    /// <summary>
    /// Convert this object into raw form.
    /// </summary>
    operator const Id() const {
      return this->get();
    }
  };
}
