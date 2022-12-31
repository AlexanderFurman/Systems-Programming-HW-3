//
// Created by Omer Meushar on 26/12/2022.
//

#ifndef HW3_CLION_HEALTHPOINTS_H
#define HW3_CLION_HEALTHPOINTS_H

#include <iostream>

//typedef int Points;

const int DEFAULT_MAX_HP = 100;

class HealthPoints
{
public:
    /** constructors and destructors **/
    HealthPoints(int MaxHP = DEFAULT_MAX_HP); ///explicit or not?
    HealthPoints(const HealthPoints&) = default;
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints& copiedHP) = default;

    /**  operator methods  **/
    /// arithmetic:
    HealthPoints& operator+=(int addedHP);
    HealthPoints& operator-=(int subbedHP);

    ///conversion operator
    explicit operator int() const;

    ///output operator << ( using getHP() )
    friend std::ostream& operator<<(std::ostream& outStream, const HealthPoints& printedHP);


    /** exceptions **/
    class InvalidArgument{};



private:
    /**  private members  **/
    int m_HP;
    int m_MaxHP;

};


///operators implemented by +=, -= ( and -() )
HealthPoints operator+(const HealthPoints& HP, int addedHP);
HealthPoints operator+(int addedHP, const HealthPoints& HP);
HealthPoints operator-(const HealthPoints& HP, int subbedHP);
//HealthPoints operator-(int subbedHP, const HealthPoints& HP); //irrelevant

///basic boolean operators (using getHP instead of friends):
bool operator<(const HealthPoints& HPLeft, HealthPoints& HPRight);
bool operator==(const HealthPoints& HPLeft, HealthPoints& HPRight);

///boolean operators implemented by ==, <
bool operator!=(const HealthPoints& HPLeft, HealthPoints& HPRight);
bool operator<=(const HealthPoints& HPLeft, HealthPoints& HPRight);
bool operator>(const HealthPoints& HPLeft, HealthPoints& HPRight);
bool operator>=(const HealthPoints& HPLeft, HealthPoints& HPRight);


#endif //HW3_CLION_HEALTHPOINTS_H
