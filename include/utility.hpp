//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_UTILITY_HPP
#define FRACTIONNUMBER_UTILITY_HPP

namespace fractional::utility {
    template<class Op, auto Checker>
    struct OperatorWraper;

    template<template<class> class Op, class OpType, auto Checker>
    struct OperatorWraper<Op<OpType>, Checker> {
        auto operator()(const OpType &lhs, const OpType &rhs) {
            Checker(lhs, rhs);
            return Op<OpType>{}(lhs, rhs);
        }

        auto operator()(const OpType &lhs) {
            Checker(lhs);
            return Op<OpType>{}(lhs);
        }
    };

    template<class _NaturalType, class _OverflowChecker>
    constexpr _NaturalType gcd(const _NaturalType &lhs, const _NaturalType &rhs) {
        using Modulo = typename _OverflowChecker::ModulusOperator;
        using Negate = typename _OverflowChecker::NegateOperator;
        using Equals = typename _OverflowChecker::EqualOperator;

        _OverflowChecker::CheckNegate(rhs);
        if (Equals{}(Negate{}(rhs), rhs)) {
            return lhs;
        }
        _OverflowChecker::CheckModulus(lhs, rhs);
        return gcd<_NaturalType, _OverflowChecker>(rhs, Modulo{}(lhs, rhs));
    }

    template<class _NaturalType, class _OverflowChecker>
    constexpr _NaturalType lcm(const _NaturalType &lhs, const _NaturalType &rhs) {
        using Multiply = typename _OverflowChecker::MultiplyOperator;
        using Divide = typename _OverflowChecker::DivideOperator;

        auto _gcd = gcd<_NaturalType, _OverflowChecker>(lhs, rhs);
        _OverflowChecker::CheckDivide(lhs, _gcd);
        auto temp = Divide{}(lhs, _gcd);
        _OverflowChecker::CheckMultiply(temp, rhs);
        return Multiply{}(temp, rhs);
    }
}

#endif //FRACTIONNUMBER_UTILITY_HPP
