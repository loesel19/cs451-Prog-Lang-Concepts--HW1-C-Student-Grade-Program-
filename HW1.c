#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog1.h"



struct StudentGrade *students;// array of students

int main(){

    char *fileName = malloc(100); //file name from input
    int intStatus; //status code for main function
    
printf("Enter input file name: ");
//read input into a string and call the readFile method with str args
scanf("%s",fileName);
int intfExists = exists(fileName);
if (intfExists == 1)
{
    intStatus = readFile(fileName);
}else{
    printf("Could not find file: \n");
    printf(fileName);
    //printf("77");
    return 1;
}
return intStatus;
}//end main




int readFile(char *fileName){
    //local vars
    FILE *file = fopen(fileName, "r"); //file we are reading
    char buff[255];//file buffer
    //get the number of students from the first line
    fgets(buff, 255, (FILE*)file);
    //set num_stds from prog1.h
    num_stds = atoi(buff);
    if (num_stds <= 0)
    {
        printf("number of students must be > 0.\n");
        return 1;
    }
    
    int i = 0;//index for array and counter for while loop
    printf("num_Stds: %d\n", num_stds);
    //allocate space for our array of studentgrades
    
    //loop through all the student info, since reading each student into 
    while (i < num_stds)
    {
        //create our student grade struct
        struct StudentGrade temp;
        //allocate memory for name, say 8bits for 30 chars
        //temp.name = malloc(240);
        //first line is going to be name
        temp.name = strdup(fgets(buff, 255, (FILE*)file));
        //next line is id
        temp.id = atoi(fgets(buff, 255, (FILE*)file));
        //next line is math then cs score
        fscanf(file, "%d", &temp.math116);
        fscanf(file, "%d", &temp.cs116);
        fgets(buff, 255, (FILE*)file); //we read the next line so that the file is read correctly
    printf("name, %s : id, %i : math, %d : cs, %d\n", temp.name, temp.id, temp.math116, temp.cs116);
        i++;
        //we need to point to this structure with our array of students
        students + i = temp;
    }
    
    return 0;
      
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
