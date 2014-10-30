#ifndef GameOfLife_H
#define GameOfLife_H

#include "Arduino.h"

class GameOfLife {
	public:
		byte[8] matrix;
		void initRandomMatrix(int p);
		void tick();
		GameOfLife();
	private:
		int cellState(int* previous, int* current, int* next);
		void loadFrame(int* previous, int* current, int* next, int row1, int row2, int row3, int column);
		void computeRow(byte* newMatrix, int row1, int row2, int row3);
}

#endif
