#include <iostream>
#include <Queue>
#include <list>

using namespace std;

class Time
{
private:
	int hours;
	int minutes;
public:
	Time()
	{
		this->hours = 0;
		this->minutes = 0;
	}
	Time(int hours, int minutes)
	{
		if (hours >= 24 || minutes >= 60)
			throw std::invalid_argument("Число не может быть больше 60");

		this->hours = hours;
		this->minutes = minutes;
	}
	void PrintTime()
	{
		if (this->hours < 10)
			cout << "0";
		cout << this->hours << ":";
		if (this->minutes < 10)
			cout << "0";
		cout << this->minutes << endl;
	}
	Time operator +(Time value)
	{
		int buffHours = this->hours;
		buffHours += value.hours;
		if (buffHours >= 24)
			buffHours = buffHours - 24;

		int buffMinutes = this->minutes;
		buffMinutes += value.minutes;
		if (buffMinutes >= 60)
		{
			buffMinutes = buffMinutes - 60;
			buffHours++;
		}

		Time buffTime(buffHours, buffMinutes);

		return buffTime;
	}
	Time operator -(Time value)
	{
		int buffHours = this->hours;
		buffHours -= value.hours;
		if (buffHours < 0)
			buffHours = 24 + buffHours;

		int buffMinutes = this->minutes;
		buffMinutes -= value.minutes;
		if (buffMinutes <= 0)
		{
			buffMinutes = 60 + buffMinutes;
			buffHours--;
		}

		Time buffTime(buffHours, buffMinutes);

		return buffTime;
	}

	bool operator > (Time value)
	{
		if (this->hours > value.hours)
			return true;
		else
			if (this->hours < value.hours)
				return false;
			else
				if (this->minutes > value.minutes)
					return true;
				else
					return false;
	}

	Time operator /(int value)
	{
		int buffHours = this->hours;
		buffHours /= value;
		int buffMinutes = this->minutes;
		buffMinutes /= value;

		return Time(buffHours, buffMinutes);
	}
};


void PrintDeque(queue<Time> queueContainer)
{
	std::deque<Time> dq = queueContainer._Get_container();
	for (auto i = dq.begin(); i != dq.end(); ++i)
		(*i).PrintTime();
}

void PrintDeque(queue<float> queueContainer)
{
	std::deque<float> dq = queueContainer._Get_container();
	for (auto i = dq.begin(); i != dq.end(); ++i)
		cout << (*i) << endl;
}


int main()
{
	Time midnight(0, 3);
	Time deepNight(2, 17);
	Time night(4, 45);
	Time earlyMorning(7, 0);
	Time lateMorning(12, 34);
	Time dayTime(15, 15);
	Time afternoon(19, 57);
	Time lateAfternoon(21, 32);

	queue<Time> queueTimeContainer;

	queueTimeContainer.push(midnight);
	queueTimeContainer.push(deepNight);
	queueTimeContainer.push(night);
	queueTimeContainer.push(earlyMorning);
	queueTimeContainer.push(lateMorning);
	queueTimeContainer.push(dayTime);
	queueTimeContainer.push(afternoon);
	queueTimeContainer.push(lateAfternoon);

	cout << "Queue with time-objects:" << endl;
	PrintDeque(queueTimeContainer);

	Time maxTime;
	Time minTime(23, 59);

	std::deque<Time> dq = queueTimeContainer._Get_container();
	for (auto i = dq.begin(); i != dq.end(); ++i)
	{
		if ((*i) > maxTime)
			maxTime = (*i);
		if (minTime > (*i))
			minTime = (*i);
	}

	cout << endl;

	queueTimeContainer.push(maxTime - minTime);

	cout << "Adding:" << endl;
	PrintDeque(queueTimeContainer);

	Time avg;
	for (auto i = dq.begin(); i != dq.end(); ++i)
		avg = avg + (*i);
	avg = avg / queueTimeContainer.size();

	vector<Time> buff;

	while (!queueTimeContainer.empty()) {
		Time value = queueTimeContainer.front();
		buff.push_back(value);
		queueTimeContainer.pop();
	}

	for (Time value : buff)
		if (value > avg)
			queueTimeContainer.push(value);

	cout << "\nRemove:" << endl;
	PrintDeque(queueTimeContainer);

	queue<float> floatQueue;

	floatQueue.push(2.1);
	floatQueue.push(4.0);
	floatQueue.push(0.7);
	floatQueue.push(5.3);

	float min = 100;
	float max = 0;

	cout << "\nQueue with float:" << endl;
	PrintDeque(floatQueue);

	std::deque<float> floatDq = floatQueue._Get_container();
	for (auto i = floatDq.begin(); i != floatDq.end(); ++i)
	{
		if ((*i) > max)
			max = (*i);
		if (min > (*i))
			min = (*i);
	}

	floatQueue.push(max - min);

	cout << "\nAdding:" << endl;
	PrintDeque(floatQueue);

	floatDq = floatQueue._Get_container();

	float avgFloat = 0;
	for (auto i = floatDq.begin(); i != floatDq.end(); ++i)
		avgFloat = avgFloat + (*i);
	avgFloat = avgFloat / floatQueue.size();
	
	vector<float> buffFloat;

	while (!floatQueue.empty()) {
		float value = floatQueue.front();
		buffFloat.push_back(value);
		floatQueue.pop();
	}

	for (float value : buffFloat)
		if (value > avgFloat)
			floatQueue.push(value);

	cout << "\nRemove:" << endl;
	PrintDeque(floatQueue);
}