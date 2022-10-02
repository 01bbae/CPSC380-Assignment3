#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

// int sortedarr[];
int arr[] = {98, 15, 59, 27, 19, 61, 47, 33, 94, 37};
int arrlen = sizeof(arr) / __SIZEOF_INT__;
int arr1len = (arrlen)/2;
int *arr1 = new int[arr1len];
int arr2len = arrlen - arr1len;
int *arr2 = new int[arr2len];
int *res = new int[sizeof(arr) / __SIZEOF_INT__];

void *subarraySorter(void *param);
void *merger(void *param);

int main(int argc, char const *argv[])
{
    // cout << "total length: " << arrlen << endl;
    // cout << "1 length: " << arr1len << endl;
    // cout << "2 length: " << arr2len << endl;
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
    // cout << "arr1" <<endl;
    // cout << "length of arr1: " << arr1len << endl;
    // for(int i = 0; i < arr1len; ++i){
    //     cout << arr1[i] << ", ";
    // }
    // cout << endl;
    // cout << "arr2" <<endl;
    // cout << "length of arr2: " << arr2len << endl;
    // for(int i = 0; i < arr2len; ++i){
    //     cout << arr2[i] << ", ";
    // }
    // cout << endl;

    // cout << "length of 1: " << arr1len <<endl;
    // cout << "length of 2: " << arr2len <<endl;


    /* create the thread */
    pthread_create(&tid1, &attr1, subarraySorter, arr1);
    pthread_create(&tid1, &attr2, subarraySorter, arr2);


    /* now wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_create(&tid3, &attr3, merger, NULL);

    pthread_join(tid3, NULL);
    for(int i=0; i< arrlen; ++i){
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}

void *subarraySorter(void *param)
{
    int * newarr;
    int newarrlen;
    if(param == arr1){
        // cout << "is array 1" << endl;
        newarr = arr1;
        newarrlen = arr1len;
    }else{
        // cout << "is array 2" << endl;
        newarr = arr2;
        newarrlen = arr2len;
    }
    // cout << "array length: " << newarrlen << endl;

    // cout << "Unsorted: " << endl;
    // for(int i = 0; i< newarrlen; ++i){
    //     cout << newarr[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < newarrlen-1; ++i)
    {
        int minindex = i;
        for (int j = i+1; j < newarrlen; ++j)
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

    // cout << "Sorted: " << endl;
    // for(int i = 0; i< newarrlen; ++i){
    //     cout << newarr[i] << " ";
    // }
    // cout << endl;
    if(param == arr1){
        arr1 = newarr;
    }else{
        arr2 =  newarr;
    }
    return nullptr;
    pthread_exit(0);
}

void *merger(void *param)
{
    int* newarr = new int[arr1len + arr2len];


    // cout << "arr1" <<endl;
    // cout << "length of arr1: " << arr1len << endl;
    // for(int i = 0; i < arr1len; ++i){
    //     cout << arr1[i] << ", ";
    // }
    // cout << endl;
    // cout << "arr2" <<endl;
    // cout << "length of arr2: " << arr2len << endl;
    // for(int i = 0; i < arr2len; ++i){
    //     cout << arr2[i] << ", ";
    // }
    // cout << endl;

    int i = 0;
    int j = 0;

    // cout << "i: " << i << " " << "j: " << j <<endl;
    while (i < arr1len and j < arr2len)
    {
        if (arr1[i] < arr2[j])
        {
            // cout << "merging arr1 element: " << arr1[i] << endl;
            newarr[i + j] = arr1[i];
            ++i;
            // cout << "i: " << i << " " << "j: " << j <<endl;
        }
        else if (arr1[i] > arr2[j])
        {
            // cout << "merging arr2 element: " << arr2[j] << endl;
            newarr[i + j] = arr2[j];
            ++j;
            // cout << "i: " << i << " " << "j: " << j <<endl;
        }
        else
        {
            // cout << "merging arr1 element: " << arr1[i] << " and " << "merging arr2 element: " << arr2[j] << endl;
            newarr[i + j] = arr1[i];
            ++i;
            newarr[i + j] = arr2[j];
            ++j;
            // cout << "i: " << i << " " << "j: " << j <<endl;
        }
    }
    if(i == arr1len){
        while(j < arr2len){
            newarr[i+j] = arr2[j];
            ++j;
        }

    }
    if (j == arr2len){
        while(i < arr1len){
            newarr[i+j] = arr1[i];
            ++i;
        }
    }

    
    // for(int i = 0; i< arrlen; ++i){
    //     cout << newarr[i] << ", ";
    // }
    // cout << endl;
    res = newarr;
    return nullptr;
    pthread_exit(0);
};