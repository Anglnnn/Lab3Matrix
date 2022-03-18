#include <string.h>
#include <iostream>
using namespace std;
//int matrice[10][10] = {
//            1,1,0,1,1,1,1,1,1,1
//            ,1,1,0,1,1,1,1,1,1,1
//            ,1,1,0,0,1,0,0,0,1,1
//            ,1,1,1,0,0,0,1,0,1,1
//            ,1,0,1,1,1,0,0,0,1,1
//            ,1,0,0,0,0,0,1,1,1,1
//            ,1,1,1,1,1,0,1,1,1,1
//            ,1,1,1,1,1,0,0,0,1,1
//            ,1,1,1,1,1,1,1,1,1,1
//            ,1,1,1,1,1,1,1,1,1,1 };
int matrice[10][10];
int X = 5, Y = 1, x = 2, y = 2;
// стек реализован в ввиде массива сиволов string
int SolveUsingStack(int, int, string);
int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "Заполните матрицу 10x10: ";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> matrice[i][j];
        }
    }
    cout << "Ваша матрица: ";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << matrice[i][j];
        }
    }
    string temp;
    cout << "Решение: ";
    SolveUsingStack(x, y, temp);
    return 0;
}
int SolveUsingStack(int x, int y, string s)
{
    string st;
    st = s;
    cout << x << "," << y << "\t";
    if (x == X && y == Y)
    {
        cout << st;
        return 0;
    }
    if (x > 0) if (matrice[x - 1][y] == 0) { matrice[x][y] += 3; SolveUsingStack(x - 1, y, st); matrice[x][y] -= 3; }
    if (x < 9) if (matrice[x + 1][y] == 0) { matrice[x][y] += 3; SolveUsingStack(x + 1, y, st); matrice[x][y] -= 3; }
    if (y > 0) if (matrice[x][y - 1] == 0) { matrice[x][y] += 3; SolveUsingStack(x, y - 1, st); matrice[x][y] -= 3; }
    if (y < 9) if (matrice[x][y + 1] == 0) { matrice[x][y] += 3; SolveUsingStack(x, y + 1, st); matrice[x][y] -= 3; }
}