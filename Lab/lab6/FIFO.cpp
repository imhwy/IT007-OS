#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

int m;
int n;
int k[100][100];
int a[100][2];

int main()
{
    cout << "--- Page Replacement algorithm ---\n1. Default referenced sequence\n2.Manual input sequence\nEnter your selection: ";

    int iluachon;
    cin >> iluachon;

    if (iluachon == 1)
    {
        n = 11;
        k[0][0] = 2; k[0][1] = 1; k[0][2] = 5; k[0][3] = 2; k[0][4] = 0; k[0][5]= 4; k[0][6] = 9; k[0][7] = 7; k[0][8] = 0; k[0][9] = 0; k[0][10] = 7;
    }
    else
    {
        cout << "Enter length of input sequence: ";
        cin >> n;
        cout << "Enter input sequence: \n";
        for (int i = 0; i < n; i++)
            cin >> k[0][i];
    }

    cout << "Input page frames: ";
    cin >> m;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            k[i][j] = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            a[i][j] = -1;
    for (int i = 0; i < n; i++)
    {
        bool b = false;
        for (int j = 0; j < m; j++)
            if (a[j][0] == k[0][i]) b = true;
        if (b)
            k[m + 1][i] = 0;
        else
        {
            int index = 0;
            for (int j = 1; j < m; j++)
                if (a[j][1] < a[index][1]) index = j;
            a[index][0] = k[0][i];
            a[index][1] = i;
            k[m + 1][i] = 1;
        }
        for (int j = 0; j < m; j++) k[j + 1][i] = a[j][0];
    }

    int count = 0;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (k[i][j] == -1) cout << "  ";
            else    cout << k[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; i++)
        if (k[m + 1][i] == 1)
        {
            cout << "* ";
            count++;
        }
        else cout << "  ";
    cout << "\nNumber of Page Fault: " << count;
}

