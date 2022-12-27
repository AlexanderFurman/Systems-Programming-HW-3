//
// Created by Omer Meushar on 26/12/2022.
//

#include "HealthPoints.h"
#include <iostream>

HealthPoints::HealthPoints(int maxHP)
{
    if(maxHP<=0) {
        throw HealthPoints::InvalidArgument();
    }
    m_HP = maxHP;
    m_MaxHP = maxHP;
}

int HealthPoints::getHP() const
{
    return m_HP;
}

int HealthPoints::getMaxHP() const
{
    return m_MaxHP;
}

HealthPoints::operator int() const
{
    return int(m_HP);
}

HealthPoints& HealthPoints::operator+=(int addedHP)
{
    if (m_HP+addedHP>=m_MaxHP) {
        m_HP = m_MaxHP;
    }
    else if(m_HP+addedHP<=0) {
        m_HP=0;
    }
    else {
        m_HP += addedHP;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(int subbedHP)
{
    return *this += -subbedHP;
}

HealthPoints operator+(const HealthPoints& HP, int addedHP)
{
    HealthPoints result = HP ;
    return result+=addedHP;
}

HealthPoints operator+(int addedHP, const HealthPoints& HP)
{
    return HP+addedHP;
}

HealthPoints operator-(const HealthPoints& HP, int subbedHP)
{
    HealthPoints result = HP ;
    return result-=subbedHP;
}

//irrelevant
//HealthPoints operator-(int subbedHP, const HealthPoints& HP)
//{
//    return HP-subbedHP;
//}

bool operator==(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return int(HPLeft) == int(HPRight);
}

bool operator!=(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return !(HPLeft == HPRight);
}

bool operator<(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return int(HPLeft) < int(HPRight);
}

bool operator>=(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return !(HPLeft < HPRight);
}


bool operator<=(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return (HPLeft == HPRight) ||  (HPLeft < HPRight);
}

bool operator>(const HealthPoints& HPLeft, HealthPoints& HPRight)
{
    return !(HPLeft <= HPRight);
}

std::ostream& operator<<(std::ostream& outStream, const HealthPoints& printedHP)
{
    outStream << printedHP.getHP() << "(" << printedHP.getMaxHP() << ")";
    return outStream;
}






