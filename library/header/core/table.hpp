/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./fragment.hpp"

namespace Schemo {
  /// <summary>
  /// Table iterator type.
  /// </summary>
  /// <typeparam name="K">Record key</typeparam>
  /// <typeparam name="V">Record value</typeparam>
  /// <typeparam name="H">Hash function</typeparam>
  template<typename K, typename V, Id(H)(const K&) = &SPL::HashTables::Function>
  using TableIterator = SPL::Unique<SPL::Iterator<SPL::HashTables::Entry<K, SPL::ArrayList<V>>>>;
  /// <summary>
  /// Table class.
  /// </summary>
  /// <typeparam name="K">Record key</typeparam>
  /// <typeparam name="V">Record value</typeparam>
  /// <typeparam name="H">Hash function</typeparam>
  template<typename K, typename V, Id(H)(const K&) = &SPL::HashTables::Function>
  class Table final {
  private:
    /// <summary>
    /// Map of records.
    /// </summary>
    SPL::HashMap<K, SPL::ArrayList<V>, H> map;
  public:
    /// <summary>
    /// Get the number of records.
    /// </summary>
    /// <returns>Returns the number of records.</returns>
    Size getSize() const {
      return this->map.getSize();
    }
    /// <summary>
    /// Determines whether or not there are no records.
    /// </summary>
    /// <returns>Returns true when there are no records, false otherwise.</returns>
    bool isEmpty() const {
      return this->map.isEmpty();
    }
    /// <summary>
    /// Get the records iterator.
    /// </summary>
    /// <returns>Returns the records iterator.</returns>
    TableIterator<K, V, H> getIterator() const {
      return this->map.getIterator();
    }
    /// <summary>
    /// Determines whether or not the given key contains a non-empty record.
    /// </summary>
    /// <param name="key">Record key.</param>
    /// <returns>Returns true when a non-empty record exists in the specified key, false otherwise.</returns>
    bool has(const K& key) const {
      return this->map.has(key) && !this->map.get(key).isEmpty();
    }
    /// <summary>
    /// Get all records that corresponds to the given key.
    /// </summary>
    /// <param name="key">Record key.</param>
    /// <returns>Returns the corresponding records.</returns>
    SPL::ArrayList<V>& get(const K& key) const {
      return this->map.get(key);
    }
    /// <summary>
    /// Add the given record in the specified key by using move semantics.
    /// </summary>
    /// <param name="key">Record key.</param>
    /// <param name="value">Record value.</param>
    void add(const K& key, SPL::Metadata::ConstantType<V>&& value) {
      this->map[key].add(SPL::Forward<SPL::Metadata::ConstantType<V>>(value));
    }
    /// <summary>
    /// Add a copy of the given record in the specified key.
    /// </summary>
    /// <param name="key">Record key.</param>
    /// <param name="value">Record value.</param>
    void add(const K& key, const V& value) {
      SPL::Metadata::ConstantType<V> copy(value);
      this->add(key, SPL::Move(copy));
    }
  };
}
