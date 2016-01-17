#include <iostream>
#include <time.h>
#include "hello.pb.h"

#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libprotoc")

int main(int argc, char **argv)
{
	pb_test::Helloworld hw;
	std::cout << "initialized: " << hw.IsInitialized() << std::endl;
	std::cout << "has 'username': " << hw.has_username() << std::endl;

	hw.set_username("zergl");
	std::cout << "initialized: " << hw.IsInitialized() << std::endl; // still 0 ??!!
	std::cout << "has 'username': " << hw.has_username() << std::endl;
	std::cout << "username: " << hw.username() << std::endl;

	//repeated fields
	/*
	hw.add_grade(1);
	hw.add_grade(20);
	hw.add_grade(123);
	*/

	int i;
	for (i = 1; i < 10; i++) 
	{
		//srand((unsigned)time(NULL)); // not work yet!!
		hw.add_grade( rand()% i);
	}

	std::cout << "there are " << hw.grade_size() << " elements in 'grade' fields." << std::endl;
	
	for (i = 0; i < hw.grade_size(); i++)
	{
		std::cout << " grade[" << i << "/"  << hw.grade_size() << "] " << hw.grade(i) << std::endl;
	}

	
    return  0;
}
