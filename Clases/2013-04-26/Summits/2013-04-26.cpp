#include <vector>

#define POS_UNKNOWN		0
#define POS_SUMMIT		1
#define POS_SLOPE		2

struct _coord {
	unsigned char r;
	unsigned char c;
};

typedef struct _coord coord;

int h;
int w;
long int d;
long int max;
long int min;

coord new_coord(unsigned char r, unsigned char c) {
	coord result;
	
	result.r = r;
	result.c = c;
	
	return result;
}

void flood_1(long int ** matrix, long int ** matrix1, vector<coord> &summits, coord pos, long int current_summit) {
	long int here, north, south, east, west;
	
	here = matrix[pos.r][pos.c];
	
	if (pos.r > 0) { north = matrix[pos.r - 1][pos.c]; } else { north = -1; }
	if (pos.c > 0) { west = matrix[pos.r][pos.c - 1]; } else { west = -1; }
	if (pos.r < h - 1) { south = matrix[pos.r + 1][pos.c]; } else { south = -1; }
	if (pos.c < w - 1) { east = matrix[pos.r][pos.c + 1]; } else { east = -1; }
	
	
	
}

void flood(long int ** matrix, vector<coord> &summits) {
	long int matrix1[h][w];
	int i, size;
	int r, c;
	long int current;
	
	// sets the exploration matrix
	for (r = 0; r < h; r++) {
		for (c = 0; c < w; c++) {
			matrix1[r][c] = POS_UNKNOWN;
		}
	}
	
	// marks the known summits on the matrix
	size = summits.size();
	for (i = 0; i < size; i++) {
		matrix1[summits[i].r][summits[i].c] = POS_SUMMIT;
	}

	// marks the known positions that cannot be summits
	for (r = 0; r < h; r++) {
		for (c = 0; c < w; c++) {
			current = matrix[r][c];
			if (current < min + d && current < max) {
				matrix1[r][c] = POS_SLOPE;
			}
		}
	}

	for (i = 0; i < size; i++) {
		current = matrix[summits[i].r][summits[i].c];
		flood(matrix, matrix1, summits, 
	}
}

int find_summits_1() {
	unsigned char r, c;
	long int matrix[h][w];
	long int current;
	vector<coord> summits;
	
	max = 0;
	min = 1000000000;
	for (r = 0; r < h; r++) {
		for(c = 0; c < w; c++) {
			current = scanf("%ld", &current);
			matrix[r][c] = current;
			
			// if the current position is higher than the previous maximum
			if (max < current) {
				// sets the new maximum
				max = current;
				// and clears the maximum coord list
				summits.clear();
			} 
			
			if (min > current) {
				min = current;
			}
			
			// if the current position is the same than the current maximum
			if (max == current) {
				// adds the coord to the list
				summits.add(new_coord(r, c));
			}
		}
		
		scanf("\n");
	}
	
	// start search
	flood(matrix, summits);
	
	return summits.size();
}

int find_summits() {
	int h, w, d;
	
	scanf("%d ", &h);
	scanf("%d ", &w);
	scanf("%d\n", &d);

	return find_summits_1(h, w, d);
}

int main(int argc, char * argv[]) {
	int testcases;
	int summits;
	
	scanf("%d\n", &testcases);
	
	while(testcases > 0) {
		
		summits = find_summits();
		printf("%d\n", summits);
		
		testcases--;
	}
	
	return 0;
}
