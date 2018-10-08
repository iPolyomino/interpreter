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

Function *make_function_asum()
{

    // args
    Variable *args_n = new Variable(Type_INT, "n");
    std::list<Variable *> args_list;
    args_list.push_back(args_n);

    // local vars
    Variable *var_s = new Variable(Type_INT, "s");
    Variable *var_i = new Variable(Type_INT, "i");
    std::list<Variable *> local_var_list;
    local_var_list.push_back(var_s);
    local_var_list.push_back(var_i);

    // body
    Exp_variable *exp_var_s = new Exp_variable("s");
    Expression *const_0 = new Exp_constant(Type_INT, 0);
    Statement *s_sub_0 = new St_assign(exp_var_s, const_0);

    Exp_variable *exp_var_i = new Exp_variable("i");
    Exp_variable *exp_var_n = new Exp_variable("n");
    Expression *exp_minus_n = new Exp_operation1(Operator_MINUS, exp_var_n);
    Statement *i_sub_minus_n = new St_assign(exp_var_i, exp_minus_n);

    Statement *statement_while = make_while();

    Statement *statement_return = new St_return(exp_var_s);

    // body - St_list
    std::list<Statement *> slist;
    slist.push_back(s_sub_0);
    slist.push_back(i_sub_minus_n);
    slist.push_back(statement_while);
    slist.push_back(statement_return);
    Statement *body = new St_list(slist);

    return new Function(Type_INT, "asum", args_list, local_var_list, body);
}

int main(void)
{
    Function *function_asum = make_function_asum();

    std::map<std::string, Function *> func;
    std::map<std::string, int> gvar;
    std::list<int> i_arglist;
    i_arglist.push_back(3);
    int r = function_asum->run(func, gvar, i_arglist);
    std::cout << r << std::endl;
    return 0;
}