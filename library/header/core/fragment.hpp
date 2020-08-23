/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./location.hpp"

namespace Schemo {
  /// <summary>
  /// Fragment class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Fragment final {
  private:
    /// <summary>
    /// String source.
    /// </summary>
    const SPL::String<T>* source;
    /// <summary>
    /// Begin offset.
    /// </summary>
    Size begin;
    /// <summary>
    /// End offset.
    /// </summary>
    Size end;
    /// <summary>
    /// Fragment location.
    /// </summary>
    Location location;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Fragment() :
      source(nullptr), begin(0), end(0) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="source">Fragment source.</param>
    /// <param name="offset">Fragment offset.</param>
    /// <param name="length">Fragment length.</param>
    /// <param name="location">Fragment location.</param>
    Fragment(const SPL::String<T>& source, const Size offset, const Size length, const Location& location) :
      source(&source), begin(offset), end(offset + length), location(location) {}
  public:
    /// <summary>
    /// Get the begin offset.
    /// </summary>
    /// <returns>Returns the begin offset.</returns>
    Size getBegin() const {
      return this->begin;
    }
    /// <summary>
    /// Get the end offset.
    /// </summary>
    /// <returns>Returns the end offset.</returns>
    Size getEnd() const {
      return this->end;
    }
    /// <summary>
    /// Get the fragment length.
    /// </summary>
    /// <returns>Returns the fragment length.</returns>
    Size getLength() const {
      return this->end - this->begin;
    }
    /// <summary>
    /// Determines whether or not the fragment is empty.
    /// </summary>
    /// <returns>Returns true when the fragment is empty, false otherwise.</returns>
    bool isEmpty() const {
      return this->getLength() == 0;
    }
    /// <summary>
    /// Get the fragment location.
    /// </summary>
    /// <returns>Returns the fragment location.</returns>
    const Location& getLocation() const {
      return this->location;
    }
  public:
    // <summary>
    /// Get the fragment character that corresponds to the specified index.
    /// </summary>
    /// <param name="index">Zero-based index.</param>
    /// <returns>Returns the corresponding character.</returns>
    const T& operator [](const Index index) const {
      return (*this->source)[this->begin + index];
    }
  };
}
