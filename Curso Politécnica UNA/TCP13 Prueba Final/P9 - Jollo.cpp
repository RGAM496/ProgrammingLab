#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_CARDS 53
#define temp_card_loop(i) for (int i = 1; i < MAX_CARDS; ++i)
#define card_loop(i) for (i = 1; i < MAX_CARDS; ++i)

#define BOY_CARDS 2
#define GIRL_CARDS 3


bool used_card[MAX_CARDS];
int boy[BOY_CARDS], girl[GIRL_CARDS];


inline int min_card (int r)
{
	while (used_card[r]) ++r;
	return r < MAX_CARDS ? r : -1;
}


inline int min_card ()
{
	if (boy[1] < girl[2])
	{
		if (boy[0] < girl[1])
			return -1;
		else
			return min_card (girl[1] + 1);
	}
	else
	{
		if (boy[0] < girl[1])
			return min_card (girl[2] + 1);
		else if (boy[0] < girl[2])
			return min_card (girl[1] + 1);
		else
			return min_card (1);
	}
}


inline bool input ()
{
	cin >> girl[0] >> girl[1] >> girl[2] >> boy[0] >> boy[1];
	return girl[0] != 0;
}

inline void mark (bool v)
{
	used_card[girl[0]] = v;
	used_card[girl[1]] = v;
	used_card[girl[2]] = v;
	used_card[boy[0]] = v;
	used_card[boy[1]] = v;
}


int main ()
{
	while (input ())
	{
		sort (girl, girl + GIRL_CARDS);
		sort (boy, boy + BOY_CARDS);

		mark (true);
		cout << min_card () << endl;
		mark (false);
	}

	return 0;
}