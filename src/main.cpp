#include <iostream>
#include "date.h"

int main()
{
	Date d1{};
	Date d2{31, 12, 1999};
	Date d3{};
	Date d4{ 10, 12, 1997 };
	Date d5{ 10, 12, 1996 };
	Date::Weekday wd{ Date::Weekday::Tuesday };


	std::cout << d1;
	std::cout << d2;
	std::cout << d2.get_year_day() << std::endl;
	std::cout << d2.get_week_day() << std::endl;

	std::cout << d2 - 4;
	std::cout << d2 - 39;

	std::cout << (d2 += 365);
	std::cout << (d2 -= 365);
	std::cout << ++d2;
	std::cout << --d2;
	std::cout << d2--;
	std::cout << d2++;
	std::cout << d2;

	std::cout << std::boolalpha << (d4 >= d5) << "\n";
	std::cout << d5 - d4 << "\n";
	std::cout << d5 + 20;
	std::cout << 100 + d5;

	std::cout << wd;
	std::cout << wd++;
	std::cout << wd;
	std::cout << ++wd;

	std::cout << wd;
	std::cout << wd--;
	std::cout << wd;
	std::cout << --wd;

	std::cout << Date::random_date();
	std::cout << Date::random_date();
	std::cout << Date::random_date();
	std::cout << Date::random_date();
	std::cout << Date::random_date();

	std::cout << "Bir tarih giriniz...\n";
	std::cin >> d3;
	std::cout << d3;
}
