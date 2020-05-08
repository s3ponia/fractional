//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_OVERFLOWCHECKER_HXX
#define FRACTIONNUMBER_OVERFLOWCHECKER_HXX

#include "overflowchecker.hpp"
#include <limits>

namespace fractional::overflow {
    using std::numeric_limits;

    namespace {
        template<class _NaturalType, class _MultiplyOperator, class _DivideOperator,
                class _LessOperator, class _GreaterOperator, class _EqualOperator>
        constexpr bool IsPositiveOne(const _NaturalType &t) {
            auto max_value = std::numeric_limits<_NaturalType>::max();
            return _GreaterOperator{}(t, _NaturalType{}) && _LessOperator{}(t, _DivideOperator{}(max_value, t)) &&
                   _EqualOperator{}(_MultiplyOperator{}(t, t), t);
        }

        template<class _NaturalType, class _NegateOperator, class _MultiplyOperator, class _DivideOperator,
                class _LessOperator, class _GreaterOperator, class _EqualOperator, class _NoEqualOperator>
        constexpr bool IsNegativeOne(const _NaturalType &t) {
            auto min_value = std::numeric_limits<_NaturalType>::lowest();
            auto max_value = std::numeric_limits<_NaturalType>::max();
            return _NoEqualOperator{}(t, min_value) && _NoEqualOperator{}(t, max_value) &&
                   IsPositiveOne<_NaturalType, _MultiplyOperator,
                           _DivideOperator, _LessOperator,
                           _GreaterOperator, _EqualOperator>(_NegateOperator{}(t));
        }
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool
    SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMultiply(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto min_value = std::numeric_limits<_NaturalType>::lowest();
        auto max_value = std::numeric_limits<_NaturalType>::max();
        if (IsNegativeOne<NaturalType, NegateOperator, MultiplyOperator, DivideOperator, LessOperator,
                GreaterOperator, EqualOperator, NoEqualOperator>(lhs) && EqualOperator{}(rhs, min_value))
            return CheckMinNegate();
        if (IsNegativeOne<NaturalType, NegateOperator, MultiplyOperator, DivideOperator, LessOperator,
                GreaterOperator, EqualOperator, NoEqualOperator>(rhs) && EqualOperator{}(lhs, min_value))
            return CheckMinNegate();

        bool is_positive_one = IsPositiveOne<NaturalType, MultiplyOperator,
                DivideOperator, LessOperator,
                GreaterOperator, EqualOperator>(lhs);

        bool is_positive_overflow = EqualOperator{}(rhs, NaturalType{}) ||
                                    LessEqualOperator{}(lhs, DivideOperator{}(max_value, rhs));

        bool is_negative_overflow =
                EqualOperator{}(rhs, NaturalType{}) || GreaterEqualOperator{}(lhs, DivideOperator{}(min_value, rhs));

        return is_positive_one ||
               (is_positive_overflow && is_negative_overflow);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckPlus(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto max_value = numeric_limits<NaturalType>::max();
        auto zero = NaturalType{};
        return !((GreaterOperator{}(rhs, zero) && GreaterOperator{}(lhs, MinusOperator{}(max_value, rhs))) ||
                 (LessOperator{}(rhs, zero) && LessOperator{}(lhs, MinusOperator{}(max_value, rhs))));
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool
    SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMinus(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto max_value = numeric_limits<NaturalType>::max();
        auto zero = NaturalType{};
        return !((LessOperator{}(rhs, zero) && GreaterOperator{}(lhs, PlusOperator{}(max_value, rhs))) ||
                 (GreaterOperator{}(rhs, zero) && LessOperator{}(lhs, PlusOperator{}(max_value, rhs))));
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckNegate(
            const NaturalType &lhs) {
        auto max_value = numeric_limits<NaturalType>::max();
        auto min_value = numeric_limits<NaturalType>::lowest();

        if (EqualOperator{}(max_value, lhs)) {
            return CheckMaxNegate();
        } else if (EqualOperator{}(min_value, lhs)) {
            return CheckMinNegate();
        }
        return true;
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMaxNegate() {
        auto max_value = numeric_limits<NaturalType>::max();
        auto min_value = numeric_limits<NaturalType>::lowest();
        return LessEqualOperator{}(PlusOperator{}(max_value, min_value), NaturalType{});
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool SignedCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMinNegate() {
        auto max_value = numeric_limits<NaturalType>::max();
        auto min_value = numeric_limits<NaturalType>::lowest();
        return GreaterEqualOperator{}(PlusOperator{}(max_value, min_value), NaturalType{});
    }
}

#endif //FRACTIONNUMBER_OVERFLOWCHECKER_HXX
