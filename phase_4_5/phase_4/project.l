/*
HY-340 PROJECT -> A PHASE SUMMER SEMESTER 2018
CHRIS MAVRIKIS 
DIMITRIS KARATHANASIS

*/

%{
#include "types.h"
#include <unistd.h>
#include "parser.h"
%}

%option noyywrap
%option yylineno

%{
extern 	char *yytext;
	

	void plus_token(){
		number_of_token=number_of_token+1;
	}

	void reset()
	{
		number_of_token=0;
	}

	char * com (char* str)
	{
		plus_token();
		return str;
	}

	char * dcom(char *str){
		plus_token();
		return str;
	}

	char * nestedcom(char *str){
		plus_token();
		return str;
	}



%}

IF  					"if" 
ELSE        			"else"
WHILE					"while"
FOR						"for"
FUNCTION				"function"
RETURN 					"return"
BREAK					"break"
CONTINUE				"continue"
AND						"and"
NOT 					"not"
OR						"or"
LOCL					"local"
TRUE					"true"
FALSE					"false"
NIL						"nil"
ASSIGN					"="

PLUS					"+"
MINUS					"-"
MULTIPLY				"*"
DIVIDE 					"/"
MODULO					"%"

EQUAL 					"=="
DIFFERENT				"!="	
DPLUS					"++"	
DMINUS					"--"	
BIGGER 					">"
SMALLER 				"<"
BIGGER_EQUAL 			">="
SMALLER_EQUAL 			"<="
LBRACKET 				\{
RBRACKET 				\}
LSBRACKET 				\[	
RSBRACKET 				\]
LPARENTHESIS			\(
RPARENTHESIS 			\)
SEMICOLON 	 			";"
COMMA 					","
COLON        			":" 	
DCOLON       			"::"
DOT         			"."
DDOT         			".."
SPACE        			" "
NEWLINE		 			\n
TAB 		 			\t
UNDERSCORE   			\_
DIGIT                   [0-9]
INTEGER					{DIGIT}+		
FLOAT					{INTEGER}"."{INTEGER}
IDENTIFIER              [a-zA-Z][a-zA-Z_0-9]*
ILLEGAL                 [\$|\`|\~|\@|\^|\_|\?|\#\!]
STRING        			\"
COMMENT  				"//".*

%x DCOMMENT1

%%
{IF}   				{return IF;}
{ELSE}              {return ELSE;}
{WHILE}             {return WHILE;}
{FOR}				{return FOR;}
{FUNCTION}			{return FUNCTION;}
{RETURN} 			{return RETURN;}
{BREAK} 			{return BREAK;}
{CONTINUE}			{return CONTINUE;}
{LOCL} 			{return LOCL;}
{TRUE}              {return TRUE;}
{FALSE}             {return FALSE;}
{NIL}               {return NIL;}

{AND} 				{return AND;}
{OR} 				{return OR;}
{NOT} 				{return NOT;}


{ASSIGN}            {return ASSIGN;}

{PLUS}              {return PLUS;}
{MINUS}             {return MINUS;}
{MULTIPLY}          {return MULTIPLY;}
{DIVIDE}            {return DIVIDE;}
{MODULO}            {return MODULO;}
{DPLUS}             {return DPLUS;}
{DMINUS} 			{return DMINUS;}

{EQUAL} 			{return EQUAL;}
{DIFFERENT}         {return DIFFERENT;}
{BIGGER}            {return BIGGER;}
{SMALLER}           {return SMALLER;}
{BIGGER_EQUAL}      {return BIGGER_EQUAL;}
{SMALLER_EQUAL}     {return SMALLER_EQUAL;}


{INTEGER}           {yylval.intVal = atoi(yytext);
					return INTEGER;}
{IDENTIFIER}        {yylval.stringVal = strdup(yytext);
					return IDENTIFIER;}

{STRING}            {
	// BEGIN(STRING);
	char *string = (char*)malloc(strlen(yytext)+1);
	int str=0;
	char inv;
	int i=0;
	int errid = 0;
	int ctr=0; 
	while (1)
	{
		str=input();
		string[i] = str;
		string = (char*)realloc(string, strlen(string)+1);
		if (str == EOF)
		{
			errid=1;
							//error_counter++;
			break;
		}

						//if last char is '"' and previous is not escape '\' exit string 
		if(string[i] == '\"' && string[i-1]!='\\'){
			ctr++;
			if(ctr == 1){
							//printf("End of string? %s\n", string);
				string[i] = '\0';
				break;

			}
		}
		if (string[i - 1] == '\\')
		{
			if (string[i] == 'n')
			{
				string[i - 1] = ' ';
				string[i] = '\n';
			}
			else if (string[i] == 't')
			{
				string[i - 1] = ' ';
				string[i] = '\t';
			}
			else if (string[i] == 'a')
			{
				string[i - 1] = ' ';
				string[i] = '\a';
			}
			else if (string[i] == 'b')
			{
				string[i - 1] = ' ';
				string[i] = '\b';
			}
			else if (string[i] == 'v')
			{
				string[i - 1] = ' ';
				string[i] = '\v';
			}
			else if (string[i] == 'e')
			{
				string[i - 1] = ' ';
				string[i] = '\e';
			}
			else if (string[i] == '?')
			{
				string[i - 1] = ' ';
				string[i] = '\?';
			}
			else if (string[i] == 'r')
			{
				string[i - 1] = ' ';
				string[i] = '\r';
			}
			else if (string[i] == '\\')
			{
				string[i - 1] = '\\';
				string[i] = '\\';
			}
			else if (string[i] == '\"')
			{
				string[i - 1] = '\\';
				string[i] = '"';
			}
			else
			{
				errid = 2;
				error_counter++;
				inv = str;							 
			}
		}
		i++;
	}

				//find, print and remove escaped characters from push
	switch (errid){
		case 1:
		printf(ANSI_COLOR_RED"ERROR: Unclosed string at line %d\n", yylineno-1);
		break;
		case 2:
		printf(ANSI_COLOR_RED"ERROR: Invalid escape character: \'\\%c\' at line: %d\n", inv, yylineno);
		break;
		default:
		yylval.stringVal = strdup(string);
		return STRING;
	}

	// BEGIN(INITIAL);
}

{FLOAT}             {yylval.realVal = atof(yytext);
					return FLOAT;}

{LBRACKET}          {return LBRACKET;}
{RBRACKET}          {return RBRACKET;}
{LSBRACKET}         {return LSBRACKET;}
{RSBRACKET}         {return RSBRACKET;}
{LPARENTHESIS}      {return LPARENTHESIS;}
{RPARENTHESIS}      {return RPARENTHESIS;}
{SEMICOLON}         {return SEMICOLON;}
{COMMA}             {return COMMA;}
{COLON}             {return COLON;}
{DCOLON}            {return DCOLON;}
{DOT}               {return DOT;}
{DDOT}              {return DDOT;}
{UNDERSCORE}        {;}



{SPACE}             {;}

{NEWLINE}           {yylineno;}

{TAB}               {;}
{ILLEGAL}			{printf(ANSI_COLOR_RED"ERROR: Unknown token: %s line: %d\n"ANSI_COLOR_RESET, yytext, yylineno);error_counter++;}

{COMMENT}           {com("COMMENT");}

"/*"                 {BEGIN(DCOMMENT1);dcom("MULTI-COMMENT START");flag++;}
<DCOMMENT1>"*/"      {flag--;
if(flag>0){
	;
	BEGIN(DCOMMENT1);
	nested = 1;
}else {
	BEGIN(INITIAL);
	nested=0;
	dcom("MULTI-COMMENT END");
}
}

<DCOMMENT1>"/*"		{BEGIN(DCOMMENT1);nestedcom("NESTED-COMMENT");flag++;}
<DCOMMENT1>.        {;}
<DCOMMENT1>\n       {yylineno;}
<DCOMMENT1><<EOF>>	 {if (flag>0 && !nested){
	error_counter+=flag;
	printf(ANSI_COLOR_RED"ERROR at line %d: Multiline comments not closed\n"ANSI_COLOR_RESET, yylineno-1);;
}
if (error_counter)
{
	printf(ANSI_COLOR_RED "Total Errors: %d\n" ANSI_COLOR_RESET, error_counter);
}
return 0;
}

<<EOF>>             {
	// printf(ANSI_COLOR_YEL"\n<--End of input reached-->\n"ANSI_COLOR_RESET);
	if(error_counter){
		printf(ANSI_COLOR_RED"Total Errors: %d\n"ANSI_COLOR_RESET, error_counter);
	}
	return 0;
}
%%


char *create()
{
	char *string = (char*)malloc(strlen(yytext)+1);
	int str, i = 0;
	while ((str = input()) != EOF && str != '\"')
	{

		string[i] = str;

		if(str == EOF){
			printf("ERROR: UNCLOSED STRING\n");
			return NULL;
		}

		if (string[i - 1] == '\\')
		{
			if(string[i] == 'n'){
				string[i-1] = ' ';
				string[i] = '\n';
			}
			else if(string[i]=='t'){
				string[i-1] = ' ';
				string[i] = '\t';
			}
			else if(string[i]=='a'){
				string[i-1] = ' ';
				string[i] = '\a';
			}
			else if(string[i]=='b'){
				string[i-1] = ' ';
				string[i] = '\b';
			}
			else if(string[i]=='v'){
				string[i-1] = ' ';
				string[i] = '\v';
			}
			else if(string[i]=='e'){
				string[i-1] = ' ';
				string[i] = '\e';
			}
			else if(string[i]=='?'){
				string[i-1] = ' ';
				string[i] = '\?';
			}
			else if(string[i]=='r'){
				string[i-1] = ' ';
				string[i] = '\r';
			}
			else if(string[i]=='\\'){
				string[i-1] = ' ';
				string[i] = '\\';
			}
			else if(string[i]=='"'){
				string[i-1] = ' ';
				string[i] = '\"';
			}
			else{
				return  NULL;
			}

		}
		i++;
	}
	return string;			
}

// int main(int argc, char* argv[])
// {
// 	printf("Starting up for the project's A'Phase  ....\n\n");
// 	printf("-------------------------- LEXICAL ANALYZER --------------------------  \n\n");
	
// 	if(argc > 1) {
// 		if(!(yyin = fopen(argv[1],"r"))) {
// 			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
// 			return 1;
// 		}
// 	}
// 	else{
// 		yyin = stdin;
// 	}
// 	if(argc>2){					//read output
// 		if(!(yyout = fopen(argv[2], "w"))){
// 			fprintf(stderr, "Cannot write to file: %s\n", argv[2]);
// 			return -1;
// 		}
// 	}
// 	yylex();

// 	printf("\n");
// 	reverse_list();
// 	print_list(head);
// 	reset();
// 	delete_list(head);

// 	printf("\n");
// 	printf("-------------------------- LEXICAL ANALYZER -------------------------- \n");
// 	printf("Completed A'Phase  at %s  on  %s !!!\n",__TIME__,__DATE__);
// }
