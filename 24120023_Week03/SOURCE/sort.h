#ifndef FUNCTION_H
#define FUNCTION_H
#include<iostream>
#include<chrono>
#include<time.h>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

template <class T>
void HoanVi(T &a, T &b);
void GenerateRandomData(int a[], int n);
// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n);
// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n);
// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

void display (int a[], int n, string path);

//Bubble Sort 
void bubble(int a[], int n);
void bblSort(int a[], int n);

//Insertion Sort
void insertIth(int a[], int n, int i);
void insSort(int a[], int n);

//Selection Sort
int locOfSmallest(int a[], int s, int e);
void SelSort(int a[], int n);

//Shaker Sort
void shakerSort(int a[], int n);

//Shell Sort
void shellSort(int a[], int n);

//Heap Sort
void heapRebuild(int a[], int pos, int n);
void heapConstruct(int a[], int n);
void heapSort(int a[], int n);

//Merge Sort
void combine(int a[], int s, int m, int e);
void mrgSort(int a[], int s, int e);
void mrgSort(int a[], int n);

//Counting Sort
void countingSort(int a[], int n);

//Quick Sort
int partition(int a[], int first, int last);
void quickSort(int a[], int first, int last);

//Radix Sort
void radixSort(int a[], int n);

//Flash Sort 
void flashSort(int a[], int n);
#endif
