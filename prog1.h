int num_stds;           // number of students

//function declarations
int readFile(char *fileName);//read data from file
int exists(char *fileName);//check if file exists

struct StudentGrade {
   int id;              // student id
   char* name;          // student name;
   int math116;
   int cs116;
};