#include <stdio.h>

#define ROWS 15
#define COLS 55

char maze[ROWS][COLS];

int stack[100][4], stackpos = -1;

void push(int row, int col, int prevrow, int prevcol) {
	stackpos++;
	stack[stackpos][0] = row;
	stack[stackpos][1] = col;
	stack[stackpos][2] = prevrow;
	stack[stackpos][3] = prevcol;
}

void pop() {
	stackpos--;
}

int isempty() {
	return (stackpos == -1);
}

// returns 1 if destination found
// returns 0 if intersection found, and also pushes the next possible paths to the stack
// returns -1 if deadend
int traverse(int currrow, int currcol, int prevrow, int prevcol) {
	int i, j;
	int intersection = 0, outgoing[3][2], numpaths;

	printf("starting traversal from (%d, %d), prev (%d, %d)\n", currrow, currcol, prevrow, prevcol);

	while(intersection == 0) {
		numpaths = 0;
		for(i = -1; i <= +1; i+=2) {
			if(currrow + i >= 0 && currrow + i < ROWS && currrow + i != prevrow) {
				printf("       testing for %d,%d = %c\n", currrow + i, currcol, 
					maze[currrow + i][currcol]);
				if(maze[currrow + i][currcol] == '*') {
					if(currrow + i == ROWS-1 && currcol == COLS-1)
						return 1;
					outgoing[numpaths][0] = currrow + i;
					outgoing[numpaths][1] = currcol;
					numpaths++;
				}
			}
			if(currcol + i >= 0 && currcol + i < COLS && currcol + i != prevcol) {
				printf("       testing for %d,%d = %c\n", currrow, currcol + i, 
					maze[currrow][currcol + i]);
				if(maze[currrow][currcol + i] == '*') {
					if(currrow == ROWS-1 && currcol + i == COLS-1)
						return 1;
					outgoing[numpaths][0] = currrow;
					outgoing[numpaths][1] = currcol + i;
					numpaths++;
				}
			}
		}

		if(numpaths == 1) {
			prevrow = currrow; prevcol = currcol;
			currrow = outgoing[numpaths - 1][0]; currcol = outgoing[numpaths - 1][1];
			printf("    moving to (%d, %d), prev (%d, %d)\n", currrow, currcol, prevrow, prevcol);
			continue;
		}
		else if(numpaths == 0) {
			printf("    deadend\n");
			return -1;
		}
		else {
			printf("    found intersection\n");
			pop();
			for(i = 0; i < numpaths; i++) {
				printf("          pushing (%d, %d), prev (%d, %d)\n", outgoing[i][0], 
					outgoing[i][1], currrow, currcol);
				push(outgoing[i][0], outgoing[i][1], currrow, currcol);
			}
			return 0;
		}
	}
}

void main() {
	char c;
	int i, j, ret;

	for(i = 0; i < ROWS; i++) {
                for(j = 0; j < COLS; j++) {
                        scanf("%c", &maze[i][j]);
                        printf("%c", maze[i][j]);
                }

                // read extra columns in row
                while(1) {
                        scanf("%c", &c);
                        if(c == '\n') {
                                break;
                        }
                }
                printf("\n");
        }

	push(0, 1, 0, 0);
	while(!isempty()) {
		ret = traverse(stack[stackpos][0], stack[stackpos][1], stack[stackpos][2], stack[stackpos][3]);
		if(ret == 1) {
			printf("found the destination\n");
			break;
		}
		else if(ret == 0) {
			continue; // intersection found, next iteration will use the top of the stack
		}
		else {
			pop(); // deadend, therefore pop, next iteration will use the next element of the stack
		}

		if(isempty()) {
			printf("path to destination does not exist\n");
			break;
		}
	}
}
