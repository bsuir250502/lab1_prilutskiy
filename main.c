#include <stdio.h>
#include <stdio_ext.h>

typedef struct exam
{
	char Title[20];
	int Grade;
} Exam;

typedef struct student
{
	
	char Name[20];
	char Faculty[20];
	char Speciality[20];
	char Group[20];
	int ExamCount;
	Exam AllExams[5]
} Student;

void GetString(char * string)
{
	fgets(string,20,stdin);
}

int GetInt(int * number)
{
	char buffer[20];
	fgets(buffer,20,stdin);
	*number = atoi(buffer);
	return strlen(buffer)>2?0:1;
}


int IsPremium(Exam * source, int count)
{
	double tmp = 0;
	int summ = 0;
	for (int i = 0; i< count; i++)
		summ += source[i].Grade;
	tmp = (double)summ/(double)count;
	return tmp>4.5?1:0;
}

void AddStudent(Student * source,int count)
{

	puts("Name");
	GetString(&source[count].Name);
	puts("Faculty");
	GetString(&source[count].Faculty);
	puts("Speciality");
	GetString(&source[count].Speciality);
	puts("Group");
	GetString(&source[count].Group);
	
	//exams
	puts("Number of Exams");
	while (1)		
		if (!GetInt(&source[count].ExamCount))
		{puts("Input error"); continue;}
		else break;
	for (int i = 0; i<source[count].ExamCount; i++)
	{
		puts("Exam title");
		GetString(&source[count].AllExams[i].Title);
		puts("Exam grade");
		GetInt(&source[count].AllExams[i].Grade);
	}
	realloc(source, count + 1);	
} 

void Print(Student * source, int count, int flag)
{
	if (count == 0)
	{
		puts("There's no students at all ;(");
		return;
	}
	puts("Our students:");
	for (int i = 0; i< count; i++)
	{
		if (flag == 1)
			{
				if (IsPremium(source[i].AllExams,source[i].ExamCount)==0) break;
			}
		printf("Name: \n", source[i].Name);
		printf("Faculty: %s\n",source[i].Faculty);
		printf("Speciality: %s\n", source[i].Speciality);
		printf("Group: %s\n", source[i].Group);
		puts("Exams:"); 
		for (int j = 0; j<source[i].ExamCount; j++)
			printf("%s - %d\n",source[i].AllExams[j].Title,source[i].AllExams[j].Grade);

	}

}
void Help()
{
	puts("Usage:");
	printf("Start program without any keys and u'l see menu immideatly. Press 1 to add student, press 2 to print the whole student list, press 3 to print only premialized students. Press 0 to exit.\n");

}

int main(int argc, char * argv[])
{
	if (argc>1)
		if (strcmp(argv[1],"-h")==0)
			{
				Help();
				return 0;
			}
	puts("Привет! Hi!");
	Student * AllStudents = (Student*)malloc(sizeof(Student));
	int StudentCount = 0;
	int inp = -1;
	while (1)
	{
		printf("1 - Add\n2 - Print all\n3 - Print premium\n0 - Exit\n");
		if (!GetInt(&inp)) {puts("Input error"); continue;}
		switch(inp)
		{
			case 0:
			free(AllStudents);
				return 0;
			case 1:
			{
				AddStudent(AllStudents, StudentCount);
				StudentCount++;
				break;
			}
			case 2:
				Print(AllStudents,StudentCount,0);
				break;
			case 3:
				Print(AllStudents,StudentCount,1);
				break;
			default:
				puts("Input error");
				break;

		}

	}
	free(AllStudents);
	return 0;
}