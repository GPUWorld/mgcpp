
//          Copyright RedPortal, mujjingun 2017 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_EXPRESSIONS_DMAT_DMAT_MULT_EXPR_HPP_
#define _MGCPP_EXPRESSIONS_DMAT_DMAT_MULT_EXPR_HPP_

#include <mgcpp/matrix/device_matrix.hpp>
#include <mgcpp/expressions/expr_eval.hpp>
#include <mgcpp/expressions/dmat_expr.hpp>

namespace mgcpp
{
    template<typename LhsExpr, typename RhsExpr>
    struct dmat_dmat_mult_expr
        : public dmat_expr<dmat_dmat_mult_expr<LhsExpr, RhsExpr>>
    {
        using lhs_expr_type = typename std::decay<LhsExpr>::type;
        using rhs_expr_type = typename std::decay<RhsExpr>::type;

        using result_type = typename lhs_expr_type::result_type;

        LhsExpr const& _lhs;
        RhsExpr const& _rhs;

        inline dmat_dmat_mult_expr(LhsExpr const& lhs,
                                   RhsExpr const& rhs) noexcept;

        inline result_type
        eval() const;
    };

    template<typename LhsExpr, typename RhsExpr>
    inline typename dmat_dmat_mult_expr<LhsExpr, RhsExpr>::result_type
    eval(dmat_dmat_mult_expr<LhsExpr, RhsExpr> const& expr);

    template<typename LhsExpr, typename RhsExpr>
    inline dmat_dmat_mult_expr<LhsExpr, RhsExpr> 
    operator*(dmat_expr<LhsExpr> const& lhs,
              dmat_expr<RhsExpr> const& rhs) noexcept;

    template<typename LhsExpr, typename RhsExpr>
    inline dmat_dmat_mult_expr<LhsExpr, RhsExpr> 
    mult(dmat_expr<LhsExpr> const& lhs,
         dmat_expr<RhsExpr> const& rhs) noexcept;
}

#include <mgcpp/expressions/dmat_dmat_mult.tpp>
#endif
