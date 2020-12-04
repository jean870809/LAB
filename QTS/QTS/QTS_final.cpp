#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <math.h>
#include <ctime>

using namespace std;
vector<double> _csv(string s);          //讀取股價
vector<string> _csvstring(string s);    //讀取檔名
double fundings(vector<int> num);       //適應函數
void writebest(vector<int> num, int t); //寫入CSV

vector<vector<string>> name;     //股票名
vector<vector<double>> data;     //全部資料
vector<vector<double>> tempdata; //所選資料
vector<vector<int>> solution;    //解集合

double change = 0.001;      //加減角度
int times = 1000;           //迭代次數
int p = 10;                 //族群規模
double allmoney = 10000000; //初始資金
int N = 10;                 //選幾檔計算
int main()
{

    //=================讀取
    ifstream inFile("train_2019_06(2019 Q1).csv", ios::in);
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
            vector<string> a = _csvstring(line);
            name.push_back(a);
            n++;
        }
        else
        {
            vector<double> a = _csv(line);
            data.push_back(a);
            n++;
        }
        //========================
    }

    vector<int> globalbest; //全域最佳組合
    //vector<int> globalworst;                 //全域最差組合
    vector<int> localbest;                   //當代最佳組合
    vector<int> localworst;                  //當代最差組合
    int bestt = 0, localbt = 0, localwt = 0; //最佳解世代
    int length = data[0].size();             //有幾檔
    vector<double> r(length, 0.5);           //機率矩陣

    //srand(time(NULL));
    srand(114);

    /*ofstream myFile; //write
    myFile.open("QTS1000LL.csv");
    ofstream rFile; //write
    rFile.open("Beta.csv");*/

    for (int t = 0; t < times; t++) //Generation
    {
        //myFile << "Generation," << t + 1 << endl;
        /*rFile << "實驗#," << 1 << ","
              << "世代#," << t + 1 << endl;*/
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
            if (globalbest.empty())
            {
                globalbest = solution[i];
            }
            if (localworst.empty())
            {
                localworst = solution[i];
                //globalworst = solution[i];
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
            globalbest = localbest;
            bestt = t;
        }
        /*if (fundings(localworst) < fundings(globalworst))
        {
            globalworst = localworst;
        }*/

        for (int n = 0; n < length; n++) //更新
        {
            if (localbest[n] == 1)
            {
                r[n] += change;
                //r[n] = min(r[n], 1.0);
            }
            if (localworst[n] == 1)
            {
                r[n] -= change;
                //r[n] = max(r[n], 0.0);
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
        myFile << endl;

        for (int i = 0; i < r.size(); i++)
        {
            rFile << r[i] << ",";
        }
        rFile << endl;*/

        solution.clear();
        localbest.clear();
        localworst.clear();
    }
    cout << fundings(globalbest) << endl;
    cout << bestt;
    //writebest(globalbest, bestt);

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

    tempdata.clear();
    stock.clear();
    funding.clear();
    //cout << trend << endl;
    return trend;
}

void writebest(vector<int> num, int t)
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
    myFile.open("QTS.csv");
    myFile << "代數," << times << endl;
    myFile << "粒子數," << p << endl;
    myFile << fixed << setprecision(10) << "旋轉角度," << change << endl;
    myFile << fixed << setprecision(10) << "初始資金," << allmoney << endl;
    myFile << fixed << setprecision(10) << "最後資金," << funding.back() << endl;
    myFile << fixed << setprecision(10) << "真實報酬," << funding.back() - allmoney << endl;
    myFile << fixed << setprecision(10) << "趨勢值," << trend << endl
           << endl;

    myFile << "選擇檔數," << n << endl;
    myFile << "找到最佳解世代," << t + 1 << endl;
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
}
