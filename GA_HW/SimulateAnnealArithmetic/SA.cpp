#include <bits/stdc++.h>

using namespace std;
int EXP_TIME = 100;
double PI = 2 * acos(0.0);
double f(double x, int d);
int main()
{

    srand(114);

    //double step[] = {0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001, 0.00000001, 0.000000001}; //步伐
    double step[] = {0.1, 0.01, 0.001};
    int stepsize = sizeof(step) / sizeof(step[0]);

    double p = -1.5;       //撒點起點
    double p_delta = 0.03; //每隔0.03撒一個點

    int all_count = 0;
    double all_b = 0;
    for (int exp_times = 0; exp_times < EXP_TIME; exp_times++)
    {
        double T = 3000.0; //初始溫度
        double af = 0.8;   //退火率

        int count = 0;
        double x = p;   //目前在哪
        double r;       //隨機0-1

        double best_x;
        double best_y;

        //double dir;
        while (T > 0.0001)
        {
            for (int i = 0; i < stepsize; i++)
            {
                double neighbor_right = x + step[i]; //右鄰居
                double neighbor_left = x - step[i];  //左鄰居

                while ((f(neighbor_right, 1) < f(x, 1)) || (f(neighbor_left, 1) < f(x, 1))) //接受解-如果左或右鄰居小於目前解
                {

                    r = ((double)rand() / RAND_MAX);
                    //dir = ((double)rand() / RAND_MAX);

                    if (f(neighbor_right, 1) < f(x, 1) || (r < exp(-(f(neighbor_right, 1) - f(x, 1)) / T))) //右鄰居<目前解 往右鄰居靠近 接受右鄰居
                    {

                        //cout << count << ",right:" << neighbor_right << "," << f(neighbor_right, 1) << ",left" << neighbor_left << "," << f(neighbor_left, 1) << ",choose:" << neighbor_right << "," << f(neighbor_right, 1) << endl;
                        x = neighbor_right;
                        neighbor_right = x + step[i];
                        neighbor_left = x - step[i];
                        count++;
                    }
                    else if (f(neighbor_left, 1) < f(x, 1) || (r < exp(-(f(neighbor_left, 1) - f(x, 1)) / T))) //左鄰居<目前解 往左鄰居靠近 接受左鄰居
                    {

                        //cout << count << ",right:" << neighbor_right << "," << f(neighbor_right, 1) << ",left" << neighbor_left << "," << f(neighbor_left, 1) << ",choose:" << neighbor_left << "," << f(neighbor_left, 1) << endl;

                        x = neighbor_left;
                        neighbor_right = x + step[i];
                        neighbor_left = x - step[i];
                        count++;
                    }
                }
                
                //cout << T << endl;
                //cout << "降溫" << endl;
                T *= af;
            }
            //T *= af;
        }

        cout << "Exp:" << exp_times + 1 << fixed << setprecision(2) << ",point" << p << ",count:" << count << ",";
        cout << fixed << setprecision(10) << "(" << x << "、" << f(x, 1) << ")" << endl;

        p += p_delta;
        all_count += count;
        all_b += f(x, 1);
    }
    cout << fixed << setprecision(10) << "最佳解平均," << all_b / EXP_TIME << endl;
    cout << "計算次數平均," << all_count / EXP_TIME << endl;

    return 0;
}

double f(double x, int d)
{
    double temp = 0;
    for (int i = 1; i <= d; i++)
    {
        temp += x * x - 10 * cos(2 * PI * x);
    }
    return 10 * d + temp;
}