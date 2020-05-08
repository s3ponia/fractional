//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_FRACTIONAL_HXX
#define FRACTIONNUMBER_FRACTIONAL_HXX

#include <numeric>
#include "utility.hpp"

using std::declval;
using namespace fractional;

template<class Fractional>
constexpr bool is_noexcept() {
    using _NType = typename Fractional::NaturalType;
    return noexcept(typename Fractional::PlusOperator{}(declval<_NType>(),
                                                        declval<_NType>())) &&
           noexcept(typename Fractional::DivideOperator{}(declval<_NType>(),
                                                          declval<_NType>())) &&
           noexcept(typename Fractional::MultiplyOperator{}(declval<_NType>(),
                                                            declval<_NType>())) &&
           noexcept(typename Fractional::NegateOperator{}(declval<_NType>())) &&
           noexcept(typename Fractional::MinusOperator{}(declval<_NType>(),
                                                         declval<_NType>())) &&
           noexcept(typename Fractional::ModulusOperator{}(declval<_NType>(),
                                                           declval<_NType>()));
}

/**
 * @param lhs = a/b
 * @param rhs = c/d
 * @return Simplified a/b + c/d -> (a * b/lcm + c * d/lcm)/lcm
 */
template<class _NType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
constexpr Fractional<_NType, _Checker, TEMPLATE_PARAMS>
operator+(const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &lhs,
          const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &rhs) noexcept(
is_noexcept<Fractional<_NType, _Checker, TEMPLATE_PARAMS>>()) {
    using Fract = Fractional<_NType, _Checker, TEMPLATE_PARAMS>;
    using NaturalType = _NType;
    using Divide = typename Fract::DivideOperator;
    using Multiply = typename Fract::MultiplyOperator;
    using Plus = typename Fract::PlusOperator;
    using Equals = typename Fract::EqualOperator;

    if (Equals{}(lhs.denominator(), rhs.denominator())) {
        return Fract{Plus{}(lhs.nominator(), rhs.nominator()), lhs.denominator()};
    }
/*
 * Result's denominator is least common multiple of b, d or less
 */
    auto lcm = utility::lcm<NaturalType, typename Fract::Checker>(
            lhs.denominator(),
            rhs.denominator());

/*
 * Calculate b / lcm
 */
    auto lhs_d_lcm = Divide{}(lhs.denominator(), lcm);

/*
 * Calculate a * b/lcm
 */
    auto lhs_ad_lcm = Multiply{}(lhs.nominator(), lhs_d_lcm);

/*
 * Calculate d / lcm
 */
    auto rhs_d_lcm = Divide{}(rhs.denominator(), lcm);

/*
 * Calculate c * d/lcm
 */
    auto rhs_cd_lcm = Multiply{}(rhs.nominator(), rhs_d_lcm);

/*
 * Calculate a * b/lcm + c * d/lcm
 */
    auto lhs_ad_lcm0rhs_cd_lcm = Plus{}(lhs_ad_lcm, rhs_cd_lcm);

/*
 * Result (a * b/lcm + c * d/lcm)/lcm
 */
    return Fract{
            lhs_ad_lcm0rhs_cd_lcm, lcm};
}

/**
 * @param lhs = a/b
 * @param rhs = c/d
 * @return Simplified a/b + c/d -> (a * b/lcm - c * d/lcm)/lcm
 */
template<class _NType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
constexpr Fractional<_NType, _Checker, TEMPLATE_PARAMS>
operator-(const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &lhs,
          const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &rhs) noexcept(
is_noexcept<Fractional<_NType, _Checker, TEMPLATE_PARAMS>>()) {
    using Fract = Fractional<_NType, _Checker, TEMPLATE_PARAMS>;
    using NaturalType = _NType;
    using Divide = typename Fract::DivideOperator;
    using Multiply = typename Fract::MultiplyOperator;
    using Minus = typename Fract::MinusOperator;
    using Equals = typename Fract::EqualOperator;

    if (Equals{}(lhs.denominator(), rhs.denominator())) {
        return Fract{Minus{}(lhs.nominator(), rhs.nominator()), lhs.denominator()};
    }

    /*
     * Result's denominator is least common multiple of b, d or less
     */
    auto lcm = utility::lcm<NaturalType, typename Fract::Checker>(
            lhs.denominator(),
            rhs.denominator());

    /*
     * Calculate b / lcm
     */
    auto lhs_d_lcm = Divide{}(lhs.denominator(), lcm);

    /*
     * Calculate a * b/lcm
     */
    auto lhs_ad_lcm = Multiply{}(lhs.nominator(), lhs_d_lcm);

    /*
     * Calculate d / lcm
     */
    auto rhs_d_lcm = Divide{}(rhs.denominator(), lcm);

    /*
     * Calculate c * d/lcm
     */
    auto rhs_cd_lcm = Multiply{}(rhs.nominator(), rhs_d_lcm);

    /*
     * Calculate a * b/lcm - c * d/lcm
     */
    auto lhs_ad_lcm0rhs_cd_lcm = Minus{}(lhs_ad_lcm, rhs_cd_lcm);

    /*
     * Result (a * b/lcm - c * d/lcm)/lcm
     */
    return Fract{lhs_ad_lcm0rhs_cd_lcm, lcm};
}

template<class _NType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
std::ostream &operator<<(std::ostream &os, const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &rhs) {
    os << rhs.nominator() << '/' << rhs.denominator();
    return os;
}

template<class _NType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
std::wostream &operator<<(std::wostream &os, const Fractional<_NType, _Checker, TEMPLATE_PARAMS> &rhs) {
    os << rhs.nominator() << '/' << rhs.denominator();
    return os;
}


#endif //FRACTIONNUMBER_FRACTIONAL_HXX
