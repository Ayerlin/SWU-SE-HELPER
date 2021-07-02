#ifndef CAR_H
#define CAR_H

class Car
{
private:
	double arrivalTime;	//����ʱ��
	double departureTime;	//�뿪ʱ��
	double waitingTime;	//�ȴ�ʱ��
	double  serviceTime;	//����ʱ��
	//const static int SERVICE_T;	//����ʱ��


public:
	Car();
	Car(double arrivalT);
	const static double MIU;	//���ڷ���ʱ��Ĳ�����

	double getArrivalTime();
	double getDepartureTime();
	double getWaitingTime();
	double getserviceTime();

	void setDepartAndWaitTime(double currTime);
	void printCarDeparture();
	void printCarArrival();
};


#endif
