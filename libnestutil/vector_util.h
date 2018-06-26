/*
 *  vector_util.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef VECTOR_UTIL_H
#define VECTOR_UTIL_H

#include <vector>

namespace vector_util
{

template < typename T >
inline void
grow( std::vector< T >& v )
{
  // use 1.5 growth strategy (see, e.g.,
  // https://github.com/facebook/folly/blob/master/folly/docs/FBVector.md)
  if ( v.size() == v.capacity() )
  {
    double kb_to_gb = 1073741824.;
    double v_memory = sizeof(std::vector< T >) / kb_to_gb + sizeof( T ) * ( v.size() / kb_to_gb ); // Gigabytes
    if ( v_memory < 1. ) {
      v.reserve( ( v.size() * 3 + 1 ) / 2 );
    }
    else if ( v_memory < 5. ) {
      v.reserve( ( v.size() * 5 + 1 ) / 4 );
    }
    else {
      v.reserve( ( v.size() * 11 + 1 ) / 10 );
    }
  }
}

} // namespace vector_util

#endif // VECTOR_UTIL_H
