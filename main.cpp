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
#include <fstream>


int main()
{
	/*std::unordered_set<int> myset =
	{ 1,2,3,4,5};

	std::ofstream outfile;

	outfile.open("example.txt", std::ios_base::app);

	for (auto it = myset.begin(); it != myset.end(); ++it) {
		outfile << *it << " ";
	}
	outfile << "\r\n";
*/
	std::unordered_set<std::string> myset =
	{ "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus","Neptune" };

	std::cout << "myset contains:";
	for (auto it = myset.begin(); it != myset.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "myset's buckets contain:\n";
	for (unsigned i = 0; i < myset.bucket_count(); ++i) {
		std::cout << "bucket #" << i << " contains:";
		for (auto local_it = myset.begin(i); local_it != myset.end(i); ++local_it)
			std::cout << " " << *local_it;
		std::cout << std::endl;
	}

	return 0;
}