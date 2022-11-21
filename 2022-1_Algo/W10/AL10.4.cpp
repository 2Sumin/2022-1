#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

int n;
matrix1 vindex;
matrix2 W;

/*
input-1
8 13
1 2
1 3
1 7
1 8
2 3
2 7
2 8
3 4
3 6
4 5
5 6
6 7
7 8
output-1
8

input-2
5 6
1 2
1 5
2 3
2 4
2 5
3 4
output-2
0
*/

/*
 <Hamiltonian circuits problem>
 -오일러 회로 : 모든 엣지 방문
 -해밀턴 회로 : 모든 정점을 한번씩 방문 후 원래 노드로 돌아오기
*/

// 1. (n-1)번쨰 정점은 0번째 정점과 이웃해야 한다. (되돌아감)
// 2. i번째 정점은 그 경로에서 (i-1)번째 정점과 이웃해야 한다.
// 3. 같은 노드에 두번 이상 방문할 수 없다.
bool promising(int i)
{
    int j;
    bool flag;
    // 1. n-1번째 노드 -> 0번째 노드로 가는 경로가 있는지 체크
    // 끝까지 갔는데 첫 노드로 돌아올 길이 없는 경우
    if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
        flag = false;
    // 2. 연결되어있지 않은(인접X) 노드인 경우
    // i번째 정점이 i-1번째 정점과 인접해야 한다
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
        flag = false;
    else
    {
        flag = true;
        j = 1;
        // 3. 이미 방문한 노드인지 검사
        // 이미 방문한 노드이면 false (같은 노드 두번 방문 불가)
        while (j < i && flag)
        {
            // vindex[i] : i번째로 방문한 노드 번호
            if (vindex[i] == vindex[j])
                flag = false;
            j++;
        }
    }
    return flag;
}

int cnt = 0;
void hamiltonian(int i)
{
    int j;
    if (promising(i))
    {
        // 출발 노드가 level 0 -> 마지막 노드가 level n-1
        // i == n-1 일 때
        //  promising을 통과했으니까 마지막 노드에서 첫 노드로 돌아올 수 있다
        //  -> solution
        if (i == n - 1)
            cnt++;

        else
            for (j = 2; j <= n; j++)
            {
                // 시작은 무조건 1번 idx에서
                // 시작을 제외한 모든 정점에 대해서 시도
                // vindex[i+1]=j <=> i+1번째로 j번 노드를 방문했다
                vindex[i + 1] = j;
                hamiltonian(i + 1);
            }
    }
}

int main()
{
    // 입력 1 - 첫째 줄에 정점의 개수 n과 간선의 개수 m이 주어진다.
    int m;
    cin >> n >> m;
    // 입력 2 - 둘째 줄부터 m개의 간선이 주어진다.
    W.resize(n + 1, vector<int>(n + 1, 0));
    vindex.resize(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        pair<int, int> edge;
        cin >> edge.first >> edge.second;
        W[edge.first][edge.second] = 1;
        W[edge.second][edge.first] = 1;
    }

    // 기말고사에서는 vindex[0]을 다른 노드로 줄 수 있다
    // vindex[0]이 1일 때는 해밀턴 회로가 존재해도 다른 노드에서 시작하면 해밀턴 회로가 존재하지 않을 수도 있다

    cout << "***output***" << endl;
    // 출력 1 - 첫째 줄에 해밀턴 회로의 개수를 출력한다.
    vindex[0] = 1; // v1을 출발 정점으로 준다

    hamiltonian(0);
    cout << "the number of hamiltonian circuit: " << cnt;
}