
//          Copyright RedPortal, mujjingun 2017 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_EXPRESSIONS_DMAT_DVEC_MULT_EXPR_HPP_
#define _MGCPP_EXPRESSIONS_DMAT_DVEC_MULT_EXPR_HPP_

#include <mgcpp/expressions/dmat_expr.hpp>
#include <mgcpp/expressions/dvec_expr.hpp>

namespace mgcpp {
template <typename MatExpr, typename VecExpr>
struct dmat_dvec_mult_expr
    : public dvec_expr<dmat_dvec_mult_expr<MatExpr, VecExpr>> {
  using lhs_expr_type = typename std::decay<MatExpr>::type;
  using rhs_expr_type = typename std::decay<VecExpr>::type;

  using result_type = typename rhs_expr_type::result_type;

  MatExpr _mat;
  VecExpr _vec;

  inline dmat_dvec_mult_expr(MatExpr const& mat, VecExpr const& vec) noexcept;
  inline dmat_dvec_mult_expr(MatExpr&& mat, VecExpr&& vec) noexcept;

  /** Evaluates the compuational graph starting from this expression.
   */
  inline result_type eval() const;
};

/** Returns a dense matrix vector product expression.
 * \param lhs the left-hand side dense matrix
 * \param rhs the right-hand side dense vector
 */
template <typename MatExpr, typename VecExpr>
inline dmat_dvec_mult_expr<MatExpr, VecExpr> operator*(
    dmat_expr<MatExpr> const& mat,
    dvec_expr<VecExpr> const& vec) noexcept;

/** Returns a dense matrix add expression.
 * \param lhs the left-hand side dense matrix
 * \param rhs the right-hand side dense vector
 */
template <typename MatExpr, typename VecExpr>
inline dmat_dvec_mult_expr<MatExpr, VecExpr> mult(
    dmat_expr<MatExpr> const& mat,
    dvec_expr<VecExpr> const& vec) noexcept;
}  // namespace mgcpp

#endif
