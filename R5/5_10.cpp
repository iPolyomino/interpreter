#include <iostream>
#include "ast.h"

int main(void)
{
    Exp_variable *var_s = new Exp_variable("s");
    Statement *s = new St_return(var_s);
    s->print(std::cout);
    return 0;
}