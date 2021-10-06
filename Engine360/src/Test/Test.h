#pragma once

class Base
{
public:
	virtual void Helper();
};

template <typename T>
class Derived : public Base
{
public:
	void Helper();
};

template <typename T>
void Derived<T>::Helper()
{
	std::cout << "This is derived" << std::endl;
}