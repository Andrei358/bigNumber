#include <fstream>
#include <iostream>
#include <cstring>

#pragma once

const int BNmaxLength=1000;

class bigNumber{
    private:
        char v[BNmaxLength];
        int L;
        bool sign;
        void setll(long long int);
        int comp(bigNumber);
        void erase0();
        void mult10(int);
        void div10(int);
        bigNumber mult(bigNumber);
        bigNumber mult2(bigNumber);
    public:
        bigNumber(){
            setll(0);
            sign=0;
        }
        bigNumber(long long int q){
            setll(q);
        }
        bigNumber& operator=(long long int);
        explicit operator int();
        bool operator==(bigNumber);
        bool operator!=(bigNumber);
        bool operator<(bigNumber);
        bool operator<=(bigNumber);
        bool operator>(bigNumber);
        bool operator>=(bigNumber);
        bigNumber operator+(bigNumber);
        bigNumber& operator+=(bigNumber);
        bigNumber& operator++();
        bigNumber operator++(int);
        bigNumber operator-(bigNumber);
        bigNumber& operator-=(bigNumber);
        bigNumber& operator--();
        bigNumber operator--(int);
        bigNumber operator*(long long int);
        bigNumber operator*=(long long int);
        bigNumber operator*(bigNumber);
        friend bool operator==(int, bigNumber);
        friend bool operator!=(int, bigNumber);
        friend bool operator<(int, bigNumber);
        friend bool operator<=(int, bigNumber);
        friend bool operator>(int, bigNumber);
        friend bool operator>=(int, bigNumber);
        friend bigNumber operator+(long long int, bigNumber);
        friend bigNumber operator-(const long long int, bigNumber);
        friend bigNumber operator*(long long int, bigNumber);
        friend std::istream& operator>>(std::istream&, bigNumber&);
        friend std::ostream& operator<<(std::ostream&, const bigNumber&);
        friend class bigVector;
        friend bigNumber abs_max(bigNumber, bigNumber);
};

