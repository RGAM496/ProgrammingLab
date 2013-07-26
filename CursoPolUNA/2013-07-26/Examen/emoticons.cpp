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
			delete it->second;
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
		int r = 0;
		for (; *s; ++s)
		{
			n = n->next_node (*s);
			if (n == 0)
				return 0;
			++r;
			if (n->emoticon)
				break;
		}
		return r;
	}

	int count_emoticons (const char *s)
	{
		int i = 0, r = 0;
		while (*s)
		{
			s += i;
			i = find_emoticon (s);
			if (i)
				++r;
			++i;
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
			getline(cin,line,'\n');
			emoticon.insert (line.c_str());
		}
		count = 0;
		while (m--)
		{
			getline(cin,line,'\n');
			count += emoticon.count_emoticons (line.c_str());
		}
		cout << count << endl;
	}

	return 0;
}