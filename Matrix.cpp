#include <iostream>

class Matrix
{
	int* matrix;
	int x, y;	
	
	public:
	Matrix(int y, int x);
	void multiply(int row, int factor);
	void scale(int row, double factor);
	void divide(int row, int factor);
	void addRow(int dest, int operand, int factor);
	void getBeef();
	void printContents();
	void setRow(int row, int* rowContents);
	void subRow(int dest, int operand, int factor);
};

void Matrix::addRow(int dest, int operand, int factor)
{
	int i;
	for (i=0; i<x; i++)
		matrix[dest*x+i] = matrix[dest*x+i] + factor*matrix[operand*x+i];
}

void Matrix::subRow(int dest, int operand, int factor)
{
	addRow(dest, operand, -factor);
}
void Matrix::scale(int row, double factor)
{
	int i;
	for (i=0; i<x; i++)
		matrix[row*x+i] = matrix[row*x+i]*factor;
}

void Matrix::divide(int row, int factor)
{
	scale(row, 1/factor);	
}

void Matrix::multiply(int row, int factor)
{
	scale(row, factor);
}

void doMath()
{
	Matrix* m = new Matrix(4, 5);
	m->subRow(2, 1, 1);
	m->subRow(3, 1, 2);
	m->addRow(4, 1, 2);
	m->getBeef();
}
void Matrix::setRow(int row, int* rowContents)
{
	int i;
	for (i=0; i<x; i++)
	{
		matrix[x*row+i] = rowContents[i];
//		printf("Inserting into spot %i", y*row+i);	
	}
}


Matrix::Matrix(int y, int x)
{
	this->y = y;
	this->x = x;
	matrix = new int[y*x];	
}

int main()
{
	Matrix* e = new Matrix(4,5);
	e->getBeef();

	int array[] = {1, 0, 3, 2, 2};
	e->setRow(0, array);
	int array2[] = {0, 1, -4, -3, -9};	
	e->setRow(1, array2);
	int array3[] = {2, -2, 18, 10, 38};
	e->setRow(2, array3);
	int array4[] = {0, -1, 4, 2, -3};
	e->setRow(3, array4);
	e->getBeef();

	e->divide(0, 2);
	e->getBeef();
}

void Matrix::getBeef()
{
	printf("I am a %i x %i matrix.\n", y, x);	
	printContents();
}

void Matrix::printContents()
{
	int i;
	for (i=0; i<y; i++)
	{
		int j;
		printf("[ ");
		for (j=0; j<x; j++)
		{
			printf("[%i] ", matrix[x*i+j]);
		}
		printf("]\n");
	}
	
}
