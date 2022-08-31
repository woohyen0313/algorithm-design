#include<iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

void swap(int *arr,int a, int b) {
	int temp=arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
void even(int* arr,int n) {
	for (int i = 0; i <n-1; i++)
	{
		if (i % 2 == 0) {
			if (arr[i] > arr[i + 1]) {
				swap(arr, i, i + 1);
			}
		}
	}
}
void odd(int* arr,int n) {
	for (int i = 0; i < n-1; i++)
	{
		if (i % 2 == 1) {
			if (arr[i] > arr[i + 1]) {
				swap(arr, i, i + 1);
			}
		}
	}
}
void evenoddsort(int *arr,int n) {


	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0) { 
			even(arr, n);

		}
		else {
			odd(arr, n);
			
		}
	}
}
void checksort(int a[], int n) {
	int i, sorted;
	sorted = 1;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] > a[i + 1]) {
			sorted = 0;
		}
		if (!sorted) {
			break;
		}
	}
	if (sorted) {
		cout << "���� �Ϸ�" << endl;
	}
	else {
		cout << "���� ����!!" << endl;
	}
}
void makerand(int arr[], int n) {

	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++) {
		arr[i] = rand()%1000;
	}
}

int main() {
	int arr[100000];
	int n = 100000;
	clock_t start, end, take;

	makerand(arr, n);
	start = clock();//���� �ð�
	evenoddsort(arr, n);
		end = clock();//���� �ð�
	take = end - start;//�ɸ� �ð�
	cout << " even-odd ���� ���� �ð� (N = " << n << "):" << double(take) << "ms" << endl;
	checksort(arr, n);

	return 0;
}