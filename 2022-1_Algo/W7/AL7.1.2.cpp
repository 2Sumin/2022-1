#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> dset; // 1차원 배열 dset 안에 그 원소가 속해있는 집합을 저장
// 처음에는 모두 서로소 집합을 형성하니까 dset[i]=i
// merge(1,10) 후에는 10이 1이 있는 집합 안으로 들어가니까
// dset[10]=1 -> find(1)=find(10)=1
// ex. dset[2]=10, dset[10]=4, dset[4]=4
// -> dset[i]=i일 때 i가 루트인 집합.
// 2,10,4는 모두 같은 집합 안에 있다.

/*
input
5 7
1 2 1
1 3 3
2 3 7
2 4 6
3 4 4
3 5 2
4 5 5
output
1 2 1
3 5 2
1 3 3
3 4 4
*/

typedef struct edge
{
    //출발, 도착, 가중치
    int u, v, w;
} edge_t;

struct edge_compare
{
    bool operator()(edge_t e1, edge_t e2)
    {
        if (e1.w > e2.w)
            return true;
        else
            return false;
    }
};
typedef vector<edge_t> set_of_edges;
typedef priority_queue<edge_t, vector<edge_t>, edge_compare> PriorityQueue;

void dset_init(int n)
{
    dset.resize(n + 1);
    for (int i = 1; i <= n; i++)
        dset[i] = i;
}

int dset_find(int i)
{
    while (dset[i] != i) // dset[i]==i이면 루트니까 루트를 찾을 때까지 계속 타고 가보기
        i = dset[i];
    return i;
}

void dset_merge(int p, int q)
{
    dset[p] = q;
    // p를 q 집합 안으로 넣음
    // 뒤에 있는 원소를 앞 원소의 집합으로 집어넣음
}

void kruskal(int n, int m, set_of_edges &E, set_of_edges &F)
//             정점 수, 간선 수, 간선 집합,         output
{
    int p, q;
    edge_t e;
    PriorityQueue PQ;

    // 간선의 집합 E를 weight에 대한 비내림차순(오름차순)으로 정렬 후 시작
    // 제일 앞에 가장 작은 원소가 오게 해서 weight가 작은 것부터 MST에 포함하기 위함
    // 프림에서는 weight를 2차원 배열에 넣어서 사용하니까 undirected 인 걸 표현하기 위해서 (x,y), (y,x) 둘 다 입력해줘야했지만
    // 크루스칼에서는 weight를 배열로 사용하는 게 아닌데다 weight순으로 정렬해야하니까 둘 다 입력할 필요없음
    for (edge_t e : E)
        PQ.push(e);

    F.clear();    // 𝐹 = ∅;
    dset_init(n); //서로소 집합 n개로 초기화

    while (F.size() < n - 1) // mst는 edge를 노드수-1개만큼 가지니까 F.size가 n-1이 됐다면 while문 다시 돌지말고 끝내기
    {
        // 1. 정렬된 PQ(여기에 저장된 건 간선!)에서 가장 위에 있는 가장 작은 원소를 꺼내온다.
        e = PQ.top();
        PQ.pop(); // edge with least weight not yet considered;

        //방금 꺼낸 e의 두 노드가 현재 같은 집합에 속해있는지 보고 아니라면 연결해주기
        // find함수를 통해서 매개변수의 루트노드가 리턴되면 현재 두 원소가 같은 집합에 속해있는지 검사
        // (루트가 같으면 같은 집합에 이미 있음)
        // -> 같은 값을 가지면 이미 conencted 된 것-> 한번 더 연결하면 cycle이니까 갖다버리기

        // 아니라면(서로 다른 집합이라면) F에 e를 포함하기
        p = dset_find(e.u); // p가 e.u가 속한 집합을 가리킴
        q = dset_find(e.v);
        if (p != q)
        {
            dset_merge(p, q); // merge 하면 원래 q 집합이랑 p집합이 합쳐져서 q가 p 집합 안으로 들어감
            // merge 후에는 find(e.u), find(e.v)의 결과가 p로 같아짐 (같은 집합에 속함)
            // merge한다는 건 p와 q 노드를 이은 edge를 MST에 사용하겠다!라는 말이니까 F에 추가하기
            F.push_back(e);
        }
    }
}

int main()
{
    // 입력1 - 첫 줄에 정점의 개수 n, 간선의 개수 m이 주어진다.
    int n, m;
    cin >> n >> m;

    // 입력2 - 두 번째 줄부터 (u,v,w) 형태로 m 개의 간선이 주어진다.
    // u와 v는 정점의 번호이고, 1부터 n까지의 자연수로 표시한다.
    // w는 간선 <u, v>의 가중치이며, 양의 정수 값으로 주어진다.
    set_of_edges E, F;

    // 프림이랑 다르게 여기서는 edge를 기준으로 봄
    edge_t input;
    for (int i = 1; i <= m; i++)
    {
        cin >> input.u >> input.v >> input.w;
        E.push_back(input);
    }

    kruskal(n, m, E, F);

    // 출력1 - 크루스칼 알고리즘의 초기 단계부터 종료 단계까지(n-1 times)
    // F 집합에 포함되는 간선을 순서대로 출력한다. (u,v,w) 형태로
    for (edge_t e : F)
    {
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
}