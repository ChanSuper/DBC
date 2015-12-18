//
// Created by 陈超 on 15/12/15.
//

#ifndef DBC_V4_MAIN_H
#define DBC_V4_MAIN_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

const int DIM = 2;

class Point{
public:
    double p[DIM];
    int state;
    int index;
    double moveDist;
    Point(){
        memset(p, 0, DIM * sizeof(double));
        state = 0;
        index = 0;
        moveDist = 0;
    }

    Point(const Point& P) {
        for(int i=0; i<DIM; i++)
            p[i] = P.p[i];
        state = P.state;
        index = P.index;
        moveDist = P.moveDist;
    }

    Point operator+(const Point& P){
        Point ret;
        for(int i=0; i<DIM; i++)
            ret.p[i] = p[i] + P.p[i];
        return ret;
    }

    Point operator-(const Point& P){
        Point ret;
        for(int i=0; i<DIM; i++)
            ret.p[i] = p[i] - P.p[i];
        return ret;
    }

    Point operator*(double factor){
        Point ret;
        for(int i=0; i<DIM; i++)
            ret.p[i] = p[i] * factor;
        return ret;
    }

    double operator*(Point& point){
        double ret = 0;
        for(int i=0; i<DIM; i++)
            ret += p[i] * point.p[i];
        return ret;
    }

    Point operator/(double factor){
        Point ret;
        for(int i=0; i<DIM; i++)
            ret.p[i] = p[i] / factor;
        return ret;
    }

    Point& operator+=(const Point& P){
        for(int i=0; i<DIM; i++)
            p[i] += P.p[i];
        return *this;
    }

    Point& operator-=(const Point& P){
        for(int i=0; i<DIM; i++)
            p[i] -= P.p[i];
        return *this;
    }

    void print() {
        for(int i=0; i<DIM; i++){
            printf("%lf ", p[i]);
        }
        printf("\n");
    }
};

typedef Point Vector; // 向量 即 点

struct Cluster{
    Point center;
    int tot;
    int familyNum;
    Cluster(){
        tot = 0;
        familyNum = 0;
    }
    Cluster(Point p, int tot, int familyNum) {
        this->center = p;
        this->tot = tot;
        this->familyNum = familyNum;
    }
};


double f(double x) {
    double y = 2.0 / (1 + exp(1-x)) - 1;

    return y > 0 ? y : 0;
}

double dist(const Point &a, const Point &b) {
    double ret = 0;
    for(int i=0; i<DIM; i++){
        ret += (a.p[i] - b.p[i]) * (a.p[i] - b.p[i]);
    }
    return sqrt(ret);
}

double dist(const Vector& v)
{
    double ret = 0;
    for(int i=0; i<DIM; i++){
        ret += v.p[i] * v.p[i];
    }
    return sqrt(ret);
}

Vector normalize(Vector v)
{
    double size = dist(v);
    if(fabs(size) < 1e-8)
        return v;
    Vector ret;
    for(int i=0; i<DIM; i++)
        ret.p[i] = v.p[i] / size;
    return ret;
}


#endif //DBC_V4_MAIN_H
