int asum(int n)
{
int s;
int i;
s = 0;
i = -n;
while(i<=n)
{
if (i<0)
{
s = s - i;
}
else
{
s = s + i;
}
i = i + 1;
}
return s;
}