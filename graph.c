#include <stdio.h>

#define MAXDIM 100

int nodes;
int edges[MAXDIM][MAXDIM];

int stack[100][2], stackpos = -1;

void push(int node, int prevnode) {
        stackpos++;
        stack[stackpos][0] = node;
	stack[stackpos][1] = prevnode;
}

void pop() {
	stackpos--;
}

int isempty() {
        return (stackpos == -1);
}

int traverse(int node, int prevnode) {
	int intersection = 0, outgoing[100], numpaths;
	int i;

        printf("starting traversal from %d, prev = %d\n", node, prevnode);

	while(intersection == 0) {
		numpaths = 0;
		for(i = 0; i < nodes; i++) {
			if(i == node)
				continue;
			if(edges[node][i] == 1) {
				if(i == nodes - 1)
					return 1;
				if(i == prevnode)
					continue;
				outgoing[numpaths++] = i;
			}
		}

		if(numpaths == 1) {
			prevnode = node;
			node = outgoing[numpaths - 1];
			printf("    moving to %d\n", node);
			continue;
		}
		else if(numpaths == 0) {
			printf("    deadend\n");
			return -1;
		}
		else {
			pop();
			for(i = 0; i < numpaths; i++) {
				printf("    pushing %d\n", outgoing[i]);
				push(outgoing[i], node);
			}
			return 0;
		}
	}
}

void main() {
	int i, j, ret;

	for(i = 0; i < MAXDIM; i++)
		for(j = 0; j < MAXDIM; j++)
			edges[i][j] = 0;

	scanf("%d", &nodes);
	while(1) {
		scanf("%d %d", &i, &j);
		if(i == -1 && j == -1)
			break;
		edges[i][j] = edges[j][i] = 1;
	}

        push(0, -1);
        while(!isempty()) {
                ret = traverse(stack[stackpos][0], stack[stackpos][1]);
                if(ret == 1) {
                        printf("found the destination\n");
                        break;
                }
                else if(ret == 0) {
                        continue;
                }
                else {
                        pop();
                }

                if(isempty()) {
                        printf("path to destination does not exist\n");
                        break;
                }
        }
}
