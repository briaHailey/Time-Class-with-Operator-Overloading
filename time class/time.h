/*
Bria Weisblat
Section: 2
 */

#include <iostream>

class Time {

    // Insertion operator overload
    friend std::ostream& operator<<(std::ostream& print, const Time timeObject);

    //Extraction operator overload
    friend std::istream& operator>>(std::istream& , Time&);

    //Addition operator overload
    friend Time operator+(const Time timeObject1, const Time timeObject2);
    //Subtraction operator overload
    friend Time operator-(const Time timeObject1, const Time timeObject2);
    // Multiplication operator overload
    friend Time operator*(const Time timeObject, const int multiplier);

    // < operator overload
    friend bool operator<(const Time timeObject1, const Time timeObject2);
    // > operator overload
    friend bool operator>(const Time timeObject1, const Time timeObject2);
    // <= operator overload
    friend bool operator<=(const Time timeObject1, const Time timeObject2);
    // >= operator overload
    friend bool operator>=(const Time timeObject1, const Time timeObject2);
    // == operator overload
    friend bool operator==(const Time timeObject1, const Time timeObject2);
    // != operator overload
    friend bool operator!=(const Time timeObject1, const Time timeObject2);


    public:

        // Default Constructor
        Time();
        // Conversion Constructor
        Time(int seconds);
        // Constructor to individually take in seconds, minutes, hours, and days
        Time(int days, int hours, int minutes, int seconds);

        // ++ pre-increment operator overload
        Time& operator++();
        // post-increment ++ operator overload
        Time operator++(int);
        // -- pre-decrement operator overload
        Time& operator--();
        // post-decrement-- operator overload
        Time operator--(int);

    private:
        int storedSeconds;
        int storedMinutes;
        int storedHours;
        int storedDays;

        void Format(int seconds);
        void ToSeconds(int seconds, int minutes, int hours, int days);

};

