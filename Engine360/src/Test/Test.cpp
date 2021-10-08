#include <iostream>
#include "Test.h"
#include <vector>

int Student::numOfStudents = 0;

Student::Student()
{
	numOfStudents++;
}

Student::~Student()
{
	numOfStudents--;
}

int main()
{
	Student* s1 = new Student();
	Student* s2 = new Student();
	Student* s3 = new Student();
	std::cout << s1->numOfStudents << std::endl;
	delete s3;
	std::cout << s1->numOfStudents << std::endl;
	delete s2;
	std::cout << s1->numOfStudents << std::endl;
	return 0;
}
