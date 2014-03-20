#include<stdio.h>
#include<string.h>
#include<stddef.h>

//File pointers
FILE* fin;
FILE* fout;

//state variable
int state = 0;
int flag1=0,flag2=0,flag3=0;

//Input buffer
char input[100];
char* ch;
char* start = NULL;
char* current = NULL;

void file_init(void)
{
	fin = fopen("input.txt","r");  
	fout = fopen("output.txt","w");

	if(fin == NULL || fout == NULL) 
	{
	    printf("File init error\n");
	}
}


void retract(void)
{
   current--;
}

int checkid(char* ch)
{
	if(*ch == ';' || *ch == '$' || *ch == '(' || *ch == ')' || *ch == '{' || *ch == '}' || *ch == '[' || *ch == ']' || *ch == 0 || *ch == '<'
||*ch == ':'|| *ch == '>' || *ch == '=' || *ch == ',' || *ch == '!' || *ch == '*' || *ch == '+'||*ch == '-'||*ch == '*' || *ch == '/' || *ch == '%' || *ch == EOF)
	  return 1;
	else
	  return 0;
}

int alpha(char* ch)
{
	if((*ch>=97 && *ch<=122) ||(*ch >=65 && *ch<=90) )
	{
		return 1;
	}
	else
	    return 0;
}

void print_keyword(int n)
{
switch(n)
    {
	case 1: fprintf(fout,"TK_KWIF                if\n");break;
	case 2: fprintf(fout,"TK_KWINT                int\n");break;
	case 3: fprintf(fout,"TK_KWREP                rep\n");break;
	case 4: fprintf(fout,"TK_KWSTR                str\n");break;
	case 5: fprintf(fout,"TK_KWFDEF                fdef\n");break;
	case 6: fprintf(fout,"TK_KWFLS               false\n");break;
	case 7: fprintf(fout,"TK_KWBOL                bool\n");break;
	case 8: fprintf(fout,"TK_KWTRU                true\n");break;
	case 9: fprintf(fout,"TK_KWELS                else\n");break;
	case 10: fprintf(fout,"TK_KWLFT               float\n");break;
	case 11: fprintf(fout,"TK_KWWHL                while\n");break;
	case 12: fprintf(fout,"TK_KWUNT                until\n");break;
	case 13: fprintf(fout,"TK_KWRET                return\n");break;
    }
	flag3 = 1;
}

void print_id(void)
{
	fprintf(fout,"TK_ID                     ");
	while(start != current)
	{
	    fprintf(fout,"%c",*start);
	    start++;
	}
	fprintf(fout,"%c\n",*start);
	flag2 = 1;
}

void print_int(void)
{
	fprintf(fout,"TK_INT                    ");
	while(start != current)
	{
	    fprintf(fout,"%c",*start);
	    start++;
	}
	fprintf(fout,"%c\n",*start);
	flag2 = 1;
}

void print_float(void)
{
	fprintf(fout,"TK_FLOAT                  ");
	while(start != current)
	{
	    fprintf(fout,"%c",*start);
	    start++;
	}
	fprintf(fout,"%c\n",*start);
	flag2 = 1;
}

int isnum(char* ch)
{
	if (*ch >=48 && *ch<=57)
	  return 1;
	return 0;
}

void print_token(int n)
{
    switch(n)
    {
	case 1: fprintf(fout,"TK_LP                     {\n");break;
	case 2: fprintf(fout,"TK_RP                     }\n");break;
	case 3: fprintf(fout,"TK_LB                     (\n");break;
	case 4: fprintf(fout,"TK_RB                     )\n");break;
	case 5: fprintf(fout,"TK_COM                     ,\n");break;
	case 6: fprintf(fout,"TK_SEMICOL                     ;\n");break;
	case 7: fprintf(fout,"TK_PLUS                     +\n");break;
	case 8: fprintf(fout,"TK_MINUS                     -\n");break;
	case 9: fprintf(fout,"TK_MUL                     *\n");break;
	case 10: fprintf(fout,"TK_LSB                     [\n");break;
	case 12: fprintf(fout,"TK_RSB                     ]\n");break;
	case 13: fprintf(fout,"TK_COL                     :\n");break;
	case 14: fprintf(fout,"TK_$                      $\n");break;
	case 15: fprintf(fout,"TK_EQ                     =\n");break;
	case 16: fprintf(fout,"TK_NOT                     !\n");break;
	case 17: fprintf(fout,"TK_GT                      >\n");break;
	case 18: fprintf(fout,"TK_LT                      <\n");break;
	case 19: fprintf(fout,"TK_GET                    >=\n");break;
	case 20: fprintf(fout,"TK_LET                    <=\n");break;
	case 21: fprintf(fout,"TK_NEQ                     !=\n");break;
	case 22: fprintf(fout,"TK_EQEQ		          ==\n");break;
    }  
	flag1 = 1;
}



int get_state(char* ch,int state)
{
       int next_state = 0;
       switch(state)
       {
	     case 0: 
	     {
		switch(*ch)
		{
			case '{': {print_token(1);next_state = 0;start = current;break;}

			case '}': {print_token(2);next_state = 0;start = current;break;}

			case '(': {print_token(3);next_state = 0;start = current;break;}

			case ')': {print_token(4);next_state = 0;start = current;break;}

			case ',': {print_token(5);next_state = 0;start = current;break;}

			case ';': {print_token(6);next_state = 0;start = current;break;}

			case '+': {print_token(7);next_state = 0;start = current;break;}

			case '-': {print_token(8);next_state = 0;start = current;break;}

			case '*': {print_token(9);next_state = 0;start = current;break;}

			case '/': {print_token(10);next_state = 0;start = current;break;}

			case '[': {print_token(11);next_state = 0;start = current;break;}

			case ']': {print_token(12);next_state = 0;start = current;break;}

			case ':': {print_token(13);next_state = 0;start = current;break;}

			case '$': {print_token(14);next_state = 0;start = current;break;}

			case 'f': {next_state = 1;break;}

			case 'i': {next_state = 2;break;}

			case 'r': {next_state = 3;break;}

			case 'e': {next_state = 4;break;}

			case 'b': {next_state = 5;break;}

			case 's': {next_state = 6;break;}

			case 'w': {next_state = 7;break;}

			case 'u': {next_state = 8;break;}

			case 't': {next_state = 9;break;}

			case '=': {next_state = 51;break;}

			case '!': {next_state = 52;break;}

			case '>': {next_state = 53;break;}

			case '<': {next_state = 54;break;}

			case '"': {next_state = 55;break;}			


			default: if(alpha(ch)){next_state = 10;}
				  else if(isnum(ch))
				   {
					next_state = 56;	
					break;
       				   } 
				else {
					fprintf(fout,"TK_ERR                    ");
					while(*current != '$' && *current != EOF && *current !=0 && *current != '\0')
					{
						fprintf(fout,"%c",*current);
						current++;
					}
					fprintf(fout,"\n");
					retract();
					break;
				     }

		}
		break;
	     }

	   case 1:
	   {
		switch(*ch)
		{
			case 'd': {next_state = 11;break;}

			case 'a': {next_state = 12;break;}

			case 'l': {next_state = 13;break;}

			default: {if(checkid(ch)){next_state = 15;retract();break;} else{next_state = 10;break;}}
		}
		break;
	   }

	   case 2:
	   {
		if(*ch == 'n')
		{
			next_state = 14;
			break;
		}
		else if(*ch == 'f')
		{
			next_state = 16;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else{next_state = 10;break;}
		}
		break;
	   }

	   case 3:
	   {
		if(*ch == 'e')
		{

			next_state = 17;
			break;
		}
		else 
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
		break;
	   }

	  case 4:
	  {
		if(*ch == 'l')
		{
			next_state = 18;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
		break;
	  }

	 case 5:
	 {
		if(*ch == 'o')
		{
			next_state = 19;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
		break;
	 }

	case 6:
	{
		if(*ch == 't')
		{
			next_state = 20;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
		break;
	}

	case 7:
	{
		if(*ch == 'h')
		{
			next_state = 21;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}

		break;
	}

	case 8:
	{
		if(*ch == 'n')
		{
			next_state = 22;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}

		break;
	}

	case 9:
	{
		if(*ch == 'r')
		{
			next_state = 23;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
		break;
	}

	case 10:
	{
		if(checkid(ch))
		{
			retract();
			print_id();
			next_state = 0;
			break;
		}		
		else if(*ch == '_' || (*ch >= '0' && *ch <= '9') || alpha(ch))
		{
			next_state = 10;
			break;
		}
		break;

	}

	case 11:
	{
		if(*ch == 'e')
		{
			next_state =  24;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;}
		break;
	}

	case 12:
	{
		if(*ch == 'l')
		{
			next_state =  25;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;}
	}

	case 13:
	{
		if(*ch == 'o')
		{
			next_state =  26;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;}
	}

	case 14:
	{
		if(*ch == 't')
		{
			next_state =  27;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;}
	}

	case 15:
	{
		retract();
		print_id();
		next_state = 0;
		break;
	}

	case 16:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(1); //prints 'if' keyword
		      next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}

	case 17:
	{
		if(*ch == 'p')
		{
			next_state = 28;
			break;
		}
		else if(*ch == 't')
		{
			next_state = 29;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;
	}

	   case 18:
	   {
		if(*ch == 's')
		{
			next_state = 30;
			break;
		}
		else 
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	   }

	 case 19:
	 {
		if(*ch == 'o')
		{
			next_state = 31;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 20:
	 {
		if(*ch == 'r')
		{
			next_state = 32;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 21:
	{
		if(*ch == 'i')
		{
			next_state = 33;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}

	case 22:
	{
		if(*ch == 't')
		{
			next_state = 34;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}
	case 23:
	{
		if(*ch == 'u')
		{
			next_state = 35;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}
	case 24:
	{
		if(*ch == 'f')
		{
			next_state = 36;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}

	case 25:
	{
		if(*ch == 's')
		{
			next_state = 37;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}

	case 26:
	{
		if(*ch == 'a')
		{
			next_state = 38;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}

	case 27:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(2); //prints 'int' keyword
		      next_state=  0;
		      break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}

	case 28:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(3); //prints 'rep' keyword
		      next_state = 0;
		      break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}

	   case 29:
	   {
		if(*ch == 'u')
		{
			next_state = 39;
			break;
		}
		else 
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	   }
	   case 30:
	   {
		if(*ch == 'e')
		{
			next_state = 40;
			break;
		}
		else 
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	   }

	 case 31:
	 {
		if(*ch == 'l')
		{
			next_state = 41;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 32:
	 {
		if(checkid(ch))
		{
		      retract();
		      print_keyword(4); //prints 'str' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	 }

	 case 33:
	 {
		if(*ch == 'l')
		{
			next_state = 42;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 34:
	{
		if(*ch == 'i')
		{
			next_state = 43;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}


	case 35:
	{
		if(*ch == 'e')
		{
			next_state =  44;
			break;
		}
		else if(checkid(ch)){next_state = 15;retract();break;} 
		else {next_state = 10;break;}
	}

	case 36:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(5); //prints 'fdef' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}

	case 37:
	 {
		if(*ch == 'e')
		{
			next_state = 45;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 38:
	 {
		if(*ch == 't')
		{
			next_state = 46;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }

	case 39:
	 {
		if(*ch == 'r')
		{
			next_state = 47;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }
	case 40:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(6); //prints 'false' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 41:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(7); //prints 'bool' keyword
			next_state = 0;
			break;

		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 42:
	 {
		if(*ch == 'e')
		{
			next_state = 48;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }
	case 43:
	{
		if(*ch == 'l')
		{
			next_state = 49;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	}
	case 44:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(8); //prints 'true' keyword
		      next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 45:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(9); //prints 'else' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 46:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(10); //prints 'float' keyword
			next_state = 0;	
			break;	
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 47:
	 {
		if(*ch == 'n')
		{
			next_state = 50;
			break;
		}
		else
		{
			if(checkid(ch)){next_state = 15;retract();break;} else {next_state = 10;break;}
		}
	 }
	case 48:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(11); //prints 'while' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 49:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(12); //prints 'until' keyword
			next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}
	case 50:
	{
		if(checkid(ch))
		{
		      retract();
		      print_keyword(13); //prints 'return' keyword
		      next_state = 0;
			break;
		}
		else
		{
		      next_state = 10;
		      break;
		}
	}

	case 51:
	{
		if(*ch == '=')
		{
			print_token(22);
			next_state = 0;
			break;
		}
		else
		{
			print_token(15);
			retract();
			next_state = 0;
			break;
		}
	}

	case 52:
	{
		if(*ch == '=')
		{
			print_token(21);
			next_state = 0;
			break;
		}
		else
		{
			print_token(16);
			retract();
			next_state = 0;
			break;
		}
	}

	case 53:
	{
		if(*ch == '=')
		{
			print_token(19);
			next_state = 0;
			break;
		}
		else
		{
			print_token(17);
			retract();
			next_state = 0;
			break;
		}
	}
	case 54:
	{
		if(*ch == '=')
		{
			print_token(20);
			next_state = 0;
			break;
		}
		else
		{
			print_token(18);
			retract();
			next_state = 0;
			break;
		}
	}

	case 55:
	{
		if(*(ch-1) == '"')
		{fprintf(fout,"TK_STRING            ");}
		if(*ch=='"')
		{
			fprintf(fout,"\n");
			next_state = 0;
			break;
		}
		else
		{
			fprintf(fout,"%c",*ch);
			next_state = 55;
			break;
		}
	}

	case 56:
	{		
		if(*ch == '.')
		{
			next_state = 57;
			break;
		}
		else if(isnum(ch))
		{
			next_state = 56;
			break;
		}
		else
		{
			retract();
			next_state = 58;
			break;
		}
	}

	case 57:
	{
		if(!isnum(ch))
		{
			      retract();
			      print_float();
			      next_state = 0;
			      break;
		}
			else
			{
				next_state = 57;
				break;
			}

	}

	case 58:	
	{
		retract();		
		print_int();
		next_state = 0;
		break;
	}
    }

}
	//printf("nextState = %d\n",next_state);
	return next_state;
}

int main(void)
{
    file_init();
    fprintf(fout,"TYPE                     LEXEME\n");
    fprintf(fout,"-------------------------------\n");
    while((fscanf(fin,"%s",input)) != EOF)
    {
	ch = input;
	start = input;
	current = input;
	while(*current != '\0' || state != 0)
	{
	    state = get_state(current,state);
	    current++;
	    if(flag1 == 1 || flag2 == 1 || flag3 == 1)
	    {
		start = current;
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
	    }
	}
    } 
	fprintf(fout,"TK_EOF\n");
	fcloseall();
	return 0;
}
