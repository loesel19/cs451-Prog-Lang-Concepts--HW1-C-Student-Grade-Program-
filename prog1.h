int num_stds;           // number of students

//function declarations
int readFile(char *fileName);//read data from file
int exists(char *fileName);//check if file exists
char calculateGrade(int score);//calculate grade
void printReport();//prints out the report at the end
double getMathAverage();//gets the average of all students scores
double getCSAverage();//gets the average of all students scores

struct StudentGrade {
   int id;              // student id
   char* name;          // student name;
   int math116;
   int cs116;
};