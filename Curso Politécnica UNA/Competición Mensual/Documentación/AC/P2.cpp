#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Node;

typedef map <char, Node *> Map;
typedef Map::iterator Iterator;


struct Node
{
	bool emoticon;
	Map next;

	Node () : emoticon(false) {}

	~Node () {
		for (Iterator it = next.begin(); it != next.end(); ++it)
		{
			delete it->second;
		}
	}


	Node * next_node (char c)
	{
		Iterator it = next.find (c);
		return it == next.end() ? 0 : it->second;
	}


	Node * insert (char c)
	{
		Node *n = new Node;
		next[c] = n;
		return n;
	}

	Node * go_next (char c)
	{
		Node *n;
		Iterator it = next.find (c);
		if (it == next.end())
		{
			n = insert (c);
			next[c] = n;
			return n;
		}
		else
		{
			return it->second;
		}
	}


	Node * insert (const char *s)
	{
		Node *n = this;
		for (; *s; ++s)
		{
			n = n->go_next (*s);
		}
		n->emoticon = true;
		return n;
	}

	int find_emoticon (const char *s)
	{
		Node *n = this;
		int r = 0, c = 0;
		for (; *s; ++s)
		{
			n = n->next_node (*s);
			if (n == 0)
			{
				break;
			}
			++c;
			if (n->emoticon)
			{
				r = c;
				c = 0;
				break;
			}
		}
		if (r)
		{
			return r;
		}
		return r;
	}

	int count_emoticons (char *s)
	{
		int i, r = 0, m, f;
		while (*s)
		{
			m = find_emoticon (s);
			if (m)
			{
				for (i = 1; i < m; ++i)
				{
					f = find_emoticon (s + i);
					if (f)
					{
						m = min (m, i + f);
						if (f == 1)
							break;
					}
				}
				++r;
				s += m;
			}
			else
				++s;
		}
		return r;
	}
};


int main ()
{
	int n, m, count;
	string line;

	while (cin >> n >> m, n || m)
	{
		Node emoticon;
		while (n--)
		{
			cin >> line;
			emoticon.insert (line.c_str());
		}
		count = 0;
		while (cin.get() != '\n');
		while (m--)
		{
			getline(cin,line,'\n');
			count += emoticon.count_emoticons (&line[0]);
		}
		cout << count << endl;
	}

	return 0;
}