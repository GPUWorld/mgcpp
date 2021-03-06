#ifndef _MGCPP_EXPRESSIONS_DVEC_REDUCE_EXPR_HPP_
#define _MGCPP_EXPRESSIONS_DVEC_REDUCE_EXPR_HPP_

#include <mgcpp/expressions/dvec_expr.hpp>
#include <mgcpp/vector/forward.hpp>

namespace mgcpp
{
template <
    typename Expr,
    typename Expr::result_type::value_type (*Function)(
        typename Expr::result_type::parent_type const& vec)>
struct dvec_reduce_expr
    : public dvec_expr<dvec_reduce_expr<Expr, Function>>
{
    using expr_type = typename std::decay<Expr>::type;

    using result_type = typename expr_type::result_type::value_type;

    Expr _expr;

    inline explicit dvec_reduce_expr(Expr const& expr) noexcept;
    inline explicit dvec_reduce_expr(Expr&& expr) noexcept;

    inline decltype(auto) eval() const;
};

template <typename Expr>
inline decltype(auto) reduce_sum(dvec_expr<Expr> const& expr) noexcept;

template <typename Expr>
inline decltype(auto) reduce_mean(dvec_expr<Expr> const& expr) noexcept;
}

#endif
