#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

// int sortedarr[];
int arr[] = {98, 15, 59, 27, 19, 61, 47, 33, 94, -37};
int arrlen = sizeof(arr) / __SIZEOF_INT__;
int arr1len = (arrlen) / 2;
int *arr1 = new int[arr1len];
int arr2len = arrlen - arr1len;
int *arr2 = new int[arr2len];
int *res = new int[sizeof(arr) / __SIZEOF_INT__];

void *subarraySorter(void *param);
void *merger(void *param);

int main(int argc, char const *argv[])
{

    pthread_t tid1, tid2, tid3;         /* the thread identifier */
    pthread_attr_t attr1, attr2, attr3; /* set of attributes for the thread */

    int arrlen = sizeof(arr) / __SIZEOF_INT__;

    /* get the default attributes */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    /* Print arr1 and arr2 */

    copy(arr, arr + arr1len, arr1);
    copy(arr + arr1len, arr + arr2len + arr1len, arr2);

    /* create the thread */
    pthread_create(&tid1, &attr1, subarraySorter, arr1);
    pthread_create(&tid1, &attr2, subarraySorter, arr2);

    /* now wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_create(&tid3, &attr3, merger, NULL);

    pthread_join(tid3, NULL);
    for (int i = 0; i < arrlen; ++i)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}

void *subarraySorter(void *param)
{
    int *newarr;
    int newarrlen;
    if (param == arr1)
    {
        newarr = arr1;
        newarrlen = arr1len;
    }
    else
    {
        newarr = arr2;
        newarrlen = arr2len;
    }

    for (int i = 0; i < newarrlen - 1; ++i)
    {
        int minindex = i;
        for (int j = i + 1; j < newarrlen; ++j)
        {
            if (newarr[minindex] > newarr[j])
            {
                minindex = j;
            }
        }
        int tmp = newarr[i];
        newarr[i] = newarr[minindex];
        newarr[minindex] = tmp;
    }

    if (param == arr1)
    {
        arr1 = newarr;
    }
    else
    {
        arr2 = newarr;
    }
    return nullptr;
    pthread_exit(0);
}

void *merger(void *param)
{
    int *newarr = new int[arr1len + arr2len];

    int i = 0;
    int j = 0;

    while (i < arr1len and j < arr2len)
    {
        if (arr1[i] < arr2[j])
        {
            newarr[i + j] = arr1[i];
            ++i;
        }
        else if (arr1[i] > arr2[j])
        {
            newarr[i + j] = arr2[j];
            ++j;
        }
        else
        {
            newarr[i + j] = arr1[i];
            ++i;
            newarr[i + j] = arr2[j];
            ++j;
        }
    }
    if (i == arr1len)
    {
        while (j < arr2len)
        {
            newarr[i + j] = arr2[j];
            ++j;
        }
    }
    if (j == arr2len)
    {
        while (i < arr1len)
        {
            newarr[i + j] = arr1[i];
            ++i;
        }
    }

    res = newarr;
    return nullptr;
    pthread_exit(0);
};