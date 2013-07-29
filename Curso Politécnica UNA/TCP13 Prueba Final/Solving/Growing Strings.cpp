#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N 10000
#define MAX_LENGTH 1001

typedef char String[MAX_LENGTH];


struct PString
{
	const char *s;
};

inline bool operator < (const PString &s, const PString &t)
{
	return strstr (s.s, t.s) != 0;
}


/* CeilIndex y LongestIncreasingSubsequenceLength adaptados de
 * http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 * para soportar todos los tipos de datos.
 */


template <typename N>
int CeilIndex(N A[], int l, int r, N key) {
	int m;
 
	while( r - l > 1 ) {
		m = l + (r - l)/2;
		(A[m] < key ? l : r) = m; // ternary expression returns an l-value
	}
 
	return r;
}

template <typename N>
int LongestIncreasingSubsequenceLength(N A[], int size) {
	// Add boundary case, when array size is one
 
	static N tailTable[MAX_N];
	int len;
 
	tailTable[0] = A[0];
	len = 0;
	for( int i = 1; i < size; i++ ) {
		if( A[i] < tailTable[0] )
			// new smallest value
			tailTable[0] = A[i];
		else if( tailTable[len] < A[i] )
			// A[i] wants to extend largest subsequence
			tailTable[++len] = A[i];
		else
			// A[i] wants to be current end candidate of an existing subsequence
			// It will replace ceil value in tailTable
			tailTable[CeilIndex(tailTable, -1, len, A[i])] = A[i];
	}


	return ++len;
}


String s[MAX_N];
PString ps[MAX_N];


int main ()
{
	int n;

	while (cin >> n, n)
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> s[i];
			ps[i].s = s[i];
		}

		sort (ps, ps + n);

		cout << LongestIncreasingSubsequenceLength (ps, n) << endl;
	}

	return 0;
}