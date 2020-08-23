/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./fragment.hpp"

namespace Schemo {
  /// <summary>
  /// Identifier class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Identifier final : public SPL::Comparable<Identifier<T>> {
  private:
    /// <summary>
    /// Identifier name.
    /// </summary>
    SPL::Strings::Ansi<T> name;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Identifier() {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="name">Identifier name.</param>
    template<Size N>
    Identifier(const T(&name)[N]) :
      name(name) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="name">Identifier name.</param>
    Identifier(const Fragment<T>& name) :
      name(name.isEmpty() ? nullptr : &(name[0]), name.getLength()) {}
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Identifier(const Identifier<T>& other) :
      name(other.name) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Identifier(Identifier<T>&& other) noexcept :
      name(SPL::Move(other.name)) {}
  public:
    /// <summary>
    /// Get the identifier length.
    /// </summary>
    /// <returns>Returns the identifier length.</returns>
    Size getLength() const {
      return this->name.getLength();
    }
    /// <summary>
    /// Compare both identifiers.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>
    /// Returns -1 when this identifier is less than the other one.
    /// Returns  0 when this identifier is equals to the other one.
    /// Returns  1 when this identifier is greater than the other one.
    /// </returns>
    int compare(const Identifier<T>& other) const {
      return this->name.compare(other.name);
    }
  public:
    // <summary>
    /// Get the character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    const T& operator [](const Index index) const {
      return this->name[index];
    }
    /// <summary>
    /// Assign all properties from the given identifier.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Identifier<T>& operator = (Identifier<T> other) noexcept {
      this->name = SPL::Move(other.name);
      return *this;
    }
  public:
    /// <summary>
    /// Identifier hash function.
    /// </summary>
    /// <param name="key">Identifier key.</param>
    /// <returns>Returns the hash code.</returns>
    static Id Hash(const Identifier<T>& key) {
      SPL::Hashes::FNV1<T> fnv1;
      const Size length = key.name.getLength();
      const T* const string = &(key.name[0]);
      for (Size offset = 0; offset < length; ++offset) {
        fnv1.next(string[offset]);
      }
      return fnv1.getHash();
    }
  };
}
