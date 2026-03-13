#pragma once


#include "Person.h"

class Leader: public Person
{
    private:
    int l_id;

    public:
    Leader(const std::string& name_in = "-")
    : Person(name_in)
    {}

    friend std::ostream& operator << (std::ostream& out, const Leader& leader)
    {
        out << leader.getName() << " " << leader.l_id;
        return out;
    }

};