#include <bits/stdc++.h>
#include <stdio.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

#define N 30            //選幾檔計算
#define change 0.0004   //加減角度
#define EXP_TIMES 50    //實驗次數
#define GEN_TIMES 10000 //迭代次數
#define P 10            //族群規模
#define allmoney 10000000.0
//double allmoney = 10000000; //初始資金

struct stock
{
    string name;          //公司名
    vector<double> price; //股價
};
struct portfolio
{
    int choose[N] = {0};                //選哪幾家
    int stock_num[N] = {0};             //購買張數
    double distribute_money[N] = {0.0}; //分配資金
    double remain_money[N + 1] = {0.0}; //剩餘資金
    vector<double> funding;             //資金水位
    double trend = 0.0;                 //趨勢值
    double m;                           //每日預期報酬
    double risk;                        //每日風險
    int generation = 0;                 //紀錄GB.LB找到的代數
    int exp = 0;                        //紀錄找到的實驗次數
    int find = 0;                       //紀錄找到最佳解的次數
};
stock dji[N];
portfolio solution[P];
string input_csv;
string output_csv;

void M_csvioname(int year, int month); //inputcsv&outputcsv
//void Y_csvioname(int year); //inputcsv&outputcsv
//void Q_csvioname(int year, int quarter); //inputcsv&outputcsv
//void H_csvioname(int year, int month); //inputcsv&outputcsv

void _csvprice(string s);                //讀取股價
void _csvname(string s);                 //讀取公司名
void cal_trend(portfolio &p);            //計算趨勢值
void assign(portfolio &a, portfolio &b); //將b的值放進a裡
void writecsv(portfolio best);
int main()
{
    srand(114);

    for (int y = 2009; y <= 2018; y++)
    {
        for (int m = 1; m <= 12; m++)
        {

            M_csvioname(y, m);

            for (int i = 0; i < N; i++)
            {
                dji[i].price.clear();
            }

            //=================讀取
            cout << input_csv << endl;
            ifstream inFile(input_csv, ios::in);
            if (!inFile)
            {
                cout << "OPEN FAIL!" << endl;
            }
            string line;
            int n = 0;
            while (getline(inFile, line))
            {
                if (n == 0)
                {
                    _csvname(line);
                    //name.push_back(a);
                    n++;
                }
                else
                {
                    _csvprice(line);
                    //data.push_back(a);
                    n++;
                }
            }

            //===============
            portfolio exp_globalbest;
            for (int exp = 0; exp < EXP_TIMES; exp++)
            {
                double r[N]; //機率矩陣
                for (int i = 0; i < N; i++)
                {
                    r[i] = 0.5;
                }

                portfolio localbest, localworst, globalbest;
                for (int t = 0; t < GEN_TIMES; t++) //迭代
                {

                    for (int p = 0; p < P; p++) //初始化
                    {
                        double random = 0;
                        for (int i = 0; i < N; i++)
                        {
                            random = (double)rand() / RAND_MAX; // 0-1小數
                            if (random > r[i])
                            {
                                solution[p].choose[i] = 0;
                            }
                            else
                            {
                                solution[p].choose[i] = 1;
                            }
                        }
                        cal_trend(solution[p]);
                        /*for (int j = 0; j < solution[p].funding.size(); j++)
                {
                    cout << j + 1 << ": " << fixed << setprecision(10) << solution[p].funding[j] << endl;
                }*/
                        //cout << "m: " << solution[p].m << endl;
                    }
                    for (int p = 0; p < P; p++) //更新LB&LW
                    {
                        if (localbest.trend == 0)
                        {
                            assign(localbest, solution[p]);
                            localbest.generation = t;
                        }
                        if (localworst.trend == 0)
                        {
                            assign(localworst, solution[p]);
                            localworst.generation = t;
                        }
                        if (solution[p].trend > localbest.trend)
                        {
                            assign(localbest, solution[p]);
                            localbest.generation = t;
                        }
                        if (solution[p].trend < localworst.trend)
                        {
                            assign(localworst, solution[p]);
                            localworst.generation = t;
                        }
                    }
                    if (localbest.trend > globalbest.trend) //更新GB
                    {
                        assign(globalbest, localbest);
                        globalbest.generation = t;
                        globalbest.exp = exp;
                    }
                    //====更新機率矩陣

                    for (int i = 0; i < N; i++)
                    {
                        if (globalbest.choose[i] == 1 && localworst.choose[i] == 0)
                        {
                            if (r[i] < 0.5)
                            {
                                r[i] = 1 - r[i];
                            }
                            r[i] += change;
                        }
                        if (globalbest.choose[i] == 0 && localworst.choose[i] == 1)
                        {
                            if (r[i] > 0.5)
                            {
                                r[i] = 1 - r[i];
                            }

                            r[i] -= change;
                        }
                    }

                    localworst.trend = 0;
                    localbest.trend = 0;
                }
                //cout << exp + 1 << "  " << globalbest.trend << endl;
                if (globalbest.trend > exp_globalbest.trend)
                {
                    assign(exp_globalbest, globalbest);
                    exp_globalbest.generation = globalbest.generation;
                    exp_globalbest.exp = globalbest.exp;
                    exp_globalbest.find = 0;
                }
                if (globalbest.trend == exp_globalbest.trend)
                {
                    exp_globalbest.find++;
                }
                globalbest.trend = 0;
            }
            if (exp_globalbest.trend != 0)
            {

                writecsv(exp_globalbest);
            }

            cout << exp_globalbest.trend << endl;
            cout << exp_globalbest.exp + 1 << endl;
            cout << exp_globalbest.generation + 1 << endl;

            inFile.close();
            exp_globalbest.trend = 0;
        }
    }
    return 0;
}
void assign(portfolio &a, portfolio &b)
{
    for (int i = 0; i < N; i++)
    {
        a.choose[i] = b.choose[i];
        a.stock_num[i] = b.stock_num[i];
        a.distribute_money[i] = b.distribute_money[i];
        a.remain_money[i] = b.remain_money[i];
    }
    a.remain_money[N] = b.remain_money[N];
    a.funding = b.funding;
    a.trend = b.trend;
    a.m = b.m;
    a.risk = b.risk;
}
void cal_trend(portfolio &p)
{
    vector<int> choose_n;
    for (int i = 0; i < N; i++)
    {
        if (p.choose[i] == 1)
        {
            choose_n.push_back(i);
        }
    }
    int n = choose_n.size(); //選了幾檔
    if (n == 0)
    {
        p.m = 0;
        p.risk = 0;
        p.trend = 0;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            p.distribute_money[choose_n[i]] = allmoney / n; //各檔分配資金
        }
        for (int i = 0; i < n; i++) //可買股數
        {
            p.stock_num[choose_n[i]] = (p.distribute_money[choose_n[i]] / (dji[choose_n[i]].price[0]));
        }
        double all_remainmoney = 0; //剩餘資金
        for (int i = 0; i < n; i++)
        {
            p.remain_money[choose_n[i]] = p.distribute_money[choose_n[i]] - p.stock_num[choose_n[i]] * (dji[choose_n[i]].price[0]);
            all_remainmoney += p.remain_money[choose_n[i]];
        }
        p.remain_money[N] = (allmoney - p.distribute_money[choose_n[0]] * n);
        all_remainmoney += p.remain_money[N];
        int day = dji[0].price.size(); //天數
        p.funding.clear();
        for (int i = 0; i < day; i++)
        {
            double temp = 0;
            for (int j = 0; j < n; j++)
            {
                temp += p.stock_num[choose_n[j]] * dji[choose_n[j]].price[i];
            }
            p.funding.push_back(all_remainmoney + temp);
        }

        //===== 算趨勢值
        double m = 0;     //每日預期報酬
        double risk = 0;  // 每日風險
        double trend = 0; // 趨勢值
        //=====m
        double temp1 = 0.0, temp2 = 0;
        for (int i = 0; i < day; i++)
        {
            //cout << i + 1 << ": " << fixed << setprecision(10) << temp1 << endl;
            //cout << "+: " << (i + 1) * p.funding[i] << " - " << (i + 1) * allmoney << endl;
            temp1 += (i + 1) * p.funding[i] - (i + 1) * allmoney;
            temp2 += (i + 1) * (i + 1);
        }
        m = temp1 / temp2;
        //cout << "m: " << m << endl;
        //====risk
        double temp = 0;
        for (int i = 0; i < day; i++)
        {
            temp += (p.funding[i] - (m * (i + 1) + allmoney)) * (p.funding[i] - (m * (i + 1) + allmoney));
        }
        risk = sqrt(temp / day);

        if (m < 0)
        {
            trend = m * risk;
        }
        else
        {
            trend = m / risk;
        }

        p.m = m;
        p.risk = risk;
        p.trend = trend;
    }
}
void writecsv(portfolio best)
{
    ofstream outFile;
    cout << output_csv << endl;
    outFile.open(output_csv);

    outFile << fixed << setprecision(10) << "初始資金," << allmoney << endl;
    outFile << fixed << setprecision(10) << "最後資金," << best.funding.back() << endl;
    outFile << fixed << setprecision(10) << "真實報酬," << best.funding.back() - allmoney << endl
            << endl;

    vector<int> choose_n;
    int day = dji[0].price.size(); //天數
    //cout << "day: " << day << endl;
    //=====2次趨勢線係數 Y = ax*x+bx+c
    MatrixXd Y(day, 1); //Y[y-c]
    for (int i = 0; i < day; i++)
    {
        Y(i, 0) = best.funding[i] - allmoney;
    }

    MatrixXd A(day, 2); //A[x^2,x]
    for (int i = 0; i < day; i++)
    {
        A(i, 0) = (i + 1) * (i + 1);
        A(i, 1) = i + 1;
    }
    MatrixXd AT(2, day); //Transpose A
    AT = A.transpose().eval();

    MatrixXd theta(2, 1);
    theta = (((AT * A).inverse()) * AT * Y).eval();

    //二次回歸方程式 Y=ax^2+bx+c
    double a = theta(0, 0);
    double b = theta(1, 0);

    double quadratic_m = 0;        //二次趨勢線算的每日預期報酬
    double quadratic_weight_m = 0; //二次趨勢線算的加權每日預期報酬
    double quadratic_risk = 0;     //二次趨勢線算的風險
    double quadratic_trend = 0;    //二次趨勢線算的趨勢值

    //==== m =  (Yd-Y1)/(d-1) or  sum(2ax+b)
    quadratic_m = ((a * day * day + b * day + allmoney) - (a * 1 * 1 + b * 1 + allmoney)) / (day - 1); //(Yd-Y1)/(d-1)
    int sum_day = 0;
    for (int i = 0; i < day; i++) //sum(2ax+b)
    {
        // quadratic_m += 2 * a * (i + 1) + b;
        quadratic_weight_m += (i + 1) * (2 * a * (i + 1) + b);
        sum_day += (i + 1);
    }
    quadratic_m = quadratic_m / day;
    quadratic_weight_m = quadratic_weight_m / sum_day;

    //=====risk = sqrt(sum((yi-Yi)^2)/d)
    double temp = 0;
    for (int i = 0; i < day; i++) //(yi-Yi)^2
    {
        temp += (best.funding[i] - (a * (i + 1) * (i + 1) + b * (i + 1) + allmoney)) * (best.funding[i] - (a * (i + 1) * (i + 1) + b * (i + 1) + allmoney));
    }
    quadratic_risk = sqrt(temp / day);
    //==== trend = m/risk
    quadratic_trend = quadratic_m / quadratic_risk;
    outFile << fixed << setprecision(10) << "二次趨勢線," << a << "x^2 + " << b << "x + " << allmoney << endl;
    outFile << fixed << setprecision(10) << "加權每日預期報酬," << quadratic_weight_m << endl;
    outFile << fixed << setprecision(10) << "風險," << quadratic_risk << endl;
    outFile << fixed << setprecision(10) << "二次趨勢值," << quadratic_weight_m / quadratic_risk << endl;
    outFile << endl;
    outFile << fixed << setprecision(10) << "平均每日預期報酬," << quadratic_m << endl;
    outFile << fixed << setprecision(10) << "風險," << quadratic_risk << endl;
    outFile << fixed << setprecision(10) << "二次趨勢值," << quadratic_trend << endl;
    outFile << endl;
    outFile << fixed << setprecision(10) << "一次趨勢線," << best.m << "x + " << allmoney << endl;
    outFile << fixed << setprecision(10) << "每日預期報酬," << best.m << endl;
    outFile << fixed << setprecision(10) << "風險," << best.risk << endl;
    outFile << fixed << setprecision(10) << "一次趨勢值," << best.trend << endl;
    outFile << endl;

    //=============
    for (int i = 0; i < N; i++)
    {
        if (best.choose[i] == 1)
        {
            choose_n.push_back(i);
        }
    }
    int n = choose_n.size(); //選了幾檔
    outFile << "投資組合檔數," << n << endl;
    outFile << "Stock#,"; //stock名
    for (int i = 0; i < n; i++)
    {
        outFile << dji[choose_n[i]].name << ",";
    }
    outFile << endl;
    /*outFile << "張數,";
    for (int i = 0; i < n; i++)
    {
        outFile << best.stock_num[choose_n[i]] << ",";
    }
    outFile << endl;
    outFile << "分配資金,";
    for (int i = 0; i < n; i++)
    {
        outFile << best.distribute_money[choose_n[i]] << ",";
    }
    outFile << endl;
    outFile << "剩餘資金,";
    for (int i = 0; i < n; i++)
    {
        outFile << best.remain_money[choose_n[i]] << ",";
    }
    outFile << best.remain_money[N] << ",";
    outFile << endl;*/

    for (int i = 0; i < day; i++) //每日資金水位
    {
        outFile << "FS(" << i + 1 << "),";
        /*for (int j = 0; j < n; j++) //幾檔
        {
            outFile << fixed << setprecision(10) << best.stock_num[choose_n[j]] * dji[choose_n[j]].price[i] + (best.distribute_money[choose_n[j]] - best.stock_num[choose_n[j]] * dji[choose_n[j]].price[0]) << ",";
        }*/
        outFile << fixed << setprecision(10) << best.funding[i] << ",";
        outFile << endl;
    }
    outFile.close();
}

void _csvprice(string s)
{
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            dji[i].price.push_back(atof(token.c_str()));
            i++;
        }
    }
}

void _csvname(string s)
{
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            dji[i].name = token;
            i++;
        }
    }
}
/*void Y_csvioname(int year)
{

    string input_name = "DJI_30/Y2Y/train_";
    string input_format = " Q1).csv";
    stringstream ss_input;
    ss_input << input_name << year << "(" << year << input_format;
    input_csv = ss_input.str();

    string output_name = "train_result/Y2Y/quadratic_result_train_";
    string output_format = " Q1).csv";
    stringstream ss_output;
    ss_output << output_name << year << "(" << year << output_format;
    output_csv = ss_output.str();

    //cout << input_csv << endl;
    //cout << output_csv << endl;
}*/
void M_csvioname(int year, int month)
{
    string input_name = "DJI_30/Y2M/train_";
    string input_format = " Q1).csv";
    stringstream ss_input;
    if (month == 1)
    {
        ss_input << input_name << year << "(" << year << input_format;
    }
    else
    {
        ss_input << input_name << year << "_" << setw(2) << setfill('0') << month << "~" << year + 1 << "_" << setw(2) << setfill('0') << month - 1 << "(" << year << input_format;
    }
    input_csv = ss_input.str();

    string output_name = "train_result/Y2M/quadratic_result_train_";
    string output_format = " Q1).csv";
    stringstream ss_output;
    if (month == 1)
    {
        ss_output << output_name << year << "(" << year << output_format;
    }
    else
    {
        ss_output << output_name << year << "_" << setw(2) << setfill('0') << month << "(" << year << output_format;
    }

    output_csv = ss_output.str();
}
/*void Q_csvioname(int year, int quarter)
{
    string input_name = "DJI_30/Y2H/train_";
    string input_format = " Q1).csv";
    stringstream ss_input;
    if (quarter == 1)
    {
        ss_input << input_name << year << "(" << year << input_format;
    }
    else
    {
        ss_input << input_name << year << "_Q" << quarter << "~" << year + 1 << "_Q" << (quarter - 1) << "(" << year << input_format;
    }
    input_csv = ss_input.str();

    string output_name = "train_result/Y2H/quadratic_result_train_";
    string output_format = " Q1).csv";
    stringstream ss_output;
    if (quarter + 2 > 12)
    {
        ss_output << output_name << year << "(" << year << output_format;
    }
    else
    {
        ss_output << output_name << year << "_Q" << quarter << "~" << year + 1 << "_Q" << (quarter - 1) << "(" << year << output_format;
    }
    output_csv = ss_output.str();
}*/
/*void H_csvioname(int year, int month)
{

    string input_name = "DJI_30/H2M/train_";
    string input_format = " Q1).csv";
    stringstream ss_input;
    if (month + 5 > 12)
    {
        ss_input << input_name << year << "_" << setw(2) << setfill('0') << month << "~" << year + 1 << "_" << setw(2) << setfill('0') << month - 7 << "(" << year << input_format;
    }
    else
    {
        ss_input << input_name << year << "_" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << month + 5 << "(" << year << input_format;
    }

    input_csv = ss_input.str();

    string output_name = "train_result/H2M/quadratic_result_train_";
    string output_format = " Q1).csv";
    stringstream ss_output;
    if (month + 5 > 12)
    {
        ss_output << output_name << year << "_" << setw(2) << setfill('0') << month << "~" << year + 1 << "_" << setw(2) << setfill('0') << month - 7 << "(" << year << output_format;
    }
    else
    {
        ss_output << output_name << year << "_" << setw(2) << setfill('0') << month << "-" << month + 5 << "(" << year << output_format;
    }
    output_csv = ss_output.str();

    //cout << input_csv << endl;
    //cout << output_csv << endl;
}*/