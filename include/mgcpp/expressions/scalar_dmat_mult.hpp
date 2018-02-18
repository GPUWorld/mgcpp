
//          Copyright RedPortal, mujjingun 2017 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _MGCPP_EXPRESSIONS_SCALAR_DMAT_MULT_EXPR_HPP_
#define _MGCPP_EXPRESSIONS_SCALAR_DMAT_MULT_EXPR_HPP_

#include <type_traits>

#include <mgcpp/expressions/dmat_expr.hpp>
#include <mgcpp/expressions/scalar_expr.hpp>

namespace mgcpp {
template <typename ScalExpr, typename DMatExpr>
struct scalar_dmat_mult_expr
    : public dmat_expr<scalar_dmat_mult_expr<ScalExpr, DMatExpr>> {
  using scal_expr_type = typename std::decay<ScalExpr>::type;
  using dmat_expr_type = typename std::decay<DMatExpr>::type;

  using result_type = typename dmat_expr_type::result_type;

  ScalExpr _scal_expr;
  DMatExpr _dmat_expr;

  inline scalar_dmat_mult_expr(ScalExpr const& scal_expr,
                               DMatExpr const& dmat_expr) noexcept;

  inline scalar_dmat_mult_expr(ScalExpr&& scal_expr,
                               DMatExpr&& dmat_expr) noexcept;

  inline result_type eval() const;
};

template <typename ScalExpr, typename DMatExpr>
inline typename scalar_dmat_mult_expr<ScalExpr, DMatExpr>::result_type eval(
    scalar_dmat_mult_expr<ScalExpr, DMatExpr> const& expr);

template <typename Scalar,
          typename DMatExpr,
          typename = typename std::enable_if<is_scalar<Scalar>::value>::type>
inline scalar_dmat_mult_expr<Scalar, DMatExpr> operator*(
    Scalar const& scalar,
    dmat_expr<DMatExpr> const& exp) noexcept;

template <typename Scalar,
          typename DMatExpr,
          typename = typename std::enable_if<is_scalar<Scalar>::value>::type>
inline scalar_dmat_mult_expr<Scalar, DMatExpr> operator*(
    dmat_expr<DMatExpr> const& exp,
    Scalar const& scalar) noexcept;

template <typename ScalExpr, typename DMatExpr>
inline scalar_dmat_mult_expr<ScalExpr, DMatExpr> operator*(
    scalar_expr<ScalExpr> const& scalar,
    dmat_expr<DMatExpr> const& exp) noexcept;

template <typename ScalExpr, typename DMatExpr>
inline scalar_dmat_mult_expr<ScalExpr, DMatExpr> operator*(
    dmat_expr<DMatExpr> const& exp,
    scalar_expr<ScalExpr> const& scalar) noexcept;

template <typename Scalar,
          typename DMatExpr,
          typename = typename std::enable_if<is_scalar<Scalar>::value>::type>
inline scalar_dmat_mult_expr<Scalar, DMatExpr> mult(
    Scalar const& scalar,
    dmat_expr<DMatExpr> const& mat_exp) noexcept;

template <typename Scalar,
          typename DMatExpr,
          typename = typename std::enable_if<is_scalar<Scalar>::value>::type>
inline scalar_dmat_mult_expr<Scalar, DMatExpr> mult(
    dmat_expr<DMatExpr> const& mat_exp,
    Scalar const& scalar) noexcept;

template <typename ScalExpr, typename DMatExpr>
inline scalar_dmat_mult_expr<ScalExpr, DMatExpr> mult(
    scalar_expr<ScalExpr> const& scalar,
    dmat_expr<DMatExpr> const& mat_exp) noexcept;

template <typename ScalExpr, typename DMatExpr>
inline scalar_dmat_mult_expr<ScalExpr, DMatExpr> mult(
    dmat_expr<DMatExpr> const& mat_exp,
    scalar_expr<ScalExpr> const& scalar) noexcept;
}  // namespace mgcpp

#endif
