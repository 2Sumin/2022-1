#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#define INF 0xffff

typedef vector<vector<int>> matrix_t;
typedef vector<int> matrix1;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

/*
input
5 7
1 2 1
1 3 3
2 3 3
2 4 6
3 4 4
3 5 2
4 5 5
output
1 1 1 1
1 1 2 1
1 1 3 3
1 1 3 3
1 1 3 3
2 1 1
3 1 3
5 3 2
4 3 4
*/

/*
[순서도] - ppt 예제
Y 집합 안의 원소와 가까운 정점 찾아 Y에 집어넣고 그 정점이랑 이어진 간선 F에 집어넣기
1. Y = {v1}, F = ∅
2. Y 안의 원소인 v1과 연결된 두 정점 v2,v3 중 더 가까운 v2 선택
   -> Y = {v1, v2}, F= {(v1,v2)}
3. Y 집합 안의 점들과 연결된 간선이 세 개 있는데 그 중 가장 짧은 것 선택 (최소 길이가 되는 간선이 두개라면 아무거나 선택)
  -> Y = {v1, v2, v3}, F={(v1,v2), (v1,v3)}
4. Y 집합과 연결된 간선 3개 중 가장 짧은 길이인 2를 가지는 정점 v5 선택
  -> Y = {v1, v2, v3, v5}, F={(v1,v2), (v1,v3), (v3,v5)}
5. 정점이 총 n개였는데 Y에 n-1개 들어갔고, 1개 남았음. 그 1개랑 Y안의 정점들이 가장 가깝게 연결될 수 있게 연결
  -> Y = {v1, v2, v3, v5, v4}, F={(v1,v2), (v1,v3), (v3,v5), (v3,v4)}
6. F에 포함된 edge의 수가 n-1개면 종료
*/

void prim(int n, matrix_t &W, set_of_edges &F)
{ // F에는 연결된 edge 저장
    int vnear, min;
    vector<int> nearest(n + 1), // Y집합에서 vi에 가장 가까운 정점의 "인덱스"
                                // Y 집합의 원소들 중 어떤 노드가 Y'의 노드와 가장 weight가 작은 edge를 가지는지 표시하기 위해서
                                // Y' 집합의 노드들에게 Y집합의 노드와 연결된 최단 길이의 edge가 Y 집합의 어떤 노드와 연결되어있는지를 nearest 배열에 적음
                                // 만약 Y 집합의 v1 노드와 Y' 집합의 v5 노드가 연결된 edge의 weight가 5라면,
                                // nearest[5]=1 (Y 집합의 1번 노드와 연결된 edge가 최단거리이다), distance[5]=5 로 저장한다
                                // 이렇게 해두면 나중에 F에 edge를 push할 때 어떤 노드와 어떤노드가 연결돼서 최소 거리 edge가 들어가는지 표시 가능

        distance(n + 1); // vi와 nearest[i]의 정점을 연결하는 간선의 가중치

    // 1. 초기화
    // 간선 집합 E의 부분집합 F를 공집합으로 둔다
    F.clear(); // 𝐹 = ∅;
    // Y는 정점의 집합 V의 부분집합

    for (int i = 2; i <= n; i++)
    {                          // v1는 이미 Y에 선택되어있어서 선택되면 안 되니까 distance -1로 초기화 해야 하는데 이 코드에서는
                               // distance가 최소인 값을 찾을 때 애초에 인덱스가 2인 노드부터 비교하니까 굳이 -1로 설정 안해줘도 됨
        nearest[i] = 1;        //처음에 v1에서 출발하니까 1로 초기화
        distance[i] = W[1][i]; // dist가 INF면 edge가 없는 것
    }

    // 2. 선택
    // - 최적의 원소 하나를 해답의 집합에 포함시키기
    // 검사 - Y 집합이 V 집합의 모든 원소를 포함하면 종료
    // 간선의 부분집합 F의 원소 개수가 n-1이면 최종 해답
    // for (int k = 1; k <= n - 1; k++)
    while (F.size() < n - 1)
    {
        // 출력 - nearest 배열의 값을 한 단계에 한 줄씩 출력한다.
        for (int i = 2; i <= n; i++)
        {
            cout << nearest[i];
            if (i != n)
                cout << " ";
        }
        cout << endl;

        min = INF;
        // V - Y 집합 (Y' 집합)에서 Y 집합의 노드(꼭 v1 아니어도 됨)와 가장 가까운 정점 vnear 선택
        // 이미 선택되어서 Y집합에 들어갔다면 distance[i]가 -1이 되고, 이 때는 더 이상 체크할 필요 없음
        // 그래서 distance[i]가 0 이상일 때만 비교하는 것
        // 아직 Y 집합에 들어가지 않은 노드 중 distance가 가장 작은 노드를 vnear로 선택
        for (int i = 2; i <= n; i++)
            if (0 <= distance[i] && distance[i] < min)
            {
                min = distance[i]; // Y집합 내의 노드와 거리가 최소인 값을 min에 저장,
                vnear = i;         //그 노드의 인덱스를 vnear에 저장
            }
        // vnear 선택 후에는 Y 집합에 vnear를 추가,
        // F 집합에 (nearest(vnear),vnear) 를 추가 -> 최소 거리 edge 추가됨

        F.push_back(make_pair(vnear, nearest[vnear])); // F 뒷부분에 방금 찾은 최소 거리를 가지는 노드 추가

        distance[vnear] = -1; // F 에 방금 추가한 노드는 이제 더이상 볼 필요가 없으니까 distance 에 -1 넣어서 앞으로 비교 안 되게

        // Y에 새로운 노드를 추가한 후 distance 새로 업데이트
        // Y와 Y' 집합의 요소가 바뀌었으므로 Y와 Y'사이를 잇는 edge도 달라짐
        // 그래서 원래 있던 distance보다 길이가 더 짧게 연결되는 edge가 생겼다면 등록해주기

        for (int i = 2; i <= n; i++)
            if (distance[i] > W[i][vnear])
            //이미 Y에 속한 노드라면 distance[i]==-1이니까 W[i][vnear]보다 값이 작음 -> 이 if문에 영향받지 않고 그냥 통과
            {
                distance[i] = W[i][vnear];
                nearest[i] = vnear; //이전에 있던 경로에서 vnear에서 가는 경로로 바뀌었으니까 업데이트
            }
    }
    for (int i = 2; i <= n; i++)
    {
        cout << nearest[i];
        if (i != n)
            cout << " ";
    }
    cout << endl;
}

int main()
{
    // 입력1 - 첫 줄에 정점의 개수 n, 간선의 개수 m이 주어진다.
    int n, m;
    cin >> n >> m;

    // 입력2 - 두 번째 줄부터 (u,v,w) 형태로 m 개의 간선이 주어진다.
    // u와 v는 정점의 번호이고, 1부터 n까지의 자연수로 표시한다.
    // w는 간선 <u, v>의 가중치이며, 양의 정수 값으로 주어진다.
    set_of_edges F;
    matrix_t W(n + 1, matrix1(n + 1, INF)); //인접 행렬 (간선의 가중치)
    // W에서 연결되지 않아서 입력되지 않는 부분에는 가중치 INF로 둬야하니까 INF로 초기화

    int x, y, z;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> z;
        // undirected graph니까
        W[x][y] = W[y][x] = z;
    }

    prim(n, W, F);
    int u, v;
    // 여기서 출력되는 게 순서대로 u,v,w -> w 다 더하면 MST의 cost
    for (edge_t e : F)
    {
        u = e.first;
        v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }
}