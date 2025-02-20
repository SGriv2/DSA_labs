#include <iostream>
#include <string>
#include <sys/time.h>

#include "rbtree.hpp"

#define SIZE 50001
#define STEP_SIZE_LOOKUP SIZE / 10
#define STEP_SIZE_DELETE (SIZE / 5000)

using std::cin, std::cout, std::endl, std::string;

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    string str[SIZE], *str1 = nullptr;
    Rbtree *tree = nullptr, *node = nullptr;

    rbInit();

    // заполнение дерева

    for (int i = 0; i < SIZE; i++)
    {
        cin >> str[i];

        node = rbCreate(&str[i], i);
        tree = rbAdd(tree, node);
    }

    // демонстрация логарифмической зависимости высоты
    // дерева от количества добавленных в него узлов

    cout << "Lookup: " << endl;
    for (int i = 0; i < SIZE; i += STEP_SIZE_LOOKUP)
    {
        if (i != 0)
        {
            double timeLookup = 0, tTime;

            for (int j = 0; j < i / 2; j++)
            {
                str1 = &str[getrand(0, i)];

                tTime = wtime();
                node = rbLookup(tree, str1);
                timeLookup += (wtime() - tTime);

                if (node->key == nullptr)
                {
                    cout << "0. Error: rbLookup" << endl;
                    return 1;
                }
            }
            cout << i << ": time = " << (timeLookup / (i / 2)) * 1000 << ", мс" << endl;
        }
    }

    // демонстрация удаления узлов из дерева

    for (int i = 0; i < SIZE; i += STEP_SIZE_DELETE)
    {
        tree = rbRemove(tree, &str[i]);
        node = rbLookup(tree, &str[i]);
        if (node->key != nullptr)
        {
            cout << "1. Error: rbRemove!" << endl;
            return 1;
        }
    }

    // проверка. Найдем каждый узел кроме удаленных узлов

    for (int i = 0; i < SIZE; i++)
    {
        if (i % STEP_SIZE_DELETE == 0)
            continue;

        node = rbLookup(tree, &str[i]);
        if (node->key == nullptr || *node->key != str[i])
        {
            cout << "2. Error: rbRemove!" << endl;
            return 1;
        }
    }

    // проверка. Добавим удаленные узлы и найдем каждый узел

    for (int i = 0; i < SIZE; i += STEP_SIZE_DELETE)
    {
        node = rbCreate(&str[i], i);
        tree = rbAdd(tree, node);
    }
    for (int i = 0; i < SIZE; i++)
    {
        node = rbLookup(tree, &str[i]);
        if (node->key == nullptr || *node->key != str[i])
        {
            cout << "3. Error: rbRemove!" << endl;
            return 1;
        }
    }

    cout << '\n'
         << "tests passed." << endl;

    free(tree);
    rbDeinit();

    return 0;
}
