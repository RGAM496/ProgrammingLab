#include <iostream>

using namespace std;

#define MAX_DIGITS 10

typedef unsigned int uint;

struct DigitCount;
ostream & operator << (ostream &s, const DigitCount &d);


struct DigitCount
{
	uint dc[MAX_DIGITS];

	inline uint & operator [] (size_t i) {return dc[i];}
	inline uint operator [] (size_t i) const {return dc[i];}

	inline void reset () {
		for (size_t i = 0; i < MAX_DIGITS; ++i)
			dc[i] = 0;
	}

	inline uint operator -= (const DigitCount &d) {
		for (size_t i = 0; i < MAX_DIGITS; ++i)
			dc[i] -= d[i];
	}


	inline void digits_until (uint n)
	{
		uint s, d, p, f, pos, i, prod;

		#ifdef DU
		cerr << "\n\tDigits until " << n << "\n\n";
		#endif
		reset ();

		// Soy un maldito pecador…
		if (n >= MAX_DIGITS)
			++dc[0];

		d = n % MAX_DIGITS;
		n /= MAX_DIGITS;
		for (i = 0; i < d; ++i)
			++dc[i];
		++dc[d];

		s = d;
		p = 1;
		pos = 1;

		#ifdef DU
		cerr << "\tn: " << n;
		cerr << "\ts: " << s;
		cerr << "\td: " << d;
		cerr << "\tp: " << p;
		cerr << "\tpos: " << pos;
		cerr << endl << *this << "\n\n";
		#endif

		while (n)
		{
			d = n % MAX_DIGITS;
			n /= MAX_DIGITS;
			f = (n == 0);

			#ifdef DU
			cerr << "\tn: " << n;
			cerr << "\ts: " << s;
			cerr << "\td: " << d;
			cerr << "\tp: " << p;
			cerr << "\tf: " << f;
			cerr << "\tpos: " << pos;
			#endif

			prod = d * pos * p;
			#ifdef DU
			cerr << "\t[t]+= " << prod;
			#endif
			dc[0] += prod - p;
			for (i = 1; i < MAX_DIGITS; ++i)
				dc[i] += prod;
			prod = p * 10;
			#ifdef DU
			cerr << "\t[i]+= " << prod;
			#endif
			for (i = f; i < d; ++i)
				dc[i] += prod;
			#ifdef DU
			cerr << "\t[d]+= " << (s+1);
			#endif
			dc[d] += s + 1;

			#ifdef DU
			cerr << endl << *this << "\n\n";
			#endif

			p = prod;
			s += d * p;
			++pos;
		}
	}


	inline void digits_between (uint a, uint b)
	{
		DigitCount da;

		--a;
		da.digits_until (a);
		digits_until (b);
		//////cerr << da << endl << (*this) << endl;
		*this -= da;
	}
};


ostream & operator << (ostream &s, const DigitCount &d)
{
	s << d[0];
	for (size_t i = 1; i < MAX_DIGITS; ++i)
		s << ' ' << d[i];
	return s;
}


int main ()
{
	uint a, b;
	DigitCount d;

	#ifdef DEBUG
	for (int i = 1; i <= 1000; ++i)
	{
		d.digits_until (i);
		cerr << i << ":\t" << d << "\t\t";
		d.digits_between (i, i);
		cerr << i << ":\t" << d << endl;
	}
	#endif

	while (cin >> a >> b, a || b)
	{
		d.digits_between (a, b);
		cout << d << endl;
	}

	return 0;
}