//HEADER FILE FOR PARSER
/*
Team Members
GOPICHAND PATURI         2011A7PS067H
SURI SRINIVAS PRAKASH    2011A7PS199H
ANIKET GARG		 2011A7PS170H
RANJITH NORI		 2011A7PS216H
**/

#include"parser.c"

void push(int toknum);
void pop();
void fill_tree_stack();
int rule_get(int nt,int t);
void print_token(int n);
void printParseTree();
void initializeParser();
void stack_push_rule(int rule);
void ParseTreeParse(FILE* fp);
