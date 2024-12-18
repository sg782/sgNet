#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>


namespace SgNet {

    class Vector{
    public:
        std::vector<double> data;
        Vector(int size);

        void print();

        int size() const;

        double dot(const Vector& v);

        void setConstant(int val);
        void set(std::vector<double> vals);
        void set(SgNet::Vector vals);

        Vector operator+ (const double val) const;
        Vector operator+ (const Vector vals) const;

        Vector operator- (const double val) const;
        Vector operator- (const Vector vals) const;

        Vector operator* (const double val) const;
        Vector operator* (const Vector vals) const;

        Vector operator/ (const double val) const;
        Vector operator/ (const Vector vals) const;

        double& operator[] (int index);
        const double& operator[] (int index) const;
    };

}

#endif