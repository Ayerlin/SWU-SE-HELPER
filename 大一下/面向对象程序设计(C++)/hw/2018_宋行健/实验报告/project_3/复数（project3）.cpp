#include <iostream>
using namespace std;

class Complex
{
	// Ĭ��Ϊ˽�б���private
	double real;
	double imaginary;
public:
	//Ĭ�Ϲ��캯����������ʼ��Ϊ0+0i
	Complex()
	{
		real = 0;
		imaginary = 0;
	}

	//������ĳ�Ա��������Ϊ�κ�ֵ
	void set(double re,double imag)
	{
		imaginary = imag;
		real = re;
	}

	//�������ʼ��Ϊʵ����+0*i
	void set(double re)
	{
		imaginary = 0;
		real = re;
	}

	// ����ʵ��
	double get_Real(void)
	{
		return real;
	}

	// �����鲿
	double get_Imaginary(void)
	{
		return imaginary;
	}

	// ���� + ����������ڰ����� Complex �������
	Complex operator+(const Complex& data)
	{
		Complex complex_num;
		complex_num.real = this->real + data.real;
		complex_num.imaginary = this->imaginary + data.imaginary;
		return complex_num;
	}

	// ���� - ����������ڰ����� Complex �������
	Complex operator-(const Complex& data)
	{
		Complex complex_num;
		complex_num.real = this->real - data.real;
		complex_num.imaginary = this->imaginary - data.imaginary;
		return complex_num;
	}

	// ���� * ����������ڰ����� Complex �������
	Complex operator*(const Complex& data)
	{
		Complex complex_num;
		complex_num.real = this->real * data.real - this->imaginary * data.imaginary;
		complex_num.imaginary = this->imaginary * data.real + this->real * data.imaginary;
		return complex_num;
	}

	// ���� == ����������ڱȽ����� Complex ����
	bool operator ==(const Complex& data)
	{
		//Complex complex_num;  ��ע�⣺��ϵ����������أ����ﲻ��Ҫ������������
		if (this->real == data.real && this->imaginary == data.imaginary)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ���� >> ����������ڱȽ����� Complex ����
	bool operator >>(const Complex& data)
	{
		if (this->real > data.real)
		{
			return true;
		}
		else if (this->real == data.real)
		{
			if (this->imaginary > data.imaginary)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	// ���� << ����������ڱȽ����� Complex ����
	bool operator <<(const Complex& data)
	{
		if (this->real < data.real)
		{
			return true;
		}
		else if (this->real == data.real)
		{
			if (this->imaginary < data.imaginary)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	// չʾ������ĸ���
	void show()	
	{
		cout << "You Input:\t" << get_Real() << " + " << get_Imaginary() << " * i" << endl;
	}

};


int main()
{
	Complex i;
	i.set(0, 1);			//��ʼ��iΪ0+1i		

	Complex complex_1;                // ���� Complex_1������Ϊ Complex
	Complex complex_2;                // ���� Complex_2������Ϊ Complex
	Complex complex_result;           // ���� Complex_result������Ϊ Complex
	double real, imaginary;           // ����double���͵ĸ�����������ɲ���
	
	// Complex_1 ��ֵΪ��ʵ�����ͣ�ֻ��һ��������Ϊʵ����
	cout << "Please intput the second complex number (One Parameter):" << endl;
	cin >> real;
	complex_1.set(real);		// �γɵ���Complex����˽�б����Ķ˿�
	complex_1.show();		// չʾ�����������
	
	// Complex_2 ��ֵΪ���������ͣ�������������һ��Ϊʵ������һ��Ϊ�鲿��
	cout << "\nPlease intput the first complex number (Two Parameters):" << endl;
	cin >> real >> imaginary;
	complex_2.set(real, imaginary);		// �γɵ���Complex����˽�б����Ķ˿�
	complex_2.show();		// չʾ�����������

	// �������������
	complex_result = complex_1 + complex_2;
	cout << "\n�ӷ���" << endl;
	cout << "("<<complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) + (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i ) == (" << complex_result.get_Real() << " + " << complex_result.get_Imaginary() << " * i )" << endl;

	// �������������
	complex_result = complex_1 - complex_2;
	cout << "\n������" << endl;
	cout << "(" << complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) - (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i ) == (" << complex_result.get_Real() << " + " << complex_result.get_Imaginary() << " * i )" << endl;

	// �������������
	cout << "\n�˷���" << endl;
	complex_result = complex_1 * complex_2;
	cout << "(" << complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) * (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i ) == (" << complex_result.get_Real() << " + " << complex_result.get_Imaginary() << " * i )" << endl;

	// ������������Ƚ�
	cout << "\n�ȴ�С��" << endl;
	if (complex_1 << complex_2)
	{
		cout << "(" << complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) < (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i )" << endl;
	}
	else if (complex_1 >> complex_2)
	{
		cout << "(" << complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) > (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i )" << endl;
	}
	else
	{
		cout << "(" << complex_1.get_Real() << " + " << complex_1.get_Imaginary() << " * i ) == (" << complex_2.get_Real() << " + " << complex_2.get_Imaginary() << " * i )" << endl;
	}

	return 0;
}