#include <iostream>
using namespace std;

int main ()
{
	int test_cases, farmers, size, animals, environment_friendliness, sum;

	cin >> test_cases;

	while (test_cases--)
	{
		cin >> farmers;
		sum = 0;
		while (farmers--)
		{
			cin >> size >> animals >> environment_friendliness;
			sum += size * environment_friendliness;
		}
		cout << sum << endl;
	}

	return 0;
}