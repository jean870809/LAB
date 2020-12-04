#include <bits/stdc++.h>

using namespace std;
#define N 30              //選幾檔計算
#define change 0.0004     //加減角度
#define EXP_TIMES 50      //實驗次數
#define GEN_TIMES 10000   //迭代次數
#define P 10              //族群規模
#define allmoney 10000000 //初始資金

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

void _csvprice(string s);                //讀取股價
void _csvname(string s);                 //讀取公司名
void cal_trend(portfolio &p);            //計算趨勢值
void assign(portfolio &a, portfolio &b); //將b的值放進a裡
void writecsv(portfolio best);
int main()
{
    srand(114);

    for (int y = 2009; y <= 2019; y++)
    {
        for (int m = 1; m <= 12; m++)
        {

            if (y == 2009 && m == 1)
            {
                m = 12;
            }
            if (y == 2019 && m == 7)
            {
                break;
            }

            M_csvioname(y, m);
            for (int i = 0; i < N; i++)
            {
                dji[i].price.clear();
            }

            //=================讀取
            //ifstream inFile("D:/LAB/c++/QTS/DJI_30/Y2Y/test_2010(2009 Q1).csv", ios::in);
            ifstream inFile(input_csv, ios::in);
            if (!inFile)
            {
                cout << "FAIL！" << endl;
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
            exp_globalbest.trend = 0.0;
            for (int exp = 0; exp < EXP_TIMES; exp++)
            {
                double r[N]; //機率矩陣
                for (int i = 0; i < N; i++)
                {
                    r[i] = 0.5;
                }

                portfolio localbest, localworst, globalbest;
                globalbest.trend = 0.0;
                localbest.trend = 0.0;
                localworst.trend = 0.0;

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
                    }
                    for (int p = 0; p < P; p++) //更新LB&LW
                    {
                        if (localbest.trend == 0.0)
                        {
                            assign(localbest, solution[p]);
                            localbest.generation = t;
                        }
                        if (localworst.trend == 0.0)
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

                    localworst.trend = 0.0;
                    localbest.trend = 0.0;
                }
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
                globalbest.trend = 0.0;
            }
            if (exp_globalbest.trend != 0)
            {
                if (y == 2019)
                    writecsv(exp_globalbest);
            }
            cout << exp_globalbest.trend << endl;
            cout << exp_globalbest.exp + 1 << endl;
            cout << exp_globalbest.generation + 1 << endl;
            inFile.close();
            exp_globalbest.trend = 0.0;
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
        p.trend = 0.0;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            p.distribute_money[choose_n[i]] = allmoney / n; //各檔分配資金
        }
        for (int i = 0; i < n; i++)
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
        double m;     //每日預期報酬
        double risk;  // 每日風險
        double trend; // 趨勢值
        double temp1 = 0, temp2 = 0;
        for (int i = 0; i < day; i++)
        {
            temp1 += (i + 1) * p.funding[i] - (i + 1) * allmoney;
            temp2 += (i + 1) * (i + 1);
        }
        m = temp1 / temp2;
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
    ofstream myFile;
    myFile.open("newGNQTS.csv");
    myFile << "代數," << GEN_TIMES << endl;
    myFile << "粒子數," << P << endl;
    myFile << "旋轉角度," << change << endl;
    myFile << "實驗次數," << EXP_TIMES << endl
           << endl;
    myFile << fixed << setprecision(10) << "初始資金," << allmoney << endl;
    myFile << fixed << setprecision(10) << "最後資金," << best.funding.back() << endl;
    myFile << fixed << setprecision(10) << "真實報酬," << best.funding.back() - allmoney << endl
           << endl;
    myFile << fixed << setprecision(10) << "預期報酬," << best.m << endl;
    myFile << fixed << setprecision(10) << "風險," << best.risk << endl;
    myFile << fixed << setprecision(10) << "趨勢值," << best.trend << endl;
    myFile << "找到最佳解世代," << best.generation + 1 << endl;
    myFile << "找到最佳解實驗#," << best.exp + 1 << endl;
    myFile << "找到最佳解次數#," << best.find << endl
           << endl;

    vector<int> choose_n;
    for (int i = 0; i < N; i++)
    {
        if (best.choose[i] == 1)
        {
            choose_n.push_back(i);
        }
    }
    int n = choose_n.size(); //選了幾檔
    myFile << "投資組合檔數," << n << endl;
    myFile << "Stock#,"; //stock名
    for (int i = 0; i < n; i++)
    {
        myFile << dji[choose_n[i]].name << ",";
    }
    myFile << endl;
    myFile << "張數,";
    for (int i = 0; i < n; i++)
    {
        myFile << best.stock_num[choose_n[i]] << ",";
    }
    myFile << endl;
    myFile << "分配資金,";
    for (int i = 0; i < n; i++)
    {
        myFile << best.distribute_money[choose_n[i]] << ",";
    }
    myFile << endl;
    myFile << "剩餘資金,";
    for (int i = 0; i < n; i++)
    {
        myFile << best.remain_money[choose_n[i]] << ",";
    }
    myFile << best.remain_money[N] << ",";
    myFile << endl;
    int day = dji[0].price.size(); //天數
    for (int i = 0; i < day; i++)  //每日資金水位
    {
        myFile << "FS(" << i + 1 << "),";
        for (int j = 0; j < n; j++) //幾檔
        {
            myFile << fixed << setprecision(10) << best.stock_num[choose_n[j]] * dji[choose_n[j]].price[i] + (best.distribute_money[choose_n[j]] - best.stock_num[choose_n[j]] * dji[choose_n[j]].price[0]) << ",";
        }
        myFile << fixed << setprecision(10) << best.funding[i] << ",";
        myFile << endl;
    }
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
void M_csvioname(int year, int month)
{
    string input_name = "D:/LAB/c++/QTS/DJI_30/M2M/train_";
    string input_format = " Q1).csv";
    stringstream ss_input;
    ss_input << input_name << year << "_" << setw(2) << setfill('0') << month << "(" << year << input_format;
    input_csv = ss_input.str();

    string output_name = "train_result/M2M/quadratic_result_train_";
    string output_format = " Q1).csv";
    stringstream ss_output;
    ss_output << output_name << year << "_" << setw(2) << setfill('0') << month << "(" << year << output_format;
    output_csv = ss_output.str();
}