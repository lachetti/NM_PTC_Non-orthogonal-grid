#pragma once

#include "librarys.h"

class point                                     // Вспомогательный класс точки на плоскости
{
public:
    double X;
    double Y;
    point() {
        X = 0.0;
        Y =0.0;
    }
    point(double x, double y){
        X = x;
        Y = y;
    }
    ~point() {}
    void SetPoint(double x, double y){
        X = x;
        Y = y;
    }
    double operator+(const point& rv) const {   // длина отрезка между двумя точками
        return (sqrt((X-rv.X)*(X-rv.X) + (Y-rv.Y)*(Y-rv.Y)));
    }
    point& operator=(const point& right) {
            //проверка на самоприсваивание
            if (this == &right) {
                return *this;
            }
            X = right.X;
            Y = right.Y;
            return *this;
        }
};

class GridRect                                  // Класс одного четырёхугольника со всеми характеристиками
{
public:
    point Point[4];                             // координаты вершин
    double l[4];                                // длины сторон
    point center;                               // координаты центра
    double S;                                   // площадь четырехугольника

    GridRect() {
        for (int i=0; i<4; i++) {
            l[i] = 0.0;
        }
        S = 0.0;
    }

    void SetRect(point P0, point P1, point P2, point P3) {
        Point[0] = P0;
        Point[1] = P1;
        Point[2] = P2;
        Point[3] = P3;

        for (int i=0; i<4; i++) {
            l[i] = Point[i] + Point[(i+1) % 4];
        }

        double d1 = Point[0] + Point[2];
        double p1 = (l[0] + l[1] + d1) / 2.0;
        double p2 = (l[2] + l[3] + d1) / 2.0;
        S = sqrt( p1 * (p1 - l[0]) * (p1 - l[1]) * (p1 - d1) ) + sqrt( p2 * (p2 - l[2]) * (p2 - l[3]) * (p2 - d1) );
    }
};

class Grid
{
public:
    GridRect **Array;
    point **NodeGrid;
    int N;
    int M;

    double f01(double x) {  return (x);  }              //  [0; 1]
    double f12(double x) {  return (1.0);   }           //  [1; 2]          1   2
    double f23(double x) {  return (-x + 3.0);  }       //  [2; 3]      0           3
    double f30(double x) {  return (0.0);   }           //  [0; 3]

    Grid() {
        N = 0;
        M = 0;
    }

    Grid(int n, int m) {
        N = n;
        M = m;

        Array = new GridRect*[N];
        for (int i=0; i<N; i++) {
            Array[i] = new GridRect[M];
        }

        NodeGrid = new point*[N+1];
        for (int i=0; i<(N+1); i++) {
            NodeGrid[i] = new point[M+1];
        }
    }
    ~Grid() {
        for (int i=0; i<N; i++) {
            delete[] Array[i];
        }
        delete[] Array;

        for (int i=0; i<(N+1); i++) {
            delete[] NodeGrid[i];
        }
        delete[] NodeGrid;
    }

    void SetGrid() {
        for (int i=0; i<(N+1); i++) {
            NodeGrid[i][0].SetPoint(i*(3.0 / (double)N), 0.0);
            NodeGrid[i][M].SetPoint((1.0 + i*(1.0 / (double)N)), 1.0);
        }

        double midx = 0.0;
        double midy = 0.0;
        for (int i=0; i<(N+1); i++) {
            for (int j=1; j<M; j++) {
                midx = NodeGrid[i][0].X + ((double)j/(double)M) * (NodeGrid[i][M].X - NodeGrid[i][0].X);
                midy = NodeGrid[i][0].Y + ((double)j/(double)M) * (NodeGrid[i][M].Y - NodeGrid[i][0].Y);
                NodeGrid[i][j].SetPoint(midx,midy);
            }
        }

        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                Array[i][j].SetRect(NodeGrid[i][j], NodeGrid[i][j+1], NodeGrid[i+1][j+1], NodeGrid[i+1][j]);
            }
        }
    }
};

