#include <cstdio>
#include <cctype>

#define LAST '*'
#define SPACE ' '
#define NEWLINE '\n'


inline char next_letter ()
{
	return toupper (getchar ());
}

inline char next_space ()
{
	char c;
	do
	{
		c = getchar ();
	}
	while (!isspace (c));
	return c;
}


inline bool search_tautogram (bool &found)
{
	char t, c;

	t = next_letter ();
	if (t == LAST)
		return false;

	found = true;
	c = next_space ();
	while (c != NEWLINE && found)
	{
		c = next_letter ();
		if (c != t)
			found = false;
		c = next_space ();
	}
	while (c != NEWLINE)
		c = next_space ();

	return true;
}


int main ()
{
	bool tautogram;

	while (search_tautogram (tautogram))
	{
		putchar (tautogram ? 'Y' : 'N');
		putchar ('\n');
	}

	return 0;
}