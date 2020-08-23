/// Copyright (c) 2020 Silas B. Domingos
/// This source code is licensed under the MIT License as described in the file LICENSE.
///
#pragma once

#include "spl/core.hpp"
#include "spl/math.hpp"
#include "spl/exceptions.hpp"
#include "spl/interfaces.hpp"
#include "spl/metadata.hpp"
#include "spl/strings.hpp"
#include "spl/arrays.hpp"
#include "spl/hashes.hpp"
#include "spl/hashtables.hpp"
#include "spl/prefixtrees.hpp"
#include "spl/types.hpp"

namespace Schemo {
  /// <summary>
  /// SPL Id type.
  /// </summary>
  using Id = SPL::Id;
  /// <summary>
  /// SPL Size type.
  /// </summary>
  using Size = SPL::Size;
  /// <summary>
  /// SPL Index type.
  /// </summary>
  using Index = SPL::Index;
  /// <summary>
  /// SPL ANSI String type.
  /// </summary>
  using AnsiString = SPL::AnsiString;
  /// <summary>
  /// Error class declaration.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Error;
  /// <summary>
  /// Token class declaration.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Token;
  /// <summary>
  /// Symbol class declaration.
  /// </summary>
  /// <typeparam name="T">Character type.</typeparam>
  template<typename T>
  class Symbol;
}
