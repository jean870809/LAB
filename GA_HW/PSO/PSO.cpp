#include <bits/stdc++.h>

using namespace std;

#define dim 1        //維度
#define upper 100    //X範圍上界
#define lower -100   //X範圍下界
#define population 5 //粒子數

#define w 0.5  //慣性權重
#define c1 1.0 //Pbest權重
#define c2 1.2 //Gbest權重

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
void initial();
void fit();
void move();
float fitness_f(float num)
{
    return fabs(num);
}

int main()
{
    initial();
    for (int i = 0; i < 350; i++)
    {
        cout << "====iteration" << i + 2 << "=====" << endl;
        fit();
        move();
    }
    return 0;
}
void initial()
{
    double length = upper - lower;
    for (int i = 0; i < population; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            pop[i].position[j] = ((float)rand() / RAND_MAX) * length + lower;
            cout << pop[i].position[j] << ",";
        }
        pop[i].pbest_fitness = 10000;
        cout << endl;
    }
    gbest.fitness = 10000;
}
void fit()
{
    cout << "fitness" << endl;

    for (int i = 0; i < population; i++)
    {
        pop[i].fitness = 0;
        for (int j = 0; j < dim; j++)
        {
            pop[i].fitness += fitness_f(pop[i].position[j]);
        }
        cout << pop[i].fitness << endl;
        if (pop[i].fitness < pop[i].pbest_fitness)
        {
            pop[i].pbest_fitness = pop[i].fitness;
            for (int j = 0; j < dim; j++)
            {
                pop[i].pbest_position[j] = pop[i].position[j];
            }
            cout << "===pbest===" << i << ":";
            cout << pop[i].pbest_fitness << endl;
        }
        if (pop[i].pbest_fitness < gbest.fitness)
        {
            gbest.fitness = pop[i].pbest_fitness;
            cout << "===gbest===" << gbest.fitness << endl;
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
        cout << "pop: " << i << ": ";
        for (int j = 0; j < dim; j++)
        {
            //r1 = rand() / RAND_MAX;
            //r2 = rand() / RAND_MAX;

            pop[i].v[j] = w * pop[i].v[j] + c1 * (pop[i].pbest_position[j] - pop[i].position[j]) + c2 * (gbest.position[j] - pop[i].position[j]);
            cout << pop[i].v[j] << "; ";
            pop[i].position[j] = pop[i].position[j] + pop[i].v[j];
            cout << pop[i].position[j] << "; ";
        }
        cout << endl;
    }
}