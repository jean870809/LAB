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
double fundings(vector<int> num);                           //適應函數 //計算趨勢值
void writebest(vector<int> num, int t, int tt, string csv); //寫入CSV

string name[30] = {"AAPL", "AXP", "BA", "CAT", "CSCO", "CVX", "DIS", "DD", "GS", "HD", "IBM", "INTC", "JNJ", "JPM", "KO", "MCD", "MMM", "MRK", "MSFT", "NKE", "PFE", "PG", "TRV", "UNH", "UTX", "V", "VZ", "WBA", "WMT", "XOM"}; //股票名
vector<vector<double>> data;                                                                                                                                                                                                     //全部資料
vector<vector<double>> tempdata;                                                                                                                                                                                                 //所選資料
vector<vector<int>> solution;                                                                                                                                                                                                    //解集合

double change = 0.0004;     //加減角度
int times = 10000;          //迭代次數
int p = 10;                 //族群規模
double allmoney = 10000000; //初始資金
int N = 30;                 //選幾檔計算
int T = 50;                 //實驗次數

int main()
{

    //=================讀取
    string input_csv = "D:/LAB/c++/QTS/DJI_30/Q2M/train_2009_10-12(2009 Q1).csv";
    string output_csv = "train_2009_10-12(2009 Q1)_result.csv";

    ifstream inFile(input_csv, ios::in);
    //"train_result/train_2010_01(2010 Q1)_result.csv"; //output file
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

    //srand(time(NULL));
    srand(114);

    /*ofstream myFile; //write
    myFile.open("GNQTS_50.csv");*/
    /*ofstream rFile; //write
    rFile.open("GNQTS_1_Beta.csv");*/
    /*ofstream GFile; //write
    GFile.open("GNQTS_50_1_GBEST.csv");*/
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
            //myFile << "Generation," << t + 1 << endl;

            //rFile << "實驗#," << tt + 1 << ",世代#," << t + 1 << endl;

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
                for (int i = 0; i < length; i++) //====not-gate -3
                {
                    /*if (localbest[i] != globalbest[i]) //localbest - globalbest新 globalbest-globalbest舊
                    {
                        if((localbest[i]==1 && r[i] < 0.5) || (localbest[i]==0 && r[i] > 0.5)){
                            r[i] = 1 - r[i];
                        }
                        
                    }*/
                }
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
                /*if (pre_globalbest[n] != globalbest[n]) //localbest - globalbest新 globalbest-globalbest舊 not-gate -2
                {
                    r[n] = 1 - r[n];
                }*/
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

            /*myFile << "Best(" << (localbt + 1) << ")," << fundings(localbest) << endl;
            myFile << "Worst(" << (localwt + 1) << ")," << fundings(localworst) << endl;
            myFile << "GBest(" << (bestt + 1) << ")," << fundings(globalbest) << endl;
            myFile << "Best_p" << endl;
            for (int i = 0; i < localbest.size(); i++)
            {
                myFile << localbest[i] << ",";
            }
            myFile << endl;
            myFile << "Worst_p" << endl;
            for (int i = 0; i < localworst.size(); i++)
            {
                myFile << localworst[i] << ",";
            }
            myFile << endl;
            myFile << "GBest_p" << endl;
            for (int i = 0; i < globalbest.size(); i++)
            {
                myFile << globalbest[i] << ",";
            }
            myFile << endl;
            myFile << "Beta" << endl;
            for (int i = 0; i < r.size(); i++)
            {
                myFile << r[i] << ",";
            }
            myFile << endl;
            myFile << endl;*/

            /*for (int i = 0; i < r.size(); i++)
            {
                rFile << r[i] << ",";
            }
            rFile << endl;*/

            solution.clear();
            localbest.clear();
            localworst.clear();
        }
        //GFile << "實驗#," << tt + 1 << ",Gbest_世代#," << GEN_best + 1 << ",GBest," << fundings(globalbest) << endl;
        globalbest.clear();
        pre_globalbest.clear();
        globalworst.clear();
        r.clear();
    }
    writebest(Gglobalbest, GEN_Gbest, EXP_Gbest, output_csv);
    inFile.close();

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
    myFile << endl
           << endl;
    myFile << fixed << setprecision(10) << "預期報酬," << m << endl;
    myFile << fixed << setprecision(10) << "風險," << risk << endl;
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
            myFile << name[i] << ",";
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
