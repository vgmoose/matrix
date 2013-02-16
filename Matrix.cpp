#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <class T>
bool from_string(T& t,
                 const string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

class Matrix
{
public:
	
	float* matrix;
	int x, y;
	float* oldmatrix;
	
    string* steps;
    
	void reset();
	Matrix(int y, int x);
    Matrix(std::vector<std::vector<float> > v);
	void multiply(int row,  float factor);
	void scale(int row,  float factor);
	void divide(int row,  float factor);
	void addRow(int dest, int operand,  float factor);
	void getBeef();
	void printContents();
	void setRow(int row, float* rowContents);
	void subRow(int dest, int operand,  float factor);
	void solve();
	void copy();
        
	void setMatrix(float* incoming);

};

Matrix* readMatrixFromInput()
{
    string s;
    std::vector<std::vector<float> > vmatrix;
    
    
    do {
        std::vector<float> v;
        std::getline(cin, s);
        
//        line >> s;
        if (s == "") break;
        
        while (s.size()!=0)
        {
//            cout << s << endl;
            float f;
            from_string<float>(f, s, std::dec);
            v.push_back(f);
                        
            // find the substring
            int x;
            for (x=0; x<s.size(); x++)
            {
//                cout << s[x] << endl;
                if (s[x] == ' ')
                {
                    s = s.substr(x+1);
                    break;
                }
                else if (x+1==s.size())
                {
                    s = "";
                }
            }
        }
        vmatrix.push_back(v);
    } while (true);
    
    return new Matrix(vmatrix);
    
    //    cout << s;
}



void Matrix::setMatrix(float* incoming)
{
	int i;	
	for (i=0; i<x*y; i++)
	{
		matrix[i] = incoming[i];
	}
}
// This method is from rosetta code
string to_roman(int value)
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
    
    string result;
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
	steps = new string[y];
}

void Matrix::solve()
{
	int i,j,k;
	for (i=0; i<y; i++)
	{
		for (j=0; j<x; j++)
		{
			if (matrix[j+x*i] != 0)
			{
			float a = matrix[j+x*i];
			if (a!=1)
			{
				divide(i+1,a);
				//i--;
				//printf("%i", i);
				getBeef();
			}
			for (k=0; k<y; k++)
			{
				if (k!=i && matrix[j+x*k]!=0)
				{
				subRow(k+1, i+1, matrix[j+x*k]); 
				}

			}
			getBeef();
			break;


		}
	}
}}
void Matrix::addRow(int dest, int operand, float factor)
{
	dest--;
	operand--;
	int i;
	for (i=0; i<x; i++)
		matrix[dest*x+i] = matrix[dest*x+i] + factor*matrix[operand*x+i];
    
    stringstream build;

	if (factor > 0) build << " +";
    else build << " ";
    
	build << factor << " " << to_roman(operand+1);
	string s = build.str();
    
	steps[dest] = s;
}

void Matrix::subRow(int dest, int operand, float factor)
{
	addRow(dest, operand, -factor);
}

void Matrix::scale(int row, float factor)
{
	row--;
    
	int i;
	for (i=0; i<x; i++)
		matrix[row*x+i] = matrix[row*x+i]*(factor+0.0);
}

void Matrix::divide(int row, float factor)
{
	scale(row, 1/factor);
    
    stringstream build;
        
	build << " /" << factor;
	string s = build.str();
    
	steps[row-1] = s;

}

void mainHub()
{
    cout << "Welcome to the Easy Matrix Program\nProgrammed by Ricky Ayoub\n\nWhat would you like to do?\n\n1) Manage Variables\t2) RREF Matrix\n3) Add Matrices  \t4) Multiply Matrices\n5) Find Determinant\t6) Find Inverse\n\nEnter the number of what you would like to do: \n\n";
}

void Matrix::multiply(int row, float factor)
{
	scale(row, factor);
    
    stringstream build;
    
	build << " *" << factor;
	string s = build.str();
    
	steps[row-1] = s;
}

void doMath()
{
 	Matrix* e = new Matrix(5,6);   
//	Matrix* e = new Matrix(3,4);
	
//	float array[] = {1, 1, 1, 3, 1};
//	e->setRow(0, array);
//	float array2[] = {1, -1, -3, -1, -1};
//	e->setRow(1, array2);
//	float array3[] = {2, 2, 2, 7, 1};
//	e->setRow(2, array3);
//	float array4[] = {-2, 0, 2, -4, 2};
//	e->setRow(3, array4);

	//float array[] = {1,2,3,1,2,2,2,1,1,2,-2,1};
	//e->setMatrix(array);
	float array[] = {2, 4, 3, 5, 6, 37, 4, 8, 7, 5, 2, 74, -2, -4, 3, 4, -5, 20, 1, 2, 2, -1, 2, 26, 5, -10, 4, 6, 4, 24, 5, -10, 4, 6, 4, 24};
	e->setMatrix(array);
	e->copy();

	e->solve();
	e->getBeef();

//	e->subRow(2, 1, 1);
//	e->subRow(3, 1, 2);
//	e->addRow(4, 1, 2);
//	
//	e->getBeef();
//
//	e->subRow(1, 3, 3);
//	e->addRow(2, 3, 4);
//	e->subRow(4, 3, 2);
//    
//	e->getBeef();
//    
//	e->divide(4, 2);
//	e->getBeef();
//	e->subRow(1, 4, 1);
//	e->addRow(2, 4, 2);
//	
//	e->getBeef();
//	e->getBeef();
    
	
}
void Matrix::setRow(int row, float* rowContents)
{
	int i;
	for (i=0; i<x; i++)
	{
		matrix[x*row+i] = rowContents[i];
        //		printf("Inserting into spot %i", y*row+i);
	}
}

Matrix::Matrix(std::vector<std::vector<float> > v)
{
//    Matrix(v.size(), v[0].size());
    int i, j;

    x = v[0].size();
    y = v.size();
    
	matrix = new float[y*x];
    reset();
    oldmatrix = new float[y*x];
    
    for (i=0; i<v.size(); i++)
    {
        for (j=0; j<v[0].size(); j++)
            matrix[i*x+j] = v[i][j];
//            cout << v[i][j];
//        cout << endl;
    }
    
    copy();
    getBeef();
    
}

Matrix::Matrix(int y, int x)
{
	this->y = y;
	this->x = x;
	matrix = new float[y*x];
    reset();
    oldmatrix = new float[y*x]; 
    
}
void test()
{
    
}
int main()
{
//    mainHub();
//    readMatrixFromInput()m;
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
			stringstream convert;
			if (oldmatrix[x*i+j] == 0) oldmatrix[x*i+j] = 0;
			convert << (oldmatrix[x*i+j]);
			
			string s = convert.str().substr(0,4);
			while (s.size() <= 4)
			{
				s = " " + s;
			}
            
			cout << s;
		}

		cout << "]" << steps[i] << endl;
        
	}
    reset();

	
}
