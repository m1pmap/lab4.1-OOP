//Задание:
//Создать адаптер контейнера(queue).Заполнить его элементами пользовательского
//типа по вариантам(Time и float).Добавить элементы в соответствии с 
//заданием(разницу максимального и минимального в конец). Удалить элементы в 
//соответствии с заданием(Элементы меньшие среднего арифметического)


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

int main()
{
	Time midnight(0,3);
	Time deepNight(2, 17);
	Time night(4, 45);
	Time earlyMorning(7, 0);
	Time lateMorning(12, 34);
	Time dayTime(15, 15);
	Time afternoon(19, 57);
	Time lateAfternoon(21, 32);

	queue<Time> queueContainer;

	queueContainer.push(midnight);
	queueContainer.push(deepNight);
	queueContainer.push(night);
	queueContainer.push(earlyMorning);
	queueContainer.push(lateMorning);
	queueContainer.push(dayTime);
	queueContainer.push(afternoon);
	queueContainer.push(lateAfternoon);

	std::deque<Time> dq = queueContainer._Get_container();
	cout << "Queue with time-objects:" << endl;
	for (auto i = dq.begin(); i != dq.end(); ++i)
		(*i).PrintTime();

	Time maxTime;
	Time minTime(23, 59);

	for (auto i = dq.begin(); i != dq.end(); ++i)
	{
		if ((*i) > maxTime)
			maxTime = (*i);
		if (minTime > (*i))
			minTime = (*i);
	}

	cout << endl;

	queueContainer.push(maxTime - minTime);

	cout << "Adding:" << endl;
	dq = queueContainer._Get_container();
	for (auto i = dq.begin(); i != dq.end(); ++i)
		(*i).PrintTime();

	Time avg;
	for (auto i = dq.begin(); i != dq.end(); ++i)
		avg = avg + (*i);
	avg = avg / queueContainer.size();

	std::vector<Time> buff;

	while (!queueContainer.empty()) {
		Time value = queueContainer.front();
		buff.push_back(value);
		queueContainer.pop();
	}

	for (Time value : buff) {
		if (value > avg) {
			queueContainer.push(value);
		}
	}

	cout << "\nRemove:" << endl;
	dq = queueContainer._Get_container();
	for (auto i = dq.begin(); i != dq.end(); ++i)
		(*i).PrintTime();
}