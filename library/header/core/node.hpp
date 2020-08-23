/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./direction.hpp"
#include "./fragment.hpp"

namespace Schemo {
  /// <summary>
  /// Node class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Node final {
  private:
    /// <summary>
    /// Node type.
    /// </summary>
    Id type;
    /// <summary>
    /// Node fragment.
    /// </summary>
    Fragment<T> fragment;
    /// <summary>
    /// Node symbol.
    /// </summary>
    Symbol<T>* symbol;
    /// <summary>
    /// Left node.
    /// </summary>
    Node<T>* left;
    /// <summary>
    /// Right node.
    /// </summary>
    Node<T>* right;
    /// <summary>
    /// Next node.
    /// </summary>
    Node<T>* next;
  private:
    /// <summary>
    /// Exchange all properties from the given objects.
    /// </summary>
    /// <param name="source">Source object.</param>
    /// <param name="target">Target object.</param>
    friend void Swap(Node<T>& source, Node<T>& target) noexcept {
      using SPL::Swap;
      Swap(source.type, target.type);
      Swap(source.fragment, target.fragment);
      Swap(source.symbol, target.symbol);
      Swap(source.left, target.left);
      Swap(source.right, target.right);
      Swap(source.next, target.next);
    }
  public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    Node() :
      type(), fragment(), symbol(nullptr), left(nullptr), right(nullptr), next(nullptr) {}
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <param name="type">Node type.</param>
    /// <param name="fragment">Node fragment.</param>
    /// <param name="symbol">Symbol fragment.</param>
    template<typename V>
    Node(const V& type, const Fragment<T>& fragment = {}, Symbol<T>* const symbol = nullptr) :
      type(static_cast<Id>(type)), fragment(fragment), symbol(symbol), left(nullptr), right(nullptr), next(nullptr) {}
    /// <summary>
    /// Move constructor.
    /// </summary>
    /// <param name="other">Other instance.</param>
    Node(Node<T>&& other) noexcept : Node<T>(0) {
      Swap(*this, other);
    }
    /// <summary>
    /// Destructor.
    /// </summary>
    ~Node() {
      delete this->left;
      delete this->right;
      delete this->next;
    }
  public:
    /// <summary>
    /// Get the node type.
    /// </summary>
    /// <returns>Returns the node type.</returns>
    Id getType() const {
      return this->type;
    }
    /// <summary>
    /// Get the node type as the specified value type.
    /// </summary>
    /// <typeparam name="V">Value type.</typeparam>
    /// <returns>Returns the node type.</returns>
    template<typename V>
    const V getType() const {
      return static_cast<V>(this->getType());
    }
    /// <summary>
    /// Get the fragment associated to the node.
    /// </summary>
    /// <returns>Returns the node fragment.</returns>
    const Fragment<T>& getFragment() const {
      return this->fragment;
    }
    /// <summary>
    /// Get the symbol associated to the node.
    /// </summary>
    /// <returns>Returns the node symbol.</returns>
    const Symbol<T>* getSymbol() const {
      return this->symbol;
    }
    /// <summary>
    /// Get the left node.
    /// </summary>
    /// <returns>Returns the left node.</returns>
    Node<T>* const getLeft() const {
      return this->left;
    }
    /// <summary>
    /// Set the left node.
    /// </summary>
    /// <param name="node">New left node.</param>
    void setLeft(Node<T>* const node) {
      this->left = node;
    }
    /// <summary>
    /// Get the right node.
    /// </summary>
    /// <returns>Returns the right node.</returns>
    Node<T>* const getRight() const {
      return this->right;
    }
    /// <summary>
    /// Set the right node.
    /// </summary>
    /// <param name="node">New right node.</param>
    void setRight(Node<T>* const node) {
      this->right = node;
    }
    /// <summary>
    /// Get the next node.
    /// </summary>
    /// <returns>Returns the next node.</returns>
    Node<T>* const getNext() const {
      return this->next;
    }
    /// <summary>
    /// Set the next node.
    /// </summary>
    /// <param name="node">New next node.</param>
    void setNext(Node<T>* const node) {
      this->next = node;
    }
    /// <summary>
    /// Get the node that corresponds to the given direction.
    /// </summary>
    /// <typeparam name="D">Direction type.</typeparam>
    /// <returns>Returns the corresponding node.</returns>
    template<Direction D>
    Node<T>* const get() const {
      if constexpr (D == Direction::Left) {
        return this->getLeft();
      }
      else if constexpr (D == Direction::Right) {
        return this->getRight();
      }
      else {
        return this->getNext();
      }
    }
    /// <summary>
    /// Set the node based on the given direction type.
    /// </summary>
    /// <typeparam name="D">Direction type.</typeparam>
    /// <param name="node">New node.</param>
    template<Direction D>
    void set(Node<T>* const node) {
      if constexpr (D == Direction::Left) {
        this->setLeft(node);
      }
      else if constexpr (D == Direction::Right) {
        this->setRight(node);
      }
      else {
        this->setNext(node);
      }
    }
  public:
    /// <summary>
    /// Assign all properties from the given node.
    /// </summary>
    /// <param name="other">Other instance.</param>
    /// <returns>Returns the instance itself.</returns>
    Node<T>& operator = (Node<T> other) noexcept {
      Swap(*this, other);
      return *this;
    }
  };
}
