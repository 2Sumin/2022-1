#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

/*
input-1
5 20
1 2 8
1 3 13
1 4 18
1 5 20
2 1 3
2 3 7
2 4 8
2 5 10
3 1 4
3 2 11
3 4 10
3 5 7
4 1 6
4 2 6
4 3 7
4 5 11
5 1 10
5 2 6
5 3 2
5 4 1
output-1
0 22 1
1 26 1 2
1 30 1 3
1 33 1 4
1 34 1 5
2 29 1 2 3
2 29 1 2 4
2 29 1 2 5
3 46 1 2 3 4 5 1
3 29 1 2 3 5 4 1
29
1 2 3 5 4 1

input-2
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
output-2
0 13 1
1 20 1 2
1 20 1 3
1 INF 1 4
2 22 1 2 3 4 1
2 INF 1 2 4 3 1
2 26 1 3 2 4 1
2 21 1 3 4 2 1
21
1 3 4 2 1
*/

/*
TSP-BRANCH AND BOUND
그래프 G와 출발 정점이 주어졌을 때
그래프의 모든 노드를 각각 한번씩만 방문하고
원래의 출발정점으로 되돌아오는 가장 짧은 경로

각 노드에서 한계값 (bound)를 구해야 함
특정 노드에서 얻을 수 있는 경로 길이의 하한을 구해야 함
유망 조건 : 경로 길이의 하한이 최소인 경로 길이보다 작은 경우

하한값 구하기
-각 경로는 정점을 정확히 한번씩 떠나야 한다
하한 : 정점을 떠나는 간선 가중치 최소값들의 합
W에서 행별로 최소값들끼리만 더하면 lowest bound

v1->v2 : 갈때마다 세로 한 줄 가로 한 줄 원소 하나 제거
-v2에서 v1으로 되돌아갈 수 없으니까 v2->v1 제외 (W[2][1])
-v2는 이미 방문한 노드이므로 v2로 가는 간선들 모두 제외 (열이 2인 것)
-이미 v1을 떠났으므로 v1에서 출발하는 간선들 모두 제외 (행이 1인 것)
이 세가지 조건 모두 제외한 후 lower bound 계산

여행 경로의 길이 : 리프 노드에서 계산
한계값은 리프노드가 아닌 노드에서만 계산

큐에 bound 계산한 것 모두 집어넣은 후에
우선순위큐를 이용해 가장 값이 작은 bound를 꺼내서
그 노드에서 가지 쳐내려가면서 계산

*/

#define INF 99999

typedef vector<int> ordered_set;
typedef vector<vector<int>> matrix2;

typedef struct node
{
    int level;
    ordered_set path;
    int bound;
} nodetype;

typedef struct node node_t;

struct compare
{
    bool operator()(node_t u, node_t v)
    {
        if (u.bound > v.bound)
            return true;
        return false;
    }
};

typedef priority_queue<node_t, vector<node_t>, compare>
    priority_queue_of_node;

int n, m;
matrix2 W;

//현재까지 path에 i 노드가 있는지 없는지 확인하는 함수
bool isIn(int i, ordered_set path)
{
    for (int j = 0; j < path.size(); j++)
        if (path[j] == i)
            return true;
    return false;
}

int length(ordered_set path)
{
    vector<int>::iterator it;
    int len = 0;
    for (it = path.begin(); it != path.end(); it++)
        if (it != path.end() - 1)
            len += W[*it][*(it + 1)];
    return len;
}

bool hasOutgoing(int v, ordered_set path)
{
    vector<int>::iterator it;
    for (it = path.begin(); it != path.end() - 1; it++)
        if (*it == v)
            return true;
    return false;
}

bool hasIncoming(int v, ordered_set path)
{
    vector<int>::iterator it;
    for (it = path.begin() + 1; it != path.end(); it++)
        if (*it == v)
            return true;
    return false;
}

int bound(node_t v)
{
    //하한값 구하기 - 각 여행 경로는 정점을 정확히 한번씩 떠나야 함
    //경로 길이의 하한 : 정점을 떠나는 간선 가중치 최소값들의 합
    int lower = length(v.path);
    for (int i = 1; i <= n; i++)
    {
        //이미 떠나온 노드 제거
        if (hasOutgoing(i, v.path))
            continue;
        int min = INF;
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            // 1로 되돌아가면 안 되니까
            if (j == 1 && i == v.path[v.path.size() - 1])
                continue;
            // v.path에 들어오는 것 제거
            if (hasIncoming(j, v.path))
                continue;
            //위 조건 제외한 각 행의 최솟값을 min에 더해줄 것
            if (min > W[i][j])
                min = W[i][j];
        }
        lower += min;
    }
    return lower;
}

node_t create_node(int level, ordered_set path)
{
    node_t v;

    v.level = level;

    for (int i = 0; i < path.size(); i++)
    {
        v.path.push_back(path[i]);
    }
    v.bound = bound(v);

    return v;
}

void copy(ordered_set path, ordered_set &opttour)
{
    opttour.clear();
    opttour.resize(path.size());
    for (int i = 0; i < path.size(); i++)
    {
        opttour[i] = path[i];
    }
}

void travel2(ordered_set &opttour, int &minlength)
{

    priority_queue_of_node PQ;
    node_t u, v;

    minlength = INF;

    ordered_set tmp(1, 1);
    v = create_node(0, tmp);

    cout << v.level << " ";
    if (bound(v) >= INF)
        cout << "INF ";
    else
        cout << bound(v) << " ";

    for (int k = 0; k < v.path.size(); k++)
    {
        cout << v.path[k];
        if (k != v.path.size() - 1)
            cout << " ";
    }
    cout << endl;

    PQ.push(v);

    while (!PQ.empty())
    {
        v = PQ.top();
        PQ.pop();
        // pruning 조건
        // 최적이 아닌 것은 아예    PQ에 집어넣지 않음 (pruning)
        if (v.bound < minlength)
        {
            for (int i = 2; i <= n; i++)
            {
                // 포함되지 않은 경우만 고려하고
                // 포함되어있다면 그냥 continue(넘김)
                if (isIn(i, v.path))
                    continue;
                u = create_node(v.level + 1, v.path);
                u.path.push_back(i);

                // level이 0에서 시작했으니까
                // level==n-2 : leaf node
                if (u.level == n - 2)
                {
                    // u->path.push_back(remaining_vertex(u->path));
                    for (int j = 2; j <= n; j++)
                    {
                        // 아직 방문하지 않은 마지막 노드 j 찾아서 방문
                        if (!isIn(j, u.path))
                            u.path.push_back(j);
                    }
                    //마지막 노드 방문 후 마지막에는 1번 노드 방문
                    u.path.push_back(1);
                    //리프노드에서 최적 값 찾기
                    if (length(u.path) < minlength)
                    {
                        minlength = length(u.path);
                        copy(u.path, opttour);
                    }
                    cout << u.level << " ";
                    if (bound(u) >= INF)
                        cout << "INF ";
                    else
                        cout << bound(u) << " ";

                    for (int k = 0; k < u.path.size(); k++)
                    {
                        cout << u.path[k];
                        if (k != u.path.size() - 1)
                            cout << " ";
                    }
                    cout << endl;
                }

                // leaf node가 아니면
                else
                {
                    u.bound = bound(u);

                    cout << u.level << " ";
                    if (bound(u) >= INF)
                        cout << "INF ";
                    else
                        cout << bound(u) << " ";

                    for (int k = 0; k < u.path.size(); k++)
                    {
                        cout << u.path[k];
                        if (k != u.path.size() - 1)
                            cout << " ";
                    }
                    cout << endl;

                    if (u.bound < minlength)
                        PQ.push(u);
                }
            }
        }
    }
}

int main()
{
    // 입력 1 - 첫 줄에 그래프의 정점 개수 n과 그래프의 간선 개수 m이 주어진다.
    cin >> n >> m;
    // 입력 2 - 둘째 줄부터 m개의 간선이 u, v, w의 형태로 주어진다.
    W.resize(n + 1, ordered_set(n + 1, INF));

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        W[u][v] = w;
    }

    cout << "***output***" << endl;

    // 출력 1 - 첫째 줄부터 분기한정법으로 방문하는 노드의 상태
    // level bound path[0] path[1] ...... path[k] 로 출력한다
    ordered_set optTour;
    int minlength;
    travel2(optTour, minlength);

    // 출력 2 - 다음 줄에 최적값 minlength를 출력한다.
    cout << minlength << endl;

    // 출력 3 - 다음 줄에는 1번 정점을 출발점으로 하는 최적 순회 경로를 출력한다.
    for (int i = 0; i < optTour.size(); i++)
    {
        cout << optTour[i];
        if (i != optTour.size() - 1)
            cout << " ";
    }
}