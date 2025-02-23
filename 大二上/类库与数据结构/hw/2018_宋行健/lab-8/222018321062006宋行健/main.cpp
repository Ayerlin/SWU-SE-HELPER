//#include "pch.h"
#include <iostream>
#include <fstream>
#include "bst.h"   // Defines BinarySearchTree class
#include <time.h>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

int main()
{
	ofstream out;			//写入文件流；
	out.open("E:\\类库与数据结构\\实验报告\\lab-8\\data.txt");
	double Num = 200;	//每个节点的模拟量
	int nodeNum = 800;	//节点个数模拟量
//	double theoryHeight = log(nodeNum)/log(2);
	
	int MAX = 10000;	//随机最大值
	srand((unsigned)time(0));

	//遍历有1个节点到有800个节点的情况
	for (int k = 1; k <= nodeNum; k++) {
		double averageHeight = 0;
		//每种节点情况随机生成200个模拟量，求出该节点的平均树高
		for (int j = 1; j <= Num; j++) {
			BinSearchTree<int> mybst;
			int item;
//			cout << "The inserted numbers: ";
			for (int i = 0; i < k; i++) {
				item = rand() % MAX;
				//cout << item << " ";
				mybst.insert(item);
			}
//			cout << "\tThe height: " << mybst.height() << endl;
			averageHeight += mybst.height();	//平均树高	
			//	cout << "The tree: \n";
			//	mybst.printTree();
		}
		cout << k << "\t" << averageHeight / Num << endl;
		//将平均树高写入文件，便于后期分析
		out << k<<"\t"<<averageHeight / Num << endl;
	}
//	cout << "\n\nTheoryHeight: " << theoryHeight << endl;
//	cout << "SimulateHeight: " << averageHeight / Num << endl;
	out.close();

	cout << "FINISH!!" << endl;

//	cout << endl << "The height: " << mybst.height() << endl;

} // binsearchtreeexample