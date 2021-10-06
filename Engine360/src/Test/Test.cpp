#include <iostream>
#include "Test.h"
#include <vector>
void Base::Helper()
{
	std::cout << "Base Helper" << std::endl;
}

int main()
{
	std::vector<Base*> v;
	Base* b;
	Derived<int> d;
	v.emplace_back(&d);
	v[0]->Helper();
	return 0;
}