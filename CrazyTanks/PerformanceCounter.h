#ifndef PERFORMANCE_COUNTER_H
#define PERFORMANCE_COUNTER_H
/*======================== Performance Counter ==================*/
#include <Windows.h>
#include <iostream>

class Counter
{
public:
	void start();
	double getTime();

private:
	double PCFreq_ = 0.0;
	__int64 counterStart_ = 0;
};

void Counter::start()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq_ = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	counterStart_ = li.QuadPart;
}

double Counter::getTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - counterStart_) / PCFreq_;
}

#endif