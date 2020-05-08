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
        template<class _NaturalType>
        constexpr _NaturalType PositiveOne() {
            auto zero = _NaturalType{};
            return ++zero;
        }

        template<class _NaturalType, typename = std::enable_if_t<std::is_signed_v<_NaturalType>>>
        constexpr _NaturalType NegativeOne() {
            auto zero = _NaturalType{};
            return --zero;
        }

        template<class _NaturalType, class _EqualOp>
        constexpr bool IsPositiveOne(const _NaturalType &t) {
            return _EqualOp{}(t, PositiveOne<_NaturalType>());
        }

        template<class _NaturalType, class _EqualOp>
        constexpr bool IsNegativeOne(const _NaturalType &t) {
            if constexpr (std::is_unsigned_v<_NaturalType>) {
                return false;
            }
            return _EqualOp{}(t, NegativeOne<_NaturalType, _EqualOp>());
        }


    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool
    IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMultiply(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto min_value = std::numeric_limits<_NaturalType>::lowest();
        auto max_value = std::numeric_limits<_NaturalType>::max();
        if (IsNegativeOne<NaturalType, EqualOperator>(lhs) && EqualOperator{}(rhs, min_value))
            return CheckMinNegate();
        if (IsNegativeOne<NaturalType, EqualOperator>(rhs) && EqualOperator{}(lhs, min_value))
            return CheckMinNegate();

        bool is_positive_one = IsPositiveOne<NaturalType, EqualOperator>(lhs);

        bool is_positive_overflow = EqualOperator{}(rhs, NaturalType{}) ||
                                    LessEqualOperator{}(lhs, DivideOperator{}(max_value, rhs));

        bool is_negative_overflow =
                EqualOperator{}(rhs, NaturalType{}) || GreaterEqualOperator{}(lhs, DivideOperator{}(min_value, rhs));

        return is_positive_one ||
               (is_positive_overflow && is_negative_overflow);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckPlus(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto max_value = numeric_limits<NaturalType>::max();
        auto zero = NaturalType{};
        return !((GreaterOperator{}(rhs, zero) && GreaterOperator{}(lhs, MinusOperator{}(max_value, rhs))) ||
                 (LessOperator{}(rhs, zero) && LessOperator{}(lhs, PlusOperator{}(max_value, rhs))));
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool
    IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMinus(
            const NaturalType &lhs, const NaturalType &rhs) {
        auto max_value = numeric_limits<NaturalType>::max();
        auto zero = NaturalType{};
        bool first_test = LessOperator{}(rhs, zero) && GreaterOperator{}(lhs, PlusOperator{}(max_value, rhs));
        bool second_test = GreaterOperator{}(rhs, zero) && LessOperator{}(lhs, MinusOperator{}(max_value, rhs));
        return !(first_test || second_test);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckNegate(
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
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMaxNegate() {
        auto max_value = numeric_limits<NaturalType>::max();
        auto min_value = numeric_limits<NaturalType>::lowest();
        return LessEqualOperator{}(PlusOperator{}(max_value, min_value), NaturalType{});
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckMinNegate() {
        auto max_value = numeric_limits<NaturalType>::max();
        auto min_value = numeric_limits<NaturalType>::lowest();
        return GreaterEqualOperator{}(PlusOperator{}(max_value, min_value), NaturalType{});
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckDivide(
            const NaturalType &lhs, const NaturalType &rhs) {
        return NoEqualOperator{}(rhs, NaturalType{}) &&
               (IsNegativeOne<NaturalType, EqualOperator>(rhs) && CheckNegate(lhs));
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckIncrement(
            const NaturalType &lhs) {
        auto max = std::numeric_limits<NaturalType>::max();
        return LessOperator{}(lhs, max);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckDecrement(
            const NaturalType &lhs) {
        auto min = std::numeric_limits<NaturalType>::lowest();
        return GreaterOperator{}(lhs, min);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckBitwiseLeftShift(
            const NaturalType &lhs, std::size_t rhs) {
        if (GreaterOperator{}(lhs, NaturalType{}) && (rhs == 0)) {
            return true;
        }
        auto digits = std::numeric_limits<NaturalType>::digits;
        assert(digits >= 0);
        return GreaterOperator{}(lhs, NaturalType{}) && GreaterOperator{}(rhs, NaturalType{}) &&
               !((NaturalType{1} << (std::size_t(digits) - rhs)) & lhs);
    }

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    constexpr bool IntegralCheckOverflow<_NaturalType, TEMPLATE_PARAMS>::CheckModulus(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (EqualOperator{}(rhs, NaturalType{}))
            return false;
        if (std::is_unsigned_v<NaturalType>)
            return true;
        auto min = std::numeric_limits<NaturalType>::lowest();
        return NoEqualOperator{}(lhs, min) || NoEqualOperator{}(rhs, NegativeOne<NaturalType>());
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckMultiply(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (!Checker::CheckMultiply(lhs, rhs)) {
            throw BinaryError(lhs, rhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckPlus(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (!Checker::CheckMultiply(lhs, rhs)) {
            throw BinaryError(lhs, rhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckDivide(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (!Checker::CheckDivide(lhs, rhs)) {
            throw BinaryError(lhs, rhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckMinus(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (!Checker::CheckMinus(lhs, rhs)) {
            throw BinaryError(lhs, rhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckNegate(
            const NaturalType &lhs) {
        if (!Checker::CheckNegate(lhs)) {
            throw UnaryError(lhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckModulus(
            const NaturalType &lhs, const NaturalType &rhs) {
        if (!Checker::CheckModulus(lhs, rhs)) {
            throw BinaryError(lhs, rhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckIncrement(
            const NaturalType &lhs) {
        if (!Checker::CheckIncrement(lhs)) {
            throw UnaryError(lhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckDecrement(
            const NaturalType &lhs) {
        if (!Checker::CheckDecrement(lhs)) {
            throw UnaryError(lhs);
        }
    }

    template<class _NaturalType, template<class...> class _Checker, DECLARATION_TEMPLATE_PARAMS>
    void
    ThrowOnCheck<_NaturalType, _Checker, TEMPLATE_PARAMS>::CheckBitwiseLeftShift(
            const NaturalType &lhs, std::size_t rhs) {
        if (!Checker::CheckBitwiseLeftShift(lhs, rhs)) {
            throw BitwiseError(lhs, rhs);
        }
    }
}

#endif //FRACTIONNUMBER_OVERFLOWCHECKER_HXX
