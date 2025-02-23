//#include "pch.h"
#include "listTemp.h"
#include "company.h"
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
	Company cmp;
	cmp.inputSalary();

	long start_t, end_t;

	start_t = clock();
	cmp.findBestPaid();
	end_t = clock();
	cmp.printBestPaid();
	cout << "time cost: " << (double)(end_t - start_t) / CLOCKS_PER_SEC << " seconds" << endl;


	start_t = clock();
	cmp.findBestPaidReverse();
	end_t = clock();
	cmp.printBestPaid();
	cout << "time cost: " << (double)(end_t - start_t) / CLOCKS_PER_SEC << " seconds" << endl;


	return 0;
}