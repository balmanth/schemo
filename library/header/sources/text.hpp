/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"
#include "./base.hpp"

namespace Schemo::Sources {
  /// <summary>
  /// Text source class.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Text final : public Base<T> {
  private:
    /// <summary>
    /// State entity class.
    /// </summary>
    class State {
    public:
      /// <summary>
      /// State offset.
      /// </summary>
      Size offset = 0;
      /// <summary>
      /// State line.
      /// </summary>
      Index line = 0;
      /// <summary>
      /// State column.
      /// </summary>
      Index column = 0;
    };
  private:
    /// <summary>
    /// String source.
    /// </summary>
    const SPL::String<T>& source;
    /// <summary>
    /// State stack.
    /// </summary>
    SPL::ArrayList<State> states;
    /// <summary>
    /// Current state.
    /// </summary>
    State state;
  public:
    /// <summary>
    /// Initialized constructor.
    /// </summary>
    /// <param name="source">Input source.</param>
    /// <param name="context">Source context.</param>
    Text(SPL::String<T>& source, Context<T>& context) :
      source(source), Base<T>(context) {}
  public:
    /// <summary>
    /// Check whether or not the source has a value.
    /// </summary>
    /// <returns>Returns true when the value exists, false otherwise.</returns>
    bool hasValue() const override {
      return this->state.offset < this->source.getLength();
    }
    /// <summary>
    /// Get the current value.
    /// </summary>
    /// <returns>Returns the current value.</returns>
    Id getValue() const override {
      return static_cast<Id>(this->source[this->state.offset]);
    }
    /// <summary>
    /// Get the current offset.
    /// </summary>
    /// <returns>Returns the current offset.</returns>
    Size getOffset() const override {
      return this->state.offset;
    }
    /// <summary>
    /// Get a temporary fragment based on the current state.
    /// </summary>
    /// <returns>Returns the temporary fragment.</returns>
    Fragment<T> getNewFragment() const override {
      if (!this->states.isEmpty()) {
        const auto& state = this->states[this->states.getLength() - 1];
        const auto length = this->state.offset - state.offset;
        if (length > 0) {
          auto location = Location(state.line, state.column);
          return { this->source, state.offset, length, location };
        }
      }
      const auto location = Location(this->state.line, this->state.column);
      const auto length = this->state.offset + 1 <= this->source.getLength() ? 1U : 0U;
      return { this->source, this->state.offset, length, location };
    }
    /// <summary>
    /// Push the current state.
    /// </summary>
    void pushState() override {
      this->states.add(this->state);
    }
    /// <summary>
    /// Restore the previous state.
    /// </summary>
    void restoreState() override {
      this->state = this->states[this->states.getLength() - 1];
    }
    /// <summary>
    /// Pop the previous state.
    /// </summary>
    void popState() override {
      this->states.remove(this->states.getLength() - 1);
    }
    /// <summary>
    /// Move to the next state.
    /// </summary>
    void nextState() override {
      if (this->getValue() != Id('\n')) {
        this->state.column++;
      }
      else {
        this->state.column = 0;
        this->state.line++;
      }
      this->state.offset++;
    }
  };
}
