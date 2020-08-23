/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Symbols {
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
      if (Flows::Expect<T, P...>().consume(source)) {
        auto& output = source.getOutput();
        auto* active = source.getSymbolNode();
        auto* current = output.getNode();
        if (active == nullptr) {
          source.setSymbolNode(current);
        }
        else {
          while (active->get<A>() != nullptr) {
            active = active->get<A>();
          }
          active->set<A>(current);
        }
        output.setNode(nullptr);
        return true;
      }
      return false;
    }
  };
}
