#pragma once

#ifndef FRISBEE_H
#define FRISBEE_H

namespace SgNet{

    class Frisbee{
    private:
    
        // is a proxy object for a pointer. I named it frisbee to help lighten my frustration

        /*
        I use it as the standard data type in my custom vector, as I got annoyed when I couldnt find a way to pass references to a standard Double
        variable around. Maybe it is possible but i couldnt think of it.

        This class simply acts as a nice little container for a double variable, but lets us point it anywhere we want.
        it is most used for when one would acll Tensor2d.byCol(), which reogranizes the data by column instead of row. I needed to still
        be able to access the same memory locations.
        
        */
    public:
        double* ref;
        Frisbee() = default;
        Frisbee(double*& ref);

        void operator= (double* val);
        void operator= (const double value) const;
        void operator= (const int value) const;
        void operator= (double value);
        void operator= (int value);
        

        double& operator*();
        bool operator== (double* val);

        void operator+= (const double val);
        void operator-= (const double val);
        void operator*= (const double val);
        void operator/= (const double val);

        const double val() const;
        double* address();

        void printValue();
        void printAddress();

    };

}


#endif