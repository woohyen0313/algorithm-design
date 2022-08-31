#include<iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

void maxHeapify(int a[], int h, int m) { 
    int v = a[h]; 
    int j ; 
    for (j = 2 * h; j <= m; j = j * 2) { 
        if (j < m && a[j] < a[j + 1]) j++; 
        if (v >= a[j]) break; 
        else a[j / 2] = a[j]; 
    }
    a[j / 2] = v;
}

void minHeapify(int a[], int h, int m) { 
    
    int v = a[h];
    int j = 0;

    for (j = 2 * h; j <= m; j = j * 2) {
        if (j<m && a[j]>a[j + 1]) j++;
        if (v <= a[j]) break; 
        else a[j / 2] = a[j];
    }
    a[j / 2] = v;
}

void minHeapSort(int a[], int n) {
    for (int i = n / 2; i >= 1; i--) { 
        minHeapify(a, i, n);
    }
    for (int i = n - 1; i >= 1; i--) { 
        swap(a[1], a[i + 1]); 
        minHeapify(a, 1, i);
    }
}


void maxHeapSort(int a[], int n) { 
    for (int i = n / 2; i >= 1; i--) {
        maxHeapify(a, i, n);
    }
    for (int i = n - 1; i >= 1; i--) {
        swap(a[1], a[i + 1]);
        maxHeapify(a, 1, i);
    }
}
void Maxcheck(int a[], int n) {
    int i, sorted;
    sorted = 1;

    for (i = 1; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            sorted = 0;
        }
        if (!sorted) {
            break;
        }
    }
    if (sorted == 1) {
        cout << "MaxHeap Sorting complete!" << endl;
    }
    else {
        cout << "Error during sorting..." << endl;
    }

}

void Mincheck(int a[], int n) {
    int i, sorted;
    sorted = 1;

    for (i = 1; i < n - 1; i++) {
        if (a[i] < a[i + 1]) {
            sorted = 0;
        }
        if (!sorted) {
            break;
        }
    }
    if (sorted == 1) {
        cout << "MinHeap Sorting complete!" << endl;
    }
    else {
        cout << "Error during sorting..." << endl;
    }

}

void makerand(int arr[], int n) {

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}
int main() {
    int a[100000];
    int n = 100000;
    clock_t start, end, take;

    makerand(a, n);
    start = clock();//시작 시간
    maxHeapSort(a,n);
    end = clock();//종료 시간
    take = end - start;//걸린 시간
    cout << "Maxheap sorting (N=" << n << ") time cost:" << double(take) << "ms" << endl;
    Maxcheck(a, n);

    makerand(a, n);
    start = clock();//시작 시간
    minHeapSort(a, n);
    end = clock();//종료 시간
    take = end - start;//걸린 시간
    cout << "Maxheap sorting (N=" << n << ") time cost:" << double(take) << "ms" << endl;
    Mincheck(a, n);
    return 0;
}