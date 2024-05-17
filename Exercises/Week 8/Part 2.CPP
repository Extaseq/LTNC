#include <bits/stdc++.h>
using namespace std;

struct String
{
    int n;

    char *str;

    String(const char *s)
    {
        n = strlen(s);
        str = new char[n + 1];
        strcpy(str, s);
    }

    ~String()
    {
        delete[] str;
    }

    void print()
    {
        cout << str << endl;
    }

    void append(const char *s2)
    {
        int new_length = n + strlen(s2);
        char *tmp = new char[new_length + 1];
        strcpy(tmp, str);
        strcat(tmp, s2);
        delete[] str;
        str = tmp;
        n = new_length;
    }
};
