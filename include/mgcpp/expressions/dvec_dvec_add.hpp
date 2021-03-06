
//          Copyright RedPortal, mujjingun 2017 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_EXPRESSIONS_DVEC_DVEC_ADD_HPP_
#define _MGCPP_EXPRESSIONS_DVEC_DVEC_ADD_HPP_

#include <mgcpp/expressions/dvec_expr.hpp>

namespace mgcpp {
template <typename LhsExpr, typename RhsExpr>
struct dvec_dvec_add_expr
    : public dvec_expr<dvec_dvec_add_expr<LhsExpr, RhsExpr>> {
  using lhs_expr_type = typename std::decay<LhsExpr>::type;
  using rhs_expr_type = typename std::decay<RhsExpr>::type;

  using result_type = typename lhs_expr_type::result_type;

  LhsExpr _lhs;
  RhsExpr _rhs;

  inline dvec_dvec_add_expr(LhsExpr const& lhs, RhsExpr const& rhs) noexcept;
  inline dvec_dvec_add_expr(LhsExpr&& lhs, RhsExpr&& rhs) noexcept;

  /** Evaluates the compuational graph starting from this expression.
   */
  inline result_type eval() const;
};

/** Returns a dense vector addition expression.
 * \param lhs the left-hand side dense vector
 * \param rhs the right-hand side dense vector
 */
template <typename LhsExpr, typename RhsExpr>
inline dvec_dvec_add_expr<LhsExpr, RhsExpr> operator+(
    dvec_expr<LhsExpr> const& lhs,
    dvec_expr<RhsExpr> const& rhs) noexcept;

/** Returns a dense vector addition expression.
 * \param lhs the left-hand side dense vector
 * \param rhs the right-hand side dense vector
 */
template <typename LhsExpr, typename RhsExpr>
inline dvec_dvec_add_expr<LhsExpr, RhsExpr> add(
    dvec_expr<LhsExpr> const& lhs,
    dvec_expr<RhsExpr> const& rhs) noexcept;
}  // namespace mgcpp

#endif  // _MGCPP_EXPRESSIONS_DVEC_DVEC_ADD_HPP_
