//
// Created by Linux Oid on 07.05.2020.
//

#include <iostream>
#include <charconv>
#include <boost/test/minimal.hpp>
#include "fractional.hpp"

#define EPS 1e-10L

#define TEST_INTEGRAL(function) do {\
function<signed char>();\
function<short>();\
function<int>();\
function<long>();\
function<long long>();\
function<int8_t>();\
function<int16_t>();\
function<int32_t>();\
function<int64_t>();\
function<ptrdiff_t>();\
function<char>();\
function<unsigned char>();\
function<unsigned short>();\
function<unsigned int>();\
function<unsigned long>();\
function<unsigned long long>();\
function<uint8_t>();\
function<uint16_t>();\
function<uint32_t>();\
function<uint64_t>();}while(0)

using floating_type = long double;
using is_signed = std::true_type;
using is_unsigned = std::false_type;

template<class T>
void test_bitwise_max(is_signed) {
    using OverflowChecker = fractional::overflow::IntegralCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift(max, 1));
    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift(min, -1));
    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift(min, 0));

    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift(1, -1));
    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift(-1, 1));
    BOOST_CHECK(OverflowChecker::CheckBitwiseLeftShift(1, 1));
}

template<class T>
void test_bitwise_max(is_unsigned) {
}


template<class T>
void test_bitwise_max() {
    using OverflowChecker = fractional::overflow::IntegralCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    test_bitwise_max<T>(typename std::conditional<std::is_unsigned_v<T>, is_unsigned, is_signed>::type{});
    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift((max >> 1u) + 1, 1));

    BOOST_CHECK(!OverflowChecker::CheckBitwiseLeftShift((max >> 1u) + 1, 1));
}

template<class T>
void test_overflow_max(is_signed) {
    using OverflowChecker = fractional::overflow::IntegralCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    BOOST_CHECK(OverflowChecker::CheckNegate(min) == OverflowChecker::CheckMultiply(-1, min));
}

template<class T>
void test_overflow_max(is_unsigned) {
}

template<class T>
void test_overflow_max() {
    using OverflowChecker = fractional::overflow::IntegralCheckOverflow<T>;
    auto max = std::numeric_limits<T>::max();
    auto min = std::numeric_limits<T>::lowest();
    if constexpr (std::is_integral_v<T>) {
        test_bitwise_max<T>();
    }
    test_overflow_max<T>(typename std::conditional<std::is_unsigned_v<T>, is_unsigned, is_signed>::type{});

    BOOST_CHECK(OverflowChecker::CheckIncrement(max) == OverflowChecker::CheckPlus(max, 1));
    BOOST_CHECK(OverflowChecker::CheckIncrement(min) == OverflowChecker::CheckPlus(min, 1));
    BOOST_CHECK(OverflowChecker::CheckDecrement(min) == OverflowChecker::CheckMinus(min, 1));
    BOOST_CHECK(OverflowChecker::CheckDecrement(max) == OverflowChecker::CheckMinus(max, 1));

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

void test_overflow_max() {
    TEST_INTEGRAL(test_overflow_max);
}

bool is_equal(long double a, long double b) {
    return std::abs(a - b) < EPS;
}

template<class fraction>
void test_fraction() {
    try {
        fraction t{2, 0};
    } catch (typename fraction::Checker::BinaryError const &er) {
        std::cout << er.lhs() << ' ' << er.rhs() << '\n';
    }
//    t = t + t;
}

int test_main(int, char *[]) {
    using namespace fractional;
    using namespace fractional::overflow;
    BOOST_CHECK(std::is_trivial<fraction>::value);

    test_fraction<fraction>();
    test_fraction<Fractional<int, overflow::NoCheck>>();

    test_overflow_max();

    return boost::exit_success;
}