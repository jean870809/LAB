#include <bits/stdc++.h>

using namespace std;


int main()
{
    srand(114);

    for (int exp = 0; exp < 100; exp++)
    {
        double r;

        r = ((double)rand() / RAND_MAX)*200 -100 ; 
        cout << r << endl;
    }

    return 0;
}

