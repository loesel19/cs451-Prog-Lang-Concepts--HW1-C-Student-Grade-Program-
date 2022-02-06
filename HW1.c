#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog1.h"

int readFile(char *fileName);
int exists(char *fileName);
int main()
{
    char *fileName = malloc(100); //file name from input
    int intStatus; //status code for main function
printf("Enter input file name: ");
//read input into a string and call the readFile method with str args
scanf(fileName);
int intfExists = exists(fileName);
if (intfExists == 1)
{
    intStatus = readFile(fileName);
}else{
    printf("Could not find that file.");
    return 1;
}
return intStatus;
}//end main




int readFile(char *fileName){
    //local vars
    FILE *file = fopen(fileName, "r"); //file we are reading
    if (file == NULL)
    {
        perror("Unable to open file");
        return 1;
    }
    char chunk[128];
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line == NULL)
    {
        perror("Unable to allocate memory for the line buffer.");
        return 1;
    }
    line[0] = "\0"; //empty the string
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used)
        {
            len *= 2;
            if(line = realloc(line, len) == NULL){
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                return 1;
            }
        }

        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;
        fputs(line, stdout);
        
    }
    
    
    
    
}//end readFile

int exists(char *fileName){
    FILE *file;
    if ((file = fopen(fileName, "r")))
    {
        //file exists
        fclose(file);
        return 1;
    }
else{
    //file does not exist
    return 0;
}
    
}//end exists
