#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_ACTIVITIES 100


template <typename N>
inline void set_max (N &a, const N &b)
{
	if (a < b)
		a = b;
}


struct Activity
{
	int start, finish;
};


inline bool operator < (const Activity &a, const Activity &b)
{
	return (a.start < b.start) || (a.start == b.start && a.finish > b.finish);
}

istream & operator >> (istream &s, Activity &a)
{
	return s >> a.start >> a.finish;
}

ostream & operator << (ostream &s, Activity &a)
{
	return s << a.start << ' ' << a.finish;
}


Activity activity[MAX_ACTIVITIES];
int minimum, maximum, n;


inline int min_subset ()
{
	int count, i, f;

	sort (activity, activity + n);
	minimum = 0;
	cerr << "min_subset\n\t" << activity[0] << endl;
	if (activity[0].start > minimum)
		return 0;
	minimum = activity[0].finish;

	count = 1;
	if (minimum >= maximum)
		return count;
	for (i = 1; i < n;)
	{
		f = minimum;
		for (; i < n && activity[i].start <= minimum; ++i)
		{
			cerr << "\t" << activity[i] << endl;
			set_max (f, activity[i].finish);
		}
		if (f == minimum)
			return 0;
		++count;
		if (f >= maximum)
			return count;
		minimum = f;
	}

	return 0;
}


int main ()
{
	while (cin >> maximum >> n, maximum || n)
	{
		for (int i = 0; i < n; ++i)
			cin >> activity[i];

		cout << min_subset () << endl;
	}

	return 0;
}