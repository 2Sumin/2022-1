#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 0xffff

typedef vector<vector<int>> matrix_t;
typedef vector<int> matrix1;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

//플로이드 : "모든 정점의 쌍"에 대한 최단 경로 구하기 (DP) (1->2, 4->5 모든 경우의 최단 경로 다 구함)
//다익스트라 : "단일 정점에서 모든 다른 정점으로" 가는 최단 경로 구하기 (Greedy)

/*
input
5 8
1 2 7
1 3 4
1 4 6
1 5 1
3 2 2
3 4 5
4 2 3
5 4 1
4
2
3
4
5
output
1 1 1 1
1 1 5 1
4 1 5 1
4 1 5 1
4 1 5 1
1 5 1
5 4 1
1 3 4
4 2 3
1 5 4 2
1 3
1 5 4
1 5
*/

/*
v1에서 출발해서 존재하는 모든 노드들을 최단 경로로 이을 수 있게
[순서도] - ppt 예제
출발은 무조건 v1에서 하는데, Y 집합 안의 원소"만" 거쳐서 갈 수 있다. v1에서 다이렉트로 갈 수 있는 경로와 Y 안의 노드를 거쳐갈 수 있는 경로 중
가장 weight가 작은 것 찾아서 정점은 Y에 집어넣고 그 정점이랑 이어진 간선 F에 집어넣기
1. Y = {v1}, F = ∅
2. v1과 연결된 두 정점 v2,v3,v4,v5 중 가장 가까운 v5 선택 (Y안에는 v1말고 포함된 게 없어서 다이렉트로 가는 것 말고는 선택지가 없음)
   -> Y = {v1, v5}, F= {(1,5))}
3. v2로 가는 것 : v1->v2 // v3로 가는 것 : v1->v3 // v4로 가는 것 : v1->v4, "v1->v5->v4" 중 가장 weight가 작은 v4 선택
   -> Y = {v1, v5,v4}, F= {(1,5),(5,4)}
4. v2로 가는 것 : v1->v2, v1->v4->v2 // v3으로 가는 것 : "v1->v3" 중 가장 weight가 작은 v3 선택
   -> Y = {v1, v5,v4, v3}, F= {(1,5),(5,4),(1,3)}
5. v2로 가는 것 : v1->v2, v1->v4->v2, "v1->v5->v4->v2"
   -> Y = {v1, v5,v4, v3,v5}, F= {(1,5),(5,4),(1,3),(4,2)}
   #최종적으로 최단 경로를 가는 데 사용되는 edge들만 F에 저장됨
   #1에서 vi로 가는 최단 경로를 찾기 위해서는 (ex. v4)
   1. vi로 도착하는 pair를 F에서 찾는다 (하나만 존재) (5,4)
   2. 1에서 찾는 pair의 시작점 (F.first)을 도착점으로 하는 pair를 F에서 찾는다. (1,5)
   3. 2번의 과정을 pair의 시작점 (F.first)이 1이 될 때까지 반복한다.
여기서 찾은 edge들을 마지막에 찾은 것부터 연결하면 그게 경로
*/

void dijkstra(int n, matrix_t &W, set_of_edges &F)
// Y에 속한 정점만 중간에 거쳐가는 정점으로 해서
// v1에서 최단경로를 가진 정점 v를 V-Y에서 선택한다
{
    int vnear, min;
    vector<int> touch(n + 1), // Y에 속한 정점들만 중간에 거치도록 해서 v1에서 vi로 가는 현재 최단 경로 상의 마지막 간선을 (v,vi)라 할 때
                              // Y에 속한 정점 v의 인덱스를 touch배열에 넣는다
                              //프림에서 nearest랑 비슷
                              // ex. v1->v2로 가는 최단 경로가 v1->v5->v4->v2 이니까 touch[v2]=4
        length(n + 1);        // Y에 속한 정점들만 중간에 거치도록 해서 "v1에서" vi로 가는 현재 최단 경로의 길이
    //프림에서 distance랑 비슷
    F.clear(); //최단경로의 집합
    for (int i = 2; i <= n; i++)
    {
        touch[i] = 1;        // v1에서 가는거니까
        length[i] = W[1][i]; // v1에서 vi로 가는 direct edge의 weight 저장
    }
    while (F.size() < n - 1) //모든 정점에 대해 다 구했을 때 끝 (Y==V)
    {
        // 출력 - touch 배열의 값을 한 단계에 한 줄씩 출력한다.
        for (int i = 2; i <= n; i++)
        {
            cout << touch[i];
            if (i != n)
                cout << " ";
        }
        cout << endl;

        min = INF;
        for (int i = 2; i <= n; i++)
            if (0 <= length[i] && length[i] < min) //이미 Y집합 안에 들어가서 -1로 length가 변한 것은 고려하지 않겠다
            {
                min = length[i];
                vnear = i; // 추가할 정점 (가장 거리가 짧은 정점)
            }

        //최단경로 상에서 v로 가는 간선을 F에 추가한다
        F.push_back(make_pair(touch[vnear], vnear));
        // touch[vnear]은 Y에 원래 있던 정점. Y의 정점 중 vnear 점에 가는 최단경로를 가진 정점이 touch[vnear]안에 들어있었음
        // Y 안의 정점 touch[vnear]에서 vnear로 가는 edge를 F에 추가

        // Y 집합에 vnear 노드가 추가됐으니까 경유해서 갈 수 있는 경로가 더 다양해짐 -> 업데이트
        for (int i = 2; i <= n; i++)
            // W[vnear][i]는 vnear 정점에서 Y' 집합의 i로 가는 간선의 가중치
            if (length[i] > length[vnear] + W[vnear][i])
            // 1번 노드에서 i번 노드까지 가는 거리를 length배열에 넣으니까 항상 누적해서 구해줘야함
            // length[vnear]+W[vnear][i] : 1에서 vnear로가는 최단거리+vnear에서 i로 가는 최단 경로 거리
            // length[i] : Y에 vnear 추가되기 전에 있던 노드들을 경유해서 1에서 i로 갈 수 있었던 최단 경로 거리
            //이 길이보다 새로 추가된 vnear를 경유해서 가는 거리가 더 짧다면 거리를 length에, 경유한 마지막 지점이 vnear이니까 이걸 touch에 업데이트
            {
                length[i] = length[vnear] + W[vnear][i]; // v1->v_vnear 로 가는 길이 + v_vnear->vi로 가는 길이 (경유 가능하니까 더하기)
                touch[i] = vnear;                        // 1에서 i 정점까지 가는 경로에서 i가 가장 마지막으로 연결된 정점
            }
        length[vnear] = -1; // Y에 이미 포함됐으면 -1
        // 프림과는 달리 1번 노드에서 i번노드까지의 거리를 누적 합으로 계산해야하니까 거리 업데이트 후 length=-1로 업데이트
    }
    for (int i = 2; i <= n; i++)
    {
        cout << touch[i];
        if (i != n)
            cout << " ";
    }
    cout << endl;
}

void printPath(int endPoint, set_of_edges F, set_of_edges &print)
{
    // endPoint를 검사해서 F.second==endPoint면 print 벡터에 추가
    // 종료조건 : F벡터에 (1,endPoint), 즉 1에서 endPoint로 다이렉트로 가는 경로를 찾으면 종료
    // endPoint가 F.second일 때 F.first가 1이면
    for (edge_t e : F)
    {
        if (e.second == endPoint)
        {
            // print.push_back(make_pair(e.first, e.second)); //벡터 뒤에 넣으면 순서대로 출력 안 됨. 1에서 출발하는 edge가 제일 앞에 저장되도록
            print.insert(print.begin(), make_pair(e.first, e.second)); //벡터 앞에 삽입
            if (e.first == 1)
                return;
            else // F에서 e.first로 가는 간선 찾기 (1에서 F로 가는 거 찾으면 멈춤)
                printPath(e.first, F, print);
        }
    }
}

int main()
{
    // 입력1 - 첫 줄에 정점의 개수 n, 간선의 개수 m이 주어진다.
    int n, m;
    cin >> n >> m;
    // 입력2 - 두 번째 줄부터 (u,v,w) 형태로 m 개의 간선이 주어진다.
    set_of_edges F;                         //최단 경로 집합
    matrix_t W(n + 1, matrix1(n + 1, INF)); //그래프의 인접행렬

    int x, y, z;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> z;
        // W[x][y] = W[y][x] = z;
        W[x][y] = z;
    }
    // 입력3 - 이후에 정점의 개수 T가 주어진다.
    int T;
    cin >> T;

    // 입력4 - 이후에 T개의 정점 번호가 주어진다.
    matrix1 node(T + 1, 0);
    for (int i = 1; i <= T; i++)
        cin >> node[i];

    dijkstra(n, W, F);

    // 출력2 - 다익스트라 알고리즘의 F 집합에 포함되는 간선을 순서대로 출력한다.
    int u, v;
    for (edge_t e : F)
    {
        u = e.first;
        v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }

    // 출력3 - T개의 정점 v에 대해서 1번 정점으로부터 정점 v로 가는 최단 경로를 출력한다.
    set_of_edges print;
    for (int i = 1; i <= T; i++)
    {
        print.clear(); //실행할 때마다 초기화
        printPath(node[i], F, print);
        for (edge_t e : print)
        {
            u = e.first;
            v = e.second;
            if (v == node[i]) //마지막 간선이면 띄어쓰기도 없애고, 시작점, 끝점 모두 출력
                cout << u << " " << v << endl;
            else
                cout << u << " "; // u,v 둘 다 출력하면 1542 출력돼야하는 게 15 54 42로 출력 됨
                                  //중간에 반복 지우기 위해서 마지막 쌍 제외하고는 시작 노드만 출력
        }
    }
}