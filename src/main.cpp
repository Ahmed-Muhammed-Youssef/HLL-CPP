#include<iostream>

int main()
{
	try 
	{
		std::cout << "hey there";
		return 0;
	}
	catch (std::exception)
	{
		return 1;
	}
}