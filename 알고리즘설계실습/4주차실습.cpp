#include<iostream>
#include<cstdlib>
#include <ctime>

using namespace std;
void shellsort(int a[], int n) {
	int h;
	int i;
	for (h = 1; h < n; h = h * 5 + 1) {}
	h = h / 5;
	for (; h > 0; h = h / 5)
	{
		for (i = h; i < n; i++)
		{
			int temp = a[i];
			int j = i;
			while (j >= h && a[j - h] > temp) {
				a[j] = a[j - h];
				j = j - h;
			}
			a[j] = temp;
		}
	}

}


void checksort(int a[], int n) {
	int i, sorted;
	sorted = 1;
	for (int i = 0; i <n-1; i++)
	{
		if (a[i] > a[i+1]) {
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

void show(int a[], int n) {
	clock_t start, end, take;
	start = clock();//���� �ð�

	shellsort(a, n);//sorting

	end = clock();//���� �ð�

	take = end - start;//�ɸ� �ð�

	cout << "������: 5h+1, ���ҽ�: h/5 �� ���� ���� �ð� (N = " << n << "):" << double(take) << "ms" << endl;
	checksort(a, n);

}
void makerand(int a[],int n) {

	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}
}

int main() {
	int n;
	int* a;

	n = 100000;
	a = new int[n+1];

	makerand(a, n);
	shellsort(a, n);
	show(a, n);
	delete []a;

	n = 500000;
	a = new int[n + 1];

	makerand(a, n);
	shellsort(a, n);
	show(a, n);
	delete[]a;

	n = 1000000;
	a = new int[n + 1];

	makerand(a, n);
	shellsort(a, n);
	show(a, n);
	delete[]a;
	
	n = 5000000;
	a = new int[n + 1];

	makerand(a, n);
	shellsort(a, n);
	show(a, n);
	delete[]a;

	n = 10000000;
	a = new int[n + 1];

	makerand(a, n);
	shellsort(a, n);
	show(a, n);
	delete[]a;

	return 0;
}