#include<time.h>
#include<stdio.h>
int main()
{
time_t rawtime;
printf("%lu\n",rawtime);
time(&rawtime);
printf("%lu\n",rawtime);
printf("%s\n",asctime(localtime(&rawtime)));
return 0;
}
