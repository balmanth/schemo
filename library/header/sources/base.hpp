/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace Schemo::Sources {
  /// <summary>
  /// Base source class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Base : public Source<T> {
  private:
    /// <summary>
    /// Current symbol.
    /// </summary>
    Symbol<T>* symbol;
    /// <summary>
    /// Token stack.
    /// </summary>
    SPL::List<Token<T>>& tokens;
    /// <summary>
    /// Error stack.
    /// </summary>
    SPL::List<Error<T>>& errors;
    /// <summary>
    /// Current output.
    /// </summary>
    Output<T> output;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="context">Source context.</param>
    Base(Context<T>& context) :
      symbol(&context.getSymbol()), tokens(context.getTokens()), errors(context.getErrors()) {};
  public:
    /// <summary>
    /// Get a temporary node based on the current state.
    /// </summary>
    /// <param name="type">Node type (When omitted with -1, it will use the output code instead).</param>
    /// <returns>Returns the temporary node.</returns>
    Node<T> getNewNode(const Id type = -1) const final override {
      auto value = type == -1 ? this->output.getCode() : type;
      auto fragment = this->getNewFragment();
      return { value, fragment, this->symbol };
    }
    /// <summary>
    /// Get a new temporary symbol based on the current state.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    /// <returns>Returns the temporary symbol.</returns>
    Symbol<T> getNewSymbol(const Id type = -1) const final override {
      auto value = type == -1 ? this->output.getCode() : type;
      auto flags = this->output.getFlags();
      auto fragment = this->getNewFragment();
      auto records = this->output.getRecords();
      Symbol<T> symbol = { value, flags, fragment, this->symbol };
      SPL::Swap(symbol.getRecords(), records);
      return symbol;
    }
    /// <summary>
    /// Get the current symbol flags in the constant form.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    const Flags& getSymbolFlags() const final override {
      return this->symbol->getFlags();
    }
    /// <summary>
    /// Get the current symbol flags.
    /// </summary>
    /// <returns>Returns the symbol flags.</returns>
    Flags& getSymbolFlags() final override {
      return this->symbol->getFlags();
    }
    /// <summary>
    /// Get the current symbol records in the constant form.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    const Table<const Id, Fragment<T>>& getSymbolRecords() const final override {
      return this->symbol->getRecords();
    }
    /// <summary>
    /// Get the current symbol records.
    /// </summary>
    /// <returns>Returns the symbol records.</returns>
    Table<const Id, Fragment<T>>& getSymbolRecords() final override {
      return this->symbol->getRecords();
    }
    /// <summary>
    /// Get the current symbol node.
    /// </summary>
    /// <returns>Returns the current symbol node.</returns>
    Node<T>* const getSymbolNode() const final override {
      return this->symbol->getNode();
    }
    /// <summary>
    /// Set the current symbol node.
    /// </summary>
    /// <param name="node">New node.</param>
    void setSymbolNode(Node<T>* const node) final override {
      this->symbol->setNode(node);
    }
    /// <summary>
    /// Get the current output in the constant form.
    /// </summary>
    /// <returns>Returns the current output.</returns>
    const Output<T>& getOutput() const final override {
      return this->output;
    }
    /// <summary>
    /// Get the current output.
    /// </summary>
    /// <returns>Returns the current output.</returns>
    Output<T>& getOutput() final override {
      return this->output;
    }
    /// <summary>
    /// Emit a new error based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="code">Error code (When omitted with -1, it will use the output code instead).</param>
    void emitError(const Id code = -1) final override {
      auto value = code == -1 ? this->output.getCode() : code;
      auto fragment = this->getNewFragment();
      this->errors.add({ value, fragment });
    }
    /// <summary>
    /// Emit a new token based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="code">Token code (When omitted with -1, it will use the output code instead).</param>
    void emitToken(const Id code = -1) final override {
      auto value = code == -1 ? this->output.getCode() : code;
      auto fragment = this->getNewFragment();
      this->tokens.add({ value, fragment });
    }
    /// <summary>
    /// Emit a new symbol based on the current state.
    /// This action can't be undone during the flow.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    void emitSymbol(const Id type = -1) final override {
      auto& table = this->symbol->getSymbols();
      auto symbol = this->getNewSymbol(type);
      auto fragment = this->getNewFragment();
      table.add(fragment, SPL::Move(symbol));
    }
    /// <summary>
    /// Push a symbol corresponding to the current state.
    /// </summary>
    /// <param name="type">Symbol type (When omitted with -1, it will use the output code instead).</param>
    void pushSymbol(const Id type = -1) final override {
      auto& table = this->symbol->getSymbols();
      auto symbol = this->getNewSymbol(type);
      auto fragment = this->getNewFragment();
      table.add(fragment, SPL::Move(symbol));
      auto& colissions = table.get(fragment);
      this->symbol = &colissions[colissions.getLength() - 1];
    }
    /// <summary>
    /// Pop the current symbol.
    /// </summary>
    void popSymbol() final override {
      this->symbol = this->symbol->getParent();
    }
  };
}
