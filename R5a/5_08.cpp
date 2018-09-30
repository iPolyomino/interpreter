#include <iostream>
#include "ast.h"

Statement *make_if()
{
    // cond
    Exp_variable *var_i = new Exp_variable("i");
    Expression *const_0 = new Exp_constant(Type_INT, 0);
    Expression *cond = new Exp_operation2(Operator_LT, var_i, const_0);

    // then
    Exp_variable *var_s = new Exp_variable("s");
    Expression *calc_s_minus = new Exp_operation2(Operator_MINUS, var_s, var_i);
    Statement *then = new St_assign(var_s, calc_s_minus);

    // else
    Expression *calc_s = new Exp_operation2(Operator_MINUS, var_s, var_i);
    Expression *calc_s_plus = new Exp_operation2(Operator_PLUS, var_s, var_i);
    Statement *els = new St_assign(var_s, calc_s_plus);

    return new St_if(cond, then, els);
}

int main(void)
{
    Statement *s = make_if();
    s->print(std::cout);
    return 0;
}