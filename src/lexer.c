#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_display();
void env_vars(tokenlist *tokens);
void tilde_exp(tokenlist *tokens);
int main()
{
	while (1) {
		show_display();

		printf("> ");
		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */

		char *input = get_input();
		printf("whole input: %s\n", input);

		tokenlist *tokens = get_tokens(input);

		env_vars(tokens);

		tilde_exp(tokens);
		for (int i = 0; i < tokens->size; i++) {
			printf("token %d: (%s)\n", i, tokens->items[i]);
		}

		free(input);
		free_tokens(tokens);


	}


	return 0;
}

char *get_input(void) {
	char *buffer = NULL;
	int bufsize = 0;
	char line[5];
	while (fgets(line, 5, stdin) != NULL)
	{
		int addby = 0;
		char *newln = strchr(line, '\n');
		if (newln != NULL)
			addby = newln - line;
		else
			addby = 5 - 1;
		buffer = (char *)realloc(buffer, bufsize + addby);
		memcpy(&buffer[bufsize], line, addby);
		bufsize += addby;
		if (newln != NULL)
			break;
	}
	buffer = (char *)realloc(buffer, bufsize + 1);
	buffer[bufsize] = 0;
	return buffer;
}

tokenlist *new_tokenlist(void) {
	tokenlist *tokens = (tokenlist *)malloc(sizeof(tokenlist));
	tokens->size = 0;
	tokens->items = (char **)malloc(sizeof(char *));
	tokens->items[0] = NULL; /* make NULL terminated */
	return tokens;
}

void add_token(tokenlist *tokens, char *item) {
	int i = tokens->size;

	tokens->items = (char **)realloc(tokens->items, (i + 2) * sizeof(char *));
	tokens->items[i] = (char *)malloc(strlen(item) + 1);
	tokens->items[i + 1] = NULL;
	strcpy(tokens->items[i], item);

	tokens->size += 1;
}

tokenlist *get_tokens(char *input) {
	char *buf = (char *)malloc(strlen(input) + 1);
	strcpy(buf, input);
	tokenlist *tokens = new_tokenlist();
	char *tok = strtok(buf, " ");
	while (tok != NULL)
	{
		add_token(tokens, tok);
		tok = strtok(NULL, " ");
	}
	free(buf);
	return tokens;
}

void free_tokens(tokenlist *tokens) {
	for (int i = 0; i < tokens->size; i++)
		free(tokens->items[i]);
	free(tokens->items);
	free(tokens);
}

/*The point of this function is print the prompt of the on our terminal.
	-We created character pointers to point to the the get environment of user, machine, and current working directory.
	-Then printed out the prompt so whenever it is called it can display the user, the machine it is connected to, and the path
	 to the current working diretcory*/
void show_display()
{
	char * user = getenv("USER"); 
	char * machine = getenv("MACHINE");
	char * pwd = getenv("PWD");
	printf("%s@%s:%s",user,machine,pwd);
}

/*The point of this function is to expand the variable of a token whenever it receives input from the user.
	- In order to complete this we had to pass in the tokens based on the input.
	- Then we needed to create pointers to both the name and the getenv of the name
	- Then we needed to create space of the string and string copy was performed to copy over, then token value string to
	  the token->item string
	*/
void env_vars(tokenlist *tokens) {
    for (int i = 0; i < tokens->size; i++) {
        if (tokens->items[i][0] == '$') //This will check if "$" is present at the begging of each string.
		{
            char *var_tokenName = tokens->items[i] + 1; //This will skip the first the character($)
            char *env_tokenValue = getenv(var_tokenName); //created a pointer that this pointing at the get enviornment of the token name.

            if (env_tokenValue != NULL) 
			{
                free(tokens->items[i]); // This will free up the old space 
                tokens->items[i] = malloc(strlen(env_tokenValue) + 1); // This will allocate memory in the heap.
                strcpy(tokens->items[i], env_tokenValue); // This will copy the env variable over.
            }
        }
    }
	
}


void tilde_exp(tokenlist *tokens)
{
	char * home = getenv("HOME"); //Needed to set a home pointer to the environment of home.
	for(int i = 0; i < tokens->size;i++)//Traverse through the string of tokens.
	{
		if(tokens->items[0][0] == '~') //checks if there is a tilde first.
		{
			
			
				char * tilde_expansion = malloc(strlen(home)+ strlen(tokens->items[i])); //create new space in the heap that will fit the home expression and the directories after that.
				strcpy(tilde_expansion,home);//copy over the home environment path to the tilde expression
				strcat(tilde_expansion, tokens->items[i]+1); //need to concatenate the rest of the string to the tilde expression.
				free(tokens->items[i]); //This will free this string space
				tokens->items[i] = tilde_expansion;//this will copy over the tilde expression plus other conetents to the items string at i completely..
		}

	}

}
