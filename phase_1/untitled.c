char *create(char * yytext)
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
						else if(string[i]=='\"'){
							string[i-1] = ' ';
							string[i] = '\"';
						}
						else{
							return  NULL;
							break;
						}
						
					}
					i++;
				}
		return string;			
}