#ifndef WASH_H
#define WASH_H

#include <queue>
#include "car.h"

class WashCmp
{
private:
	std::queue<Car> carQueue;
	const static int CAPACITY;	//���г���
	const static double LAMTA;	//���ڳ����������ʱ��Ĳ���
	

	int numServedCars;
	int totalWaitingTime;

	double getNextArrival(double* TIME); //accept user input to get the next arrival time
	void processArrivalNonEmptyQ(double currTime); //a car arrives and the waiting queue is not empty
	void processArrivalEmptyQ(double currTime); //a car arrives and the waiting queue is empty
	void processDeparture();
	void processRemain(); //no more arriving cars, process the remaining cars in the waiting queue

public:
	WashCmp();
	void simulation();
	void printCmpStatistic();
};


#endif