/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../core/types.hpp"
#include "../core/flags.hpp"
#include "../core/table.hpp"
#include "../core/output.hpp"
#include "../core/node.hpp"

namespace Schemo {
  /// <summary>
  /// Source interface.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Source {
  public:
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~Source() = default;
  public:
    /// <summary>
    /// Determines whether or not the source has a value.
    /// </summary>
    /// <returns>Returns true when the value exists, false otherwise.</returns>
    virtual bool hasValue() const = 0;
    /// <summary>
    /// Get the current value.
    /// </summary>
    /// <returns>Returns the current value.</returns>
    virtual Id getValue() const = 0;
    /// <summary>
    /// Get the current value offset.
    /// </summary>
    /// <returns>Returns the current value offset.</returns>
    virtual Size getOffset() const = 0;
    /// <summary>
    /// Get a temporary fragment based on the current state.
    /// </summary>
    /// <returns>Returns the temporary fragment.</returns>
    virtual Fragment<T> getNewFragment() const = 0;
    /// <summary>
    /// Get a temporary node based on the current state.
    /// </summary>
    /// <param name="type">Node type (When omitted with -1, it will use the output code instead).</param>
    /// <returns>Returns the temporary node.</returns>
    virtual Node<T> getNewNode(const Id type = -1) const = 0;
    /// <summary>
    /// Get a new temporary symbol based on the current state.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    /// <returns>Returns the temporary symbol.</returns>
    virtual Symbol<T> getNewSymbol(const Id type = -1) const = 0;
    /// <summary>
    /// Get the current symbol flags in the constant form.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    virtual const Flags& getSymbolFlags() const = 0;
    /// <summary>
    /// Get the current symbol flags.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    virtual Flags& getSymbolFlags() = 0;
    /// <summary>
    /// Get the current symbol records in the constant form.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    virtual const Table<const Id, Fragment<T>>& getSymbolRecords() const = 0;
    /// <summary>
    /// Get the current symbol records.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    virtual Table<const Id, Fragment<T>>& getSymbolRecords() = 0;
    /// <summary>
    /// Get the current symbol node.
    /// </summary>
    /// <returns>Returns the symbol node.</returns>
    virtual Node<T>* const getSymbolNode() const = 0;
    /// <summary>
    /// Set the current symbol node.
    /// </summary>
    /// <param name="node">New node.</param>
    virtual void setSymbolNode(Node<T>* const node) = 0;
    /// <summary>
    /// Get the current output in the constant form.
    /// </summary>
    /// <returns>Returns the current output.</returns>
    virtual const Output<T>& getOutput() const = 0;
    /// <summary>
    /// Get the current output.
    /// </summary>
    /// <returns>Returns the current output.</returns>
    virtual Output<T>& getOutput() = 0;
    /// <summary>
    /// Emit a new error based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="code">Error code (When omitted with -1, it will use the output code instead).</param>
    virtual void emitError(const Id code = -1) = 0;
    /// <summary>
    /// Emit a new token based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="code">Token code (When omitted with -1, it will use the output code instead).</param>
    virtual void emitToken(const Id code = -1) = 0;
    /// <summary>
    /// Emit a new inner symbol based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    virtual void emitSymbol(const Id type = -1) = 0;
    /// <summary>
    /// Push a symbol corresponding to the current state.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    virtual void pushSymbol(const Id type = -1) = 0;
    /// <summary>
    /// Pop the current symbol.
    /// </summary>
    virtual void popSymbol() = 0;
    /// <summary>
    /// Push the current state.
    /// </summary>
    virtual void pushState() = 0;
    /// <summary>
    /// Restore the previous state.
    /// </summary>
    virtual void restoreState() = 0;
    /// <summary>
    /// Pop the previous state.
    /// </summary>
    virtual void popState() = 0;
    /// <summary>
    /// Move to the next state.
    /// </summary>
    virtual void nextState() = 0;
  };
}
