//=====================================================================
//
//     ast.cpp: mini-C プログラムの抽象構文木 (実装)
//
//            コンパイラ実習  2004 (c) 平岡佑介, 石浦菜岐佐
//
//=====================================================================

#include "ast.h"

std::string Type_string(Type t)
{
  switch (t)
  {
  case Type_INT:
    return "int";
  case Type_CHAR:
    return "char";
  default:
    return "UNDEF";
  }
}

std::string Operator_string(Operator o)
{
  switch (o)
  {
  case Operator_PLUS:
    return "+";
  case Operator_MINUS:
    return "-";
  case Operator_MUL:
    return "*";
  case Operator_DIV:
    return "/";
  case Operator_MOD:
    return "%";
  case Operator_LT:
    return "<";
  case Operator_GT:
    return ">";
  case Operator_LE:
    return "<=";
  case Operator_GE:
    return ">=";
  case Operator_NE:
    return "!=";
  case Operator_EQ:
    return "==";
  default:
    return "???";
  }
}

static int tmp = 0;

//---------------------------------------------------------------------
//  tab(int)
//    インデントを行うための関数 (ast.cpp の中だけで用いる)
//    indent で指定された段数の 2 倍のスペースを返す
//---------------------------------------------------------------------
static std::string tab(int indent)
{
  std::string tab_ = "";
  for (int i = 0; i < indent; i++)
  {
    tab_ += "  ";
  }
  return tab_;
}

void Exp_constant::print(std::ostream &os) const
{
  switch (type())
  {
  case Type_INT:
    os << value();
    break;
  case Type_CHAR:
  {
    os << '\'';
    if (value() == '\n')
    {
      os << '\\';
      os << 'n';
    }
    else if (value() == '\t')
    {
      os << '\\';
      os << 't';
    }
    else if (value() == '\\')
    {
      os << '\\';
      os << '\\';
    }
    else
    {
      os << (char)value();
    }
    os << '\'';
    break;
  }
  default:
    assert(0);
  }
}

void Exp_variable::print(std::ostream &os) const
{
  os << name();
}

int Exp_variable::run(
    std::map<std::string, Function *> &func,
    std::map<std::string, int> &gvar,
    std::map<std::string, int> &lvar) const
{
  std::map<std::string, int>::const_iterator p;
  if ((p = lvar.find(name())) != lvar.end())
  {
    return p->second;
  }
  else if ((p = gvar.find(name())) != gvar.end())
  {
    return p->second;
  }
  else
  {
    std::cerr << "undefined variable p" << std::endl;
    exit(1);
  }
};

void Exp_operation1::print(std::ostream &os) const
{
  os << "(" << Operator_string(operation());
  if (operand())
  {
    operand()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << ")";
}

void Exp_operation2::print(std::ostream &os) const
{
  os << "(";
  if (operand1())
  {
    operand1()->print(os);
  }
  else
  {
    os << "UNDEF operand1";
  }
  os << " " << Operator_string(operation()) << " ";
  if (operand2())
  {
    operand2()->print(os);
  }
  else
  {
    os << "UNDEF operand2";
  }
  os << ")";
}

Exp_function::~Exp_function()
{
  for (auto item : args_)
  {
    delete item;
  }
}

void Exp_function::print(std::ostream &os) const
{
  os << name();
  os << "(";
  bool isCommaRequired = false;
  for (auto item : args_)
  {
    if (isCommaRequired)
    {
      os << ",";
    }
    item->print(os);
    isCommaRequired = true;
  }
  os << ")";
}

int Exp_function::run(
    std::map<std::string, Function *> &func,
    std::map<std::string, int> &gvar,
    std::map<std::string, int> &lvar) const
{
  return 0;
}

void St_assign::print(std::ostream &os, int indent) const
{
  os << tab(indent);
  if (lhs())
  {
    lhs()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << " = ";
  if (rhs())
  {
    rhs()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << ";" << std::endl;
}

St_list::~St_list()
{
  for (auto state : statements_)
  {
    delete state;
  }
}

void St_list::print(std::ostream &os, int indent) const
{
  for (auto state : statements_)
  {
    state->print(os, indent);
  }
}

void St_if::print(std::ostream &os, int indent) const
{
  os << tab(indent) << "if (";
  if (condition())
  {
    condition()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << ") {" << std::endl;
  then_part()->print(os, indent + 1);
  os << tab(indent) << "}";
  if (else_part())
  {
    os << " else {" << std::endl;
    else_part()->print(os, indent + 1);
    os << tab(indent) << "}" << std::endl;
  }
}

void St_while::print(std::ostream &os, int indent) const
{
  os << tab(indent) << "while (";
  if (condition())
  {
    condition()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << ") {" << std::endl;
  body()->print(os, indent + 1);
  os << tab(indent) << "}" << std::endl;
}

void St_return::print(std::ostream &os, int indent) const
{
  os << tab(indent) << "return ";
  if (value())
  {
    value()->print(os);
  }
  else
  {
    os << "UNDEF";
  }
  os << ";" << std::endl;
}

void St_function::print(std::ostream &os, int indent) const
{
  os << tab(indent);
  function_.print(os);
  os << ";" << std::endl;
}

void Variable::print(std::ostream &os) const
{
  os << Type_string(type()) << " " << name();
}

Function::~Function()
{
  for (auto arg : args_)
  {
    delete arg;
  }
  for (auto local_var : local_vars_)
  {
    delete local_var;
  }
  delete body_;
}

void Function::print(std::ostream &os) const
{
  os << Type_string(type()) << " " << name() << "(";
  bool isCommaRequired = false;
  for (auto arg : args_)
  {
    if (isCommaRequired)
    {
      os << ", ";
    }
    arg->print(os);
  }
  os << ") {" << std::endl;
  for (auto local_var : local_vars_)
  {
    os << tab(1);
    local_var->print(os);
    os << ";" << std::endl;
  }

  body()->print(os, 1);
  os << "}" << std::endl;
}

Program::~Program()
{
  for (auto v : vars_)
  {
    delete v;
  }
  for (auto fn : funcs_)
  {
    delete fn;
  }
  delete main_;
}

void Program::print(std::ostream &os) const
{
  for (auto v : vars_)
  {
    v->print(os);
    os << ";" << std::endl;
  }
  for (auto f : funcs_)
  {
    f->print(os);
  }
  main()->print(os);
}
