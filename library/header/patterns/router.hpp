/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace Schemo::Patterns {
  /// <summary>
  /// Router pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="...P">Path types.</typeparam>
  template<typename T, typename ...P>
  class Router final : public Pattern<T> {
  private:
    /// <summary>
    /// Tuple type.
    /// </summary>
    using Tuple = SPL::Tuple<typename P::template Pattern<T>...>;
    /// <summary>
    /// PrefixMap type.
    /// </summary>
    using PrefixMap = SPL::PrefixMap<const Id*, Pattern<T>*>;
    /// <summary>
    /// PrefixNode type.
    /// </summary>
    using PrefixNode = SPL::PrefixTrees::Node<const Id*, Pattern<T>*>;
  private:
    /// <summary>
    /// Patterns tuple.
    /// </summary>
    static Tuple patterns;
    /// <summary>
    /// Options map. 
    /// </summary>
    const static PrefixMap options;
  private:
    /// <summary>
    /// Add the template path that corresponds to the given index into the map.
    /// </summary>
    /// <typeparam name="I">Path index.</typeparam>
    /// <param name="map">Map instance.</param>
    template<Size I>
    static void addPath(PrefixMap& map) {
      if constexpr (I < sizeof...(P)) {
        map.set(SPL::Types::PickType<I, P...>::values, &Router<T, P...>::patterns.get<I>());
        Router<T, P...>::addPath<I + 1>(map);
      }
    }
    /// <summary>
    /// Get a new map containing all the template paths.
    /// </summary>
    /// <returns>Returns the new map.</returns>
    static const PrefixMap getPathMap() {
      PrefixMap map;
      if constexpr (sizeof...(P) > 0) {
        Router<T, P...>::addPath<0>(map);
      }
      return map;
    }
  private:
    /// <summary>
    /// Find the node that corresponds to the path in the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <param name="node">Input node.</param>
    /// <returns>Returns the corresponding node or null when no nodes where found.</returns>
    const PrefixNode* find(Source<T>& source, const PrefixNode* node) const {
      source.pushState();
      while (source.hasValue() && node != nullptr) {
        int comparison = SPL::Compare(node->getKey(), source.getValue());
        if (comparison < 0) {
          node = node->getLeftNode();
        }
        else if (comparison > 0) {
          node = node->getRightNode();
        }
        else {
          if (node->isTerminal()) {
            source.popState();
            return node;
          }
          source.nextState();
          node = node->getDownNode();
        }
      }
      source.restoreState();
      source.popState();
      return nullptr;
    }
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      const PrefixNode* node = Router<T, P...>::options;
      const PrefixNode* longest = nullptr;
      while ((node = this->find(source, node)) != nullptr) {
        longest = node;
        node = node->getDownNode();
        source.nextState();
      }
      if (longest != nullptr) {
        return longest->value->consume(source);
      }
      return false;
    }
  };
  /// <summary>
  /// Initialize all patterns.
  /// </summary>
  template<typename T, typename ...P>
  typename Router<T, P...>::Tuple Router<T, P...>::patterns = { P::template Pattern<T>()... };
  /// <summary>
  /// Initialize all options.
  /// </summary>
  template<typename T, typename ...P>
  const typename Router<T, P...>::PrefixMap Router<T, P...>::options = Router<T, P...>::getPathMap();
}
