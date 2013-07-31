#include <iostream>
#include <map>
#include <set>

using namespace std;

#define MAX_K 1000000000
#define MAX_W 100000

typedef unsigned int uint;
typedef set <uint> Set;
typedef map <uint, Set> Map;
typedef Map::iterator Iterator;

const char tell[2][3] = {
	"N\n",
	"Y\n"
};


Map kid_wishes;


inline uint add_wish (uint a, uint b)
{
	Set &s = kid_wishes[a];
	s.insert (b);
	return s.size ();
}


inline void disconnect (uint a, uint b)
{
	Set &s = kid_wishes[b];
	s.erase (a);
}


inline uint find_cycle (Iterator it)
{
	uint k, r, goal, k_old;
	Iterator it_old;

	r = 1;
	if (it->second.empty ())
		return 0;
	k_old = goal = it->first;
	k = *(it->second.begin ());
	it_old = it;
	it = kid_wishes.find (k);
	it->second.erase (k_old);
	kid_wishes.erase (it_old);
	while (true)
	{
		++r;
		if (it->second.empty ())
			return 0;
		k_old = k;
		k = *(it->second.begin ());
		if (k == goal)
			return r;
		it_old = it;
		it = kid_wishes.find (k);
		it->second.erase (k_old);
		kid_wishes.erase (it_old);
	}
}


int main ()
{
	uint kids, wishes, a, b, w;
	bool answer;

	while (cin >> kids >> wishes, kids || wishes)
	{
		kid_wishes.clear ();
		answer = true;
		for (w = 0; w < wishes; ++w)
		{
			cin >> a >> b;
			if (add_wish (a,b) > 2 || add_wish (b, a) > 2)
			{
				answer = false;
				break;
			}
		}
		for (++w; w < wishes; ++w)
			cin >> a >> b;
		while (answer && ! kid_wishes.empty ())
		{
			a = find_cycle (kid_wishes.begin ());
			if (a > 0 && a < kids)
				answer = false;
		}

		cout << tell[answer];
	}

	return 0;
}