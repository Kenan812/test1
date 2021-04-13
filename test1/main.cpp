#include <iostream>

/* New comment */

using namespace std;


/* New comment */

void SomeUselessFoo(int ccc);


int main()
{
	for (int i = 0; i < 10; i++)
		cout << i + 1 << "\n";


	SomeUselessFoo(2);

	return 0;
}

void SomeUselessFoo(int ccc)
{
	ccc++;
	cout << "Hello world";
}
