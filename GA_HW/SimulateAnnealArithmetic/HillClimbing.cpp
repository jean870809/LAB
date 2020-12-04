#include <bits/stdc++.h>

using namespace std;

int EXP_TIME = 100;
double PI = 2 * acos(0.0);
double abs_cal(double x); //計算絕對值
int main()
{
    double step[9] = {0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001,0.0000001,0.00000001,0.000000001}; //步伐
    int stepsize = sizeof(step)/sizeof(step[0]);

    double best_step = 0;
    double best_ans = 100;

    int all_count = 0;
    double all_b = 0;

    double p = -1.5;
    //ofstream File;
    //File.open("HillClimbing.csv");
    for (int exp = 0; exp < EXP_TIME; exp++)
    {
        cout << exp + 1 << endl;
        //File <<fixed  <<  setprecision(10)<< r << ",";
        //cout << abs_cal(r)<< endl;
        int count = 0;
        double x = p; //目前在哪
        cout << "x:" << x << endl;
        
        for (int i = 0; i < stepsize; i++)
        {
            double neighbor_right = x + step[i]; //右鄰居
            double neighbor_left = x - step[i];  //左鄰居

            while ((abs_cal(neighbor_right) < abs_cal(x)) || (abs_cal(neighbor_left) < abs_cal(x))) //如果左或右鄰居小於目前解
            {
                if (abs_cal(neighbor_right) < abs_cal(x)) //右鄰居<目前解 往右鄰居靠近
                {
                    x = neighbor_right;
                    neighbor_right = x + step[i];
                    neighbor_left = x - step[i];
                    count++;
                }
                if (abs_cal(neighbor_left) < abs_cal(x)) //左鄰居<目前解 往左鄰居靠近
                {
                    x = neighbor_left;
                    neighbor_right = x + step[i];
                    neighbor_left = x - step[i];
                    count++;
                }
            }
        }
        cout << "count:" << count << ",";
        cout << fixed << setprecision(10) << "(" << x << "、" << abs_cal(x) << ")" << endl;

        all_count += count;
        all_b += abs_cal(x);
        p += 0.03;
    }
    cout << fixed << setprecision(10) << "最佳解平均," << all_b / EXP_TIME << endl;
    cout << "計算次數平均," << all_count / EXP_TIME << endl;

    return 0;
}

double abs_cal(double x)
{
    double temp = 0;
    int d = 1;
    for (int i = 1; i <= d; i++)
    {
        temp += x * x - 10 * cos(2 * PI * x);
    }
    return 10 * d + temp;
}