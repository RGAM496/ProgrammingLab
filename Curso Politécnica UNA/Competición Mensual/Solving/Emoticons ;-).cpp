#include <iostream>
#include <map>
#include <string>
#include <limits>

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
			//cerr << *s;
			n = n->next_node (*s);
			if (n == 0)
			{
				//cerr << "\t\t0\n";
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
		//cerr << "\t\t" << r;
		/*if (r)
		{
			//cerr << "\t\tFOUND!\n";
			return r;
		}*/
		//cerr << endl;
		return r;
	}

	int count_emoticons (char *s)
	{
		int i = 0, r = 0;
		while (*s)
		{
			i = find_emoticon (s);
			if (i)
			{
				++r;
				s += i;
				//cerr << "\t\t\t\tCOUNT: " << r << "\n";
			}
			else
				++s;
		}
		//cerr << "\n\tFINAL COUNT: " << r << "\n\n";
		return r;
	}
};


int main ()
{
	int n, m, count;
	const int lim = numeric_limits <streamsize> :: max();
	string line;

	while (cin >> n >> m, n || m)
	{
		//cerr << "\nTEST CASE " << n << " " << m << "\n\n";
		Node emoticon;
		cin.ignore (lim, '\n');
		while (n--)
		{
			getline(cin,line,'\n');
			emoticon.insert (line.c_str());
		}
		count = 0;
		while (m--)
		{
			getline(cin,line,'\n');
			count += emoticon.count_emoticons (&line[0]);
		}
		cout << count << endl;
	}

	return 0;
}