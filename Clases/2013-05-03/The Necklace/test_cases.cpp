#include <iostream>
#include <random>
#include <cstring>

using namespace std;

#define MIN_BEADS 5
#define MAX_BEADS 1000
#define MIN_COLOR 1
#define MAX_COLOR 50


int main(int argc, char const *argv[])
{
	int test_cases, beads, c1, c2;
	default_random_engine beads_generator, color_generator;
	uniform_int_distribution <int> beads_dice (MIN_BEADS, MAX_BEADS);
	uniform_int_distribution <int> color_dice (MIN_COLOR, MAX_COLOR);

	if (argc == 1 || (test_cases = atoi (argv[1])) == 0) {
		cout << "\n\tSyntax: test_cases <number of cases>\n";
		return 1;
	}

	cout << test_cases << endl;
	for (int i = 0; i < test_cases; ++i)
	{
		beads = beads_dice (beads_generator);
		cout << beads << endl;
		for (int j = 0; j < beads; ++j)
		{
			c1 = color_dice (color_generator);
			c2 = color_dice (color_generator);
			cout << c1 << " " << c2 << endl;
		}
	}

	return 0;
}