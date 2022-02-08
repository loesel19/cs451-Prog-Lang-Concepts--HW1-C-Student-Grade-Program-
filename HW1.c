
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog1.h"

struct StudentGrade *students;// array of students

// Program 1: Student Grade file analyzer/report generator
// Course: CS451 Winter 2022
// Instructor: Il-Hyung Cho
// Student: Andrew Loesel
// Email: aaloesel@svsu.edu
// Program Description:
/*
    This program will get the name or path of a file containing information about student grades
    from the user. Then calls the exists method to see if the file exists. If the file exists
    readFile is called so that the data from the file can be abstracted into the program as
    an array of StudentGrade structs. If readFile is completed sucessfully then we call the
    printReport function which will print out all the students names, ids, grades(calls calculateGrade)
    and then calls getMathAverage and getCSAverage functions to calculate and printOut the 
    averages of scores in the two classes. After this the program is finished running.
*/
int main(){
    /*
        This is the main function of the program. Firstly it creates a char * for the file name
        that will be read in with scanf. Secondly, it controls the workflow of the program, calling
        methods to make sure the file exists and then calls readFile to get the data. Next
        calls printReport to print out information to the user. It also keeps an int variable
        for the status of the program which will be returned unless the file is not found(in
        that case 1 is returned).
    */

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
    //print out report if the status returned from readfile is 0
    if(intStatus == 0){
    printReport();
    }
    else{
    return intStatus;
    }
}else{
    printf("Could not find file: \n");
    printf(fileName);
    //printf("77");
    return 1;
}
return intStatus;
}//end main




int readFile(char *fileName){
    /*
        FUNCTION NAME: readFile
        @params: 
        char *fileName - the string representation of the file name/ path that the user wishes
        to analyze.
        RETURNS : an integer representing the function status code. 0 = ok
        FUNCTION DESCRIPTION:
            This function opens a user specified file, and firstly sets the num_stds int
            of the prog1.h header file so that the rest of the program knows how many students
            are being analyzed. Next, space is allocated for the students array, pointed to by
            struct StudentGrade *students. Next we loop through all the students in the file(the
            specified number(num_stds)). Each iteration of the loop creates a new temp StudentGrade
            structure and a pointer to it. 3 lines of the file will be read, firstly the student name,
            next is the id and lastly the math and cs grades. After the temp has been given the appropriate
            data we point to it by incrementing the students pointer (*(students + i) = *ptr). After
            the loop is finished we return 0.
    */
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
    /*
        FUNCTION NAME: printReport
        @params: none
        RETURNS: void
        FUNCTION DESCRIPTION:
            This function is responsible for showing the output of the analysis to the user.
            Firstly it prints out headers for information types. Next it enters a loop which iterates
            num_stds times. In the loop we create a new new StudentGrade stuct representing the student
            we want to print, and assign it the struct at *(students + i). We use printf and variable 
            placeholders to ensure that the output is neat. We can print name and id off the bat,
            and then we call calculateGrade with the math and cs scores to get a character representation
            of the students grade and print this out. After the loop we print out a break line, and
            call getMathAverage and getCSAverage to get the class averages for the two,we print these out and
            end the function.

    */
//first print out the headers
printf(" Student Name      Student ID      Math 116   CS 116\n");
printf("--------------     ----------      --------   ------\n");
//now we loop through the array of students that we created and print out their data
for (size_t i = 0; i < num_stds; i++){
    struct StudentGrade currStudent = *(students+ i);
    //print name and id
    printf("%*.*s         %06i",14,14, currStudent.name, currStudent.id);
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
printf("*** END OF REPORT ***\n");


}//end printReport
char calculateGrade(int score){
    /*
        FUNCTION NAME: calculateGrade
        @params : int score - an integer representing the score for which we want a letter grade
        RETURNS : a character representation of the grade.
        FUNCTION DESCRIPTION:
            This function goes through conditionals in order to see what letter grade should be
            assigned to the score provided, this letter is then returned.
    */
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
    /*
        FUNCTION NAME : getMathAverage
        @params : none
        RETURNS : a double representing the class average math score.
        FUNCTION DESCRIPTION:
            This creates an integer representing the sum of the students math scores. We then loop
            through all the StudentGrades pointed to by the StudentGrade *students array. In each iteration
            we get a struct of the currentStudent and add their math score to the total. After the loop we want
            to get the average, so firstly we have to get a double representation of total. We also multiply this
            by 100 so that the first two decimal places of the double will be accurate. We then divide the total by
            (100 * num_stds) the 100 is so that our score is accurate. Lastly we return the double value.
    */
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
    /*
        FUNCTION NAME : getCSAverage
        @params : none
        RETURNS : a double representing the class average cs score.
        FUNCTION DESCRIPTION:
            This creates an integer representing the sum of the students cs scores. We then loop
            through all the StudentGrades pointed to by the StudentGrade *students array. In each iteration
            we get a struct of the currentStudent and add their cs score to the total. After the loop we want
            to get the average, so firstly we have to get a double representation of total. We also multiply this
            by 100 so that the first two decimal places of the double will be accurate. We then divide the total by
            (100 * num_stds) the 100 is so that our score is accurate. Lastly we return the double value.
    */
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
    /*
        FUNCTION NAME : exists
        @params : char *fileName - the file name or path of the user designated file to analyze
        RETURNS : an integer either 1 or 0. 1 means the file exists, 0 means it does not.
        FUNCTION DESCRIPTION:
            This function takes in the file name or path, and tries to open the file. If opened sucessfully the
            file is closed and the function returns 1 (sucess). If file not opened the function returns 0 (not found).
    */
    FILE *file; //the file we wish to check if exists
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
