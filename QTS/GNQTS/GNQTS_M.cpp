#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <math.h>
#include <ctime>

using namespace std;
vector<double> _csv(string s);                              //讀取股價
vector<string> _csvstring(string s);                        //讀取檔名
double fundings(vector<int> num);                           //適應函數 //計算趨勢值
void writebest(vector<int> num, int t, int tt, string csv); //寫入CSV

vector<vector<string>> name;     //股票名
vector<vector<double>> data;     //全部資料
vector<vector<double>> tempdata; //所選資料
vector<vector<int>> solution;    //解集合

double change = 0.0004;     //加減角度
int times = 10000;          //迭代次數
int p = 10;                 //族群規模
double allmoney = 10000000; //初始資金
int N = 30;                 //選幾檔計算
int T = 50;                 //實驗次數

int main()
{
    srand(114);
    //=================讀取
    string input_csv;
    string output_csv;
    for (int y = 2009; y <= 2018; y++)
    {
        for (int m = 1; m <= 12; m++)
        {
            /*if (y == 2009)
            {
                m = 12;
            }
            if (y == 2019 && m == 12)
            {
                break;
            }*/
            string input_name = "D:/LAB/c++/QTS/DJI_30/M#/train_";
            string input_format = " Q1).csv";
            stringstream ss_input;
            ss_input << input_name << y << "_" << setw(2) << setfill('0') << m << "(" << y << input_format;
            input_csv = ss_input.str();

            string output_name = "train_result/M#/train_";
            string output_format = " Q1)_result.csv";
            stringstream ss_output;
            ss_output << output_name << y << "_" << setw(2) << setfill('0') << m << "(" << y << output_format;
            output_csv = ss_output.str();

            cout << input_csv << endl;
            cout << output_csv << endl;
            ifstream inFile(input_csv, ios::in);
            if (!inFile)
            {
                cout << "開啟檔案失敗！" << endl;
            }
            string line;
            int n = 0;
            while (getline(inFile, line))
            {
                //========================
                if (n == 0)
                {
                    vector<string> b = _csvstring(line);
                    name.push_back(b);
                    n++;
                }
                else
                {
                    vector<double> c = _csv(line);
                    data.push_back(c);
                    n++;
                }
                //========================
            }
            int length = data[0].size(); //有幾檔

            vector<int> Gglobalbest(length, 0); //全域最佳組合
            int EXP_Gbest = 0, GEN_Gbest = 0;   //全域最佳解之實驗代/世代

            for (int tt = 0; tt < T; tt++)
            {
                vector<int> globalbest(length, 0);  //當代實驗最佳組合
                vector<int> globalworst(length, 0); //當代實驗最差組合
                vector<int> pre_globalbest(length, 0);
                vector<int> localbest;                                    //當代最佳組合
                vector<int> localworst;                                   //當代最差組合
                int GEN_best = 0, localbt = 0, localwt = 0, EXP_best = 0; //最佳解世代
                vector<double> r(length, 0.5);                            //機率矩陣

                for (int t = 0; t < times; t++) //Generation
                {
                    for (int i = 0; i < p; i++)
                    {
                        vector<int> a;
                        double x = 0;
                        for (int j = 0; j < length; j++)
                        {
                            x = (double)rand() / RAND_MAX; // 0-1小數
                            if (x > r[j])                  //測量解
                            {
                                a.push_back(0);
                            }
                            else
                            {
                                a.push_back(1);
                            }
                        }
                        solution.push_back(a);
                        a.clear(); //釋放記憶體
                    }
                    for (int i = 0; i < p; i++) //測量
                    {
                        if (localbest.empty())
                        {
                            localbest = solution[i];
                            localbt = i;
                        }
                        if (localworst.empty())
                        {
                            localworst = solution[i];
                            localwt = i;
                        }
                        if (fundings(solution[i]) > fundings(localbest))
                        {
                            localbest.clear();
                            localbest = solution[i];
                            localbt = i;
                        }
                        if (fundings(solution[i]) < fundings(localworst))
                        {
                            localworst.clear();
                            localworst = solution[i];
                            localwt = i;
                        }
                    }
                    if (fundings(localbest) > fundings(globalbest))
                    {
                        pre_globalbest = globalbest;
                        globalbest = localbest; //新的gbest
                        GEN_best = t;
                        EXP_best = tt;
                    }
                    if (fundings(globalbest) > fundings(Gglobalbest))
                    {
                        Gglobalbest = globalbest;
                        EXP_Gbest = EXP_best;
                        GEN_Gbest = GEN_best;
                    }

                    for (int n = 0; n < length; n++) //更新機率矩陣
                    {
                        if (globalbest[n] == 1 && localworst[n] == 0)
                        {
                            if (r[n] < 0.5) //not-gate -1
                            {
                                r[n] = 1 - r[n];
                            }
                            r[n] += change;
                        }
                        if (globalbest[n] == 0 && localworst[n] == 1)
                        {
                            if (r[n] > 0.5)
                            {
                                r[n] = 1 - r[n];
                            }
                            r[n] -= change;
                        }
                    }

                    solution.clear();
                    localbest.clear();
                    localworst.clear();
                }
                globalbest.clear();
                pre_globalbest.clear();
                globalworst.clear();
                r.clear();
            }
            writebest(Gglobalbest, GEN_Gbest, EXP_Gbest, output_csv);
            name.clear();
            data.clear();
            inFile.close();
        }
    }
    return 0;
}

vector<double> _csv(string s)
{
    vector<double> arr;
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            arr.push_back(atof(token.c_str()));
            i++;
        }
    }

    return arr;
}

vector<string> _csvstring(string s)
{
    vector<string> arr;
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            arr.push_back(token);
            i++;
        }
    }

    return arr;
}

double fundings(vector<int> num)
{
    int n = 0; //檔數
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == 1)
        {
            n++;
            vector<double> a;
            for (int j = 0; j < data.size(); j++)
            {
                a.push_back(data[j][i]);
            }
            tempdata.push_back(a);
            a.clear();
        }
    }
    if (n == 0)
    {
        return 0;
    }
    else
    {
        int distrimoney = allmoney / n; //各檔分配資金
        vector<int> stock;              //可買股數
        for (int i = 0; i < n; i++)
        {
            stock.push_back(distrimoney / (tempdata[i][0]));
        }
        double remainmoney = 0; //剩餘資金
        for (int i = 0; i < n; i++)
        {
            remainmoney += distrimoney - stock[i] * tempdata[i][0];
        }
        remainmoney += (allmoney - distrimoney * n);
        vector<double> funding; //資金水位

        for (int i = 0; i < tempdata[0].size(); i++) //day
        {
            double temp = 0;
            for (int j = 0; j < n; j++) //幾檔
            {

                temp += stock[j] * tempdata[j][i]; //每日資金水位
            }
            funding.push_back(remainmoney + temp);
        }

        // 趨勢值
        double m;     //每日預期報酬
        double risk;  // 每日風險
        double trend; // 趨勢值
        double temp1 = 0, temp2 = 0;
        for (int i = 0; i < tempdata[0].size(); i++)
        {
            temp1 += (i + 1) * funding[i] - (i + 1) * allmoney;
            temp2 += (i + 1) * (i + 1);
        }
        m = temp1 / temp2;
        double temp = 0;
        for (int i = 0; i < tempdata[0].size(); i++)
        {
            temp += (funding[i] - (m * (i + 1) + allmoney)) * (funding[i] - (m * (i + 1) + allmoney));
        }
        risk = sqrt(temp / (tempdata[0].size()));
        if (m < 0)
        {
            trend = m * risk;
        }
        else
        {
            trend = m / risk;
        }

        tempdata.clear();
        stock.clear();
        funding.clear();
        return trend;
    }
}
void writebest(vector<int> num, int t, int tt, string csv)
{
    int n = 0; //檔數
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == 1)
        {
            n++;
            vector<double> a;
            for (int j = 0; j < data.size(); j++)
            {
                a.push_back(data[j][i]);
            }
            tempdata.push_back(a);
        }
    }
    int distrimoney = allmoney / n; //各檔分配資金
    vector<int> stock;              //可買股數
    for (int i = 0; i < n; i++)
    {
        stock.push_back(distrimoney / (tempdata[i][0]));
    }
    double remainmoney = 0; //剩餘資金
    for (int i = 0; i < n; i++)
    {
        remainmoney += distrimoney - stock[i] * tempdata[i][0];
    }
    remainmoney += (allmoney - distrimoney * n);

    vector<double> funding; //資金水位

    for (int i = 0; i < tempdata[0].size(); i++) //day
    {
        double temp = 0;
        for (int j = 0; j < n; j++) //幾檔
        {

            temp += stock[j] * tempdata[j][i]; //每日資金水位
        }
        funding.push_back(remainmoney + temp);
    }

    // 趨勢值
    double m;     //每日預期報酬
    double risk;  // 每日風險
    double trend; // 趨勢值
    double temp1 = 0, temp2 = 0;
    for (int i = 0; i < tempdata[0].size(); i++)
    {
        temp1 += (i + 1) * funding[i] - (i + 1) * allmoney;
        temp2 += (i + 1) * (i + 1);
    }
    m = temp1 / temp2;
    double temp = 0;
    for (int i = 0; i < tempdata[0].size(); i++)
    {
        temp += (funding[i] - (m * (i + 1) + allmoney)) * (funding[i] - (m * (i + 1) + allmoney));
    }
    risk = sqrt(temp / (tempdata[0].size()));
    trend = m / risk;

    //write
    ofstream myFile;
    myFile.open(csv);
    myFile << "代數," << times << endl;
    myFile << "粒子數," << p << endl;
    myFile << fixed << setprecision(10) << "旋轉角度," << change << endl;
    myFile << "實驗次數," << T << endl
           << endl;
    myFile << fixed << setprecision(10) << "初始資金," << allmoney << endl;
    myFile << fixed << setprecision(10) << "最後資金," << funding.back() << endl;
    myFile << fixed << setprecision(10) << "真實報酬," << funding.back() - allmoney << endl;
    myFile << fixed << setprecision(10) << "趨勢值," << trend << endl
           << endl;

    myFile << "選擇檔數," << n << endl;
    myFile << "找到最佳解世代," << t + 1 << endl;
    myFile << "找到最佳解實驗," << tt + 1 << endl;
    myFile << "Stock#,"; //stock名
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == 1)
        {
            myFile << name[0][i] << ",";
        }
    }
    myFile << endl;
    myFile << "分配資金,"; //每檔分配資金
    for (int i = 0; i < n; i++)
    {

        myFile << distrimoney << ",";
    }
    myFile << endl;
    myFile << "張數,"; //每檔可買張數
    for (int i = 0; i < n; i++)
    {

        myFile << stock[i] << ",";
    }
    myFile << endl;
    myFile << "剩餘資金,"; //每檔剩餘資金
    for (int i = 0; i < n; i++)
    {

        myFile << fixed << setprecision(10) << distrimoney - stock[i] * tempdata[i][0] << ",";
    }
    myFile << endl;

    for (int i = 0; i < tempdata[0].size(); i++) //每日資金水位
    {
        myFile << "FS(" << i + 1 << "),";
        for (int j = 0; j < n; j++) //幾檔
        {
            myFile << fixed << setprecision(10) << stock[j] * tempdata[j][i] + (distrimoney - stock[j] * tempdata[j][0]) << ",";
        }
        myFile << fixed << setprecision(10) << funding[i] << ",";
        myFile << endl;
    }
    myFile.close();
}
