int factorial(int num)
{
  if (num == 0)
  {
    return 1;
  }
  return num * factorial(num - 1);
}

int main()
{
  int n;
  putchar('n');
  putchar('=');
  n = getint();

  putint(factorial(n));
  putchar('\n');
}