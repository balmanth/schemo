/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Nodes {
  /// <summary>
  /// Replace pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="R">Replacement direction.</typeparam>
  /// <typeparam name="L">Link direction.</typeparam>
  /// <typeparam name="...E">Expected pattern types.</typeparam>
  template<typename T, auto N, Direction R, Direction L, template<typename> class ...E>
  class Replace final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      auto& output = source.getOutput();
      auto* active = output.getNode();
      output.setNode(nullptr);
      const bool result = Flows::Expect<T, E...>().consume(source);
      auto* current = output.getNode();
      if (result) {
        auto model = source.getNewNode(static_cast<Id>(N));
        auto* child = new Node<T>(SPL::Move(model));
        child->set<L>(current);
        if (active != nullptr) {
          auto* parent = child;
          while (parent->get<R>() != nullptr) {
            parent = parent->get<R>();
          }
          parent->set<R>(active);
        }
        active = child;
      }
      else {
        delete current;
      }
      output.setNode(active);
      return result;
    }
  };
}
