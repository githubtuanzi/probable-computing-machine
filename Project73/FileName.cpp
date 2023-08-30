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
	s = new int[m * n];//�ڶ���Ϊ����̬�ط���һ���ڴ�ռ�
	memset(s, 0, m * n * sizeof(int));//��ʼ������Ϊ��
	/*memset���ڴ渳ֵ������ԭ�ͣ�void* memset(void* str, int c, size _t n)
	�����ַ�c������str��ָ���ַ�����ǰn���ַ���memset��ֵʱ�ǰ��ֽڸ�ֵ�ģ�
	������ת���ɶ�����֮������һ���ֽڡ�
	��strָ��char�͵�ַ����c��Ϊ����ֵ��charֻռһ���ֽڣ���
	��Ϊ��char�ͣ���c=0 or -1�������ı�ԭֵ
	*/
}

Matrix::~Matrix()
{
	row = 0;
	column = 0;
	if (s != NULL) delete s;
	//��s���ǿ�ָ�룬���ͷ�s��ָ����ڴ�ռ䣬�����ͷ�һ����ָ����Ѿ����ͷŵ�ָ������³������
	s = NULL;
	//�����������ָ����������sָ����ڴ�ռ��Ѿ����ͷţ�
	//��s��Ȼ����ָ����ڴ�ĵ�ַ�������ᵼ�³������
}

Matrix::Matrix(const Matrix& c)//�ж�̬�����ڴ���࣬ʹ��������캯��
{
	row = c.row;
	column = c.column;
	if (row * column != 0)
	{
		s = new int[row * column];
		//�ڶ�������һ���µ��ڴ�ռ䣬���ⱻ���������뿽������ָ��ͬһ���ڴ�ռ�
		for (int i = 0; i < row * column; i++)
			s[i] = c.s[i];//һһ��ֵ
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
	if (!m1.s) return m2;//�ж�m1�Ƿ����뵽�ռ���Ƿ�Ϊ�վ���
	if (!m2.s) return m1;//�ж�m2�Ƿ����뵽�ռ���Ƿ�Ϊ�վ���
	//�ж�m1��m2�������Ƿ���ȣ���Ȳſ����
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