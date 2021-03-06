/*
Team Members
GOPICHAND PATURI         2011A7PS067H
SURI SRINIVAS PRAKASH    2011A7PS199H
ANIKET GARG		 2011A7PS170H
RANJITH NORI		 2011A7PS216H
**/



#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int s[21][25] = {0};//PARSE TABLE
FILE* fin = NULL;
FILE* fout = NULL;

int stack[100]; int top1 = -1; //ACTUAL STACK
int tree_stack[100]; int top2 = -1;//STACK TO PRINT PRE-ORDER TRAVERSAL FINALLY

//STACK PUSH
void push(int toknum)
{
	stack[++top1] = toknum;
}

//STACK POP
void pop()
{
	tree_stack[++top2] = stack[top1];
	top1--;
}

//INITIALIZE TREE STACK
void fill_tree_stack()
{
	int i;
	for (i=0;i<sizeof(tree_stack);i++)
	tree_stack[i]=-1;
}

int rule_get(int nt,int t)
{
	return s[nt-100][t];
}


enum 
{
    TK_LP,TK_RP,TK_KWINT,TK_KWLFT,TK_LB,TK_RB,TK_INT,TK_FLOAT,TK_ID,TK_KWBOL,TK_KWSTR,TK_KWIF,TK_KWWHL,TK_EQ,TK_KWELS,TK_GET,TK_SEMICOL,TK_AND,
    TK_KWTRU,TK_KWFLS,TK_PLUS,TK_MINUS,TK_MUL,TK_DIV,TK_$
}token; //terminal

enum
{
	TK_PRG=100,TK_STMTS,TK_STMT,TK_ASSIGN,TK_INIT,TK_INIT2,TK_IFEXPR,TK_IFSTMT,TK_BLOCK,TK_IFEXPR2,TK_WHILEEXPR,
	TK_EXP,TK_EXP2,TK_TERM,TK_TERM2,TK_FACTOR,TK_EXPBOOL,TK_EXPBOOL2,TK_TERMBOOL,TK_TERMBOOL2,TK_DATATYPE
}tok; //non-terminal



//TOKEN PRINT TO TERMINAL
void print_token(int n)
{
    switch(n)
    {
	case TK_LP: printf("TK_LP\n");break;
	case TK_RP: printf("TK_RP\n");break;
	case TK_LB: printf("TK_LB\n");break;
	case TK_RB: printf("TK_RB\n");break;
	case TK_SEMICOL: printf("TK_SEMICOL\n");break;
	case TK_PLUS: printf("TK_PLUS\n");break;
	case TK_MINUS: printf("TK_MINUS\n");break;
	case TK_MUL: printf("TK_MUL\n");break;
	case TK_DIV: printf("TK_DIV\n");break;
	case TK_$: printf("TK_$\n");break;
	case TK_EQ: printf("TK_EQ\n");break;
	case TK_GET: printf("TK_GET\n");break;
	case TK_AND: printf("TK_AND\n");break;
	case TK_INT: printf("TK_INT\n");break;	
	case TK_FLOAT: printf("TK_FLOAT\n");break;
	case TK_KWINT: printf("TK_KWINT\n");break;
	case TK_KWLFT: printf("TK_KWLFT\n");break;
	case TK_ID: printf("TK_ID\n");break;
	case TK_KWBOL: printf("TK_KWBOL\n");break;	
	case TK_KWSTR: printf("TK_KWSTR\n");break;
	case TK_KWIF: printf("TK_KWIF\n");break;
	case TK_KWELS: printf("TK_KWELS\n");break;
	case TK_KWTRU: printf("TK_KWTRU\n");break;
	case TK_KWFLS: printf("TK_KWFLS\n");break;
	case TK_KWWHL: printf("TK_KWWHL\n");break;	

	case TK_PRG: printf("TK_PRG\n");break;
	case TK_STMTS: printf("TK_STMTS\n");break;
	case TK_STMT: printf("TK_STMT\n");break;
	case TK_ASSIGN: printf("TK_ASSIGN\n");break;
	case TK_INIT: printf("TK_INIT\n");break;

	case TK_INIT2: printf("TK_INIT2\n");break;
	case TK_IFEXPR: printf("TK_IFEXPR\n");break;
	case TK_IFSTMT: printf("TK_IFSTMT\n");break;
	case TK_BLOCK: printf("TK_BLOCK\n");break;
	case TK_IFEXPR2: printf("TK_IFEXPR2\n");break;

	case TK_WHILEEXPR: printf("TK_WHILEEXPR\n");break;
	case TK_EXP: printf("TK_EXP\n");break;
	case TK_EXP2: printf("TK_EXP2\n");break;
	case TK_TERM: printf("TK_TERM\n");break;
	case TK_TERM2: printf("TK_TERM2\n");break;

	case TK_FACTOR: printf("TK_FACTOR\n");break;
	case TK_EXPBOOL: printf("TK_EXPBOOL\n");break;
	case TK_EXPBOOL2: printf("TK_EXPBOOL2\n");break;
	case TK_TERMBOOL: printf("TK_TERMBOOL\n");break;
	case TK_TERMBOOL2: printf("TK_TERMBOOL2\n");break;

	case TK_DATATYPE: printf("TK_DATATYPE\n");break;
    }  
	
}



//PREORDER TRAVERSAL OF THE TREE
void printParseTree()
{
	int i=0;
	//printf("\nPreorder traversal : \n");
	while (tree_stack[i]!=-1 && i<sizeof(tree_stack))
	{
	 	print_token(tree_stack[i++]);
	}
}



// PARSE TABLE....RULE NUMBERS INITIALIZED
void initializeParser()
{
	s[0][0]=1; s[0][24]=43;
	s[1][1]=3; s[1][2]=2; s[1][3]=2; s[1][8]=2; s[1][9]=2; s[1][10]=2; s[1][11]=2; s[1][12]=2;
	s[2][2]=5; s[2][3]=5; s[2][8]=4; s[2][9]=5; s[2][10]=5; s[2][11]=6; s[2][12]=7;
	s[3][8]=8; s[3][16]=43;
	s[4][2]=9; s[4][3]=9; s[4][9]=9; s[4][10]=9;
	s[5][13]=11; s[5][16]=10;
	s[6][0]=43; s[6][2]=43; s[6][3]=43; s[6][8]=43; s[6][9]=43; s[6][10]=43; s[6][11]=12; s[6][12]=43;
	s[7][11]=13;
	s[8][0]=15; s[8][2]=14; s[8][3]=14; s[8][8]=14; s[8][9]=14; s[8][10]=14; s[8][11]=14; s[8][12]=14;
	s[9][1]=16; s[9][2]=16; s[9][3]=16; s[9][8]=16; s[9][9]=16; s[9][10]=16; s[9][11]=16; s[9][12]=16; s[9][14]=17;
	s[10][1]=43; s[10][2]=43; s[10][3]=43; s[10][8]=43; s[10][9]=43; s[10][10]=43; s[10][11]=43; s[10][12]=18;
	s[11][5]=43; s[11][6]=19; s[11][7]=19; s[11][8]=19; s[11][10]=19; s[11][15]=43; s[11][16]=43; s[11][17]=43; s[11][18]=19; s[11][19]=19;
	s[12][1]=22;s[12][5]=22; s[12][15]=22; s[12][16]=22; s[12][17]=22; s[12][20]=20; s[12][21]=21;
	s[13][6]=23; s[13][7]=23; s[13][8]=23; s[13][10]=23; s[13][18]=23; s[13][19]=23;
	s[14][1]=26;s[14][5]=26; s[14][15]=26; s[14][16]=26; s[14][17]=26; s[14][20]=26; s[14][21]=26; s[14][22]=24; s[14][23]=25;
	s[15][5]=43; s[15][6]=28; s[15][7]=29; s[15][8]=27; s[15][10]=32; s[15][15]=43; s[15][16]=43; s[15][17]=43; s[15][18]=30; s[15][19]=31;
	s[15][1]=43;s[15][20]=43; s[15][21]=43; s[15][22]=43; s[15][23]=43;
	s[16][5]=43; s[16][6]=33; s[16][7]=33; s[16][8]=33; s[16][10]=33; s[16][16]=43; s[16][18]=33; s[16][19]=33;
	s[17][1]=35;s[17][5]=35; s[17][16]=35; s[17][17]=34;
	s[18][5]=43; s[18][6]=36; s[18][7]=36; s[18][8]=36; s[18][10]=36; s[18][16]=43; s[18][17]=43; s[18][18]=36; s[18][19]=36;
	s[19][1]=38;s[19][5]=38; s[19][15]=37; s[19][16]=38; s[19][17]=38;
	s[20][2]=39; s[20][3]=40;s[20][8]=43;s[20][9]=41;s[20][10]=42;	
}

//RULE BOOK....TO PUSH APPROPRIATE NON-TERMINALS 
void stack_push_rule(int rule)
{
	
switch (rule)
{
	case 1 :
		pop(); push(TK_RP);push(TK_STMTS);push(TK_LP); break;
	case 2 :
		pop(); push(TK_STMTS);push(TK_STMT); break;
	case 3 :
		pop();break;
	case 4 :
		pop(); push(TK_SEMICOL); push(TK_ASSIGN); break;
	case 5 :
		pop(); push(TK_SEMICOL); push(TK_INIT); break;
	case 6 :
		pop(); push(TK_IFEXPR); break;
	case 7 :
		pop(); push(TK_WHILEEXPR); break;
	case 8 :
		pop(); push(TK_EXPBOOL);push(TK_EQ);push(TK_ID); break;
	case 9 :
		pop(); push(TK_INIT2);push(TK_ID);push(TK_DATATYPE); break;
	case 10 :
		pop();break;
	case 11 :
		pop(); push(TK_EXPBOOL);push(TK_EQ);break;
	case 12 :
		pop(); push(TK_IFEXPR2);push(TK_IFSTMT);break;
	case 13 :
		pop(); push(TK_BLOCK);push(TK_RB);push(TK_EXPBOOL);push(TK_LB);push(TK_KWIF);break;
	case 14 :
		pop(); push(TK_STMT);break;
	case 15 :
		pop(); push(TK_RP);push(TK_STMTS);push(TK_LP);break;
	case 16 :
		pop(); break;
	case 17 :
		pop(); push(TK_BLOCK);push(TK_KWELS); break;
	case 18 :
		pop();push(TK_BLOCK);push(TK_RB);push(TK_EXPBOOL);push(TK_LB);push(TK_KWWHL);break;
	case 19 :
		pop();push(TK_EXP2);push(TK_TERM); break;
	case 20 :
		pop();push(TK_EXP2);push(TK_TERM);push(TK_PLUS);break;
	case 21 :
		pop();push(TK_EXP2);push(TK_TERM);push(TK_MINUS);break;
	case 22 :
		pop();break;
	case 23 :
		pop(); push(TK_TERM2);push(TK_FACTOR); break;
	case 24 :
		pop();push(TK_TERM2);push(TK_FACTOR);push(TK_MUL); break;
	case 25 :
		pop();push(TK_TERM2);push(TK_FACTOR);push(TK_DIV);break;
	case 26 :
		pop();break;
	case 27 :
		pop(); push(TK_ID); break;
	case 28 :
		pop(); push(TK_INT); break;
	case 29 :
		pop(); push(TK_FLOAT); break;
	case 30 :
		pop(); push(TK_KWTRU); break;
	case 31 :
		pop(); push(TK_KWFLS); break;
	case 32 :
		pop();push(TK_KWSTR);break;
	case 33 :
		pop(); push(TK_EXPBOOL2);push(TK_TERMBOOL);break;
	case 34 :
		pop(); push(TK_EXPBOOL2);push(TK_TERMBOOL);push(TK_AND);break;
	case 35 :
		pop();break;
	case 36 :
		pop(); push(TK_TERMBOOL2);push(TK_EXP);break;
	case 37 :
		pop(); push(TK_TERMBOOL2);push(TK_EXP);push(TK_GET); break;
	case 38 :
		pop();break;
	case 39 :
		pop();push(TK_KWINT);break;
	case 40 :
		pop(); push(TK_KWLFT); break;
	case 41 :
		pop(); push(TK_KWBOL); break;
	case 42 :
		pop();push(TK_KWSTR);break;
	case 43 ://SYNCH
		pop();break;
}
}


//FUNCTION TO TAKE AND PARSE TOKENS
void ParseTreeParse(FILE* fp)
{
	int cur,ruleno;
	char token[40];
	push(TK_$);
	push(TK_PRG);
	while(fscanf(fp,"%s %d",token,&cur) != EOF)
	{	
		while (stack[top1] >= 100)
	{
		ruleno = rule_get(stack[top1],cur);
		stack_push_rule(ruleno); 
	}
	
	if (stack[top1]==TK_$) 
	{
		break;
	}
	pop(); 
	}

}



int main(void)
{
	FILE* fp = fopen("output.txt","r");
	initializeParser(); 
	fill_tree_stack();
	fin = fopen("output.txt","r");
	fout = fopen("finaloutput.txt","w");
	ParseTreeParse(fp);
	printParseTree(fp); //preorder
}

