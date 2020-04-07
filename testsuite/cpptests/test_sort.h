/*
 *  test_sort.h
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

#ifndef TEST_SORT_H
#define TEST_SORT_H

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// C++ includes:
#include <algorithm>
#include <vector>

// Includes from libnestutil:
#include "sort.h"

namespace nest
{
/**
 * Wrapper for quicksort3way.
 *
 * When calling nest::sort() directly it is impossible to sort with the
 * built in quicksort3way from tests. This is because if NEST is compiled
 * with Boost support, nest::sort() sorts with Boost, and if NEST is not
 * compiled with Boost, nest::sort() calls quicksort3way, but the Boost
 * tests are not compiled.
 */
void
nest_quicksort( BlockVector< int >& bv0, BlockVector< int >& bv1 )
{
  nest::quicksort3way( bv0, bv1, 0, bv0.size() - 1 );
}

/**
 * Fixture filling two BlockVectors and a vector with lineary decreasing numbers.
 * The vector is then sorted.
 */
struct fill_bv_vec_linear
{
  fill_bv_vec_linear()
    : N( 20000 )
    , bv_sort( N )
    , bv_perm( N )
    , vec_sort( N )
  {
    for ( int i = 0; i < N; ++i )
    {
      int element = N - i;
      bv_sort[ i ] = element;
      bv_perm[ i ] = element;
      vec_sort[ i ] = element;
    }
    std::sort( vec_sort.begin(), vec_sort.end() );
  }

  const int N;
  BlockVector< int > bv_sort;
  BlockVector< int > bv_perm;
  std::vector< int > vec_sort;
};

/**
 * Fixture filling two BlockVectors and a vector with random numbers.
 * The vector is then sorted.
 */
struct fill_bv_vec_random
{
  fill_bv_vec_random()
    : N( 20000 )
    , bv_sort( N )
    , bv_perm( N )
    , vec_sort( N )
  {
    for ( int i = 0; i < N; ++i )
    {
      const size_t k = std::rand() % N;
      bv_sort[ i ] = k;
      bv_perm[ i ] = k;
      vec_sort[ i ] = k;
    }
    std::sort( vec_sort.begin(), vec_sort.end() );
  }

  const int N;
  BlockVector< int > bv_sort;
  BlockVector< int > bv_perm;
  std::vector< int > vec_sort;
};

BOOST_AUTO_TEST_SUITE( test_sort )

/**
 * Tests whether two arrays with randomly generated numbers are sorted
 * correctly when sorting with the built-in quicksort.
 */
BOOST_FIXTURE_TEST_CASE( test_quicksort_random, fill_bv_vec_random )
{
  nest_quicksort( bv_sort, bv_perm );

  BOOST_REQUIRE( std::is_sorted( bv_sort.begin(), bv_sort.end() ) );
  BOOST_REQUIRE( std::is_sorted( bv_perm.begin(), bv_perm.end() ) );

  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_sort.begin() ) );
  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_perm.begin() ) );
}

/**
 * Tests whether two arrays with linearly decreasing numbers are sorted
 * correctly when sorting with the built-in quicksort.
 */
BOOST_FIXTURE_TEST_CASE( test_quicksort_linear, fill_bv_vec_linear )
{
  nest_quicksort( bv_sort, bv_perm );

  BOOST_REQUIRE( std::is_sorted( bv_sort.begin(), bv_sort.end() ) );
  BOOST_REQUIRE( std::is_sorted( bv_perm.begin(), bv_perm.end() ) );

  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_sort.begin() ) );
  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_perm.begin() ) );
}

/**
 * Tests whether two arrays with randomly generated numbers are sorted
 * correctly when sorting with Boost.
 */
BOOST_FIXTURE_TEST_CASE( test_boost_random, fill_bv_vec_random )
{
  // Making sure we are sorting with boost
  static_assert( HAVE_BOOST, "Compiling Boost tests, but HAVE_BOOST!=1." );

  sort( bv_sort, bv_perm );

  BOOST_REQUIRE( std::is_sorted( bv_sort.begin(), bv_sort.end() ) );
  BOOST_REQUIRE( std::is_sorted( bv_perm.begin(), bv_perm.end() ) );

  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_sort.begin() ) );
  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_perm.begin() ) );
}

/**
 * Tests whether two arrays with linearly increasing numbers are sorted
 * correctly when sorting with Boost.
 */
BOOST_FIXTURE_TEST_CASE( test_boost_linear, fill_bv_vec_linear )
{
  // Making sure we are sorting with boost
  static_assert( HAVE_BOOST, "Compiling Boost tests, but HAVE_BOOST!=1." );

  sort( bv_sort, bv_perm );

  BOOST_REQUIRE( std::is_sorted( bv_sort.begin(), bv_sort.end() ) );
  BOOST_REQUIRE( std::is_sorted( bv_perm.begin(), bv_perm.end() ) );

  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_sort.begin() ) );
  BOOST_REQUIRE( std::equal( vec_sort.begin(), vec_sort.end(), bv_perm.begin() ) );
}

BOOST_AUTO_TEST_SUITE_END()

} // of namespace nest

#endif /* TEST_SORT_H */
