#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map <string, int> Map;
typedef Map::iterator Iterator;

Map used_substr;


int main ()
{
	string st, sub;
	int s, l, i, j;
	int max_used;

	cin >> st;

	s = st.size();
	for (i = 0; i < s; ++i)
	{
		l = s - i;
		for (j = 1; j <= l; ++j)
		{
			sub = st.substr (i, j);
			used_substr[sub]++;
		}
	}

	max_used = 0;
	sub = "";
	for (Iterator it = used_substr.begin(); it != used_substr.end(); ++it)
	{
		if (it->second > max_used)
		{
			max_used = it->second;
			sub = it->first;
		}
		else if (it->second == max_used && it->first.size() > sub.size())
		{
			sub = it->first;
		}
	}

	cout << sub << endl;

	return 0;
}