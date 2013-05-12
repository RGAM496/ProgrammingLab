#include <cstdio>
#include <cstring>
#include <string>
#include <map>

using std::string;
using std::map;

#define MAX_STRINGS 1500
#define MAX_LENGTH 11

#define loop(i,n) for (int i = 0; i < n; ++i)


inline int fgets (char *s)
{
	int len;
	fgets (s, MAX_LENGTH, stdin);
	len = strlen(s);
	s[len-1] = '\0';
}


template <class Vtype, size_t MAX_SIZE>
struct Stack
{
	Vtype first[MAX_SIZE], *last;

	inline void clear () {last = first;}
	inline void push (Vtype &v) {*last = v; ++last;}
	inline Vtype & push () {return *last++;}
	inline void pop () {--last;}
	inline size_t size () {return last - first;}
	inline Vtype & at (size_t n) {return first[n];}
	inline Vtype & operator [] (size_t n) {return at(n);}
};


Stack <char[MAX_LENGTH], MAX_STRINGS> lang_m;
map <string, bool> concatenations;


int main ()
{
	int t, test_cases, m, n;
	char s[MAX_LENGTH];
	string st;

	scanf ("%d", &test_cases);
	for (t = 1; t <= test_cases; ++t)
	{
		lang_m.clear();
		concatenations.clear();
		scanf ("%d %d%*c", &m, &n);
		loop (i, m) {
			fgets(lang_m.push());
		}
		loop (i, n) {
			fgets(s);
			loop (j, m) {
				st = lang_m[j];
				st += s;
				concatenations[st];
			}
		}
		printf("Case %d: %d\n", t, concatenations.size());
	}

	return 0;
}