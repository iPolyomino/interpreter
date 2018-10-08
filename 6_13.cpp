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

Function *make_function_main()
{
    // global variable
    Variable *var_g = new Variable(Type_INT, "g");
    std::list<Variable *> vars;
    vars.push_back(var_g);

    // asum function
    Function *asum = make_function_asum();
    std::list<Function *> funcs;
    funcs.push_back(asum);

    // main function
    std::list<Variable *> arglist;

    Variable *var_a = new Variable(Type_INT, "a");
    std::list<Variable *> local_vars;
    local_vars.push_back(var_a);

    Exp_variable *exp_var_g = new Exp_variable("g");
    Expression *const_3 = new Exp_constant(Type_INT, 3);
    Statement *g_sub_3 = new St_assign(exp_var_g, const_3);

    Exp_variable *exp_var_a = new Exp_variable("a");
    std::list<Expression *> arglist_g;
    arglist_g.push_back(exp_var_g);
    Expression *exp_asum = new Exp_function("asum", arglist_g);
    Statement *a_sub_asum_g = new St_assign(exp_var_a, exp_asum);

    std::list<Expression *> arglist_a;
    arglist_a.push_back(exp_var_a);
    Statement *statement_putint = new St_function("putint", arglist_a);

    // body - St_list
    std::list<Statement *> slist;
    slist.push_back(g_sub_3);
    slist.push_back(a_sub_asum_g);
    slist.push_back(statement_putint);
    Statement *body = new St_list(slist);

    return new Function(Type_INT, "main", arglist, local_vars, body);
}
int main(void)
{
    std::list<Variable *> gvar;
    std::list<Function *> func;
    gvar.push_back(new Variable(Type_INT, "g"));
    func.push_back(make_function_asum());

    Program *p = new Program(gvar, func, make_function_main());
    p->run();

    return 0;
}