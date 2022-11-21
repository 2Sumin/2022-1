#include <iostream>
using namespace std;

/*
삼각형 배열 받아서 최상단에서 최하단까지 최대 경로합 구하기
이동은 바로 아래와 바로 아래의 오른쪽만 가능

*/

/*
input
4
3
7 4
2 4 6
8 5 9 3
output
23
3 7 4 9
input2 -> mid 폴더에서 계산하면 경로 2개 나옴
5
1
2 2
3 2 3
4 2 2 5
5 2 2 2 4
output
15
1 2 3 5 4
*/

int n;
int triangle[100][100], //삼각형 안의 숫자 입력받기
    cost[100][100],     // triangle 배열에서 바닥부터 더 큰 값 더해서 저장해놓은 배열
    // cost[0][0]에는 최대거리 적혀있고, 바닥에는 triangle[i][n-1]이랑 같은 값, 중간부터는 더한 값
    record[100]; //최대 경로 저장하기 -> cost배열의 큰 값이 있는 위치의 triangle 배열에 있는 값을 저장
int cnt = 0;

void init()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cost[i][j] = -1;
}

int path2(int x, int y)
{
    //가장 아랫줄 (삼각형의 밑변)이면 그냥 삼각형에 있는 숫자 그대로 리턴
    // 인 줄 알앗는데,,,y면 열이니까 가장 마지막 원소만 triangle 값 그대로 리턴하게 됨
    // y==n-1인 원소는 가장 마지막 줄 가장 오른쪽 원소 하나
    if (y == n - 1)
        return triangle[x][y];

    //참조자 선언 int& 참조자이름 = 변수 이름
    // 이렇게 하려면 cost[x][y]와 ret의 타입이 같아야 한다 (둘 다 int)
    // 이렇게 선언된 참조자는 대상 변수와 같은 메모리 위치를 참조하게 된다
    //(참조자를 이용해 증감연산을 하면 참조 변수 뿐 아니라 대상 변수도 같이 변경된다)
    // ex. int x=10; int& y=x; -> 이 때는 x,y 둘 다 10
    // y++; ->참조자를 이용해 증가연산
    // 이렇게 하면 x,y 모두 다 11로 바뀐다
    int &ret = cost[x][y];
    //이 경우, ret값이 바뀌면 cost[x][y]의 값도 바뀌게 된다

    //이미 접근해서 계산된 경로라면 그 값을 리턴
    if (ret != -1)  //원래 cost배열은 -1로 초기화돼있엇는데 지금 -1이 아니면 이미 다른 값이 들어간 것
        return ret; // cost[x][y]값을 위에서 ret에 넣어뒀으니까 저장된 cost[i][j] 값 리턴

    //아래 행 오른쪽 원소와 바로 아래 원소 비교해서 둘 중 더 큰 값과
    //원래 삼각형 배열에 저장되어있던 값을 더해주기
    ret = triangle[x][y] + max(path2(x + 1, y + 1), path2(x + 1, y));
    return ret;
}

void calc() //경로 출력
{
    int num = 0; //행 계산용. 가장 위에 있는 것부터 비교하니까 처음에는 행이 0이어야함
    //이건 행이나 열이 증가함에 따라 자동으로 증가하는 변수가 아니고
    // 아래랑 아래 오른쪽의 원소만 비교해야하니까 행이 커지더라도 num은 그대로거나(바로 아래) 1커짐(아래 오른쪽)

    for (int i = 0; i < n; i++) //행별로 하나씩 경로 출력
    {
        // i번째 행에서 바로 아래 원소랑 오른쪽대각선 아래 원소 비교
        // 삼각형의 경로이니까 cost배열이 아니라 triangle 배열에 입력받았던 값 그대로 경로를 출력해야함
        record[cnt] = triangle[i][num]; //제일 꼭대기값에서부터 시작
        // cost배열에서 열 비교할 때 행의 가장 오른쪽 원소라 해도 num+1<=i 이니까
        // 원래 과제 제출할 때는 if문을 if ((num + 1 <= i) && (cost[i][num] <= cost[i][num + 1]))로 했지만
        //실제로 num+1<=i는 당연하게 만족되므로 지워도 되는 조건
        // 경로의 합을 저장해둔 cost배열에서 현재 위치 바로 아래와 아래 오른쪽 원소 중 더 큰 값을 저장
        // 이미 record[cnt]에 triangle[i][num]을 저장해뒀으니까
        // cost[i][num]이 더 큰 값이라면 수정할 필요없이 다음 행으로 넘어가기
        if ((cost[i][num] <= cost[i][num + 1])) //이 부분에서 "이상"으로 해놔서 오른쪽이랑 왼쪽이랑 값 같으면 무조건 오른쪽 값 선택
        // 경로 모두 구하려면 이 부분 수정하면 될 듯 -> "<"으로 바꾸면 왼쪽 경로 출력 됨
        //실제로 input2에서 max경로 2개 나오는데, <=했을 때랑 < 했을 때 다른 경로 출력됨
        {
            num++;
            record[cnt] = triangle[i][num];
        }
        cnt++;
    }
}

int main()
{
    //입력1-첫 번째 줄에는 삼각형의 높이 n이 주어진다.
    cin >> n;

    //입력2-두 번째 줄부터 n개의 줄에 각각 삼각형의 숫자들이 주어진다.
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> triangle[i][j];
    init();

    //출력1-첫 번째 줄에 최대 경로의 합을 출력한다.
    cout << path2(0, 0) << endl;

    //출력2-두 번째 줄에 최대 경로를 출력한다.
    cost[n - 1][n - 1] = triangle[n - 1][n - 1];
    calc();
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << record[i] << " ";
        else
            cout << record[i] << endl;
    }

    //아래는 답은 아니고 cost배열 값 확인용
    cout << "cost" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
            cout << cost[i][j] << " ";
        cout << endl;
    }

    return 0;
}