#include <iostream>
#include "ast.h"

int main(void)
{
    Exp_variable *var_a = new Exp_variable("a");
    std::list<Expression *> arglist;
    arglist.push_back(var_a);
    Statement *s = new St_function("putint", arglist);
    s->print(std::cout);
    return 0;
}