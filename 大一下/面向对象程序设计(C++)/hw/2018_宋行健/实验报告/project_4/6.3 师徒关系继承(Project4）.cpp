#include <iostream>
#include <vector>

using namespace std;

//����:����
class MenPai
{
private:
	string Men_Pai;			//������������
	vector <string> MenPai_Gongfu;		//���ɵĹ����кܶ��֣���һ����̬vectorȥ������
public:
	int num_MenPai_Gongfu;		//������������ʾ�����ɵĵڼ�������
	
	//Ĭ�Ϲ��캯������ʼ��������Ϊnull�����ɵĵ�һ���书Ϊnull
	MenPai()
	{
		Men_Pai = "NULL";
		MenPai_Gongfu.push_back( "NULL");
	}

	//������������
	void set_Men_Pai(string menpai)
	{
		Men_Pai = menpai;
	}

	//���������书��ÿ����һ�Σ�vector <string> MenPai_Gongfu����һ���ڴ�
	void set_MenPai_Gongfu(string Gongfu)
	{
		MenPai_Gongfu[num_MenPai_Gongfu] = Gongfu;		//��������ַ�������ǰһλ
		MenPai_Gongfu.push_back("");		//�����µ��ڴ�
		num_MenPai_Gongfu++;		//����������һ
	}

	//�������˽�б����Ķ˿�
	string get_Men_Pai()
	{
		return Men_Pai;
	}	
	string get_MenPai_Gongfu(int num_menpai)
	{
		return MenPai_Gongfu[num_menpai];
	}
};

//���ࣺʦ��
class ShiFu:public MenPai
{
private:
	string Name_ShiFu;			//����ʦ������
	vector <string> ShiFu_Gongfu;		//ʦ����Ĺ����кܶ��֣���һ����̬vectorȥ������
public:
	int num_shifu_gongfu = 0;		//������������ʾ���ʦ���ĵڼ�������

	//Ĭ�Ϲ��캯������ʼ��ʦ����Ϊnull��ʦ���ĵ�һ���书Ϊnull
	ShiFu()
	{
		Name_ShiFu = "NULL";
		ShiFu_Gongfu.push_back( "NULL");
	}

	//����ʦ������
	void set_Name_ShiFu(string nameshifu)
	{
		Name_ShiFu = nameshifu;
	}

	//����ʦ���书��ÿ����һ�Σ�vector <string> ShiFu_Gongfu����һ���ڴ�
	void set_ShiFu_Gongfu(string Gongfu)
	{
		ShiFu_Gongfu[num_shifu_gongfu] = Gongfu;		//��������ַ�������ǰһλ
		ShiFu_Gongfu.push_back("");		//�����µ��ڴ�
		num_shifu_gongfu++;		//����������һ
	}

	//�������˽�б����Ķ˿�
	string get_Name_ShiFu()
	{
		return Name_ShiFu;
	}
	string get_ShiFu_Gongfu(int num_shifu_gongfu)
	{
		return ShiFu_Gongfu[num_shifu_gongfu];
	}

	//չʾ�����ĸ�����
	void come_from()
	{
		cout << "���ɣ�" << get_Men_Pai() << endl;
	}

	//չʾӢ�ۻ���书
	void GongFu(int num_menpai_gongfu)
	{
		cout << "���ɵ��书��" << get_MenPai_Gongfu(num_menpai_gongfu) << endl;
		cout << "�Լ����书��";
		for (int j = 0; j < (int)ShiFu_Gongfu.size(); j++)
		{
			cout << get_ShiFu_Gongfu(j) << "   ";
		}
		cout << endl;
	}

	//չʾӢ����Ϣ�����ɡ��书��
	void show(int num_menpai_gongfu)
	{
		cout << "���֣�" << get_Name_ShiFu()<< endl;
		come_from();
		GongFu(num_menpai_gongfu);
		cout << endl;
	}
};

//���ࣺӢ��
class Hero : public ShiFu
{
private:
	string Name;			//����Ӣ������
	string Gongfu_self;		//�Լ��о��������书
public:
	//Ĭ�Ϲ��캯������ʼ��Ӣ����Ϊnull��Ӣ�۵��书Ϊnull
	Hero()
	{
		Name = "NULL";
		Gongfu_self = "NULL";
	}

	//����Ӣ������
	void set_Name_self(string nameself)
	{
		Name = nameself;
	}
	//����Ӣ���书
	void set_self_Gongfu(string Gongfu)
	{
		Gongfu_self = Gongfu;
	}

	//�������˽�б����Ķ˿�
	string get_Name_self()
	{
		return Name;
	}
	string get_self_Gongfu()
	{
		return Gongfu_self;
	}

	//չʾ�����ĸ����ɺ�ʦ��
	void come_from()
	{
		cout << "���ɣ�" << get_Men_Pai() << endl;
		cout << "ʦ����" << get_Name_ShiFu() << endl;
	}

	//չʾӢ�ۻ���书
	void GongFu(int num_shifu_gongfu,int num_menpai_gongfu)
	{
		cout << "���ɵ��书��" << get_MenPai_Gongfu(num_menpai_gongfu) << endl;
		cout << "ʦ�����书��" << get_ShiFu_Gongfu(num_shifu_gongfu) << endl;
		cout << "�Լ����书��" << get_self_Gongfu() << endl;
	}

	//չʾӢ����Ϣ�����ɡ�ʦ�����书��
	void show(int num_shifu_gongfu,int num_menpai_gongfu)
	{
		cout << "���֣�" << get_Name_self() << endl;
		come_from();
		GongFu(num_shifu_gongfu, num_menpai_gongfu);
		cout << endl;
	}
};


int main(void)
{
	MenPai DongXie;		//���ɣ���а
	MenPai XiDu;		//���ɣ�����
	MenPai NanDi;		//���ɣ��ϵ�
	MenPai BeiGai;		//���ɣ���ؤ

	ShiFu HongQiGong;		//ʦ�������߹�
	ShiFu HuangYaoShi;		//ʦ������ҩʦ
	ShiFu DuanZhiXing;		//ʦ����������
	ShiFu OuYangFeng;		//ʦ����ŷ����
	Hero GuoJing;		//Ӣ�ۣ�����
	Hero HuangRong;		//Ӣ�ۣ�����
	Hero YangGuo;		//Ӣ�ۣ����
	Hero MeiChaoFeng;	//Ӣ�ۣ�÷����
	Hero MuNianCi;		//Ӣ�ۣ������
	Hero YangKang;		//Ӣ�ۣ��
	Hero OuYangKe;		//Ӣ�ۣ�ŷ����

	//���ɣ���а
	DongXie.set_Men_Pai("��а");
	DongXie.set_MenPai_Gongfu("���һ����书");
	DongXie.set_MenPai_Gongfu("�ڱ̲��Ʒ�");

	//���ɣ�����
	XiDu.set_Men_Pai("����");
	XiDu.set_MenPai_Gongfu("��˲Ϣǧ��");
	XiDu.set_MenPai_Gongfu("������ѩɽ��");
	XiDu.set_MenPai_Gongfu("��͸�Ǵ�Ѩ��");

	//���ɣ��ϵ�
	NanDi.set_Men_Pai("�ϵ�");
	NanDi.set_MenPai_Gongfu("��һ��ָ");
	NanDi.set_MenPai_Gongfu("�����칦");
	
	//���ɣ���ؤ
	BeiGai.set_Men_Pai("��ؤ");
	BeiGai.set_MenPai_Gongfu("�ٴ򹷰���");
	BeiGai.set_MenPai_Gongfu("����ң��");

	//ʦ������ҩʦ
	HuangYaoShi.set_Name_ShiFu("��ҩʦ");
	HuangYaoShi.set_Men_Pai(DongXie.get_Men_Pai());
	HuangYaoShi.set_MenPai_Gongfu(DongXie.get_MenPai_Gongfu(1));
	HuangYaoShi.set_ShiFu_Gongfu("�ٵ�ָ��ͨ");
	HuangYaoShi.set_ShiFu_Gongfu("�����｣��");
	HuangYaoShi.set_ShiFu_Gongfu("��������Ѩ��");
	HuangYaoShi.set_ShiFu_Gongfu("����Ӣ����");
	HuangYaoShi.show(0);

	//ʦ����ŷ����
	OuYangFeng.set_Name_ShiFu("ŷ����");
	OuYangFeng.set_Men_Pai(XiDu.get_Men_Pai());
	OuYangFeng.set_MenPai_Gongfu(XiDu.get_MenPai_Gongfu(0));
	OuYangFeng.set_ShiFu_Gongfu("������ȭ��");
	OuYangFeng.set_ShiFu_Gongfu("�������ȷ�");
	OuYangFeng.set_ShiFu_Gongfu("�۾�������");
	OuYangFeng.show(0);

	//ʦ����������
	DuanZhiXing.set_Name_ShiFu("������");
	DuanZhiXing.set_Men_Pai(NanDi.get_Men_Pai());
	DuanZhiXing.set_MenPai_Gongfu(NanDi.get_MenPai_Gongfu(0));
	DuanZhiXing.set_ShiFu_Gongfu("�پ����澭");
	DuanZhiXing.set_ShiFu_Gongfu("�����칦");
	DuanZhiXing.set_ShiFu_Gongfu("��һ��ָ");
	DuanZhiXing.show(0);

	//ʦ�������߹�
	HongQiGong.set_Name_ShiFu("���߹�");
	HongQiGong.set_Men_Pai(BeiGai.get_Men_Pai());
	HongQiGong.set_MenPai_Gongfu(BeiGai.get_MenPai_Gongfu(0));
	HongQiGong.set_ShiFu_Gongfu("�ٽ���ʮ����");
	HongQiGong.set_ShiFu_Gongfu("�ڴ򹷰���");
	HongQiGong.set_ShiFu_Gongfu("�۾����澭");
	HongQiGong.show(0);
	
	//Ӣ�ۣ�����
	GuoJing.set_Name_self("����");
	GuoJing.set_Name_ShiFu(HongQiGong.get_Name_ShiFu());
	GuoJing.set_ShiFu_Gongfu(HongQiGong.get_ShiFu_Gongfu(0));
	GuoJing.set_self_Gongfu("���һ���");
	GuoJing.show(0, 0);

	//Ӣ�ۣ�����
	HuangRong.set_Name_self("����");
	HuangRong.set_Men_Pai(DongXie.get_Men_Pai());
	HuangRong.set_MenPai_Gongfu(DongXie.get_MenPai_Gongfu(0));
	HuangRong.set_Name_ShiFu(HongQiGong.get_Name_ShiFu());
	HuangRong.set_ShiFu_Gongfu(HongQiGong.get_ShiFu_Gongfu(1));
	HuangRong.set_self_Gongfu("���｣��");
	HuangRong.show(0, 0);

	//Ӣ�ۣ����
	YangGuo.set_Name_self("���");
	YangGuo.set_Name_ShiFu(HongQiGong.get_Name_ShiFu());
	YangGuo.set_ShiFu_Gongfu(HongQiGong.get_ShiFu_Gongfu(1));
	YangGuo.set_self_Gongfu("��Ȼ������");
	YangGuo.show(0, 0);

	//Ӣ�ۣ�÷����
	MeiChaoFeng.set_Name_self("÷����");
	MeiChaoFeng.set_Men_Pai(DongXie.get_Men_Pai());
	MeiChaoFeng.set_MenPai_Gongfu(DongXie.get_MenPai_Gongfu(1));
	MeiChaoFeng.set_Name_ShiFu(HuangYaoShi.get_Name_ShiFu());
	MeiChaoFeng.set_ShiFu_Gongfu(HuangYaoShi.get_ShiFu_Gongfu(1));
	MeiChaoFeng.set_self_Gongfu("�����׹�צ");
	MeiChaoFeng.show(0, 0);

	//Ӣ�ۣ������
	MuNianCi.set_Name_self("�����");
	MuNianCi.set_Name_ShiFu(HongQiGong.get_Name_ShiFu());
	MuNianCi.set_self_Gongfu("���ǹ��");
	MuNianCi.show(0, 0);

	//Ӣ�ۣ��
	YangKang.set_Name_self("�");
	YangKang.set_Name_ShiFu(OuYangFeng.get_Name_ShiFu());
	YangKang.set_ShiFu_Gongfu(OuYangFeng.get_ShiFu_Gongfu(1));
	YangKang.set_self_Gongfu("ȫ�潣��");
	YangKang.show(0, 0);

	//Ӣ�ۣ�ŷ����
	OuYangKe.set_Name_self("ŷ����");
	OuYangKe.set_Name_ShiFu(OuYangFeng.get_Name_ShiFu());
	OuYangKe.set_ShiFu_Gongfu(OuYangFeng.get_ShiFu_Gongfu(0));
	OuYangKe.set_self_Gongfu("����ѩɽ��");
	OuYangKe.show(0, 0);

	return 0;
}