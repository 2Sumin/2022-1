#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define INF 999999

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

//최적 이진탐색트리 문제
/*
sample input
4
10 20 30 40
3 3 1 1
sample output
0 3 9 11 14
0 3 5 8
0 1 3
0 1
0
0 1 1 2 2
0 2 2 2
0 3 3
0 4
0
14
20 10 30 40
10 20 30 40
*/

//변수 정리
// matrix1 p(n + 1, 0); // 탐색 확률
// matrix1 K(n + 1, 0); // key 저장
// matrix2 A(n + 2, matrix1(n + 1, 0)); // K를 탐색하는 최적값
// matrix2 R(n + 2, matrix1(n + 1, 0)); // K를 탐색하는 최적해 (경로) -
// subtree 의 루트가 되는 인덱스값이 담겨있음
// 처음 R[1][n]의 값은 트리 전체의 root
// R[1][n]=k 라면 k가 root고,
// 그 왼쪽 subtree의 루트가 R[1][k], 오른쪽 subtree의 루트가 R[k+1][n]
// 루트가 R[i][i]라면 더 이상 밑에 달린 자식이 없다

typedef struct node *node_ptr;
typedef struct node
{
    int key;
    node_ptr left;
    node_ptr right;
} node_t;

node_ptr create_node(int k)
{
    node_ptr newNode = (node_ptr)malloc(sizeof(node_t));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = k;
    return newNode;
}

int sum(int a, int b, matrix1 p)
{
    int sum = 0;
    for (int i = a; i <= b; i++)
        sum += p[i];
    return sum;
}

int minimum(int i, int j, int &mink, matrix2 &M)
{
    // M[i][j]=minValue, P[i][j]=minK
    //최적해는 리턴값 (minValue)안에 넣어주고,
    //최적값 (mink) 는 mink안에 저장해두기
    int minValue = INF, value;

    // 행렬 곱 횟수 구하는 문제랑은 달리 min구할 때 k를 i~j까지 해줘야하니까
    // for문에서 k를 하나 더 탐색하도록 만들어줌
    for (int k = i; k <= j; k++)
    {
        // left subtree 최적값 + right subtree 최적값
        // M[1][4] -> k는 가장 상위 트리 루트의 값
        // k=1 -> M[1][0]+M[2][4] -> 루트 1의 오른쪽에만 서브트리 연결된 형태. A[i][i-1]=0으로 초기화되어있음
        // k=2 -> M[1][1]+M[3][4]
        // k=3 -> M[1][2]+M[4][4]
        // k=4 -> M[1][3]+M[5][4] -> 루트 4의 왼쪽에만 서브트리 연결된 형태. A[i][i-1]=0으로 초기화되어있음
        value = M[i][k - 1] + M[k + 1][j];
        if (minValue > value)
        {
            minValue = value;
            mink = k;
        }
    }
    return minValue;
}

void optsearchtree(int n, matrix1 &p, matrix2 &A, matrix2 &R)
{
    for (int i = 1; i <= n; i++)
    {
        A[i][i - 1] = 0;
        // ki노드가 혼자 있으면 검색횟수 1이니까
        // A[i][i]=p[i] (ki라는 키를 검색하는 횟수는 pi)로 main diagonal 채우고 시작 (bottom)
        A[i][i] = p[i];
        R[i][i - 1] = 0;
        // k가 하나밖에 없으면 루트가 자기자신이 되니까
        R[i][i] = i;
    }

    A[n + 1][n] = R[n + 1][n] = 0;

    for (int diagonal = 1; diagonal <= n - 1; diagonal++)
        for (int i = 1; i <= n - diagonal; i++)
        {
            int j = i + diagonal, k;
            // 루트 없이 탐색한 횟수의 최솟값 + 루트 포함해서 탐색한 횟수 (확률)
            A[i][j] = minimum(i, j, k, A) + sum(i, j, p); //최적값
            R[i][j] = k;                                  //최적해
        }
}

// R 배열 보고 트리 그릴 때
// 처음 R[1][n]의 값은 트리 전체의 root
// R[1][n]=k 라면 k가 root고,
// 그 왼쪽 subtree의 루트가 R[1][k-1], 오른쪽 subtree의 루트가 R[k+1][n]
// 이런식으로 계속 찾아나가다가
// main에서 노드 개수로 입력해준 n이랑 비교해보고 더 이상 서브트리의 루트가 나오지 않겠다 싶으면
// R에서 더 찾을 필요없이 그냥 대소관계만 파악하고 서브트리 루트 밑에 달아주기
// ex. 노드가 4개로 주어졌다면 메인 루트(1), 서브트리 왼쪽,오른쪽 루트 하나씩 (2) 하고 나면
// 4-3=1 노드 한개 남음 -> 하나면 서브트리 루트 둘 중 R[i][i]가 아닌 서브트리 루트의 자식노드로 들어갈 꺼니까
// 더 이상 R배열 이용해서 위치 찾을 필요없이 그냥 서브트리 루트 값보다 크면 오른쪽, 작으면 왼쪽에 넣고 종료

node_ptr tree(int i, int j, matrix1 &K, matrix2 &R)
{
    int k = R[i][j]; // root
    if (k == 0)
        return NULL;
    else
    {
        node_ptr node = create_node(K[k]);
        node->left = tree(i, k - 1, K, R);
        node->right = tree(k + 1, j, K, R);
        return node;
    }
}

void printUpperTriangle(matrix2 arr, int n)
{
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = i - 1; j <= n; j++)
        {
            if (j == n)
                cout << arr[i][j] << endl;
            else
                cout << arr[i][j] << " ";
        }
    }
}

void preorder(node_ptr ptr, int n)
{
    static int cnt = 0; // static keyword를 사용하면 함수가 최초로 호출될때만 초기화 됨
    if (ptr)
    {
        cnt++;
        if (cnt == n)
            cout << ptr->key << endl;
        else
            cout << ptr->key << " ";
        // cout << ptr->key << " ";
        preorder(ptr->left, n);
        preorder(ptr->right, n);
    }
}
void inorder(node_ptr ptr, int n)
{
    static int cnt = 0;
    if (ptr)
    {
        inorder(ptr->left, n);
        cnt++;
        // cout << ptr->key << " ";
        if (cnt == n)
            cout << ptr->key;
        else
            cout << ptr->key << " ";

        inorder(ptr->right, n);
    }
}

int main()
{
    // 입력1 - 첫 번째 줄에 key의 개수 n이 주어진다.
    int n;
    cin >> n;

    // 입력2 - 두 번째 줄에 n 개의 key 값이 주어진다. (key 값은 정렬되어 있다고 가정해도 된다.)
    matrix1 K(n + 1, 0); // key 저장

    for (int i = 1; i <= n; i++)
        cin >> K[i];

    // 입력3 - 세 번째 줄에 n 개의 빈도값 p가 주어진다. (p[i] 값은 양의 정수값으로 주어진다.)
    matrix1 p(n + 1, 0); // 탐색 확률
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    // A,R 모두 인덱스 1부터 시작할꺼니까
    matrix2 A(n + 2, matrix1(n + 1, 0)); // K를 탐색하는 최적값
    matrix2 R(n + 2, matrix1(n + 1, 0)); // K를 탐색하는 최적해 (경로)
    optsearchtree(n, p, A, R);

    // 출력1 - 먼저 행렬 A의 윗 부분 삼각형을 출력한다. (0을 포함)
    printUpperTriangle(A, n);

    // 출력2 - 다음으로 행렬 R의 윗 부분 삼각형을 출력한다. (0을 포함)
    printUpperTriangle(R, n);

    // 출력3 - 최적 이진탐색트리에서 평균검색시간의 최적값을 출력한다.
    cout << A[1][n] << endl;

    // 출력4 - 최적 이진탐색트리의 preorder 순회 탐색 결과를 출력한다.
    node_ptr root = tree(1, n, K, R);
    preorder(root, n);
    //  출력5 - 최적 이진탐색트리의 inorder 순회 탐색 결과를 출력한다.
    inorder(root, n);
}
