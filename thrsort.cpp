#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

// int sortedarr[];
int arr[] = {2, 3, 1, 5, 4};
void *sublistSorter(void *param);

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;        /* the thread identifier */
    pthread_attr_t attr1, attr2; /* set of attributes for the thread */

    int arrlen = sizeof(arr) / __SIZEOF_INT__;

    /* initializing 2 split arrays */
    int arr1len, arr2len;
    if (arrlen % 2 == 0)
    {
        arr1len = floor(arrlen / 2);
        arr2len = floor(arrlen / 2 + 1);
    }
    int arr1[arr1len], arr2[arr2len];

    /* get the default attributes */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    /* create the thread */
    pthread_create(&tid1, &attr1, sublistSorter, &arr1);
    pthread_create(&tid1, &attr2, sublistSorter, &arr2);

    struct Args
    {
        int *args1;
        int *args2;
    };

    /* now wait for the thread to exit */
    if (pthread_join(tid1, &arr1) == 0 and pthread_join(tid2, &arr2) == 0)
    {
        Args args;
        args.args1 = &arr1;
        args.args2 = &arr2;
        pthread_create(&tid3, &attr3, merger, args);
    }
    else
    {
        perror("thread join failed");
    }
    pthread_join(tid3, &arr);
    cout << arr << endl;

    return 0;
}

void *sublistSorter(void *param)
{

    // int newarr[sizeof(param) / __SIZEOF_INT__];
    // for (int i = 0; i < sizeof(param) / __SIZEOF_INT__; ++i;)
    // {
    //     int min = param[i];
    //     for (int j = i + 1; j < sizeof(param) / __SIZEOF_INT__; ++j)
    //     {
    //         if (min > param[j])
    //         {
    //             min = param[j];
    //         }
    //     }
    //     newarr[i] = min;
    // }
    // param = newarr;
    pthread_exit(0);
};

void *merger(void *param)
{

    // int newarr[sizeof(arg1) / __SIZEOF_INT__ + sizeof(arg2) / __SIZEOF_INT__];
    // int i, j = 0;

    // while (i < sizeof(arg1) / __SIZEOF_INT__ and j < sizeof(arg2) / __SIZEOF_INT__)
    // {
    //     if (args1[i] < args[j])
    //     {
    //         newarr[i + j] = args1[i];
    //         ++i;
    //     }
    //     else if (args1[i] > args2[j])
    //     {
    //         newarr[i + j] = args2[j];
    //         ++j;
    //     }
    //     else
    //     {
    //         newarr[i + j] = args1[i];
    //         ++i;
    //         newarr[i + j] = args2[j];
    //         ++j;
    //     }
    // }
    // arr = newarr;
    pthread_exit(0);
};