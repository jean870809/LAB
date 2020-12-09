#include <bits/stdc++.h>

using namespace std;

#define M_PI 3.14159265358979323846 //PI

#define EXP_TIME 100  //實驗次數
#define dim 1         //維度
#define upper 3.5     //X範圍上界
#define lower -3.5    //X範圍下界
#define population 25 //粒子數

#define w 0.5  //慣性權重
#define c1 1.2 //Pbest權重
#define c2 1.5 //Gbest權重

struct particle
{
    float position[dim];       //位置
    float fitness;             //適應值
    float v[dim] = {0};        //速度
    float pbest_position[dim]; //自己曾經最好的位置
    float pbest_fitness;       //自己曾經最好的適應值
};

particle pop[population]; //粒子們
particle gbest;
int gbest_gen = 0;   //在第幾代找到最佳解
int gbest_count = 0; //花幾次計算次數找到最佳解
int cal_count = 0;   //計算次數

void initial();
void fit(int gen);
void move();
void fitness_f(particle &p)
{
    for (int j = 0; j < dim; j++)
    {
        //p.fitness += fabs(p.position[j]);
        p.fitness += (p.position[j] * p.position[j] - 10 * cos(2 * M_PI * p.position[j]));
    }
    p.fitness += 10 * dim;
}

int main()
{
    double average_find = 0;    //平均找到代數
    double average_count = 0;   //平均找到計算次數
    double average_fitness = 0; //平均找到適應值
    ofstream output;
    output.open("output2.csv");
    output << "實驗#,"
           << "GBEST,"
           << "GBEST找到世代,"
           << "GBEST找到計算次數" << endl;
    for (int exp = 0; exp < EXP_TIME; exp++)
    {
        initial();
        cal_count = 0;
        for (int i = 0; i < 300; i++)
        {
            //cout << "====iteration" << i + 2 << "=====" << endl;
            fit(i + 2);
            move();
        }
        cout << "===" << exp + 1 << "====" << endl;
        cout << "===gbest=== " << gbest_gen << ": ";
        cout << gbest.fitness << endl;
        cout << "===Count=== " << gbest_count << endl;
        output << exp + 1 << "," << gbest.fitness << "," << gbest_gen << "," << gbest_count << endl;
        average_find += gbest_gen;
        average_count += gbest_count;
        average_fitness += gbest.fitness;
    }
    cout << "EXP:" << EXP_TIME << endl;
    cout << "w:" << w << ",c1: " << c1 << ",c2: " << c2 << endl;
    cout << "AVE_GEN: " << average_find / EXP_TIME << endl;
    cout << "AVE_FIT: " << average_fitness / EXP_TIME << endl;
    cout << "AVE_COUNT: " << average_count / EXP_TIME << endl;

    output << "AVE_GEN: ," << average_find / EXP_TIME << endl;
    output << "AVE_FIT: ," << average_fitness / EXP_TIME << endl;
    output << "AVE_COUNT: ," << average_count / EXP_TIME << endl;

    return 0;
}
void initial()
{
    float length = upper - lower;
    for (int i = 0; i < population; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            pop[i].position[j] = ((float)rand() / RAND_MAX) * length + lower;
        }
        pop[i].pbest_fitness = 10000;
    }
    gbest.fitness = 10000;
    gbest_count = 0;
    gbest_gen = 0;
}
void fit(int gen)
{

    for (int i = 0; i < population; i++)
    {
        pop[i].fitness = 0;
        fitness_f(pop[i]);
        cal_count++;
        if (pop[i].fitness < pop[i].pbest_fitness)
        {
            pop[i].pbest_fitness = pop[i].fitness;
            for (int j = 0; j < dim; j++)
            {
                pop[i].pbest_position[j] = pop[i].position[j];
            }
        }
        if (pop[i].pbest_fitness < gbest.fitness)
        {
            gbest.fitness = pop[i].pbest_fitness;
            gbest_gen = gen;
            gbest_count = cal_count;
            for (int j = 0; j < dim; j++)
            {
                gbest.position[j] = pop[i].pbest_position[j];
            }
        }
    }
}
void move()
{
    float r1 = 0, r2 = 0;
    for (int i = 0; i < population; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            r1 = (float)rand() / RAND_MAX;
            r2 = (float)rand() / RAND_MAX;

            pop[i].v[j] = w * pop[i].v[j] + c1 * r1 * (pop[i].pbest_position[j] - pop[i].position[j]) + c2 * r2 * (gbest.position[j] - pop[i].position[j]);
            pop[i].position[j] = pop[i].position[j] + pop[i].v[j];
        }
    }
}
