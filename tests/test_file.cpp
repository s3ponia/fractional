//
// Created by Linux Oid on 07.05.2020.
//

#include <iostream>
#include <boost/test/minimal.hpp>
#include "fractional.hpp"

#define EPS 1e-10L

using floating_type = long double;

template<class T>
void test_overflow_multiply_max() {
    using OverflowChecker = fractional::overflow::SignedCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::min();
    BOOST_CHECK(!OverflowChecker::CheckNegate(min));
    BOOST_CHECK(OverflowChecker::CheckNegate(max));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(-1, min));
    BOOST_CHECK(OverflowChecker::CheckMultiply(-1, max));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(2, max));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(2, min));
    BOOST_CHECK(!OverflowChecker::CheckPlus(min, min));
    BOOST_CHECK(!OverflowChecker::CheckPlus(max, max));
}

bool is_equal(long double a, long double b) {
    return std::abs(a - b) < EPS;
}

int test_main(int, char *[])             // note the name!
{
    using namespace fractional;
    using namespace fractional::overflow;
    std::cout << -std::numeric_limits<int>::max() << ' ' << -std::numeric_limits<int>::min() << ' '
              << std::numeric_limits<int>::min() << '\n';
    BOOST_CHECK(std::is_trivial<fraction>::value);
//    test_overflow_multiply_max<int>();
//    test_overflow_multiply_max<long>();
    test_overflow_multiply_max<unsigned>();

    return boost::exit_success;
}