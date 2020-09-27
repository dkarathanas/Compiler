#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YEL  "\x1B[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*Enum type in .h file cause of ISO C forbids forward references to ‘enum’ types error, once i moved them error went away*/
//these are the types that we use, help to print the list
typedef enum token_types{KEYWORD,LOGIC_OPERATOR,ASSIGNMENT_OPERATOR,ARITHMETIC_OPERATOR,
RELATIONAL_OPERATOR,INTEGER,FLOAT,IDENTIFIER,STRING,PUNCTUATION,SPACE,TAB,ILLEGAL_TYPE,EEOF,COMMENT,DCOMMENT,NESTED_COMMENT}token_types;


typedef struct list {
  char	*name;	
  unsigned	num_line;	
  unsigned	num_token;
  token_types     type;
  char	*token_name;
  char *helper;
  struct list *next;
}list;

void plus_token();
void reset();
void delete_list(list * head);
void insert_list(char * name, unsigned num_line,unsigned num_token,token_types t,char *help);
void reverse_list();
void print_list(list *head);
char 	*create();

struct list *head=NULL;
unsigned number_of_token=0;
int error_counter = 0;
unsigned flag = 0;
int nested = 0;