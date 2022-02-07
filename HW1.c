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
    //read file
    intStatus = readFile(fileName);
    //print out report
    printReport();
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
    /*
    I have come across two options for continuing here.
    1: I could send a struct holding the current student being read from the file to a
       method to print it out, and inside this readFile method I would maintain arrays
       of the students scores to later calculate the averages with.
    2: create an array of students that is pointed to by a global scope pointer so that
       student data can be accessed from any method in this file.
    1 is probably an easier roundabout way of doing this program, but 2 seems like a less
    roundabout method and more solid approach to the problem. Plus doing it this way I
    will get to practice with pointers more, so I will do 2.
    */
    int i = 0;//index for array and counter for while loop
    printf("num_Stds: %d\n", num_stds);
    //allocate proper amount of space for our students array
    students = malloc(num_stds * (sizeof(struct StudentGrade)));
    //loop through all the student info, since reading each student into 
    while (i < num_stds)
    {
        struct StudentGrade *ptr;//pointer to used to point to our StudentGrade
        struct StudentGrade temp;//tempory studentGrade
        //allocate memory for name, say 8bits for 30 chars
        //temp.name = malloc(240);
        //first line is going to be name
        temp.name = strdup(fgets(buff, 255, (FILE*)file));
        //we want to remove new line character from the name
        strtok(temp.name, "\n");
        //next line is id
        temp.id = atoi(fgets(buff, 255, (FILE*)file));
        //next line is math then cs score
        fscanf(file, "%d", &temp.math116);
        fscanf(file, "%d", &temp.cs116);
        fgets(buff, 255, (FILE*)file); //we read the next line so that the file is read correctly
    //printf("name, %s : id, %i : math, %d : cs, %d\n", temp.name, temp.id, temp.math116, temp.cs116);
       
        //we need to point to this structure with our array of students
        ptr = &temp;
        *(students + i) = *ptr;
        i++;
       

    }
    return 0;
      
}//end readFile

void printReport(){
//first print out the headers
printf(" Student Name      Student ID      Math 116   CS 116\n");
printf("--------------     ----------      --------   ------\n");
//now we loop through the array of students that we created and print out their data
for (size_t i = 0; i < num_stds; i++){
    struct StudentGrade currStudent = *(students+ i);
    //print name and id
    printf("%*.*s     %*i",14,14, currStudent.name, 10, currStudent.id);
    //print math score with grade
    char grade = calculateGrade(currStudent.math116); 
    printf("      %*d(%c)", 5, currStudent.math116, grade);
    //get cs grade
    grade = calculateGrade(currStudent.cs116);
    printf("   %*d(%c)\n", 3, currStudent.cs116, grade);
    
}
//print a break before we print out the class averages
printf("====================================================\n");
double mathAverage = getMathAverage();
double csAverage = getCSAverage();
//now print class averages
printf("Math 116 Average: %*.*f\n",3,2, mathAverage);
printf("CS 116 Average: %*.*f\n",3,2, csAverage);
printf("*** END OF REPORT ***");


}//end printReport
char calculateGrade(int score){
    if (score < 60){
        return 'F';
    }else if (score < 70){
        return 'D';
    }else if(score < 80){
        return 'C';
    }else if(score < 90){
        return 'B';
    }else{
        return 'A';
    }
    
    
}//end calculateGrade
double getMathAverage(){
int total = 0; //the total so far
//loop through students and add each score to total
for(size_t i = 0; i < num_stds; i++){
    struct StudentGrade currStudent= *(students + i); //current student
    total = total + currStudent.math116;
}
//now we have to convert total to a double
total = total * 100;
double dblTotal = (double)total / (100.00 * num_stds);
//now we return the total/num of students as a double
return dblTotal;
}
double getCSAverage(){
int total = 0; //the total so far
//loop through students and add each score to total
for(size_t i = 0; i < num_stds; i++){
    struct StudentGrade currStudent= *(students + i); //current student
    total = total + currStudent.cs116;
}
//now we convert total to a double
total = total * 100;
double dblTotal = (double)total / (100.00 * num_stds);
//now we return the total/num of students as a double
return dblTotal;
}

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
