#include <iostream>

class Matrix
{
	int* matrix;
	int x, y;	
	
	public:
	Matrix(int y, int x);
	void multiply(int row, int factor);
	void scale(int row, double factor);
	void divide(int row, double factor);
	void addRow(int dest, int operand, int factor);
	void getBeef();
	void printContents();
	void setRow(int row, int* rowContents);
	void subRow(int dest, int operand, int factor);
};

void Matrix::addRow(int dest, int operand, int factor)
{
	dest--;
	operand--;
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
	row--;

	int i;
	for (i=0; i<x; i++)
		matrix[row*x+i] = matrix[row*x+i]*factor;
}

void Matrix::divide(int row, double factor)
{
	scale(row, 1/factor);	
}

void Matrix::multiply(int row, int factor)
{
	scale(row, factor);
}

void doMath()
{
	Matrix* e = new Matrix(4,5);

	int array[] = {1, 1, 1, 3, 1};
	e->setRow(0, array);
	int array2[] = {1, -1, -3, -1, -1};	
	e->setRow(1, array2);
	int array3[] = {2, 2, 2, 7, 1};
	e->setRow(2, array3);
	int array4[] = {-2, 0, 2, -4, 2};
	e->setRow(3, array4);

	e->getBeef();

	e->subRow(2, 1, 1);
	e->subRow(3, 1, 2);
	e->addRow(4, 1, 2);
	
	e->getBeef();

	e->subRow(1, 3, 3);
	e->addRow(2, 3, 4);
	e->subRow(4, 3, 2);

	e->getBeef();

	e->divide(4, 2);
	e->getBeef();
	e->subRow(1, 4, 1);
	e->addRow(2, 4, 2);
	
	e->getBeef();

	
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
	doMath();

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
