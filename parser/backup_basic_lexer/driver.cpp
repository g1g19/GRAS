#include<cstdlib>
#include<cstdlib>
#include<cstdio>

using namespace std;

int main(void)
{
     char s[100];
     system("gcc -o lex lexer.c");
     system("./lex");	
     
     FILE* fp = NULL;
     fp = fopen("output.txt","r");
     int n;
     printf("Press 1 to exit\n");
     scanf("%d",&n);
      fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
     while(n != 1 && (fscanf(fp,"%s",s))!=EOF)
     {
	fscanf(fp,"%s",s);
	printf("%s        ",s);
	if((fscanf(fp,"%s",s)) != EOF)
	{
		printf("%s\n",s);
	}
	else
	{
		exit(0);
		printf("\n");
	}	
	scanf("%d",&n);
     }     
     printf("\n");
     return 0;
}
