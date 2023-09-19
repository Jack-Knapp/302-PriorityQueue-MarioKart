#include "priorityQ.h"
#include "priorityQ.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	priorityQ<string, int> bands;

	bands.push_back("Sum41", 12);
	bands.push_back("Simple Plan", 18);
	bands.push_back("Blink-182", 3);
	bands.push_back("My Chemical Romance", 7);
	bands.push_back("Green Day", 5);
	bands.push_back("Weezer", 11);
	bands.push_back("Red Hot Chili Peppers", 9);
	bands.push_back("Nirvana", 3);

    cout << "---------------------------------------111111111111111111---------------------------------\n";

	bands.decrease_priority("Sum41", 5);
	bands.decrease_priority("Red Hot Chili Peppers", 6);
	bands.decrease_priority("Green Day", 2);
	bands.decrease_priority("Nirvana", 1);
	bands.decrease_priority("My Chemical Romance", 4);

	cout << "---------------------------------------222222222222222222---------------------------------\n";

	while (!bands.isEmpty())
	{
		cout << bands.get_front_key() << ":";
		cout << bands.get_front_priority() << endl;

		bands.pop_front();
	}	

	return 0;
}