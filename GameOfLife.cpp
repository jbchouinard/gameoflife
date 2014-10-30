#include "GameOfLife.h"

GameOfLife::GameOfLife() {
	for(int i=0;i<8;i++) { matrix[i] = B00000000; }
}

//Compute the state of the middle cell of a 9-cell frame for the next tick

int GameOfLife::cellState(int* previous, int* current, int* next) {
	
	int state=0;
	int total=0;

	for(int i=0; i<3; i++) {
		total = total + previous[i] + current[i] + next[i];
	}
	
	//Do not count middle cell
	total = total - current[2];

	if(n==2) state = current[2];
	else if (n==3) state = 1;
	
	return state;		

}

//Load the next column (externally defined) into the 9-cell frame

void GameOfLife::loadFrame(int* previous, int* current, int* next, int row1, int row2, int row3, int column) {

	previous = current;
	current = next;

	next[0] = bitRead(matrix[row1], column);
	next[1] = bitRead(matrix[row2], column);
	next[2] = bitRead(matrix[row3], column);

}

//Compute a row of the matrix for the next tick. Row2 is assumed to be the middle row.
//Geometry is not checked. The caller is responsible for determining rows.

void GameOfLife::computeRow(byte* newMatrix, int row1, int row2, int row3) {

	int[3] previous;
	int[3] current;
	int[3] next;

	/First we do the left cell

	loadFrame(previous, current, next, row1, row2, row3, 7);
	loadFrame(previous, current, next, row1, row2, row3, 0);
	loadFrame(previous, current, next, row1, row2, row3, 1);

	bitWrite(newMatrix[row2], 0, cellState(previous, current, next));

	//Then the middle cells

	for(int column=1; i<7; i++) {

		loadFrame(previous, current, next, row1, row2, row3, column+1);
		bitWrite(newMatrix[row2], column, cellState(previous, current, next));
	}
	
	//Then the right cell
	
	loadFrame(previous, current, next, row1, row2, row3, 0);
	bitWrite(newMatrix[row2], 7, cellState(previous, current, next));

}

//Initialize a matrix with each cell having probability p/100 of being alive

void GameOfLife::initRandomMatrix(int p) {
	for(int row=0; row<8; row++) {
		for(int column=0; column<8; column++) {	
			if(p>random(0,99)) bitSet(matrix[row], column);
			else bitClear(matrix[row], column);
		}
	}
}


//Compute the next tick of Life

void GameOfLife::tick() {
	
	byte[8] newMatrix;
	
	//Top edge
	computeRow(newMatrix, 7, 0, 1);
	
	//Bottom edge
	computeRow(newMatrix, 6, 7, 0);

	//Compute middle lines
	for(int row=1; row<7; row++) {
		computeRow(newMatrix, row-1, row, row+1);
	}

	matrix=newMatrix;
}
