#include <bits/stdc++.h>
using namespace std;


struct Point
{
    int x, y;
};

void print1(Point p)
{
    cout << p.x << " " << p.y << endl;
}

void print2(Point &p)
{
    cout << p.x << " " << p.y << endl;
}

Point mid_point(const Point p1, const Point p2)
{
    Point res;
    res.x = p1.x / 2 + p2.x / 2;
    res.y = p1.y / 2 + p2.y / 2;
    return res;
}

struct Rect
{
    int x, y, w, h;
    bool contains(const Point &p) const
    {
        return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h;
    }
};

struct Ship
{
    Rect r1;
    string id;
    int dx, dy;
    void moved()
    {
        r1.x += dx;
        r1.y += dy;
    }
};

void display(const Ship& ship)
{
    cout << ship.r1.x << " " << ship.r1.y << endl;
    cout << ship.id << endl;
}
