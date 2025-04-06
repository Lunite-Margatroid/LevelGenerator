
#include "GridMap.h"
#include <iostream>
int main()
{
	GridMap grid;
	for (int i = 0; i < 20; i++)
	{
		int x = rand() % 30;
		x -= 15;
		int y = rand() % 50;
		y -= 25;
		std::cout << "Insert: (" << x << ", " << y << ") " << "Count: " << i + 1 << std::endl;
		grid.InsertNode(x, y, i);
	}

	grid.PrintNode(std::cout);
	grid.PrintASCII(std::cout);

	return 0;
}