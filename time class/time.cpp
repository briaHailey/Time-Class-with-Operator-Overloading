/*
Bria Weisblat
Section: 2
 */

#include "time.h"
#include <iostream>

// Default constructor: initialize time to 0
Time::Time(){
    storedSeconds = 0;
    storedMinutes = 0;
    storedHours = 0;
    storedDays = 0;
}

// Constructor: take in seconds and convert to proper format
Time::Time(int seconds){
    // If the time is negative, default stored seconds to zero
    if (seconds < 0){
        storedSeconds = 0;
    }
    // Convert from seconds to proper format
    Time::Format(seconds);
}

// Constructor: intialize the object using four parameters
Time::Time(int days, int hours, int minutes, int seconds){
    // If any parameters are negative, set the whole time object to 0
    if ( (seconds < 0) || (minutes < 0) || (hours < 0) || (days<0)) {
        storedSeconds = 0;
        storedMinutes = 0;
        storedHours = 0;
        storedDays = 0;
    }
    // Convert the time to seconds
    long int time = seconds + minutes*60 + hours*3600 + days*86400;
    // Convert from seconds to proper format
    Time::Format(time);
}

void Time::Format(int seconds){
    storedSeconds = 0;
    storedMinutes = 0;
    storedHours = 0;
    storedDays = 0;

    // If seconds are negative convert the time to 0
    if (seconds < 0){
        storedSeconds = 0;
    }
    // If the seconds value is less than 59, store the number of seconds
    else if (seconds <= 59){
        storedSeconds = seconds + 0;
    }

    // If seconds can be converted to a whole number of minutes, store minutes and seconds
    else if ( (seconds >=60) && (seconds <= 3599) ){
        // Calculate and store whole number of minutes
        storedMinutes = seconds/60;
        // Calculate and store remaining seconds
        storedSeconds = seconds - (storedMinutes*60);
        // Not enough seconds for hours or days, set those to 0
    }
    else if ( (seconds >= 3600) && (seconds <= 86399) ){
        // Calculate and store whole number of hours
        storedHours = seconds/3600;
        // Calculate and store remaining minutes
        storedMinutes = ( (seconds - (storedHours * 3600)) /60 );
        // Calculate and store remaining seconds
        storedSeconds = seconds - (storedHours * 3600) - (storedMinutes*60);
    }
    else if (seconds >= 86400){
        storedDays = seconds/86400;
        storedHours = ( (seconds - (storedDays * 86400)) / 3600 );
        storedMinutes = ( (seconds - (storedDays * 86400) - (storedHours * 3600)) / 60 );
        storedSeconds = seconds - (storedDays * 86400) - (storedHours * 3600) - (storedMinutes*60);
    }
}

// Convert a time to seconds
void Time::ToSeconds(int seconds, int minutes, int hours, int days){
    storedSeconds = seconds + (minutes * 60) + (hours * 3600) + (days * 86400);
}

// Insertion operator overload (print object in correct format)
std::ostream &operator<<(std::ostream &print, const Time timeObject) {
    print << timeObject.storedDays << "~";
    if (timeObject.storedHours < 10){
        print << "0" << timeObject.storedHours;
    }
    else {
        print << timeObject.storedHours;
    }
    print << ':';
    if (timeObject.storedMinutes < 10){
        print << "0" << timeObject.storedMinutes;
    }
    else {
        print << timeObject.storedMinutes;
    }
    print << ':';
    if (timeObject.storedSeconds < 10){
        print << "0" << timeObject.storedSeconds;
    }
    else {
        print << timeObject.storedSeconds;
    }

    return print;
}
// Extraction operator overload
std::istream& operator>>(std::istream& is, Time& timeObject)
{
    char tilde, col1, col2;
    is >> timeObject.storedDays >> tilde >> timeObject.storedHours >> col1 >> timeObject.storedMinutes >> col2 >> timeObject.storedSeconds;
    long int totalSeconds = timeObject.storedDays * 86400 + timeObject.storedHours * 3600 + timeObject.storedMinutes * 60 + timeObject.storedSeconds;
    timeObject.Format(totalSeconds);
    return is;
}

Time operator+(const Time timeObject1, const Time timeObject2) {
    Time timeSum;
    // Convert both time objects to seconds and store them temporary variables
    long int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    long int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);
    // Add the number of seconds and store the value
    timeSum.storedSeconds = timeObjectTemp1 + timeObjectTemp2;
    // Convert back to proper time format
    timeSum.Format(timeSum.storedSeconds);

    return timeSum;
}

Time operator-(const Time timeObject1, const Time timeObject2) {
    Time timeDifference;
    // Convert both time objects to seconds and store them temporary variables
    int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);
    // Subtract the number of seconds of object two from the number of seconds of object one and store the value
    timeDifference.storedSeconds = timeObjectTemp1 - timeObjectTemp2;
    // Convert back to proper time format
    timeDifference.Format(timeDifference.storedSeconds);

    return timeDifference;
}

Time operator*(const Time timeObject, const int multiplier) {
    Time timeProduct;
    // Convert the time object to seconds and store it in a temporary variable
    int timeObjectTemp = timeObject.storedSeconds + (timeObject.storedMinutes * 60) + (timeObject.storedHours * 3600) + (timeObject.storedDays * 86400);
    // Multiply the number of seconds in the time object by the multiplier and store in a temporary variable
    timeProduct.storedSeconds = timeObjectTemp * multiplier;
    //Convert back to proper time format
    timeProduct.Format(timeProduct.storedSeconds);

    return timeProduct;
}

bool operator<(const Time timeObject1, const Time timeObject2){
    bool isLess;
    // Convert both time objects to seconds and store them temporary variables
    int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 < timeObjectTemp2){
        isLess = true;
    }
    else {
        isLess = false;
    }
    return isLess;
}

bool operator>(const Time timeObject1, const Time timeObject2 ){
    bool isGreater;

    // Convert both time objects to seconds and store them temporary variables
    long int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    long int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 > timeObjectTemp2){
        isGreater = true;
    }
    else {
        isGreater = false;
    }
    return isGreater;
}

bool operator<=(const Time timeObject1, const Time timeObject2){
    bool isLessOrEqual;

    // Convert both time objects to seconds and store them temporary variables
    unsigned int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    unsigned int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 <= timeObjectTemp2){
        isLessOrEqual = true;
    }
    else {
        isLessOrEqual = false;
    }
    return isLessOrEqual;
}

bool operator>=(const Time timeObject1, const Time timeObject2){
    bool isGreaterOrEqual;

    // Convert both time objects to seconds and store them temporary variables
    unsigned int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    unsigned int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 >= timeObjectTemp2){
        isGreaterOrEqual = true;
    }
    else {
        isGreaterOrEqual = false;
    }
    return isGreaterOrEqual;
}

bool operator==(const Time timeObject1, const Time timeObject2){
    bool isEqual;

    // Convert both time objects to seconds and store them temporary variables
    unsigned int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    unsigned int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 == timeObjectTemp2){
        isEqual = true;
    }
    else {
        isEqual = false;
    }
    return isEqual;
}

bool operator!=(const Time timeObject1, const Time timeObject2){
    bool isNotEqual;
    // Convert both time objects to seconds and store them temporary variables
    unsigned int timeObjectTemp1 = timeObject1.storedSeconds + (timeObject1.storedMinutes * 60) + (timeObject1.storedHours * 3600) + (timeObject1.storedDays * 86400);
    unsigned int timeObjectTemp2 = timeObject2.storedSeconds + (timeObject2.storedMinutes * 60) + (timeObject2.storedHours * 3600) + (timeObject2.storedDays * 86400);

    // Perform the comparison
    if (timeObjectTemp1 != timeObjectTemp2){
        isNotEqual = true;
    }
    else {
        isNotEqual = false;
    }
    return isNotEqual;
}

Time &Time::operator++() {
    storedSeconds = storedSeconds + (storedMinutes * 60) + (storedHours * 3600) + (storedDays * 86400) +1;
    Time::Format(storedSeconds);
    return *this;
}

Time Time::operator++(int)	// post-fix increment
{
    // Copy current object into a temporary variable
    Time temp = *this;
    // Increment by one and store the value
    storedSeconds = storedSeconds + (storedMinutes * 60) + (storedHours * 3600) + (storedDays * 86400) +1;
    Time::Format(storedSeconds);
    // Return the old value
    return temp;
}

Time &Time::operator--() {
    storedSeconds = storedSeconds + (storedMinutes * 60) + (storedHours * 3600) + (storedDays * 86400) -1;
    Time::Format(storedSeconds);
    return *this;
}

Time Time::operator--(int)	// post-fix increment
{
    // Copy current object into a temporary variable
    Time temp = *this;
    // Increment by one and store the value
    storedSeconds = storedSeconds + (storedMinutes * 60) + (storedHours * 3600) + (storedDays * 86400) -1;
    Time::Format(storedSeconds);
    // Return the old value
    return temp;
}
