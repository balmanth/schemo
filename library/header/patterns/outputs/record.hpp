/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "../types.hpp"
#include "../flows/expect.hpp"

namespace Schemo::Patterns::Outputs {
  /// <summary>
  /// Record pattern.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  /// <typeparam name="R">Record code.</typeparam>
  /// <typeparam name="...P">Pattern types.</typeparam>
  template<typename T, auto R, template<typename> class ...P>
  class Record final : public Pattern<T> {
  public:
    /// <summary>
    /// Consume the pattern using the specified source.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <returns>Returns true when the pattern found and consumed, false otherwise.</returns>
    bool consume(Source<T>& source) override {
      if (source.hasValue()) {
        if (Flows::Expect<T, P...>().consume(source)) {
          auto& output = source.getOutput();
          auto& records = output.getRecords();
          const Id key = static_cast<Id>(R);
          const Fragment<T> value = source.getNewFragment();
          records.add(key, value);
          return true;
        }
      }
      return false;
    }
  };
}
