#include <vk_api/api.h>

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

void getStatusString(std::stringstream& stringStream);

int main(int argc, char* argv[])
{
	std::string accessToken;
	
	if (argc == 2)
	{
		accessToken = argv[1];
	}
	else
	{
		std::cout << "Enter access token: ";
		std::cin >> accessToken;
	}

	system("cls");
	setlocale(0, "");

	VKApi api = VKApi(accessToken, "5.131", "ru");

	MethodData setStatusMethod;

	setStatusMethod.SetName("status.set");
	setStatusMethod.AddArgument("text", "");

	while (true)
	{
		std::stringstream stringStream;

		getStatusString(stringStream);

		setStatusMethod.GetArgument("text") = stringStream.str();

		api.CallMethod(setStatusMethod);

		std::this_thread::sleep_for(std::chrono::minutes(1));
	}

	return 0;
}

void getStatusString(std::stringstream& stringStream)
{
	time_t currentTime;
	tm newYear = { 0 };
	
	
	time(&currentTime);
	newYear = localtime(&currentTime);
	
	newYear.tm_year += 1;
	newYear.tm_mon = 11;
	newYear.tm_mday = 31;
	newYear.tm_hour = 23;
	newYear.tm_min = 59;
	newYear.tm_sec = 59;

	const double secondsUntilNewYear = std::abs(difftime(mktime(&newYear), currentTime));

	const int daysUntilNewYear = std::floor(secondsUntilNewYear / (60 * 60 * 24));
	int minutesUntilNewYear = std::floor(secondsUntilNewYear / 60);
	int hoursUntilNewYear = std::floor(secondsUntilNewYear / (60 * 60));

	minutesUntilNewYear -= hoursUntilNewYear * 60;
	hoursUntilNewYear -= daysUntilNewYear * 24;

	stringStream << (const char*)u8"%F0%9F%8E%85 До нового года";

	const int daysDividedByTen = daysUntilNewYear % 10;

	if (daysUntilNewYear != 11 && daysDividedByTen == 1)
	{
		stringStream << (const char*)u8" остался ";
	}
	else
	{
		stringStream << (const char*)u8" осталось ";
	}

	stringStream << daysUntilNewYear;

	if (daysUntilNewYear > 4 && daysUntilNewYear < 21 || daysUntilNewYear > 24 && daysUntilNewYear < 31)
	{
		stringStream << (const char*)u8" дней ";
	}
	else if (daysDividedByTen == 1)
	{
		stringStream << (const char*)u8" день ";
	}
	else
	{
		stringStream << (const char*)u8" дня ";
	}

	const int hoursDividedByTen = hoursUntilNewYear % 10;

	stringStream << hoursUntilNewYear;

	if (hoursDividedByTen == 1 && hoursUntilNewYear != 11)
	{
		stringStream << (const char*)u8" час ";
	}
	else if (hoursUntilNewYear > 4 && hoursUntilNewYear < 21)
	{
		stringStream << (const char*)u8" часов ";
	}
	else
	{
		stringStream << (const char*)u8" часа ";
	}

	stringStream << minutesUntilNewYear << (const char*)u8" минут";

	const int minutesDividedByTen = minutesUntilNewYear % 10;
	const int minutesDividedByHundred = minutesUntilNewYear % 10;

	if (minutesUntilNewYear < 10 || minutesUntilNewYear > 20)
	{
		if (minutesDividedByTen == 1)
			stringStream << (const char*)u8"у";
		else if (minutesDividedByTen > 1 && minutesDividedByTen < 5)
			stringStream << (const char*)u8"а";
	}
}