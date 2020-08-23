/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./flags.hpp"
#include "./table.hpp"
#include "./node.hpp"

namespace Schemo {
  /// <summary>
  /// Output class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Output final {
  private:
    /// <summary>
    /// Output code.
    /// </summary>
    Id code;
    /// <summary>
    /// Output flags.
    /// </summary>
    Flags flags;
    /// <summary>
    /// Output records.
    /// </summary>
    Table<const Id, Fragment<T>> records;
    /// <summary>
    /// Output node.
    /// </summary>
    Node<T>* node;
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Output() :
      code(0), node(nullptr) {}
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Output() {
      delete this->node;
    }
  public:
    /// <summary>
    /// Get the output code.
    /// </summary>
    /// <returns>Returns the output code.</returns>
    Id getCode() const {
      return this->code;
    }
    /// <summary>
    /// Set the output code.
    /// </summary>
    /// <param name="code">New output code.</param>
    void setCode(const Id code) {
      this->code = code;
    }
    /// <summary>
    /// Get the output flags in the constant form.
    /// </summary>
    /// <returns>Returns the output flags.</returns>
    const Flags& getFlags() const {
      return this->flags;
    }
    /// <summary>
    /// Get the output flags.
    /// </summary>
    /// <returns>Returns the output flags.</returns>
    Flags& getFlags() {
      return this->flags;
    }
    /// <summary>
    /// Get the output records in the constant form.
    /// </summary>
    /// <returns>Returns the output records.</returns>
    const Table<const Id, Fragment<T>>& getRecords() const {
      return this->records;
    }
    /// <summary>
    /// Get the output records.
    /// </summary>
    /// <returns>Returns the output records.</returns>
    Table<const Id, Fragment<T>>& getRecords() {
      return this->records;
    }
    /// <summary>
    /// Get the output node.
    /// </summary>
    /// <returns>Returns the output node.</returns>
    Node<T>* const getNode() const {
      return this->node;
    }
    /// <summary>
    /// Set the output node.
    /// </summary>
    /// <param name="node">Output node.</param>
    void setNode(Node<T>* const node) {
      this->node = node;
    }
  };
}
