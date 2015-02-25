#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int wrapX(int i, int j, int size){
	i += j;
	while (i < 0) i += size;
	while (i >= size) i -= size;
	return i;
}

int wrapY(int i, int j, int size){
	i += j;
	while (i < 0) i += size;
	while (i >= size) i -= size;
	return i;
}


int adjacent(int **board, int i, int j, int size){
	int k,l,count;
	count = 0;

	for(k = -1; k <= 1; k++)
		for(l = -1; l <= 1; l++)
			if(k != 0 || l != 0)
				if(board[wrapX(i,k,size)][wrapY(j,l,size)] == 1)
					count++;
	return count;
}


void new_gen(int **board1, int **board2, int size){
	sleep(1);
	system("clear");

	int i, j, neighbours;

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++){
			neighbours = adjacent(board1, i, j, size);
			if (neighbours == 2) board2[i][j] = board1[i][j];
			if (neighbours == 3) board2[i][j] = 1;
			if (neighbours < 2) board2[i][j] = 0;
			if (neighbours > 3) board2[i][j] = 0;
		}

		for(i = 0; i < (size + 2);  i++)
			printf("-");
		printf("\n");
		for(i = 0; i < size;  i++){
			printf("|");
			for(j = 0; j < size; j++){
				if(board1[i][j] == 1)
					printf("x");
				else printf(" ");
			}
			printf("|\n");
		}
		for(i = 0; i < (size + 2);  i++)
			printf("-");
		printf("\n");

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++){
			int *temp = board1[i][j];
			board1[i][j] = board2[i][j];
			board2[i][j] = temp;
	}

}


void main(int argc, char *argv[]){

	int gridSize;

	FILE *file = fopen(argv[1], "r");
	fscanf(file, "%d", &gridSize);

	//int threads = atoi(argv[2]);

	int **A, **B;
	int i, j, k, l;

	A = malloc(gridSize * sizeof(int *));
	for(i = 0; i < gridSize; i++)
		A[i] = malloc(gridSize * sizeof(int));

	for(i = 0; i < gridSize; i++)
		for(j = 0; j < gridSize; j++)
			fscanf(file, "%d", &A[i][j]);

	fclose(file);

	B = malloc(gridSize * sizeof(int *));
	for(i = 0; i < gridSize; i++)
		B[i] = malloc(gridSize * sizeof(int));

	while(1)
		new_gen(A,B,gridSize);
}