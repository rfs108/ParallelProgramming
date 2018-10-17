#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
char string[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};
FILE *fp;
fp = fopen("cmb.txt","a");
for (int i=0;i<36;i++)
{
 
 for (int j=0;j<36;j++)
{
	for (int k=0;k<36;k++)
	{
	fprintf(fp,"%c",string[i]);
 fprintf(fp,"%c",string[j]);
  fprintf(fp,"%c\n",string[k]);
}
}
}
 return 0;

}
