/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "./sources/text.hpp"
#include "./sources/tokens.hpp"

namespace Schemo {
  /// <summary>
  /// Text source.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using TextSource = Sources::Text<T>;
  /// <summary>
  /// Token source.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  using TokenSource = Sources::Tokens<T>;
}
