#include <bits/stdc++.h>

using namespace std;

int main()
{
    char x[] = "TOBEISNOTTOBE";
    
    int len = strlen(x);
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (x[j] == x[i])
            {
                for (int k = j + 1; k < len; k++)
                {
                    x[k - 1] = x[k];
                }
                len--; //陣列長度-1
                j--;   //重複點再次進行查重
            }
        }
    }
    cout << strlen(x) <<" " << len <<endl;
    for (int i = 0; i < strlen(x); i++)
    {
        cout << x[i];
    }
    cout << endl;
    for (int i = 0; i < len; i++)
    {
        cout << x[i];
    }
    
    return 0;
}