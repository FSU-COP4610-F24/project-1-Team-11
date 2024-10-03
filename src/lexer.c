#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
typedef struct
{
    int jobs_n;
    int pid;
    char *command;
} background_struct;

background_struct jobs[10];

int job_counter = 0;

void show_display();
void env_vars(tokenlist *tokens);
void tilde_exp(tokenlist *tokens);
char *path_search(tokenlist *tokens);
void execute_path(tokenlist *tokens, bool background_checker);
void io_redirection(tokenlist *tokens);
void pip_execution(tokenlist *tokens);
bool background_checker(tokenlist *tokens);
void backgorund();

int main()
{
<<<<<<< HEAD
	// init pid = -1 for 10 slots in bg_list chdir for path
    // cd
    //chdir
    //sret
	
	for(int i=0; i<10; i++){
		bg_list[i].Pid=-1; 
	}

=======
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717
   while (1) {
    
    /*for(int i = 0; i < job_counter; i++)
    {
       int status;
        int finish = waitpid(jobs[i].pid, &status, WNOHANG);
        if(finish > 0)
        {
            printf("[%d] %s\n", jobs[i].jobs_n, jobs[i].command);
            free(jobs[i].command);
            for(int l = i; l < job_counter - 1; l++)
            {
                jobs[l] = jobs[l + 1];
            }

<<<<<<< HEAD
	

		for (int i=0; i<10; i++) { //in 0 .. 10
			if ((bg_list[i].Pid) != -1) {
                int status; 
				waitpid((bg_list[i].Pid),&status,WNOHANG);
				if (WIFEXITED(status)) {
					// print info of bg finished
                    printf("finished: pid: %d, cmd: %s\n", bg_list[i].Pid , bg_list[i].cmds);
					bg_list[i].Pid = -1;
                    
				}
			}
		}


=======
            job_counter--;
            i--;
        }*/
    
   
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717
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
        bool back = background_checker(tokens);

        bool IO = false; //this is a checker for io redirection
        bool pipe = false; //this is a checker for piping

        for(int i = 0; i < tokens->size;i++)
        {
<<<<<<< HEAD
			if(strcmp(tokens->items[i], "&") == 0){
				bg=true;
			}
            
            if(strcmp(tokens->items[i], "<") == 0 || strcmp(tokens->items[i], ">") == 0 )
=======
            if(strcmp(tokens->items[i], "<") == 0)
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717
            {
                IO = true;
            }
            if(strcmp(tokens->items[i], "|") == 0)
            {
                pipe = true;
            }
        }
<<<<<<< HEAD


        
		 if(bg == true)
        {
             char *commandPath= path_search(tokens); //Need a pointer to point to the path search.


            //Need an if else statement to check if the command exist or not.
            if(commandPath)
            {
                backgroundProcess(tokens);
                free(commandPath);
            }
            else
            {
                printf("Command not found\n");
            }
        }
       else if(IO == true)
=======
        if(strcmp(tokens->items[0], "jobs") == 0)
        {
            backgorund();
        }

        if(IO == true)
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717
        {
            io_redirection(tokens);
        }
        else if(pipe == true)
        {
            pip_execution(tokens);
        }
        
        else
        {
            char *commandPath= path_search(tokens); //Need a pointer to point to the path search.

            //Need an if else statement to check if the command exist or not.
            if(commandPath)
            {
                execute_path(tokens, back); //tried this as tokens already
                free(commandPath);
            }
            else
            {
                printf("Command not found\n");
            }
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
       if(tokens->items[i][0] == '~') //checks if there is a tilde first.
       {
               char * tilde_expansion = malloc(strlen(home)+ strlen(tokens->items[i])); //create new space in the heap that will fit the home expression and the directories after that.
               strcpy(tilde_expansion,home);//copy over the home environment path to the tilde expression
               strcat(tilde_expansion, tokens->items[i]+1); //need to concatenate the rest of the string to the tilde expression.
               free(tokens->items[i]); //This will free this string space
               tokens->items[i] = tilde_expansion;//this will copy over the tilde expression plus other conetents to the items string at i completely..
       }
   }

}

/*For this function we needed to traverse through the $PATH command to search if a specific command when the token
has an input */
char *path_search(tokenlist *tokens){
    if(tokens->size == 0)
    {
        return NULL;
    }
  
   char *command= tokens->items[0]; //Create a pointer that points to the command
   char *path= getenv("PATH"); // Create a pointer to the path.
  
   char *copiedPath= malloc(strlen(path)+1); //Allocates space for the path.
   strcpy(copiedPath, path);
   

   char *directory=strtok(copiedPath,":"); //":" will separate the path.
   char *fullPath= NULL;



   while(directory !=NULL){ //This will iterate over the path until it reaches null terminating char.
      
       fullPath= malloc(strlen(directory)+ strlen(command)+2); //add 2 for the "/" and the command once everything is strcat.
      
      
       if (!fullPath){
           free(copiedPath);
           return fullPath;
       }
       //This will copy the dir to the full path followed by the "/" and the command
       if (fullPath !=NULL){
           strcpy(fullPath,directory);
           strcat(fullPath, "/");
           strcat(fullPath, command);

       }

       // checks if the command exist and is an executable.
       if(access(fullPath, F_OK)== 0){
          
           free(copiedPath); // free the path copy
          
           return fullPath; // Return the dynamically allocated full path
       }
       // after I look at the contents of this directory. I need to free the memory and set it to Null for the next cycle.
       free(fullPath);
       fullPath=NULL;
       directory=strtok(NULL,":");
       }

   free(copiedPath);  //delete memory at the end of the search.
   return NULL; //This will show that command is not found.
   }
  



<<<<<<< HEAD

void execute_path(tokenlist *tokens){
if (tokens->size==0){
    return;
}
=======
void execute_path(tokenlist *tokens, bool background_checker){
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717

   char *fullPath= path_search(tokens);
   int status;

   pid_t pid = fork();
          
       if (pid==0){
          

           char *commands[tokens->size+1];
           for(int i= 0; i<tokens->size; i++){
               commands[i]=tokens-> items[i];
          
               }
               commands[tokens->size]=NULL;
               execv(fullPath, commands);

          
       }else if(pid>0)
       {
            if (background_checker == true) {
    // Ensure job_counter does not exceed jobs array size
    if (job_counter >= 10) {
        printf("Error: Maximum number of background jobs reached.\n");
        return;
    }

    // Storing job number, PID, and command
    jobs[job_counter].jobs_n = job_counter + 1;
    jobs[job_counter].pid = pid;

    jobs[job_counter].command = (char*)malloc(strlen(tokens->items[0]) + 1);
    if (jobs[job_counter].command == NULL) {
        return; 
    }

    // Copy the command string into the allocated memory
    strcpy(jobs[job_counter].command, tokens->items[0]);

    // Print the background job info
    printf("[%d] %d\n", jobs[job_counter].jobs_n, pid);

    // Increment the job counter
    job_counter++;
}

            else
            {
            waitpid(pid,&status,0);
            }
       }else{
           printf("Pid did not work");
       }



free(fullPath);
}
void io_redirection(tokenlist *tokens)
{
    if(tokens -> size == 0)
    {
        return;
    }
    bool in_flag = false;
    bool out_flag = false;
    char * input_file = NULL;
    char * output_file = NULL;
    tokenlist * commands =  new_tokenlist();

    for(int i = 0; i < tokens->size; i++) //traverse through tokens
    {
        if(strcmp(tokens->items[i],"<" )== 0) // check if there is an input symbol
        {
            in_flag = true; //set flag to true
            input_file = tokens->items[++i]; //input pointer will point the input file
        }
        else if(strcmp(tokens->items[i],">")== 0) //check if there is an output symbol
        {
            out_flag = true; //set flag to true
            output_file = tokens->items[++i]; //output pointer will point the output file
        }
        else
        {
            add_token(commands, tokens->items[i]); //add commands to a separate token list.
        }
    }

    int pid = fork();
    if(pid == 0)
    {
        if(in_flag == true)
        {
            int file_directory_input = open(input_file, O_RDONLY);
            if(file_directory_input < 0)
            {
                printf("Error: the input file does not exist\n");
                exit(EXIT_FAILURE); //exits if input file does not exist.
            }
            dup2(file_directory_input, STDIN_FILENO); //redirection of input
            close(file_directory_input); //close input file descriptors
        }
        if(out_flag == true)
        {
            int file_directory_input = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0600); //have create or overwrite and read/write permissions
            if(file_directory_input < 0)
            {
                printf("Error: the output file does not exist\n");
                exit(EXIT_FAILURE); //exits if input file does not exist.
            }
            dup2(file_directory_input, STDOUT_FILENO); //redirection of output
            close(file_directory_input); //close input file descriptors
            
        }
        execute_path(commands, false); //need to execute the command that is stored in the new token list
        free_tokens(commands); //needs to free up the space.
        exit(EXIT_SUCCESS); //exits whenever the process is sucessful.
    }
    
    else if(pid > 0)
    {
        waitpid(pid,NULL,0);
    }

    free_tokens(commands);

};
/*This funtion for pipe execution has mutilple stages. The first part is the set up where if
the user does not enter anything it will return nothing. The next part is separating the 
commands(it has a similar process to the io_redirection funtion). Next I had to create the pipes;
we have an array that store file descriptors for each pipe. The array stores 2 descriptors per pipe
(reading and writing) for n-1 for n commands. Next, we set up forking and redirection. Lastly, we had
to close all pipes and clean up the memory.*/
void pip_execution(tokenlist * tokens)
{
    if(tokens->size == 0)
    {
        return;
    }
    int l = 0; //track the current number of commands
    int command_amount = 0;
    tokenlist **commands = (tokenlist**) malloc(sizeof(tokenlist *) * tokens->size); //created a two d array in the heap.
    tokenlist * the_command = new_tokenlist();
    //separted the commands similar to the io_redirection function.
    for(int i = 0; i < tokens->size; i++)
    {
        if(strcmp(tokens->items[i], "|") == 0)
        {
            commands[command_amount++] = the_command; //this will store the current command.
            the_command = new_tokenlist(); // created a new tokenlist for the next command given.
        }
        else
        {
            add_token(the_command, tokens->items[i]); //This will add tokens to the current command.
        }

    }
    commands[command_amount++] = the_command; //this will help add the last command.
    
    int file_directories_pipes[2 *(command_amount - 1)]; //from lecture notes: create pipes for (n-1) commands.

    //This will create the pipe by using pipe()
    for(int i = 0; i < command_amount - 1; i++)
    {
        if(pipe(file_directories_pipes + (i * 2)) < 0)
        {
            exit(EXIT_FAILURE);
        }
    }
    while( l < command_amount)
    {
        int pid = fork();
        if(pid == 0)
        {
            if(l > 0)
            {
                dup2(file_directories_pipes[(l - 1) *2], STDIN_FILENO); //getting the input from the previous pipe only if it is not the fist command.
            }
            if(l < command_amount - 1)
            {
                dup2(file_directories_pipes[l*2+1], STDOUT_FILENO); //outputting the next pipe as long as it is not the last command.
               
            }
            for(int k = 0; k < 2*(command_amount - 1); k++)
            {
                close(file_directories_pipes[k]); //this will close all the file pip descriptors
            }

            execute_path(commands[l], false);
            exit(EXIT_SUCCESS);

        }
        if(pid < 0)
        {
            exit(EXIT_FAILURE);
        }
        l = l+1;
    }
    for(int i = 0; i < 2*(command_amount - 1); i++)
    {
        close(file_directories_pipes[i]); //This will close all the pipe file descriptors in the parent process.
    }
    for(int i = 0; i < command_amount; i++)
    {
        wait(NULL); //this will wait for the child processes to finish.
    }
    for(int i = 0; i < command_amount; i++)
    {
        free_tokens(commands[i]); //This will free all the allocated memory for commands.
    }
    free(commands); 
}
bool background_checker(tokenlist *tokens)
{
    if(tokens->size > 0 && strcmp(tokens->items[tokens->size -1],"&") == 0)
    {
        free(tokens->items[tokens->size-1]);
        tokens->items[tokens->size -1] = NULL;
        tokens->size--;
        return true;
    }
    return false;
}
void backgorund()
{
    /*int status;
    for(int i = 0; i < job_counter; i++)
    {
       
        int finish = waitpid(jobs[i].pid, &status, WNOHANG);
        if(finish > 0)
        {
            printf("[%d] + done %s\n", jobs[i].jobs_n, jobs[i].command);
            free(jobs[i].command);
            for(int l = i; l < job_counter - 1; l++)
            {
                jobs[l] = jobs[l + 1];
            }

<<<<<<< HEAD


void backgroundProcess(tokenlist *tokens) {
    

    char *fullPath = path_search(tokens);
    int status; 
    
    if (!fullPath) {
        //printf("Command not found\n");
        return;
    }

    // Check if the last token is '&' and remove it
    if (strcmp(tokens->items[tokens->size - 1], "&") == 0) {
        tokens->size--;  // Ignore '&' for command execution
    }

    pid_t pid = fork();

    
    char *commands[tokens->size + 1];
    for (int i = 0; i < tokens->size; i++) {
        commands[i] = tokens->items[i];
        printf("Token %d: %s\n", i, commands[i]);
    }
    commands[tokens->size] = NULL;

    if (pid == 0) {  // Child process
        // commands[0] = fullPath;
        
        
        execv(fullPath, commands);
        printf("execv failed!");
        exit(0);

        
    } else if (pid > 0) {  // Parent process
        waitpid(pid, &status, WNOHANG);

        for (int i = 0; i < 10; i++) {
            if (bg_list[i].Pid == -1) {
                bg_list[i].Pid = pid;
                bg_list[i].cmds[0] = '\0';  // Reset command string

                
                for (int j = 0; j < tokens->size; j++) {
                    strcat(bg_list[i].cmds, commands[j]);
                    printf("%s ", commands[j]);
                }
                printf("\n");
                break;
            }
        }
        printf("end of bg func\n");
    }
}

=======
            job_counter--;
            i--;
        }
        else if(finish == 0)
        {
            printf("[%d] + %d running %s\n", jobs[i].jobs_n, jobs[i].pid, jobs[i].command);
        }
    }*/
}
>>>>>>> 6d6abf9903c85d93084b8d81cf6d958bc327a717
