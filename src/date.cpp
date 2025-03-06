#include "date.h"

Date::Date(int day, int month, int year)
    : mday(day)
    , mmonth(month)
    , myear(year)
{
}
[[nodiscard]] int Date::get_month_day() const { return mday; }
[[nodiscard]] int Date::get_month() const { return mmonth; }
[[nodiscard]] int Date::get_year() const { return myear; }
[[nodiscard]] int Date::get_year_day() const
{
    int sum {};
    for (int i = mmonth - 1; i > 0; --i)
        sum += month_table[isleap(myear) == true ? 1 : 0][i - 1];

    return sum + mday;
}
[[nodiscard]] Weekday Date::get_week_day() const
{
    return static_cast<Weekday>(sakamuto(mday, mmonth, myear));
}

Date& Date::set_month_day(int day)
{
    mday = day;
    return *this;
}
Date& Date::set_month(int month)
{
    mmonth = month;
    return *this;
}
Date& Date::set_year(int year)
{
    myear = year;
    return *this;
}
Date& Date::set_date(int day, int month, int year)
{
    mday = day;
    mmonth = month;
    myear = year;
    return *this;
}

[[nodiscard]] Date Date::random_date()
{
    int random_month = rand() % (12 - 1 + 1) + 1;
    int random_year = rand() % (2025 - 1940 + 1) + 1940;
    int random_day = rand() % (month_table[isleap(random_year) == true ? 1 : 0][random_month - 1] - 1 + 1) + 1;

    return { random_day, random_month, random_year };
}
[[nodiscard]] bool Date::isleap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}
[[nodiscard]] int Date::sakamuto(int d, int m, int y)
{
    if (m < 3)
        y -= 1;

    return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
}
Date Date::convertDaysToDate(int total_days)
{
    int year = 1900;
    int month = 0;
    int day = total_days;

    while (true) {
        int days_in_current_year = 0;
        for (int i = 0; i < 12; i++)
            days_in_current_year += ((isleap(year) == true) ? month_table[1][i] : month_table[0][i]);

        if (day <= days_in_current_year) {
            break;
        }

        day -= days_in_current_year;
        year++;
    }

    for (month = 0; month < 12; month++) {
        if (day <= ((isleap(year) == true) ? month_table[1][month] : month_table[0][month])) {
            break;
        }
        day -= ((isleap(year) == true) ? month_table[1][month] : month_table[0][month]);
    }

    return { day, month + 1, year };
}

Date Date::operator-(int day) const
{
    int sum { get_year_day() };
    for (int i = year_base; i < myear; ++i)
        sum += isleap(i) == true ? 366 : 365;

    if (day > sum)
        return { 1, 1, year_base };

    sum -= day;

    return convertDaysToDate(sum);
}

Date& Date::operator+=(int day)
{
    int sum { get_year_day() };
    for (int i = year_base; i < myear; ++i)
        sum += isleap(i) == true ? 366 : 365;

    sum += day;

    Date d { convertDaysToDate(sum) };
    mday = d.mday;
    mmonth = d.mmonth;
    myear = d.myear;

    return *this;
}

Date& Date::operator-=(int day)
{
    int sum { get_year_day() };
    for (int i = year_base; i < myear; ++i)
        sum += isleap(i) == true ? 366 : 365;

    if (day > sum)
        return *this;

    sum -= day;

    Date d { convertDaysToDate(sum) };
    mday = d.mday;
    mmonth = d.mmonth;
    myear = d.myear;

    return *this;
}

Date& Date::operator++()
{
    return (*this += 1);
}
Date Date::operator++(int)
{
    Date retval { *this };
    ++*this;
    return retval;
}
Date& Date::operator--()
{
    return (*this -= 1);
}
Date Date::operator--(int)
{
    Date retval { *this };
    --*this;
    return retval;
}

bool operator<(const Date& d1, const Date& d2)
{
    int sum1 { d1.get_year_day() };
    for (int i = year_base; i < d1.myear; ++i)
        sum1 += Date::isleap(i) == true ? 366 : 365;

    int sum2 { d2.get_year_day() };
    for (int i = year_base; i < d2.myear; ++i)
        sum2 += Date::isleap(i) == true ? 366 : 365;

    return sum1 < sum2;
}

bool operator==(const Date& d1, const Date& d2)
{
    int sum1 { d1.get_year_day() };
    for (int i = year_base; i < d1.myear; ++i)
        sum1 += Date::isleap(i) == true ? 366 : 365;

    int sum2 { d2.get_year_day() };
    for (int i = year_base; i < d2.myear; ++i)
        sum2 += Date::isleap(i) == true ? 366 : 365;

    return sum1 == sum2;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    return os << date.mday << " " << date.mmonth << " " << date.myear << "\n";
}
std::istream& operator>>(std::istream& is, Date& date)
{
    char delimiter;
    return is >> date.mday >> delimiter >> date.mmonth >> delimiter >> date.myear;
}
std::ostream& operator<<(std::ostream& os, Weekday wd)
{
    static const char* const pdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    return os << pdays[static_cast<int>(wd)] << "\n";
}

[[nodiscard]] bool operator>(const Date& d1, const Date& d2)
{
    return d2 < d1;
}

[[nodiscard]] bool operator>=(const Date& d1, const Date& d2)
{
    return !(d1 < d2);
}

[[nodiscard]] bool operator<=(const Date& d1, const Date& d2)
{
    return !(d1 > d2);
}

[[nodiscard]] bool operator!=(const Date& d1, const Date& d2)
{
    return !(d1 == d2);
}

[[nodiscard]] int operator-(const Date& d1, const Date& d2)
{
    int sum1 { d1.get_year_day() };
    for (int i = year_base; i < d1.get_year(); ++i)
        sum1 += Date::isleap(i) == true ? 366 : 365;

    int sum2 { d2.get_year_day() };
    for (int i = year_base; i < d2.get_year(); ++i)
        sum2 += Date::isleap(i) == true ? 366 : 365;

    return std::abs(sum2 - sum1);
}
[[nodiscard]] Date operator+(const Date& d, int day)
{
    int sum { d.get_year_day() };
    for (int i = year_base; i < d.get_year(); ++i)
        sum += Date::isleap(i) == true ? 366 : 365;

    sum += day;

    return Date::convertDaysToDate(sum);
}

[[nodiscard]] Date operator+(int day, const Date& d)
{
    int sum { d.get_year_day() };
    for (int i = year_base; i < d.get_year(); ++i)
        sum += Date::isleap(i) == true ? 366 : 365;

    sum += day;

    return Date::convertDaysToDate(sum);
}

Weekday& operator++(Weekday& wd)
{
    return wd = wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1);
}
Weekday operator++(Weekday& wd, int)
{
    Weekday retval(wd);
    ++wd;
    return retval;
}
Weekday& operator--(Weekday& wd)
{
    return wd = wd == Weekday::Sunday ? Weekday::Saturday : static_cast<Weekday>(static_cast<int>(wd) - 1);
}

Weekday operator--(Weekday& wd, int)
{
    Weekday retval(wd);
    --wd;
    return retval;
}