#pragma once

#ifndef FRISBEE_H
#define FRISBEE_H

namespace SgNet{

    class Frisbee{
    private:
    
        // is a proxy object for a pointer. I named it frisbee to help lighten my frustration
    public:
        double* ref;
        Frisbee() = default;
        Frisbee(double*& ref);

        void operator= (double* val);
        void operator= (double value);

        double& operator*();
        bool operator== (double* val);

        const double val() const;

        void printValue();
        void printAddress();

    };

}


#endif