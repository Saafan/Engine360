#include <iostream>
#include "Test.h"

void Student::PrintStatic(int x)
{
	static int m;
	if (x != m)
	{
		m = x;
		std::cout << "Static m: " << m << std::endl;
	}
}



template<typename t>
void Student::Lol(t x)
{

}
