#include <cstdio>
#include <cstring>

#define MAX_STRING 11
#define MAX_MN 1500


template <class value_type, size_t SIZE>
struct Stack
{
	value_type first[SIZE], *last;

	value_type & operator [] (size_t n) {return first[n];}
	value_type & front () {return first[0];}
	value_type & back () {return last[-1];}

	value_type & push () {return *last++;}
	void push (value_type &v) {*last++ = v;}
	void pop () {--last;}
	size_t size () {return last - first;}
	void clear () {last = first;}
};


struct String
{
	int len;
	char s[MAX_STRING];
	Stack <String *, MAX_MN> related;

	bool es_comienzo_de (const String *st) {
		const char *s1, *s2;
		int i;
		if (len > st->len)
			return false;
		for (i = 0, s1 = s, s2 = st->s; i < len; ++i, ++s1, ++s2)
			if (*s1 != *s2)
				return false;
		return true;
	}

	bool es_final_de (const String *st) {
		const char *s1, *s2;
		int i;
		if (len > st->len)
			return false;
		for (i = 0, s1 = s + len - 1, s2 = st->s + st->len - 1; i < len; ++i, --s1, --s2)
			if (*s1 != *s2)
				return false;
		return true;
	}

	void clear () {related.clear();}
};


struct Language
: public Stack <String, MAX_MN>
{
	String & readline () {
		String &st = push();
		st.clear();
		scanf("%s", st.s);
		st.len = strlen (st.s);
		return st;
	}

	void readline_comienzo () {
		int strings_count = size(), i;
		String &st = readline (), *item;
		for (i = 0, item = first; i < strings_count; ++i, ++item) {
			if (st.es_comienzo_de (item))
				st.related.push (item);
		}
	}

	void readline_final () {
		int strings_count = size(), i;
		String &st = readline (), *item;
		for (i = 0, item = first; i < strings_count; ++i, ++item) {
			if (st.es_final_de (item))
				st.related.push (item);
		}
	}

	void debug () {
		for (int i = 0; i < size(); ++i) {
			fprintf(stderr, "%d: %s [%d]\n", i, first[i].s, first[i].related.size());
		}
		fprintf(stderr, "\n");
	}
} lang_m, lang_n;


int main ()
{
	int T, m, n;

	scanf ("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case)
	{
		scanf ("%d %d", &m, &n);
		fprintf(stderr, "%d %d\n", m, n);
		lang_m.clear();
		lang_n.clear();
		for (int i = 0; i < m; ++i)
			lang_m.readline_comienzo ();
		for (int i = 0; i < n; ++i)
			lang_n.readline_final ();

		lang_m.debug();
		lang_n.debug();
	}

	return 0;
}