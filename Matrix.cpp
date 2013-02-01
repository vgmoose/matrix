#include <iostream>
#include <string>
#include <sstream>

class Matrix
{
public:
	
	int* matrix;
	int x, y;
	int* oldmatrix;
	
    std::string* steps;
    
	void reset();
	Matrix(int y, int x);
	void multiply(int row, int factor);
	void scale(int row, double factor);
	void divide(int row, double factor);
	void addRow(int dest, int operand, int factor);
	void getBeef();
	void printContents();
	void setRow(int row, int* rowContents);
	void subRow(int dest, int operand, int factor);
	void solve();
	void copy();
};

// This method is from rosetta code
std::string to_roman(int value)
{
    struct romandata_t { int value; char const* numeral; };
    static romandata_t const romandata[] =
    { 1000, "M",
        900, "CM",
        500, "D",
        400, "CD",
        100, "C",
        90, "XC",
        50, "L",
        40, "XL",
        10, "X",
        9, "IX",
        5, "V",
        4, "IV",
        1, "I",
        0, NULL }; // end marker
    
    std::string result;
    for (romandata_t const* current = romandata; current->value > 0; ++current)
    {
        while (value >= current->value)
        {
            result += current->numeral;
            value  -= current->value;
        }
    }
    return result;
}

void Matrix::reset()
{
	steps = new std::string[y];
}

void Matrix::solve()
{
	int i;
	for (i=0; i<x; i++)
	{
        //		while (matrix[i+x*
	}
}
void Matrix::addRow(int dest, int operand, int factor)
{
	dest--;
	operand--;
	int i;
	for (i=0; i<x; i++)
		matrix[dest*x+i] = matrix[dest*x+i] + factor*matrix[operand*x+i];
    
    std::stringstream build;

	if (factor > 0) build << " +";
    else build << " ";
    
	build << factor << " " << to_roman(operand+1);
	std::string s = build.str();
    
	steps[dest] = s;
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
    
    std::stringstream build;
        
	build << " /" << factor;
	std::string s = build.str();
    
	steps[row-1] = s;

}

void Matrix::multiply(int row, int factor)
{
	scale(row, factor);
    
    std::stringstream build;
    
	build << " *" << factor;
	std::string s = build.str();
    
	steps[row-1] = s;
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

	e->copy();
//	e->getBeef();

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
    reset();
    	oldmatrix = new int[y*x]; 
    
}

int main()
{
	doMath();
    
}

void Matrix::copy()
{
	int i;	
    for (i=0; i<x*y; i++)
	oldmatrix[i] = matrix[i];	
}
void Matrix::getBeef()
{
	printf("\n");
    //	printf("I am a %i x %i matrix.\n", y, x);
    
	printContents();

	copy();
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
			std::stringstream convert;
			convert << (oldmatrix[x*i+j]);
			
			std::string s = convert.str();
			while (s.size() <= 3)
			{
				s = " " + s;
			}
            
			std::cout << s;
		}

		std::cout << "]" << steps[i] << std::endl;
        
	}
    reset();

	
}
