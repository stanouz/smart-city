enum WeekDay{monday, tuesday, wednesday, thursday, friday, saturday, sunday};

class Date{
public:
    Date();
    ~Date();
    bool isBetween(Date date1, Date date2);
    void setDate(int day_, int month_, int year_);
    void setTime(int hour_, int minute_);

    bool operator<=(Date &d2);
    bool operator>=(Date &d2);

private:
    int day, month, year;
    int hour, minute;
    WeekDay weedDay;
};
