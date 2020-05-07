//
// Created by Linux Oid on 07.05.2020.
//

#include <iostream>
#include <boost/test/minimal.hpp>
#include "fractional.hpp"

#define EPS 1e-10L

using floating_type = long double;

bool is_equal(long double a, long double b) {
    return (a - b) < EPS;
}

int test_main(int, char *[])             // note the name!
{
    using namespace fractional;
    using namespace fractional::overflow;
    std::cout << -78 % 33;
    BOOST_CHECK(std::is_trivial<fraction>::value);
    Fractional<int, NoCheck> t{2, 1};
    auto f = t;
    f = t + f;
    BOOST_CHECK(is_equal(f, 4));

    return boost::exit_success;
}