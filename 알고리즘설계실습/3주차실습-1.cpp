#include<iostream>
#include<ctime>
#define N 200
using namespace std;

int main() {
    clock_t start, end, take;

    int a[N][N];
    int b[N][N];
    int c[N][N];
    int d[N];

    for (int i = 0; i < N; i++)//�迭�� ���� �Է�
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = i;
            b[i][j] = i;
            c[i][j] = i;
        }  
    }

    start = clock(); //���۽ð� 
    for (int i = 0; i < N; i++) {//3�� for��
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                d[k] = a[i][j] * b[i][j] * c[i][j];
            }
        }
    }
    end = clock();// ����ð� 

    take = end - start;//�ɸ� �ð�

    cout << "n^3(Cubic complexity) �ҿ�ð� = " << double(take) << "ms" << endl ; // �ɸ��ð� ���
    return 0;
}