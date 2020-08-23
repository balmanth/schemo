/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./symbol.hpp"
#include "./token.hpp"
#include "./error.hpp"
#include "./node.hpp"

namespace Schemo {
  /// <summary>
  /// Context class.
  /// </summary>
  /// <typeparam name="T">Character type</typeparam>
  template<typename T>
  class Context final {
  private:
    /// <summary>
    /// Context symbol.
    /// </summary>
    Symbol<T> symbol;
    /// <summary>
    /// Context tokens.
    /// </summary>
    TokenList<T> tokens;
    /// <summary>
    /// Context errors.
    /// </summary>
    ErrorList<T> errors;
  public:
    /// <summary>
    /// Get the context symbol.
    /// </summary>
    /// <returns>Returns the context symbol.</returns>
    Symbol<T>& getSymbol() {
      return this->symbol;
    }
    /// <summary>
    /// Get the context node.
    /// </summary>
    /// <returns>Returns the context node.</returns>
    Node<T>* const getNode() {
      return this->symbol.getNode();
    }
    /// <summary>
    /// Get the context symbols.
    /// </summary>
    /// <returns>Returns the context symbols.</returns>
    Table<const Identifier<T>, Symbol<T>, &Identifier<T>::Hash>& getSymbols() {
      return this->symbol.getSymbols();
    }
    /// <summary>
    /// Get the context records.
    /// </summary>
    /// <returns>Returns the context record.</returns>
    Table<const Id, Fragment<T>>& getRecords() {
      return this->symbol.getRecords();
    }
    /// <summary>
    /// Get the context tokens.
    /// </summary>
    /// <returns>Returns the context tokens.</returns>
    TokenList<T>& getTokens() {
      return this->tokens;
    }
    /// <summary>
    /// Add a new token into the token list.
    /// </summary>
    /// <param name="token">New token.</param>
    /// <returns>Returns the current number of tokens.</returns>
    Size addToken(const Token<T>& token) {
      return this->tokens.add(token);
    }
    /// <summary>
    /// Get the context errors.
    /// </summary>
    /// <returns>Returns the context errors.</returns>
    ErrorList<T>& getErrors() {
      return this->errors;
    }
    /// <summary>
    /// Add a new error into the error list.
    /// </summary>
    /// <param name="error">New error.</param>
    /// <returns>Returns the current number of errors.</returns>
    Size addError(const Error<T>& error) {
      return this->errors.add(error);
    }
  };
}
