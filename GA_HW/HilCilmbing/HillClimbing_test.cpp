#include <bits/stdc++.h>

using namespace std;

int EXP_TIME = 1;
double f(double num); //計算絕對值
int main()
{
    srand(114);
    double step[6] = {10.0, 1.0, 0.1, 0.01, 0.001, 0.0001}; //步伐
    //double step = 10;
    double best_step = 0;
    double best_ans = 99999999999;

    int all_count = 0;
    double all_b = 0;
    for (int exp = 0; exp < EXP_TIME; exp++)
    {
        double r;

        r = ((double)rand() / RAND_MAX) * 200 - 100; // 隨機撒點在[-100,100]區間
        //cout << "實驗" << exp + 1 << endl;
        cout <<fixed  <<  setprecision(4)<< r << endl;
        cout << f(r)<< endl;
        int count = 0;
        double x = r; //目前在哪

        for (int i = 0; i < sizeof(step); i++)
        {
            double neighbor_right = x + step[i]; //右鄰居
            double neighbor_left = x - step[i];  //左鄰居

            while ((f(neighbor_right) < f(x)) || (f(neighbor_left) < f(x))) //如果左或右鄰居小於目前解
            {
                if (f(neighbor_right) < f(x)) //右鄰居<目前解 往右鄰居靠近
                {
                    x = neighbor_right;
                    neighbor_right = x + step[i];
                    neighbor_left = x - step[i];
                    count++;
                    //cout <<fixed  <<  setprecision(4)<< "x:" << x << ",f(x):" << abs_cal(x) << endl;
                }
                if (f(neighbor_left) < f(x)) //左鄰居<目前解 往左鄰居靠近
                {
                    x = neighbor_left;
                    neighbor_right = x + step[i];
                    neighbor_left = x - step[i];
                    
                    count++;
                    //cout <<fixed  <<  setprecision(4)<< "x:" << x << ",f(x):" << abs_cal(x) << endl;
                }
            }
        }
        cout <<fixed  <<  setprecision(10)<< "最佳解 x:" << x << ",f(x):" << f(x) << endl;
        cout << "走幾次" << count << endl;

        all_count += count;
        all_b += f(x);
    }
    cout << fixed << setprecision(10) << "最佳解平均" << all_b / EXP_TIME << endl;
    cout << "計算次數平均" << all_count / EXP_TIME << endl;

    return 0;
}

double f(double num)
{
    return num*num;
}