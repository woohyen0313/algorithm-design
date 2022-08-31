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

    for (int i = 0; i < N; i++)//배열에 정수 입력
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = i;
            b[i][j] = i;
            c[i][j] = i;
        }  
    }

    start = clock(); //시작시간 
    for (int i = 0; i < N; i++) {//3중 for문
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                d[k] = a[i][j] * b[i][j] * c[i][j];
            }
        }
    }
    end = clock();// 종료시간 

    take = end - start;//걸린 시간

    cout << "n^3(Cubic complexity) 소요시간 = " << double(take) << "ms" << endl ; // 걸린시간 출력
    return 0;
}