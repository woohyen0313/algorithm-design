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
    //��Ʈ����ŷ ����� ���� dptsp�� �����Ͽ���. ������ �̿��Ͽ� dp�� �����ؾ��ϱ� ������ 
    //��Ʈ ����ŷ�� ���� ������ ǥ���Ͽ���.

    if (visited == ((1 << N) - 1)) {// ��� ���ø� �湮�� �Ϳ� ���� ��� ó��
            return dist[cur][start];
    }

    if (vist[cur][visited] != maximum)//vis�� ���� ��� maximum���� �ʱ�ȭ �س��Ҵ� ���� maximum�� �ƴϸ� ���� �ִ� ���̴�.
        return vist[cur][visited];//�������� ���� �������ش�
    
    for (int i = 0; i < N; i++) { //�湮�ؾ��ϴ� ������ ���� �ݺ��Ͽ���
        if ((visited & (1 << i) )|| cur == i)//�ڱ� �ڽ��̰ų� �̹� �湮�� ��츦 �Ѿ�� �Ѵ�.
            continue;
        vist[cur][visited] = min(vist[cur][visited], (dist[cur][i] + dp(i, start, visited + (1 << i))));// tsp dp ��ȭ���� ������ �κ����� ��������� �ۼ��Ͽ���. dp���̺��� ä���

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