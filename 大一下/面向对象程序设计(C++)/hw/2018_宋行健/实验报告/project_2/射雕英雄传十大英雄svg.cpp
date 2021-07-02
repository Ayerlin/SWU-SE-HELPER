#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ifstream in;			//�����ļ�����
	ofstream out;			//д���ļ�����
	string name_temp;		//��ѭ��ʱ��ʱ��Ӣ�����ƣ�
	string line;			//�����ļ�����ÿ�ζ�һ�У����������
	//��ÿ��Ӣ��������һ��vector���棻
	vector<string> HeroName = { "����","����","�","�����","��Х��","��Ƽ","������","��ϧ��","��ҩʦ","�����","���","������","��ϣ��","�Ű���","ȫ��","��СӨ" ,"ŷ����","����","̷����","������","�𴦻�","����һ","�´�ͨ","�ﲻ��","������","�ܲ�ͨ","��־ƽ","������","������","÷����","½�˷�","��Ĭ��","½��Ӣ","ŷ����","һ�ƴ�ʦ","���߹�","������","��ǧ��","��ǧ��","��կ��","���պ���","���պ���","�","������","������","��������","ɳͨ��","��ͨ��","�����","������" };
	vector<int> Hero_number(HeroName.size(), 0);			//��������������СͬӢ�����֣���ʼֵ��Ϊ0��

	cout << "���Ӣ�۴�ʮ��Ӣ�ۣ�" << endl;
	in.open("E:\\C++\\���Ӣ�۴�.txt");			//��Ҫ������ļ���

	if (!in)
		cout << "Open failed(in)" << endl;			//����ԭ�ļ��Ƿ�򿪳ɹ���
	else
	{
		while (getline(in, line))			//��in���ж��������ݣ��򽫶�������ݴ���line��
		{
			for (int i = 0; i < HeroName.size(); i++)
			{
				name_temp = HeroName[i];		//��ʱ��Ҫ�ҵ�Ӣ�����֣�
				if (!line.find(name_temp))			//���line�к���Ӣ�����ƹؼ��ּ�������+1��
				{
					Hero_number[i] += 1;
				}
			}
		}
	}
	in.close();		//�ر��ļ���

	//ð�������ų�ǰʮλ��
	int number_temp;
	for (int i = 0; i < HeroName.size() - 1; i++)
	{
		for (int j = 0; j < HeroName.size() - 1 - i; j++)
		{
			if (Hero_number[j] < Hero_number[j + 1])
			{
				//�Գ��ִ�������ð������
				number_temp = Hero_number[j];
				Hero_number[j] = Hero_number[j + 1];
				Hero_number[j + 1] = number_temp;

				//ͬʱ�����Ӧ��Ӣ�����ֽ���λ�ý�����
				name_temp = HeroName[j];
				HeroName[j] = HeroName[j + 1];
				HeroName[j + 1] = name_temp;
			}
		}
	}

	//���ǰʮ��Ӣ�ۣ�
	for (int i = 0; i < 10; i++)
	{
		cout << "TOP " << i + 1 << " :" << HeroName[i] << "\t" << Hero_number[i] << "��" << endl;
	}

	ofstream svg;
	float height[10];
	svg.open("E:\\C++\\���Ӣ�۴�svg.svg");			//����һ��svg�ļ�
	svg << "<?xml version=\"1.0\" encoding=\"GB2312\"?> " << endl;		//����ΪGB2312������ʾ������
	svg << "<svg width=\"800\" height=\"850\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;

	for (int i = 0; i < 10; i++)
	{
		height[i] = 0.5 * Hero_number[i];		//�����ִ���ת��Ϊ�߶�
	}

	for (int i = 0; i < 10; i++)		//���߶ȱ�ʾΪ���εĳ���
	{
		svg << "<rect x=\"" << (i + 1) * 70 << "\" y=\"" << 800 - (height[i]) << "\" width = \"50\" height = \"" << height[i] << "\" style =\"fill:blue;\"/> " << endl;
		svg << "<text font-size=\"20\" x=\"" << (i + 1) * 70 + 5 << "\" y=\"" << 780 - (height[i]) << "\">" << Hero_number[i] << "</text>" << endl;
	}

	//��������
	svg << "<line x1 = \"30\" y1 = \"800\" x2 = \"800\" y2 = \"800\" style=\"stroke:black; stroke - width:10\"/>" << endl;		//X��
	svg << "<line x1 = \"30\" y1 = \"800\" x2 = \"30\" y2 = \"80\" style=\"stroke:black; stroke - width:10\"/>" << endl;		//Y��
	//X���ͷ
	svg << "<line x1 = \"800\" y1 = \"800\" x2 = \"780\" y2 = \"780\" style=\"stroke:black; stroke - width:10\"/>" << endl;
	svg << "<line x1 = \"800\" y1 = \"800\" x2 = \"780\" y2 = \"820\" style=\"stroke:black; stroke - width:10\"/>" << endl;
	//Y���ͷ
	svg << "<line x1 = \"50\" y1 = \"100\" x2 = \"30\" y2 = \"80\" style=\"stroke:black; stroke - width:10\"/>" << endl;
	svg << "<line x1 = \"10\" y1 = \"100\" x2 = \"30\" y2 = \"80\" style=\"stroke:black; stroke - width:10\"/>" << endl;

	for (int i = 0; i < 10; i++)		//��ע����������
	{
		svg << "<text style=\"cursor: move; pointer-events: inherit;\" font-size=\"20px\" font-family=\"SimSun\"  x=\"" << (i + 1) * 70 << "\" y=\"820\">" << HeroName[i] << "</text>" << endl;
	}

	svg << "</svg>" << endl;
	svg.close();

	return 0;
}