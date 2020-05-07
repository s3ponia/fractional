//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_FRACTIONAL_HPP
#define FRACTIONNUMBER_FRACTIONAL_HPP

#include <type_traits>
#include <functional>
#include "overflowchecker.hpp"
#include "utility.hpp"

namespace fractional {
    template<class _NaturalType,
            template<class...> class _OverflowChecker = overflow::ThrowOnCheck,
            class _EqualOperator = std::equal_to<_NaturalType>,
            class _NoEqualOperator = std::not_equal_to<_NaturalType>,
            class _GreaterOperator = std::greater<_NaturalType>,
            class _GreaterEqualOperator = std::greater_equal<_NaturalType>,
            class _LessOperator = std::less<_NaturalType>,
            class _LessEqualOperator = std::less_equal<_NaturalType>,
            class _PlusOperator = std::plus<_NaturalType>,
            class _MinusOperator = std::minus<_NaturalType>,
            class _MultiplyOperator = std::multiplies<_NaturalType>,
            class _DivideOperator = std::divides<_NaturalType>,
            class _NegateOperator = std::negate<_NaturalType>,
            class _ModulusOperator = std::modulus<_NaturalType>>
    class Fractional {
    public:
        using NaturalType = _NaturalType;

        using Checker = _OverflowChecker<_NaturalType, TEMPLATE_PARAMS>;

        using PlusOperator = utility::OperatorWraper<_PlusOperator, Checker::CheckPlus>;
        using MinusOperator = utility::OperatorWraper<_MinusOperator, Checker::CheckMinus>;
        using MultiplyOperator = utility::OperatorWraper<_MultiplyOperator, Checker::CheckMultiply>;
        using DivideOperator = utility::OperatorWraper<_DivideOperator, Checker::CheckDivide>;
        using NegateOperator = utility::OperatorWraper<_NegateOperator, Checker::CheckNegate>;
        using ModulusOperator = utility::OperatorWraper<_ModulusOperator, Checker::CheckModulus>;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        constexpr Fractional() noexcept = delete;

        constexpr Fractional(
                const Fractional &) noexcept(std::is_nothrow_copy_constructible<NaturalType>::value) = default;

        constexpr Fractional(Fractional &&) noexcept(std::is_nothrow_move_constructible<NaturalType>::value) = default;

        constexpr Fractional &
        operator=(const Fractional &) noexcept(std::is_nothrow_copy_assignable<NaturalType>::value) = default;

        constexpr Fractional &
        operator=(Fractional &&) noexcept(std::is_nothrow_move_assignable<NaturalType>::value) = default;

        constexpr Fractional(const NaturalType &nominator,
                             const NaturalType &denominator) noexcept(std::is_nothrow_copy_constructible<NaturalType>::value)
                : nominator_(nominator), denominator_(denominator) {}

        constexpr Fractional(NaturalType &&nominator,
                             NaturalType &&denominator) noexcept(std::is_nothrow_move_constructible<NaturalType>::value)
                : nominator_(nominator), denominator_(denominator) {}

        template<class T, typename = typename std::enable_if<
                std::is_floating_point<T>::value &&
                std::is_convertible<NaturalType, T>::value
        >::type>
        operator T() {
            return std::divides<T>{}(nominator_, denominator_);
        }

        const NaturalType &nominator() const {
            return nominator_;
        }

        const NaturalType &denominator() const {
            return denominator_;
        }

    private:
        NaturalType nominator_;
        NaturalType denominator_;
    };

    using fraction = Fractional<int>;
}

#include "fractional.hxx"

#endif //FRACTIONNUMBER_FRACTIONAL_HPP