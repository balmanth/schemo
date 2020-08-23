/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Nodes {
  /// <summary>
  /// Pivot tree pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="N">Node type.</typeparam>
  /// <typeparam name="A">Active direction.</typeparam>
  /// <typeparam name="L">Link direction.</typeparam>
  /// <typeparam name="P">Pivot pattern type.</typeparam>
  /// <typeparam name="...E">Expected pattern types.</typeparam>
  template<typename T, auto N, Direction A, Direction L, template<typename> class P, template<typename> class ...E>
  class Pivot final : public Pattern<T> {
    static_assert(A != L, "Active direction must not be equals to the Link direction.");
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      bool result = P<T>().consume(source);
      if (result) {
        auto model = source.getNewNode(static_cast<Id>(N));
        auto& output = source.getOutput();
        auto* active = output.getNode();
        output.setNode(nullptr);
        if ((result = Flows::Expect<T, E...>().consume(source))) {
          auto* child = new Node<T>(SPL::Move(model));
          child->set<A>(active);
          child->set<L>(output.getNode());
          output.setNode(child);
        }
        else {
          delete output.getNode();
          output.setNode(active);
        }
      }
      return result;
    }
  };
}
