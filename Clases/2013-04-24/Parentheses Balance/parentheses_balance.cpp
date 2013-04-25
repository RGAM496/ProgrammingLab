#include <cstdio>

#define MAX_LENGTH 128


struct stack
{
	int v[MAX_LENGTH];
	int *front, *rear;

	inline void reset () {front = rear = v - 1;}

	inline bool is_empty () {return front == rear;}

	inline void push (int c) {*rear++ = c;}
	inline int pop () {return *rear--;}

	/*void debug () {
		for (int *p = front + 1; p <= rear; ++p)
			printf (" %c", *p);
		putchar('\n');
	}*/
};


/*******************************************************************/


int main ()
{
	int test_cases, c, caux;
	stack pila;
	bool is_correct;

	scanf("%d", &test_cases);

	while (test_cases)
	{
		c = getchar();
		is_correct = true;
		pila.reset();
		while (is_correct && c != '\n' && c != EOF)
		{
			switch (c)
			{
				case '(':
				case '[':
				{
					pila.push(c);
					break;
				}

				case ')':
				{
					if (pila.is_empty())
						is_correct = false;
					else {
						caux = pila.pop();
						is_correct = (caux == '(');
					}
					break;
				}

				case ']':
				{
					if (pila.is_empty())
						is_correct = false;
					else {
						caux = pila.pop();
						is_correct = (caux == '[');
					}
					break;
				}
			}

			c = getchar();
		}
		//pila.debug();
		if (is_correct)
			puts(pila.is_empty() ? "yes" : "no");
		else {
			puts("no");
			if (test_cases > 1) {
				while (c != '\n')
					c = getchar();
			}
		}

		--test_cases;
	}
}