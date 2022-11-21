#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

/*
input-1
4 16
2 5 10 5
40 30 50 10
output-1
0 0 0 115
1 2 40 115
1 0 0 82
2 7 70 115
2 2 40 98
3 17 120 0
3 7 70 80
3 12 90 98
3 2 40 50
4 17 100 0
4 12 90 90
90

input-2
4 16
5 2 10 5
30 40 50 10
output-2
0 0 0 115
1 2 40 115
1 0 0 82
2 7 70 115
2 2 40 98
3 17 120 0
3 7 70 80
3 12 90 98
3 2 40 50
4 17 100 0
4 12 90 90
90
*/

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

typedef struct node *node_pointer;
typedef struct node
{
    int level; // the node's level in the state space tree
    int weight;
    int profit;
    int profit_per_unit;
    int bound;
} nodetype;

struct compare
{
    bool operator()(node_pointer u, node_pointer v)
    {
        if (u->bound < v->bound)
            return true;
        return false;
    }
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare>
    priority_queue_of_node;

struct compare_sort
{
    bool operator()(nodetype *i, nodetype *j)
    {
        if (i->profit_per_unit < j->profit_per_unit)
            return true;
        return false;
    }
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare_sort> PriorityQueue;

node_pointer create_node_sort(int i, int w, int p)
{
    node_pointer item = (node_pointer)malloc(sizeof(nodetype));
    item->weight = w;
    item->profit = p;
    item->profit_per_unit = p / w;
    return item;
}

void sorting(PriorityQueue &PQ, int n, matrix1 &w, matrix1 &p)
{
    for (int i = 1; i <= n; i++)
    {
        node_pointer item = create_node_sort(i, w[i], p[i]);
        PQ.push(item);
    }
}

int n, maxprofit, W;
matrix1 w, p, sorted_w, sorted_p;

int bound(node_pointer u)
{
    int j, k, totweight;
    int result;
    if (u->weight >= W)
        return 0;

    else
    {
        result = u->profit;
        j = u->level + 1;
        totweight = u->weight;
        while (j <= n && totweight + sorted_w[j] <= W)
        {
            totweight += sorted_w[j];
            result += sorted_p[j];
            j++;
        }
        k = j;
        if (k <= n)
            result += (W - totweight) * (sorted_p[k] / sorted_w[k]);
        return result;
    }
}

node_pointer create_node_knapsack(int level, int weight, int profit)
{
    node_pointer v = (node_pointer)malloc(sizeof(nodetype));
    v->level = level;
    v->weight = weight;
    v->profit = profit;
    v->bound = bound(v);
    cout << v->level << " " << v->weight << " " << v->profit << " " << v->bound << endl;
    return v;
}

void knapsack6()
{
    priority_queue_of_node PQ;
    node_pointer u, v;
    maxprofit = 0;
    PQ.push(create_node_knapsack(0, 0, 0));
    while (!PQ.empty())
    {
        v = PQ.top();
        cout << "POP!!" << v->level << " " << v->weight << " " << v->profit << " " << v->bound << endl;
        PQ.pop();
        if (v->bound > maxprofit)
        {
            u = create_node_knapsack(v->level + 1,
                                     v->weight + sorted_w[v->level + 1],
                                     v->profit + sorted_p[v->level + 1]);
            if (u->weight <= W && u->profit > maxprofit)
                maxprofit = u->profit;
            if (u->bound > maxprofit)
                PQ.push(u);
            u = create_node_knapsack(v->level + 1, v->weight, v->profit);
            if (u->bound > maxprofit)
                PQ.push(u);
        }
    }
}

int main()
{
    //입력 1 - 첫 줄에 아이템의 개수 n과 배낭 무게 W가 주어진다.
    cin >> n >> W;

    //입력 2 - 둘째 줄에 n개의 아이템 무게 w가 주어진다.
    w.resize(n + 1);
    sorted_w.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    //입력 3 - 셋째 줄에 n개의 아이템 이익 p가 주어진다.
    p.resize(n + 1);
    sorted_p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    // 정렬
    PriorityQueue PQ;
    sorting(PQ, n, w, p);
    int i = 1;
    while (!PQ.empty())
    {
        node_pointer ptr = PQ.top();
        sorted_w[i] = ptr->weight;
        sorted_p[i++] = ptr->profit;
        PQ.pop();
    }

    cout << "***output***" << endl;
    cout << "SST level weight profit bound" << endl;

    //출력 1 - 첫 줄부터 Best FS로 방문하는 모든 노드의 상태를 출력한다.
    // level weight profit bound
    knapsack6();

    //출력 2 - 상태의 출력이 모두 끝나고 다음 줄에 최대 이익 maxprofit을 출력한다.
    cout << "max profit: " << maxprofit;
}