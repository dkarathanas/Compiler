/*
HY-340 PROJECT -> A PHASE SUMMER SEMESTER 2018
CHRIS MAVRIKIS 
DIMITRIS KARATHANASIS

*/
%option noyywrap
%option yylineno
%{
	#include "types.h"
%}

%{	
extern 	char *yytext;

/*Error handle for numbers with identifiers and illegal characters that alpha doesnt support */

void plus_token(){
	number_of_token=number_of_token+1;
}

void reset()
{
	number_of_token=0;
}

void delete_list(list * head){
	list * current=head;
	while(current){
		free(current);
		current->name=NULL;
		current->num_line=0;
		current->num_token=0;
		current->type=0;
		current->helper=NULL;
		current->token_name=NULL;
		current=current->next;
	}
}
void set_token_type(list *head){
	if(head->type==0){
		head->token_name="KEYWORD";
		}else if(head->type==1)
		{
        head->token_name="LOGIC_OPERATOR";
		}else if(head->type==2)
		{
		head->token_name="ASSIGNMENT_OPERATOR";
		}else if(head->type==3)
		{
        head->token_name="ARITHMETIC_OPERATOR";
		}else if(head->type==4)
		{
		head->token_name="RELATIONAL_OPERATOR";
		}else if(head->type==5)
		{
		head->token_name="INTCONST";
		}else if(head->type==6)
		{
		head->token_name="REALCONST";
		}else if(head->type==7)
		{
		head->token_name="IDENTIFIER";
		}else if(head->type==8)
		{
		head->token_name="STRING";
		}else if(head->type==9)
		{
		head->token_name="PUNCTUATION";
		}else if(head->type==10)
		{
		head->token_name="SPACE";
		}else if(head->type==11)
		{
		head->token_name="TAB";
		}else if(head->type==12)
		{
		head->token_name="ILLEGAL_TYPE";
		}else if(head->type==13)
		{
		head->token_name="EOF";
		}else if(head->type==14)
		{
		head->token_name="COMMENT";
		}
		else if (head->type==15)
		{
		head->token_name="DCOMMENT";
		}else if (head->type==16)
		{
		head->token_name="NESTED-COMMENT";
		}
}

void insert_list(char * name, unsigned num_line,unsigned num_token,token_types t,char *help)
{
list *current;
list *tmp;
current=malloc(sizeof(struct list));
//TODO Change size
current->name = strdup(name);
assert(current);
//strcpy(current->name, name);
current->num_line=num_line;
current->num_token=num_token;
current->type=t;
current->token_name=NULL;
current->helper=help;

set_token_type(current);
if (head==NULL)
	{
	head = current;
	tmp  = current;

	}else
	{ 
	current->next=head;
	head=current;
 	}
}

void reverse_list(){
 list *tmp=head , *nextCell;
 head=NULL;
 while(tmp){
 	nextCell=tmp->next;
 	tmp->next=head;
 	head=tmp;
 	tmp=nextCell;
 }
}


void print_list(list *head){
	
	while(head){	
		printf(ANSI_COLOR_GREEN "\n LINE : %2u    TOKEN #%u  \" %s \"       \t %s       %-10s  \n" ANSI_COLOR_GREEN ANSI_COLOR_RESET ,head->num_line,head->num_token,head->name,head->token_name,head->helper);
		head=head->next;
		}
}

void keywords(char* str)
{
insert_list(yytext,yylineno,number_of_token++,KEYWORD,str);
}

void logic(char* str)
{
insert_list(yytext,yylineno,number_of_token++,LOGIC_OPERATOR,str);
}

void assignment(char* str)
{
insert_list(yytext,yylineno,number_of_token++,ASSIGNMENT_OPERATOR,str);
}

void arithmetic(char* str)
{
insert_list(yytext,yylineno,number_of_token++,ARITHMETIC_OPERATOR,str);
}

void relational(char* str)
{
insert_list(yytext,yylineno,number_of_token++,RELATIONAL_OPERATOR,str);
}

void integer(char* str)
{
insert_list(yytext,yylineno,number_of_token++,INTEGER,str);
}

void id(char* str)
{
insert_list(yytext,yylineno,number_of_token++,IDENTIFIER,str);
}

void  real(char* str)
{
insert_list(yytext,yylineno,number_of_token++,FLOAT,str);
}

void multi_str(char* str, char *tmp)
{
insert_list(tmp,yylineno,number_of_token++,STRING,str);
}

void punctuation(char* str)
{
insert_list(yytext,yylineno,number_of_token++,PUNCTUATION,str);
}

void com (char* str)
{
insert_list("//",yylineno,number_of_token++,COMMENT,str);
}

void dcom(char *str){
if(str=="MULTI-COMMENT END"){
insert_list(yytext,yylineno,number_of_token++,DCOMMENT,str);
}else{
insert_list(yytext,yylineno,number_of_token,DCOMMENT,str);
}
}

void nestedcom(char *str){
	insert_list(yytext,yylineno,number_of_token++,NESTED_COMMENT,str);
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
LOCAL					"local"
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

{IF}   				{keywords("IF");}
{ELSE}              {keywords("ELSE");}
{WHILE}             {keywords("WHILE");}
{FOR}				{keywords("FOR");}
{FUNCTION}			{keywords("FUCNTION");}
{RETURN} 			{keywords("RETURN");}
{BREAK} 			{keywords("BREAK");}
{CONTINUE}			{keywords("CONTINUE");}
{LOCAL} 			{keywords("LOCAL");}
{TRUE}              {keywords("TRUE");}
{FALSE}             {keywords("FALSE");}
{NIL}               {keywords("NIL");}

{AND} 				{logic("AND");}
{OR} 				{logic("OR");}
{NOT} 				{logic("NOT");}


{ASSIGN}            {assignment("ASSIGN");}

{PLUS}              {arithmetic("PLUSS");}
{MINUS}             {arithmetic("MINUS");}
{MULTIPLY}          {arithmetic("MULTIPLY");}
{DIVIDE}            {arithmetic("DIVIDE");}
{MODULO}            {arithmetic("MODULO");}
{DPLUS}             {arithmetic("DPLUS");}
{DMINUS}            {arithmetic("DMINUS");}


{EQUAL}             {relational("EQUAL");}
{DIFFERENT}         {relational("DIFFERENT");}
{BIGGER}            {relational("BIGGER");}
{SMALLER}           {relational("SMALLER");}
{BIGGER_EQUAL}      {relational("BIGGER_EQUAL");}
{SMALLER_EQUAL}     {relational("SMALLER_EQUAL");}

{INTEGER}           {integer("INTEGER");}
{IDENTIFIER}        {id("IDENTIFIER");}

{STRING}            {
					BEGIN(STRING);
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
						multi_str("STRING",string);
				}
				
				BEGIN(INITIAL);
				}

{FLOAT}             {real("FLOAT");}

{LBRACKET}          {punctuation("LBRACKET");}
{RBRACKET}          {punctuation("RBRACKET");}
{LSBRACKET}         {punctuation("LSBRACKET");}
{RSBRACKET}         {punctuation("RSBRACKET");}
{LPARENTHESIS}      {punctuation("LPARENTHESIS");}
{RPARENTHESIS}      {punctuation("RPARENTHESIS");}
{SEMICOLON}         {punctuation("SEMICOLON");}
{COMMA}             {punctuation("COMMA");}
{COLON}             {punctuation("COLON");}
{DCOLON}            {punctuation("DCOLON");}
{DOT}               {punctuation("DOT");}
{DDOT}              {punctuation("DDOT");}
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
					printf(ANSI_COLOR_YEL"\n<--End of input reached-->\n"ANSI_COLOR_RESET);
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

