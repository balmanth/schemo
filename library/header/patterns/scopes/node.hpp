/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Scopes {
  /// <summary>
  /// Node pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="A">Attachment direction.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, Direction A, template<typename> class ...P>
  class Node final : public Pattern<T> {
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
      const bool result = Flows::Expect<T, P...>().consume(source);
      auto* current = output.getNode();
      if (result) {
        if (active == nullptr) {
          active = current;
        }
        else {
          auto* parent = active;
          while (parent->get<A>() != nullptr) {
            parent = parent->get<A>();
          }
          parent->set<A>(current);
        }
      }
      else {
        delete current;
      }
      output.setNode(active);
      return result;
    }
  };
}
