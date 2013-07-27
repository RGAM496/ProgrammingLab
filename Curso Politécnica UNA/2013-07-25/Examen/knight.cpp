#include <iostream>

using namespace std;


const int board[8][8] = {
	{2,	3,	4,	4,	4,	4,	3,	2},
	{3,	4,	6,	6,	6,	6,	4,	3},
	{4,	6,	8,	8,	8,	8,	6,	4},
	{4,	6,	8,	8,	8,	8,	6,	4},
	{4,	6,	8,	8,	8,	8,	6,	4},
	{4,	6,	8,	8,	8,	8,	6,	4},
	{3,	4,	6,	6,	6,	6,	4,	3},
	{2,	3,	4,	4,	4,	4,	3,	2}
};


template <typename N>
inline void set_min (N &a, const N &b)
{
	if (a > b)
		a = b;
}


struct Knight
{
	int f, c;

	inline int attacked_squares () {
		return board[f][c];
	}
};


istream & operator >> (istream &s, Knight &k)
{
	char c;
	s >> c >> k.f;
	k.c = c - 'a';
	--k.f;
}


int main ()
{
	Knight k;
	int n;

	cin >> n;
	while (n--)
	{
		cin >> k;
		cout << k.attacked_squares() << endl;
	}

	return 0;
}