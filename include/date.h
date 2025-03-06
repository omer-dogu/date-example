#pragma once

#include <cstdlib>
#include <ctime>
#include <iosfwd>
#include <iostream>

namespace {
static constexpr int year_base = 1900;
static constexpr int random_min_year = 1940;
static constexpr int random_max_year = 2025;
static constexpr int t[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
static constexpr int month_table[2][12] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};
}
enum class Weekday { Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday };

class Date {
public:
    Date() = default;
    Date(int day, int month, int year);
    // explicit Date(const char*);
    // explicit Date(time_t);

    [[nodiscard]] int get_month_day() const;
    [[nodiscard]] int get_month() const;
    [[nodiscard]] int get_year() const;
    [[nodiscard]] int get_year_day() const;
    [[nodiscard]] Weekday get_week_day() const;

    Date& set_month_day(int day);
    Date& set_month(int month);
    Date& set_year(int year);
    Date& set_date(int day, int month, int year);

    [[nodiscard]] static Date random_date();
    [[nodiscard]] static bool isleap(int year);
    [[nodiscard]] static int sakamuto(int, int m, int y);
    static Date convertDaysToDate(int total_days);

    Date operator-(int day) const;
    Date& operator+=(int day);
    Date& operator-=(int day);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    friend bool operator<(const Date& d1, const Date& d2);
    friend bool operator==(const Date& d1, const Date& d2);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

private:
    int mday { 1 };
    int mmonth { 1 };
    int myear { year_base };
};

[[nodiscard]] bool operator>(const Date& d1, const Date& d2);
[[nodiscard]] bool operator>=(const Date& d1, const Date& d2);
[[nodiscard]] bool operator<=(const Date& d1, const Date& d2);
[[nodiscard]] bool operator!=(const Date& d1, const Date& d2);
[[nodiscard]] int operator-(const Date& d1, const Date& d2);
[[nodiscard]] Date operator+(const Date& d, int day);
[[nodiscard]] Date operator+(int day, const Date& d);
Weekday& operator++(Weekday& wd);
Weekday operator++(Weekday& wd, int);
Weekday& operator--(Weekday& wd);
Weekday operator--(Weekday& wd, int);
std::ostream& operator<<(std::ostream& os, Weekday wd);