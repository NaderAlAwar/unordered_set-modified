//#include "my_unordered_set.h"
#include <iostream>
#include <string>
#include <iterator>

#include <time.h>
#include <algorithm>
#include "my_list.h"
#include <iterator>
#include "my_unordered_set.h"
//#include <list>
//#include <unordered_set>


int main()
{
	std::unordered_set<std::string> myset =
	{ "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus","Neptune" };


	std::cout << "myset contains:";
	for (auto it = myset.begin(); it != myset.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "myset contains:";
	for (auto it = myset.begin(); it != myset.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	return 0;
}