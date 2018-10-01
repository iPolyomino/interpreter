#include <iostream>
#include "ast.h"

int main(void)
{

    Variable *v = new Variable(Type_INT, "a");
    v->print(std::cout);
    return 0;
}