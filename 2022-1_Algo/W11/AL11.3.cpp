#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
input-1
3 4
3
0 0
0 1
1 0
output-1
0
2
0
4

input-2
3 10
2
0 0
1 1
output-2
32
448
416
*/

/*
[기사의 여행 문제]
 nXm 체스보드에서 기사가
 모든 지역을 반드시 한번씩만 방문하는 경로 또는 회로 찾기
 8방향으로 움직일 수 있는데 모든 지역을 방문하고 되돌아옴:회로, 되돌아오지 않음 : 경로
 방문하는 순서대로 방문한 칸에 숫자 쓰기

 해밀턴 회로 : 무방향 그래프에서 임의의 정점에서 출발해서 간선을 따라 "모든 정점"을 한번만 방문하고 출발정점으로 되돌아오는 사이클

*/

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

int n, m, s, cnt;   // s : 출발 정점 (모두 방문 후 되돌아갈 수 있는지 판단)
int count_for_path; //해밀턴 경로 수
matrix1 mark;       // 이미 방문했으면 몇번째 방문했는지 저장
matrix2 graph;      // i번째 노드에서 갈 수 있는 노드의 인접리스트

void make_graph()
{
    // 움직일 수 있는 8개의 이동 경로
    int imov[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int jmov[] = {1, 2, 2, 1, -1, -2, -2, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 8; k++)
            {
                int ni = i + imov[k];
                int nj = j + jmov[k];
                //이동 가능한지 체크
                if (ni >= 0 && nj >= 0 && ni < n && nj < m)
                    // i * m + j : 현재 위치
                    //  ni * m + nj : 다음 위치 (현재 위치에서 방문 가능한 곳)
                    graph[i * m + j].push_back(ni * m + nj);
            }
}

// k: k번째 방문 , v: 현재 노드
void tour(int kth, int v)
{
    if (kth == n * m)
    {
        count_for_path++;
        matrix1 adj = graph[v];
        // v(현재노드)에 인접한 노드 리스트를 adj 배열에 저장
        // 만약 찾았으면
        //  0~n*m까지 k가 진행, s가 adj에 있으면(연결되어있으면 - 회로인지 체크)
        if (find(adj.begin(), adj.end(), s) != adj.end())
        {

            cnt++;
            /*for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    printf("%2d ", mark[i * m + j]);
                cout << endl;
            }*/
        }
    }
    else
    {
        // graph[v] : v에 인접한 노드들이 저장되어있는 배열
        // graph[v]의 인접 노드(u)에서
        for (int u : graph[v])
            //아직 방문하지 않은 정점이면
            if (mark[u] == 0)
            {
                // k+1번째에 u 노드를 방문하겠다
                mark[u] = kth + 1;
                tour(kth + 1, u);
                //노드를 방문하고 돌아왔으면 다시 방문하지 않은 상태로 돌리기
                mark[u] = 0;
            }
    }
}

int main()
{
    // 입력 1 - 첫 번째 줄에 체스보드의 크기 n(행의 크기)과 m(열의 크기)이 주어진다.
    cin >> n >> m;
    graph.resize(n * m, matrix1(0));
    mark.resize(n * m, 0);
    make_graph();
    // 입력 2 - 두 번째 줄에 출발정점의 개수 T가 주어진다.
    int T;
    cin >> T;

    // 입력 3 - 이후로 T개의 출발정점이 i(row), j(col) 의 쌍으로 주어진다.
    matrix2 startPoint;
    for (int i = 0; i < T; i++)
    {
        matrix1 tmp;
        pair<int, int> edge;
        cin >> edge.first >> edge.second;
        tmp.push_back(edge.first);
        tmp.push_back(edge.second);
        startPoint.push_back(tmp);
    }

    cout << "***output***" << endl;

    // 출력 1 - 첫 번째 줄에 해밀턴 회로의 개수를 출력한다.

    s = 0;       // 출발점
    mark[s] = 1; // 출발정점
    cnt = 0;
    tour(1, s);
    cout << "the number of Hamiltonian circuit: " << cnt << endl;

    // 출력 2 - 입력에서 주어진 출발정점 각각에 대해 해밀턴 경로의 수를 한 줄에 하나씩 출력한다.
    for (int i = 0; i < T; i++)
    {
        int total = 0;
        s = startPoint[i][0] * m + startPoint[i][1];
        mark.resize(n * m, 0);
        fill(mark.begin(), mark.end(), 0);
        mark[s] = 1; //출발 정점
        count_for_path = 0;
        tour(1, s);
        total += count_for_path;
        cout << "*number of Hamiltoniam course from startingpoint ( " << startPoint[i][0] << ", " << startPoint[i][1] << " ) : " << total << endl;
    }
}