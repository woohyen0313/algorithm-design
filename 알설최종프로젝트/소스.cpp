#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;

int dist[1500][1500];
int vist[1500][100000];
bool visited[1500];
int N;
int maximum = 100000;



int dp(int cur, int start, int visited ) {
    //비트마스킹 기법을 통해 dptsp를 구현하였다. 집합을 이용하여 dp를 구현해야하기 때문에 
    //비트 마스킹을 통해 집합을 표현하였다.

    if (visited == ((1 << N) - 1)) {// 모든 도시를 방문한 것에 대한 경우 처리
            return dist[cur][start];
    }

    if (vist[cur][visited] != maximum)//vis의 값을 모두 maximum으로 초기화 해놓았다 이후 maximum이 아니면 길이 있는 것이다.
        return vist[cur][visited];//정상적인 값을 리턴해준다
    
    for (int i = 0; i < N; i++) { //방문해야하는 도시의 수를 반복하였다
        if ((visited & (1 << i) )|| cur == i)//자기 자신이거나 이미 방문한 경우를 넘어가게 한다.
            continue;
        vist[cur][visited] = min(vist[cur][visited], (dist[cur][i] + dp(i, start, visited + (1 << i))));// tsp dp 점화식을 구현한 부분으로 재귀적으로 작성하였다. dp테이블을 채운다

    }

    return vist[cur][visited];
}

int main() {
 
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> dist[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 100000; j++) {
            vist[i][j]=maximum;
        }
    }


    cout << dp(0,0,1) << endl;




    return 0;
}