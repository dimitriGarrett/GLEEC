#include <iostream>

struct A
{
    int b;
};

int main()
{
    std::cout << meta::reflect<A>(0) << std::endl;

	std::cout << "Hello World!" << std::endl;
	return 0;
}
