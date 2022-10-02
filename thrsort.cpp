#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

// int sortedarr[];
int arr[] = {2, 3, 1, 5, 4};
int arr1[(sizeof(arr) / __SIZEOF_INT__)/2];
int arr1len = (sizeof(arr) / __SIZEOF_INT__)/2;
int arr2[(sizeof(arr) / __SIZEOF_INT__) - (sizeof(arr1) / __SIZEOF_INT__)];
int arr2len = (sizeof(arr) / __SIZEOF_INT__) - (sizeof(arr1) / __SIZEOF_INT__);
int res[sizeof(arr) / __SIZEOF_INT__];

void *subarraySorter(void *param);
void *merger(void *param);

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2, tid3;        /* the thread identifier */
    pthread_attr_t attr1, attr2, attr3; /* set of attributes for the thread */

    int arrlen = sizeof(arr) / __SIZEOF_INT__;

    /* get the default attributes */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    

    /* Print arr1 and arr2 */

    copy(arr, arr+arr1len, arr1);
    copy(arr+arr1len, arr+arr2len+arr1len, arr2);
    cout << "arr1" <<endl;
    for(int i = 0; i < arr1len; ++i){
        cout << arr1[i] << ", ";
    }
    cout << endl;
    cout << "arr2" <<endl;
    for(int i = 0; i < arr2len; ++i){
        cout << arr2[i] << ", ";
    }
    cout << endl;

    // cout << "length of 1: " << arr1len <<endl;
    // cout << "length of 2: " << arr2len <<endl;


    /* create the thread */
    pthread_create(&tid1, &attr1, subarraySorter, arr1);
    pthread_create(&tid1, &attr2, subarraySorter, arr2);


    /* now wait for the thread to exit */
    if (pthread_join(tid1, NULL) == 0 and pthread_join(tid2, NULL) == 0)
    {
        pthread_create(&tid3, &attr3, merger, NULL);
    }
    else
    {
        perror("thread join failed");
    }
    pthread_join(tid3, NULL);
    for(int i = 0; i< arrlen; ++i){
        cout << res[i] << ", ";
    }
    cout << endl;

    return 0;
}

void *subarraySorter(void *param)
{
    int* newarr = (int *) param;
    int newarrlen = sizeof(newarr) / __SIZEOF_INT__;
    cout << "array length: " << newarrlen << endl;

    cout << "Print in thread: Unsorted" << endl;
    for(int i = 0; i< newarrlen; ++i){
        cout << newarr[i] << " ";
    }
    cout << endl;

    int minidx = 0;
    for (int i = 0; i < newarrlen -1; ++i)
    {
        for (int j = i+1; j < newarrlen; ++j)
        {
            if (newarr[minidx] > newarr[j])
            {
                minidx = j;
            }
        }
        newarr[i] = newarr[minidx];
    }

    cout << "Print in thread: Sorted" << endl;
    for(int i = 0; i< newarrlen; ++i){
        cout << newarr[i] << " ";
    }
    cout << endl;

    param = newarr; /* Not Sure*/
    return nullptr;
    pthread_exit(0);
}

void *merger(void *param)
{
    int newarr[sizeof(arr1) / __SIZEOF_INT__ + sizeof(arr2) / __SIZEOF_INT__];
    int i, j = 0;

    while (i < sizeof(arr1) / __SIZEOF_INT__ and j < sizeof(arr2) / __SIZEOF_INT__)
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
    memcpy(res,newarr,sizeof(newarr) / __SIZEOF_INT__);
    return nullptr;
    pthread_exit(0);
};