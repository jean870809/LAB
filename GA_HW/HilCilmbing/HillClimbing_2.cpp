#include <bits/stdc++.h>

using namespace std;

int EXP_TIME = 100;
double abs_cal(double num); //計算絕對值
int main()
{
    srand(114);
    //double step = 0.01; //步伐

    double best_step = 0;
    double best_ans = 100;

    for (int step = 1; step <= 10; step++)
    {
        int all_count = 0;
        double all_b = 0;

        for (int exp = 0; exp < EXP_TIME; exp++)
        {
            double r;

            r = ((double)rand() / RAND_MAX) * 200 - 100; // 隨機撒點在[-100,100]區間
            //cout << "實驗" << exp + 1 << endl;
            //cout << r << endl;
            int count = 0;
            double x = r;                                                                           //目前在哪
            double neighbor_right = x + step;                                                       //右鄰居
            double neighbor_left = x - step;                                                        //左鄰居
            int dir = -1;                                                                           //目前走的方向 1為右 0為左
            while ((abs_cal(neighbor_right) < abs_cal(x)) || (abs_cal(neighbor_left) < abs_cal(x))) //如果左或右鄰居小於目前解
            {
                if (abs_cal(neighbor_right) < abs_cal(x)) //右鄰居<目前解 往右鄰居靠近
                {
                    x = neighbor_right;
                    neighbor_right = x + step;
                    neighbor_left = x - step;
                    count++;
                }
                if (abs_cal(neighbor_left) < abs_cal(x)) //左鄰居<目前解 往左鄰居靠近
                {
                    x = neighbor_left;
                    neighbor_right = x + step;
                    neighbor_left = x - step;
                    count++;
                }
            }
            //cout << "x:" << x << ",f(x):" << abs_cal(x) << endl;
            //cout << "走幾次" << count << endl;

            all_count += count;
            all_b += abs_cal(x);
        }
        cout << "最佳解平均" << all_b / EXP_TIME << endl;
        cout << "計算次數平均" << all_count / EXP_TIME << endl;
        if (best_ans > (all_b / EXP_TIME))
        {
            best_ans = all_b / EXP_TIME;
            best_step = step;
        }
    }
    cout << endl
         << endl;
    cout << fixed << setprecision(4) << best_step << endl;
    cout << fixed << setprecision(4) << best_ans << endl;

    return 0;
}

double abs_cal(double num)
{
    return abs(num);
}