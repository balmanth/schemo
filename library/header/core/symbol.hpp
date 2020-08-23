/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./flags.hpp"
#include "./fragment.hpp"
#include "./table.hpp"
#include "./node.hpp"

namespace Schemo {
  /// <summary>
  /// Symbol class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Symbol final {
  private:
    /// <summary>
    /// Symbol type.
    /// </summary>
    Id type;
    /// <summary>
    /// Symbol flags.
    /// </summary>
    Flags flags;
    /// <summary>
    /// Symbol fragment.
    /// </summary>
    Fragment<T> fragment;
    /// <summary>
    /// Symbols table.
    /// </summary>
    Table<const Identifier<T>, Symbol<T>, &Identifier<T>::Hash> symbols;
    /// <summary>
    /// Records table.
    /// </summary>
    Table<const Id, Fragment<T>> records;
    /// <summary>
    /// Parent symbol.
    /// </summary>
    Symbol<T>* parent;
    /// <summary>
    /// Symbol node.
    /// </summary>
    Node<T>* node;
    /// <summary>
    /// Symbol index.
    /// </summary>
    Index index;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Symbol() :
      type(), flags(), fragment(), parent(nullptr), node(nullptr) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="type">Symbol type.</param>
    /// <param name="flags">Symbol flags.</param>
    /// <param name="fragment">Symbol fragment.</param>
    /// <param name="parent">Symbol parent.</param>
    template<typename V>
    Symbol(const V& type, const Flags flags = 0, const Fragment<T>& fragment = {}, Symbol<T>* const parent = nullptr) :
      type(static_cast<Id>(type)), flags(flags), fragment(fragment), parent(parent), node(nullptr),
      index(parent != nullptr ? parent->getSymbols().getSize() : 0) {}
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Symbol() {
      delete this->node;
    }
  public:
    /// <summary>
    /// Get the symbol type.
    /// </summary>
    /// <returns>Returns the symbol type.</returns>
    Id getType() const {
      return this->type;
    }
    /// <summary>
    /// Get the symbol type as the specified value type.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <returns>Returns the symbol type.</returns>
    template<typename V>
    const V getType() const {
      return static_cast<V>(this->getType());
    }
    /// <summary>
    /// Get the symbol flags in the constant form.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    const Flags& getFlags() const {
      return this->flags;
    }
    /// <summary>
    /// Get the symbol flags.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    Flags& getFlags() {
      return this->flags;
    }
    /// <summary>
    /// Get the symbol fragment.
    /// </summary>
    /// <returns>Returns the symbol fragment.</returns>
    const Fragment<T>& getFragment() const {
      return this->fragment;
    }
    /// <summary>
    /// Get the parent symbol in the constant form.
    /// </summary>
    /// <returns>Returns the parent symbol.</returns>
    const Symbol<T>* const getParent() const {
      return this->parent;
    }
    /// <summary>
    /// Get the parent symbol.
    /// </summary>
    /// <returns>Returns the parent symbol.</returns>
    Symbol<T>* const getParent() {
      return this->parent;
    }
    /// <summary>
    /// Get the symbol index.
    /// </summary>
    /// <returns>Returns the symbol index.</returns>
    Index getIndex() const {
      return this->index;
    }
    /// <summary>
    /// Get the symbols table in the constant form.
    /// </summary>
    /// <returns>Returns the symbols table.</returns>
    const Table<const Identifier<T>, Symbol<T>, &Identifier<T>::Hash>& getSymbols() const {
      return this->symbols;
    }
    /// <summary>
    /// Get the symbols table.
    /// </summary>
    /// <returns>Returns the symbols table.</returns>
    Table<const Identifier<T>, Symbol<T>, &Identifier<T>::Hash>& getSymbols() {
      return this->symbols;
    }
    /// <summary>
    /// Get the records table in the constant form.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    const Table<const Id, Fragment<T>>& getRecords() const {
      return this->records;
    }
    /// <summary>
    /// Get the records table.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    Table<const Id, Fragment<T>>& getRecords() {
      return this->records;
    }
    /// <summary>
    /// Get the symbol node.
    /// </summary>
    /// <returns>Returns the symbol node.</returns>
    Node<T>* const getNode() const {
      return this->node;
    }
    /// <summary>
    /// Set the symbol node.
    /// </summary>
    /// <param name="node">Symbol node.</param>
    void setNode(Node<T>* const node) {
      this->node = node;
    }
  };
}
