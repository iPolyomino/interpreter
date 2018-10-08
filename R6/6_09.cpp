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

Statement *make_while()
{
    // cond
    Exp_variable *var_i = new Exp_variable("i");
    Exp_variable *var_n = new Exp_variable("n");
    Expression *cond = new Exp_operation2(Operator_LE, var_i, var_n);

    // body
    Statement *state_if = make_if();
    Expression *const_1 = new Exp_constant(Type_INT, 1);
    Expression *calc_i_plus_1 = new Exp_operation2(Operator_PLUS, var_i, const_1);
    Statement *state_i = new St_assign(var_i, calc_i_plus_1);

    // body - St_list
    std::list<Statement *> slist;
    slist.push_back(state_if);
    slist.push_back(state_i);
    Statement *body = new St_list(slist);

    return new St_while(cond, body);
}

int main(void)
{
    Statement *s = make_while();

    std::map<std::string, Function *> func;
    std::map<std::string, int> gvar;
    std::map<std::string, int> lvar;

    lvar["i"] = -3;
    lvar["n"] = 3;
    lvar["s"] = 0;

    Return_t td = s->run(func, gvar, lvar);
    std::cout << "i = " << lvar["i"] << std::endl;
    std::cout << "n = " << lvar["n"] << std::endl;
    std::cout << "s = " << lvar["s"] << std::endl;

    return 0;
}