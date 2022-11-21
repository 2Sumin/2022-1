#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

/*
input-1
4 9
1 2 2
1 3 9
2 1 1
2 3 6
2 4 4
3 2 7
3 4 8
4 1 6
4 2 3
output-1
21
1 3 4 2 1
1 7 21
2 0 1
2 4 10
2 6 20
3 1 8
3 4 14
3 5 12
4 0 6
4 1 4
*/
/*
TSP - DP
W : 주어진 그래프 G=(V,E)의 인접 행렬
V : 모든 도시의 집합
A : V의 부분 집합
D[vi][A] : A에 속한 도시를 각각 한번씩만 거쳐서 vi->v1으로 가는 최단경로의 길이

 if A = {v3,v4}
 D[v2][A]=min(length(v2,v3,v4,v1),length(v2,v4,v3,v2)) = min(20,INF) = 20
<재귀 관계식>
vj가 A에 포함되는 정점이라 했을 때
D[vi][A]=min(W[i][j]+D[vj][A-{vj}]) (A가 공집합이 아닐 때)
: vi->vj로 다이렉트로 + vj->v1로 A 집합에서 vj뺀 나머지 노드 지나서
D[vi][A]=W[i][1] (A가 공집합일 때는 아무것도 안 거치고 바로 vi->v1)

*/

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

#define INF 99999

int n, m, minlength;

// A집합에 i가 속하는지
bool isIn(int i, int A)
{
    return (A & (1 << (i - 2))) != 0;
}

// A의 원소의 개수가 k개인가?
int count(int A)
{
    int cnt = 0;
    for (; A != 0; A >>= 1)
        if (A & 1)
            cnt++;
    return cnt;
}

// A집합에서 j원소만 제외한 것 (차집합)
int diff(int A, int j)
{
    return (A & ~(1 << (j - 2)));
}

int minimum(int n, int i, int &minJ, int A, matrix2 &W, matrix2 &D)
{ // vi -> vj 최솟값
    int minV = INF, value;
    for (int j = 2; j <= n; j++)
    {
        if (!isIn(j, A))
            continue;
        // vj 가 A의 원소일 때만
        //[diff(A,j)] = [A-{vj}] (차집합)
        int value = W[i][j] + D[j][diff(A, j)];
        if (minV > value)
        {
            minV = value;
            minJ = j;
        }
    }
    return minV;
}

void travel(int n, matrix2 &W, matrix2 &D, matrix2 &P, int &minlength)
{
    // D[1,,,n][subset of V-{v1}]
    int i, j, k, A;
    int subset_size = pow(2, n - 1);

    // A집합이 0이면(공집합이면) 아무것도 안 거치고 바로 vi->v1 (W[i][1])
    for (i = 2; i <= n; i++)
        D[i][0] = W[i][1];
    // k: 부분집합의 원소 개수
    for (k = 1; k <= n - 2; k++)
        // V-{v1}의 모든 부분집합 A에 대해 k개의 정점을 가지고 있다면
        for (A = 0; A < subset_size; A++)
        {
            // A의 원소의 개수가 k일 때 처리
            if (count(A) != k)
                continue;
            for (i = 2; i <= n; i++)
            {
                // vi가 A에 속해있으면 안 됨 (vi->A->v1)
                if (isIn(i, A))
                    continue;
                // vi가 A의 원소가 아니라면
                D[i][A] = minimum(n, i, j, A, W, D);
                P[i][A] = j; //나중에 경로 찾기를 위해
            }
        }
    A = subset_size - 1; // A = V - {v1}
    D[1][A] = minimum(n, 1, j, A, W, D);
    P[1][A] = j;
    minlength = D[1][A];
}

void tour(int v, int A, matrix2 &P)
{
    int k = P[v][A];
    if (A == 0)
    {
        cout << "1" << endl;
        return;
    }
    else
    {
        cout << k << " ";
        tour(k, diff(A, k), P);
    }
}

int main()
{
    // 입력 1 - 첫 줄에 그래프의 정점 개수 n과 그래프의 간선 개수 m이 주어진다.
    cin >> n >> m;
    // 입력 2 - 둘째 줄부터 m개의 간선이 u, v, w의 형태로 주어진다.
    matrix2 D, W, P;
    D.resize(n + 1, matrix1(pow(2, n - 1), 0));
    W.resize(n + 1, matrix1(n + 1, INF));
    P.resize(n + 1, matrix1(pow(2, n - 1), 0));

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        W[u][v] = w;
    }

    for (int i = 1; i <= n; i++)
        W[i][i] = 0;

    // 출력 1 - 첫 줄에 순회 경로의 최적 경로값 minlength를 출력한다.
    travel(n, W, D, P, minlength);
    cout << "min length: " << minlength << endl;

    // 출력 2 - 둘째 줄에 1번 정점에서 시작하여 1번 정점으로 되돌아 오는 최적 경로를 출력한다.
    cout << "1 ";
    tour(1, pow(2, n - 1) - 1, P);

    // 출력 3 - 셋째 줄부터 D 테이블을 참조하여 D[i][j]가 무한대가 아닌 항목을 아래와 같이 출력한다.
    // i j D[i][j]
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < pow(2, n - 1); j++)
        {
            if (D[i][j] != INF && D[i][j])
                cout << i << " " << j << " " << D[i][j] << endl;
        }
    }
}