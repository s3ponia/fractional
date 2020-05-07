//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_FRACTIONAL_HXX
#define FRACTIONNUMBER_FRACTIONAL_HXX

#include <numeric>
#include "utility.hpp"

namespace fractional {
    /**
     * @param lhs = a/b
     * @param rhs = c/d
     * @return Simplified a/b + c/d -> (a * b/lcm + c * d/lcm)/lcm
     */
    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    constexpr Fractional<_NaturalType, _Checker, TEMPLATE_PARAMS>
    operator+(const Fractional<_NaturalType, _Checker, TEMPLATE_PARAMS> &lhs,
              const Fractional<_NaturalType, _Checker, TEMPLATE_PARAMS> &rhs) {
        using Fract = Fractional<_NaturalType, _Checker, TEMPLATE_PARAMS>;
        using NaturalType = _NaturalType;
        using Divide = typename Fract::DivideOperator;
        using Multiply = typename Fract::MultiplyOperator;

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


        return Fract{lhs.nominator() + rhs.nominator(), lcm};
    }
}

#endif //FRACTIONNUMBER_FRACTIONAL_HXX
