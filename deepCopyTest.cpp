#include "priorityQ.h"
#include "priorityQ.cpp"
#include <string>
#include <iostream>
using namespace std;

void outputPQ(priorityQ<string, int>);

int main()
{
	priorityQ<string, int> names1;

	names1.push_back("Tim", 22);
	names1.push_back("Eric", 11);
	names1.push_back("Dr. Steve Brule", 50);
	names1.push_back("Jan Sylar", 7);
	names1.push_back("Wayne Skyar", 10);
	names1.push_back("James Qwall", 23);
	names1.push_back("David Liebe Hart", 3);
	names1.push_back("Ron Austar", 19);
	names1.push_back("Mr. Henderson", 16);

	priorityQ<string, int> names2(names1);

	names2.pop_front();
	names2.pop_front();
	names2.decrease_priority("Dr. Steve Brule", 49);

	cout << "Priority Queues after copy constructor" << endl;
	cout << "Names1" << endl;
	outputPQ(names1);
	cout << endl << endl << "Names2" << endl;
	outputPQ(names2);

	names1 = names2;

	names1.push_back("Jeff Goldblum", 1);
	names2.pop_front();
	names2.decrease_priority("Dr. Steve Brule", 1);

	cout << endl << "Priority Queues are assignment operator" << endl;
	cout << "Names1" << endl;
	outputPQ(names1);
	cout << endl << endl << "Names2" << endl;
	outputPQ(names2);

	return 0;
}

void outputPQ(priorityQ<string, int> pQ)
{
	while (!pQ.isEmpty())
	{
		cout << pQ.get_front_key() << ":";
		cout << pQ.get_front_priority() << endl;

		pQ.pop_front();
	}

	return;
}