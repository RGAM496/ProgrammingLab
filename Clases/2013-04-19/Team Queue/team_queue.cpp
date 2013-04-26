#include <cstdio>
#include <cstring>
#include <queue>

#define MAX_TEAMS 1000
#define MAX_ELEMS 1000000
#define ENQUEUE "ENQUEUE"
#define DEQUEUE "DEQUEUE"
#define STOP "STOP"


/*****************************************************/


inline int get_int (int &n)
{
	return scanf("%d", &n);
}

inline int get_string (char *str)
{
	return scanf("%s", str);
}


inline int fputs (const char *str)
{
	return fputs (str, stdout);
}

inline void print_scenario ()
{
	static int scenario = 0;
	fputs("Scenario #");
	printf("%d", ++scenario);
	putchar('\n');
}


/*****************************************************/


/*struct ElemQueue
: public std::queue<int>
{
	int team;
};*/

typedef std::queue<int> ElemQueue;
typedef std::queue<ElemQueue*> TeamQueue;


/*****************************************************/

int team_of[MAX_ELEMS];

int main ()
{
	int total_teams, team_elements, element;
	char command[8];
	ElemQueue *t;

	get_int(total_teams);
	while (total_teams)
	{
		print_scenario();

		TeamQueue team_queue;
		ElemQueue team[total_teams];

		// Parsing head.
		for (int i = 0; i < total_teams; ++i)
		{
			//team[i].team = i;
			get_int(team_elements);
			while (team_elements--)
			{
				get_int(element);
				team_of[element] = i;
			}
		}

		// Reading commands.
		get_string(command);
		while (strcmp( command, STOP))
		{
			if (!strcmp( command, ENQUEUE))
			{
				get_int(element);
				t = team + team_of[element];
				if (t->empty())
					team_queue.push(t);
				t->push(element);
			}
			else // DEQUEUE
			{
				t = team_queue.front();
				element = t->front();
				printf("%d\n", element);
				t->pop();
				if (t->empty())
					team_queue.pop();
			}

			get_string(command);
		}

		get_int(total_teams);
	}

	return 0;
}