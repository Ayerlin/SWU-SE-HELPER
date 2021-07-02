#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
string exchange(int number);			//����������ת��Ϊ�ַ�����

int main()
{
	ifstream in;			//�����ļ�����
	ofstream out;			//д���ļ�����
	int number=1;			//�ڼ��صļ���������
	string name;			//�ļ����ƣ��ڼ��أ�
	string line;			//�����ļ�����ÿ�ζ�һ�У����������
	string location;			//�ļ���ַ���ƣ�
	char *loc;			//�ļ���ַ�����ַ�����λָ�룻

	in.open("E:\\C++\\���Ӣ�۴�.txt");			//��Ҫ������ļ���
	out.open("E:\\C++\\���Ӣ�۴�out\\ǰ��.txt");			//��ǰ�ԣ�

	if (!in)
		cout << "Open failed(in)" << endl;			//����ԭ�ļ��Ƿ�򿪳ɹ���
	
	else 
	{
		name = exchange(number);			//����������ת��Ϊ�ַ����������ڼ��ء���
		while (getline(in, line))			//��in���ж��������ݣ��򽫶�������ݴ���line��
		{
			if (!line.find(name))			//���line�к��С��ڼ��ء��ؼ��֣����½��ļ���
			{
				out.close();					//�ر���һ���ļ���	
				cout << name << endl;			//���Ӹ��ƹ��̣�
				location = "E:\\C++\\���Ӣ�۴�out\\" + name + ".txt";			//location�����ļ���������ַ���ַ�����
				loc = &location[0];			//loc�����ļ���������ַ�ַ������ڴ��ַ��
		
				out.open(loc);			//�����ļ���
				if (!out)
				{
					cout << "Open failed(out)" << endl;			//����ļ��Ƿ񴴽��ɹ�,�����ɹ�������ѭ����
					break;
				}
				number++;			//����������һ��
				name = exchange(number);				//����������ת��Ϊ�ַ����������ڼ��ء���			
			}
			out << line << endl;			//һ��һ�н�����д���ļ���
		}
		cout << endl;
		cout << "FINISH!!!" << endl;			//���������ʾ��
	}

	out.close();			//�رմ򿪵������ļ���
	in.close();

	return 0;
}

string exchange(int number)			//����������ת��Ϊ�ַ�����
{
	string name;			//�ڼ��أ�
	int number_1;			//����������ʮλ��
	int number_2;			//���������ĸ�λ��
	number_1 = number / 10;
	number_2 = number % 10;
	
	if (number_1 == 0)			//��������Ϊ��λ����ʮλΪ0��
	{
		switch (number_2)
		{
		case 1:name = "һ"; break;
		case 2:name = "��"; break;
		case 3:name = "��"; break;
		case 4:name = "��"; break;
		case 5:name = "��"; break;
		case 6:name = "��"; break;
		case 7:name = "��"; break;
		case 8:name = "��"; break;
		case 9:name = "��"; break;
		}
	}
	else if (number_1 == 1)			//��������Ϊ10~19��
	{
		switch (number_2)
		{
		case 0:name = "ʮ"; break;
		case 1:name = "ʮһ"; break;
		case 2:name = "ʮ��"; break;
		case 3:name = "ʮ��"; break;
		case 4:name = "ʮ��"; break;
		case 5:name = "ʮ��"; break;
		case 6:name = "ʮ��"; break;
		case 7:name = "ʮ��"; break;
		case 8:name = "ʮ��"; break;
		case 9:name = "ʮ��"; break;
		}
	}
	else					//��������Ϊ20~99��
	{
		switch (number_1)			//�����ʮλ��
		{
		case 2:name = "��"; break;
		case 3:name = "��"; break;
		case 4:name = "��"; break;
		case 5:name = "��"; break;
		case 6:name = "��"; break;
		case 7:name = "��"; break;
		case 8:name = "��"; break;
		case 9:name = "��"; break;
		}

		switch (number_2)			//�������λ��
		{
		case 0:name = name + "ʮ"; break;
		case 1:name = name + "ʮһ"; break;
		case 2:name = name + "ʮ��"; break;
		case 3:name = name + "ʮ��"; break;
		case 4:name = name + "ʮ��"; break;
		case 5:name = name + "ʮ��"; break;
		case 6:name = name + "ʮ��"; break;
		case 7:name = name + "ʮ��"; break;
		case 8:name = name + "ʮ��"; break;
		case 9:name = name + "ʮ��"; break;
		}
	}
	name = "��" + name + "��";			//�������ƣ��ڼ��أ�
	//cout << name << endl;

	return name;			//���������ַ�����
}