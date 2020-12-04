
#include <bits/stdc++.h>

using namespace std;

//int a[] = {1, 2, 3, 4}; //在此只列举了几何中有6个元素的情况
int a[] = {5, 1, 4, 3, 2, 6, 8, 7}; //test sort
void print(int flag)                //采用二进制方法输出集合元素
{
    int temp = flag;
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        if (temp & 1 >= 1)
            cout << a[i] << " ";
        temp >>= 1;
    }
    cout << endl;
}

int main()
{
    /*int flag = 0;
    while (flag < pow(2, sizeof(a) / sizeof(a[0])))
    { //加上空集一共有2^n个集合
        print(flag);
        flag++;
    }
    cout << "Subset nums = " << flag << endl; //flag即为子集个数*/
    sort(a, a + 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}