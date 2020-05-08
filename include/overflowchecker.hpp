//
// Created by Linux Oid on 07.05.2020.
//

#ifndef FRACTIONNUMBER_OVERFLOWCHECKER_HPP
#define FRACTIONNUMBER_OVERFLOWCHECKER_HPP

#include <functional>
#include <exception>
#include <string>

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

#define DECLARATION_DEFAULT_TEMPLATE_PARAMS \
class _EqualOperator = std::equal_to<_NaturalType>,\
class _NoEqualOperator = std::not_equal_to<_NaturalType>,\
class _GreaterOperator = std::greater<_NaturalType>,\
class _GreaterEqualOperator = std::greater_equal<_NaturalType>,\
class _LessOperator = std::less<_NaturalType>,\
class _LessEqualOperator = std::less_equal<_NaturalType>,\
class _PlusOperator = std::plus<_NaturalType>,\
class _MinusOperator = std::minus<_NaturalType>,\
class _MultiplyOperator = std::multiplies<_NaturalType>,\
class _DivideOperator = std::divides<_NaturalType>,\
class _NegateOperator = std::negate<_NaturalType>,\
class _ModulusOperator = std::modulus<_NaturalType>

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
    using namespace std::string_literals;

    template<class _LhsType, class _RhsType>
    struct OverflowBinaryError final : std::exception {
        using LhsType = _LhsType;
        using RhsType = _RhsType;

        OverflowBinaryError(const LhsType &lhs, const RhsType &rhs) : lhs_(lhs), rhs_(rhs) {}

        const LhsType &lhs() const noexcept {
            return lhs_;
        }

        const RhsType &rhs() const noexcept {
            return rhs_;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return "Binary Overflow error.";
        }

    private:
        LhsType lhs_;
        RhsType rhs_;
    };

    template<class _NaturalType>
    struct OverflowUnaryError final : std::exception {
        using NaturalType = _NaturalType;

        explicit OverflowUnaryError(const NaturalType &op) : operand_(op) {}

        const NaturalType &operand() const noexcept {
            return operand_;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return "Unary Overflow error.";
        }

    private:
        NaturalType operand_;
    };

    template<class _NaturalType, DECLARATION_DEFAULT_TEMPLATE_PARAMS >
    struct CheckNoOverflow {
        using NaturalType = _NaturalType;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _DivideOperator;
        using NegateOperator = _NegateOperator;
        using ModulusOperator = _ModulusOperator;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        static bool CheckMultiply(const NaturalType &lhs, const NaturalType &rhs) noexcept {
            return true;
        }

        static bool CheckPlus(const NaturalType &lhs, const NaturalType &rhs) noexcept {
            return true;
        }

        static bool CheckDivide(const NaturalType &lhs, const NaturalType &rhs) noexcept {
            return true;
        }

        static bool CheckMinus(const NaturalType &lhs, const NaturalType &rhs) noexcept {
            return true;
        }

        static bool CheckNegate(const NaturalType &lhs) noexcept {
            return true;
        }

        static bool CheckModulus(const NaturalType &lhs, const NaturalType &rhs) noexcept {
            return true;
        }

        static bool CheckIncrement(const NaturalType &lhs) noexcept {
            return true;
        }

        static bool CheckDecrement(const NaturalType &lhs) noexcept {
            return true;
        }

        static bool CheckBitwiseLeftShift(const NaturalType &lhs, std::size_t rhs) noexcept {
            return true;
        }
    };

    /**
     * Class for checking overflowing
     * Contains static methods to check overflow, return true if it is not overflows, false otherwise
     */
    template<class _NaturalType, DECLARATION_DEFAULT_TEMPLATE_PARAMS >
    struct IntegralCheckOverflow {
        static_assert(_EqualOperator{}(_NaturalType{}, _NegateOperator{}(_NaturalType{})),
                      "Default constructed NaturalType must be zero.");
        static_assert(std::numeric_limits<_NaturalType>::is_specialized,
                      "std::numeric_limits<_NaturalType> must be specialized");
        static_assert(std::numeric_limits<_NaturalType>::is_integer,
                      "_NaturalType must be integer");
        using NaturalType = _NaturalType;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _DivideOperator;
        using NegateOperator = _NegateOperator;
        using ModulusOperator = _ModulusOperator;

        using EqualOperator = _EqualOperator;
        using NoEqualOperator = _NoEqualOperator;
        using GreaterOperator = _GreaterOperator;
        using GreaterEqualOperator = _GreaterEqualOperator;
        using LessOperator = _LessOperator;
        using LessEqualOperator = _LessEqualOperator;

        static constexpr bool CheckMaxNegate();

        static constexpr bool CheckMinNegate();

        static constexpr bool CheckMultiply(const NaturalType &lhs, const NaturalType &rhs);

        static constexpr bool CheckPlus(const NaturalType &lhs, const NaturalType &rhs);

        static constexpr bool CheckMinus(const NaturalType &lhs, const NaturalType &rhs);

        static constexpr bool CheckDivide(const NaturalType &lhs, const NaturalType &rhs);

        static constexpr bool CheckNegate(const NaturalType &lhs);

        static constexpr bool CheckModulus(const NaturalType &lhs, const NaturalType &rhs);

        static constexpr bool CheckIncrement(const NaturalType &lhs);

        static constexpr bool CheckDecrement(const NaturalType &lhs);

        static constexpr bool CheckBitwiseLeftShift(const NaturalType &lhs, std::size_t rhs);
    };

    template<class _NaturalType, template<class...> class _Checker = IntegralCheckOverflow, DECLARATION_DEFAULT_TEMPLATE_PARAMS >
    struct ThrowOnCheck {
        using NaturalType = _NaturalType;

        using Checker = _Checker<NaturalType, TEMPLATE_PARAMS>;
        using BinaryError = OverflowBinaryError<NaturalType, NaturalType>;
        using BitwiseError = OverflowBinaryError<NaturalType, std::size_t>;
        using UnaryError = OverflowUnaryError<NaturalType>;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _DivideOperator;
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

    template<class _NaturalType, template<class...> class _Checker = CheckNoOverflow, DECLARATION_DEFAULT_TEMPLATE_PARAMS >
    struct NoCheck {
        using NaturalType = _NaturalType;

        using Checker = _Checker<NaturalType, TEMPLATE_PARAMS>;
        using BinaryError = OverflowBinaryError<NaturalType, NaturalType>;
        using BitwiseError = OverflowBinaryError<NaturalType, std::size_t>;
        using UnaryError = OverflowUnaryError<NaturalType>;

        using PlusOperator = _PlusOperator;
        using MinusOperator = _MinusOperator;
        using MultiplyOperator = _MultiplyOperator;
        using DivideOperator = _DivideOperator;
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

    template<class _NaturalType>
    struct OverflowChecker : ThrowOnCheck<_NaturalType> {
    };
}

#include "overflowchecker.hxx"

#endif //FRACTIONNUMBER_OVERFLOWCHECKER_HPP
