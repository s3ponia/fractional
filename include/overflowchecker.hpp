//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_OVERFLOWCHECKER_HPP
#define FRACTIONNUMBER_OVERFLOWCHECKER_HPP

#include <functional>
#include <exception>

#define DECLARATION_TEMPLATE_PARAMS \
class _EqualOperator,\
class _NoEqualOperator,\
class _GreaterOperator,\
class _GreaterEqualOperator,\
class _LessOperator,\
class _LessEqualOperator,\
class _PlusOperator,\
class _MinusOperator,\
class _MultiplyOperator,\
class _DivideOperator,\
class _NegateOperator,\
class _ModulusOperator

#define TEMPLATE_PARAMS \
_EqualOperator,\
_NoEqualOperator,\
_GreaterOperator,\
_GreaterEqualOperator,\
_LessOperator,\
_LessEqualOperator,\
_PlusOperator,\
_MinusOperator,\
_MultiplyOperator,\
_DivideOperator,\
_NegateOperator,\
_ModulusOperator


namespace fractional::overflow {

    struct OverflowError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    struct CheckOverflow {
        using NaturalType = _NaturalType;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _MultiplyOperator;
        using NegateOperator = _NegateOperator;
        using ModulusOperator = _ModulusOperator;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        static bool CheckMultiply(const NaturalType &lhs, const NaturalType &rhs);

        static bool CheckPlus(const NaturalType &lhs, const NaturalType &rhs);

        static bool CheckDivide(const NaturalType &lhs, const NaturalType &rhs);

        static bool CheckMinus(const NaturalType &lhs, const NaturalType &rhs);

        static bool CheckNegate(const NaturalType &lhs);

        static bool CheckModulus(const NaturalType &lhs, const NaturalType &rhs);

        static bool CheckIncrement(const NaturalType &lhs);

        static bool CheckDecrement(const NaturalType &lhs);

        static bool CheckBitwiseLeftShift(const NaturalType &lhs, std::size_t rhs);
    };

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    struct ThrowOnCheck {
        using NaturalType = _NaturalType;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _MultiplyOperator;
        using NegateOperator = _NegateOperator;
        using ModulusOperator = _ModulusOperator;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        static void CheckMultiply(const NaturalType &lhs, const NaturalType &rhs);

        static void CheckPlus(const NaturalType &lhs, const NaturalType &rhs);

        static void CheckDivide(const NaturalType &lhs, const NaturalType &rhs);

        static void CheckMinus(const NaturalType &lhs, const NaturalType &rhs);

        static void CheckNegate(const NaturalType &lhs);

        static void CheckModulus(const NaturalType &lhs, const NaturalType &rhs);

        static void CheckIncrement(const NaturalType &lhs);

        static void CheckDecrement(const NaturalType &lhs);

        static void CheckBitwiseLeftShift(const NaturalType &lhs, std::size_t rhs);
    };

    template<class _NaturalType, DECLARATION_TEMPLATE_PARAMS>
    struct NoCheck {
        using NaturalType = _NaturalType;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _MultiplyOperator;
        using NegateOperator = _NegateOperator;
        using ModulusOperator = _ModulusOperator;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        static void CheckMultiply(const NaturalType &lhs, const NaturalType &rhs) noexcept {};

        static void CheckPlus(const NaturalType &lhs, const NaturalType &rhs) noexcept {};

        static void CheckDivide(const NaturalType &lhs, const NaturalType &rhs) noexcept {};

        static void CheckMinus(const NaturalType &lhs, const NaturalType &rhs) noexcept {};

        static void CheckNegate(const NaturalType &lhs) noexcept {};

        static void CheckModulus(const NaturalType &lhs, const NaturalType &rhs) noexcept {};

        static void CheckIncrement(const NaturalType &lhs) noexcept {};

        static void CheckDecrement(const NaturalType &lhs) noexcept {};

        static void CheckBitwiseLeftShift(const NaturalType &lhs, std::size_t rhs) noexcept {};
    };
}

#include "overflowchecker.hxx"

#endif //FRACTIONNUMBER_OVERFLOWCHECKER_HPP
