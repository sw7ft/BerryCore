// Locale support -*- C++ -*-

// Copyright (C) 2002-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/ctype_base.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h.

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const unsigned char*	__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef short		mask;
    static const mask upper    	= _UP_;
    static const mask lower 	= _LO_;
    static const mask alpha 	= _LO_ | _UP_ | _XA_;
    static const mask digit 	= _DI_;
    static const mask xdigit 	= _XD_;
    static const mask space 	= _CN_ | _SP_ | _XS_;
    static const mask print 	= _DI_ | _LO_ | _PU_ | _SP_ | _UP_ | _XA_;
    static const mask graph 	= _DI_ | _LO_ | _PU_ | _UP_ | _XA_;
    static const mask cntrl 	= _BB_;
    static const mask punct 	= _PU_;
    static const mask alnum 	= _DI_ | _LO_ | _UP_ | _XA_;
#if __cplusplus >= 201103L
    static const mask blank	= _SP_ | _XB_;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
