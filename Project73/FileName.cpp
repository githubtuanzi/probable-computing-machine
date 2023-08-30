#include<iostream>
#include<iomanip>
using namespace std;

class Matrix
{
public:
	Matrix() { row = 0; column = 0; s = NULL; };
	Matrix(int,int);
	Matrix(const Matrix&);
	friend istream& operator>>(istream&, Matrix&);
	friend Matrix operator+(const Matrix&,const  Matrix&);
    Matrix& operator=(const Matrix&);
	~Matrix();
	void display();
private:
	int row;
	int column;
	int* s;
};

int main()
{
	Matrix M1, M2, M3;
	cin >> M1 >> M2;
	M3 = M1 + M2;
	cout << "M1:\n";
	M1.display();
	cout << "M2:\n";
	M2.display();
	cout << "M3:\n";
	M3.display();
	return 0;
}

Matrix::Matrix(int m, int n)
{
	row = m;
	column = n;
	s = new int[m * n];//在堆区为矩阵动态地分配一段内存空间
	memset(s, 0, m * n * sizeof(int));//初始化矩阵为零
	/*memset是内存赋值函数，原型：void* memset(void* str, int c, size _t n)
	复制字符c到参数str所指向字符串的前n个字符。memset赋值时是按字节赋值的，
	将参数转化成二进制之后填入一个字节。
	若str指向char型地址，则c可为任意值（char只占一个字节），
	若为非char型，则c=0 or -1，否则会改变原值
	*/
}

Matrix::~Matrix()
{
	row = 0;
	column = 0;
	if (s != NULL) delete s;
	//若s不是空指针，则释放s所指向的内存空间，避免释放一个空指针或已经被释放的指针而导致程序崩溃
	s = NULL;
	//避免出现悬空指针的情况，即s指向的内存空间已经被释放，
	//但s仍然存有指向该内存的地址，这样会导致程序错误
}

Matrix::Matrix(const Matrix& c)//有动态分配内存的类，使用深拷贝构造函数
{
	row = c.row;
	column = c.column;
	if (row * column != 0)
	{
		s = new int[row * column];
		//在堆区申请一段新的内存空间，避免被拷贝的类与拷贝的类指向同一段内存空间
		for (int i = 0; i < row * column; i++)
			s[i] = c.s[i];//一一赋值
	}
	else s = NULL;
}

Matrix& Matrix:: operator=(const Matrix& c)
{
	if (this == &c) return *this;
	this->row = c.row;
	this->column = c.column;
	this->s = new int[row * column];
	for (int i = 0; i < row * column; i++)
	{
		this->s[i] = c.s[i];
	}
	return *this;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	if (!m1.s) return m2;//判断m1是否申请到空间或是否为空矩阵
	if (!m2.s) return m1;//判断m2是否申请到空间或是否为空矩阵
	//判断m1和m2行与列是否相等，相等才可相加
	if ((m1.row != m2.row) || (m1.column != m2.column))
		throw logic_error("Size mismatch in Matrix addition");
	Matrix m;
	m = m1;
	for (int i = 0; i < (m1.row) * (m1.column); i++)
	{
		m.s[i] = m1.s[i] + m2.s[i];
	}
	return m;
}

void Matrix::display()
{
	for (int x = 0; x < row * column; x++)
	{
		cout << setw(5) << setiosflags(ios::left) << s[x];
		if ((x + 1) % column == 0) cout << endl;
	}
	return;
}

istream& operator>>(istream& input, Matrix& M)
{
	cout << "please input the value of the row:";
	input >> M.row;
	cout << "please input the value of the colume:";
	input >> M.column;
	cout << "please input a Matrixc according to the row and colume you have input:\n";
	M.s = new int[M.row * M.column];
	for (int i = 0; i < (M.row * M.column); i++)
		input >> M.s[i];
	return input;
}