//
// Created by Linux Oid on 07.05.2020.
//

#include <iostream>
#include <boost/test/minimal.hpp>
#include "fractional.hpp"

#define EPS 1e-10L

using floating_type = long double;
using is_signed = std::true_type;
using is_unsigned = std::false_type;

template<class T>
void test_overflow_multiply_max(is_signed) {
    using OverflowChecker = fractional::overflow::SignedCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    BOOST_CHECK(OverflowChecker::CheckNegate(min) == OverflowChecker::CheckMultiply(-1, min));
    BOOST_CHECK(OverflowChecker::CheckNegate(max) == OverflowChecker::CheckMultiply(-1, max));
    BOOST_CHECK(OverflowChecker::CheckNegate(0));

    BOOST_CHECK(OverflowChecker::CheckPlus(0, 0));
    BOOST_CHECK(OverflowChecker::CheckPlus(0, 1));
    BOOST_CHECK(OverflowChecker::CheckPlus(1, 0));
    BOOST_CHECK(OverflowChecker::CheckPlus(1, 1));
    BOOST_CHECK(OverflowChecker::CheckPlus(min, max));
    BOOST_CHECK(!OverflowChecker::CheckPlus(max, max));

    BOOST_CHECK(OverflowChecker::CheckMultiply(0, 0));
    BOOST_CHECK(OverflowChecker::CheckMultiply(1, max));
    BOOST_CHECK(OverflowChecker::CheckMultiply(1, min));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(max, max));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(2, max));
}

template<class T>
void test_overflow_multiply_max(is_unsigned) {
    using OverflowChecker = fractional::overflow::SignedCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    BOOST_CHECK(OverflowChecker::CheckNegate(max) == OverflowChecker::CheckMultiply(-1, max));
    BOOST_CHECK(OverflowChecker::CheckNegate(0));

    BOOST_CHECK(OverflowChecker::CheckPlus(0, 0));
    BOOST_CHECK(OverflowChecker::CheckPlus(0, 1));
    BOOST_CHECK(OverflowChecker::CheckPlus(1, 0));
    BOOST_CHECK(OverflowChecker::CheckPlus(1, 1));
    BOOST_CHECK(OverflowChecker::CheckPlus(min, max));
    BOOST_CHECK(!OverflowChecker::CheckPlus(-1, 1));
    BOOST_CHECK(!OverflowChecker::CheckPlus(max, max));

    BOOST_CHECK(OverflowChecker::CheckMultiply(0, 0));
    BOOST_CHECK(OverflowChecker::CheckMultiply(1, max));
    BOOST_CHECK(OverflowChecker::CheckMultiply(1, min));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(max, max));
    BOOST_CHECK(!OverflowChecker::CheckMultiply(2, max));
}

template<class T>
void test_overflow_multiply_max() {
    test_overflow_multiply_max<T>(typename std::conditional<std::is_unsigned_v<T>, is_unsigned, is_signed>::type{});
}

bool is_equal(long double a, long double b) {
    return std::abs(a - b) < EPS;
}

int test_main(int, char *[])             // note the name!
{
    using namespace fractional;
    using namespace fractional::overflow;
    BOOST_CHECK(std::is_trivial<fraction>::value);
    test_overflow_multiply_max<char>();
    test_overflow_multiply_max<short>();
    test_overflow_multiply_max<int>();
    test_overflow_multiply_max<long>();
    test_overflow_multiply_max<int8_t>();
    test_overflow_multiply_max<int16_t>();
    test_overflow_multiply_max<int32_t>();
    test_overflow_multiply_max<int64_t>();
    test_overflow_multiply_max<ptrdiff_t>();
    test_overflow_multiply_max<unsigned>();
    test_overflow_multiply_max<uint8_t>();
    test_overflow_multiply_max<uint16_t>();
    test_overflow_multiply_max<uint32_t>();
    test_overflow_multiply_max<uint64_t>();

    test_overflow_multiply_max<float>();
    test_overflow_multiply_max<double>();
    test_overflow_multiply_max<long double>();

    return boost::exit_success;
}