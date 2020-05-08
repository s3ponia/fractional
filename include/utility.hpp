//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_UTILITY_HPP
#define FRACTIONNUMBER_UTILITY_HPP

namespace fractional::utility {
    using std::declval;

    template<class Op, auto Checker>
    struct OperatorWrapper;

    template<template<class> class Op, class OpType, auto Checker>
    struct OperatorWrapper<Op<OpType>, Checker> {
        auto operator()(const OpType &lhs, const OpType &rhs) noexcept(noexcept(Checker(lhs, rhs))) {
            Checker(lhs, rhs);
            return Op<OpType>{}(lhs, rhs);
        }

        auto operator()(const OpType &lhs) noexcept(noexcept(Checker(lhs))) {
            Checker(lhs);
            return Op<OpType>{}(lhs);
        }
    };

    template<class _NType, class _OverflowChecker>
    constexpr _NType gcd(const _NType &lhs, const _NType &rhs) noexcept(
    noexcept(_OverflowChecker::CheckNegate(declval<_NType>())) &&
    noexcept(_OverflowChecker::CheckModulus(declval<_NType>(), declval<_NType>())) &&
    noexcept(typename _OverflowChecker::EqualOperator{}(declval<_NType>(), declval<_NType>())) &&
    noexcept(typename _OverflowChecker::ModulusOperator{}(declval<_NType>(), declval<_NType>())) &&
    noexcept(typename _OverflowChecker::NegateOperator{}(declval<_NType>()))
    ) {
        using Modulo = typename _OverflowChecker::ModulusOperator;
        using Negate = typename _OverflowChecker::NegateOperator;
        using Equals = typename _OverflowChecker::EqualOperator;

        _OverflowChecker::CheckNegate(rhs);
        if (Equals{}(Negate{}(rhs), rhs)) {
            return lhs;
        }
        _OverflowChecker::CheckModulus(lhs, rhs);
        return gcd<_NType, _OverflowChecker>(rhs, Modulo{}(lhs, rhs));
    }

    template<class _NType, class _OverflowChecker>
    constexpr _NType lcm(const _NType &lhs, const _NType &rhs) noexcept(
    noexcept(_OverflowChecker::CheckDivide) &&
    noexcept(_OverflowChecker::CheckMultiply) &&
    noexcept(typename _OverflowChecker::DivideOperator{}(declval<_NType>(), declval<_NType>())) &&
    noexcept(typename _OverflowChecker::MultiplyOperator{}(declval<_NType>(), declval<_NType>())) &&
    noexcept(gcd<_NType, _OverflowChecker>(lhs, rhs))
    ) {
        using Multiply = typename _OverflowChecker::MultiplyOperator;
        using Divide = typename _OverflowChecker::DivideOperator;

        auto _gcd = gcd<_NType, _OverflowChecker>(lhs, rhs);
        _OverflowChecker::CheckDivide(lhs, _gcd);
        auto temp = Divide{}(lhs, _gcd);
        _OverflowChecker::CheckMultiply(temp, rhs);
        return Multiply{}(temp, rhs);
    }
}

#endif //FRACTIONNUMBER_UTILITY_HPP
