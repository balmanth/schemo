/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./types.hpp"

namespace Schemo {
  /// <summary>
  /// Location class.
  /// </summary>
  class Location final {
  private:
    /// <summary>
    /// Line number.
    /// </summary>
    Index line;
    /// <summary>
    /// Column number.
    /// </summary>
    Index column;
  public:
    /// <summary>
    /// Default initialized constructor.
    /// </summary>
    /// <param name="line">Location line.</param>
    /// <param name="column">Location column.</param>
    Location(const Index line = 0, const Index column = 0) :
      line(line), column(column) {}
  public:
    /// <summary>
    /// Get the line number.
    /// </summary>
    /// <returns>Returns the line number.</returns>
    Index getLine() const {
      return this->line;
    }
    /// <summary>
    /// Get the column number.
    /// </summary>
    /// <returns>Returns the column number.</returns>
    Index getColumn() const {
      return this->column;
    }
  };
}
