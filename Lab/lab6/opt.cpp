#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

bool Search(int key, int *a, int Size)
{
    for(int j = 0; j < Size; j++)
        if(a[j] == key)
            return true;
    return false;
}

int Find(int *page, int *frame, int pageNumber, int frameNumber, int ind)
{
    int res = -1, longest = ind;
    for(int i = 0; i < frameNumber; i++)
    {
        int j;
        for(j = ind; j < pageNumber; j++)
            if(frame[i] == page[j])
            {
                if(j > longest)
                {
                    longest = j;
                    res = i;
                }
                break;
            }
        if(j == pageNumber)
            return i;
    }
    if(res == -1)
        return 0;
    return res;
}

int main(){
    int option;
    int *seq, fn, pn;

    cout << "--- Page Replacement algorithm ---\n";
    cout << "1. Default referenced sequence\n";
    cout << "2. Manual input sequence\n";
    cout << "Enter your selection (1 or 2): ";
    cin >> option;

    if(option == 1)
    {
        pn = 11;
        seq = new int[pn];
        seq[0] = 2; seq[1] = 1; seq[2] = 5; seq[3] = 2; seq[4] = 0; seq[5] = 4; seq[6] = 9; seq[7] == 7; seq[8] = 0; seq[9] = 0; seq[10] = 7;
    }
    else
    {
        cout << "Enter length of input sequence: ";
        cin >> pn;
        seq = new int[pn];
        cout << "Enter input sequence: \n";
        for(int i = 0; i < pn; i++)
            cin >> seq[i];
    }

    cout << "Input page frames: ";
    cin >> fn;

    int **result = new int*[fn + 1];
    for(int i = 0; i <= fn; i++)
        result[i] = new int[pn];

    int cnt = 0;
    int *pf = new int[fn];
    int hit = 0;
    for(int i = 0; i < pn; i++){
        if(Search(seq[i], pf, cnt))
        {
            hit++;
            result[fn][i] = -2;
            for(int j = 0; j < fn; j++)
                if(j < cnt)
                    result[j][i] = pf[j];
                else
                    result[j][i] = -1;
            continue;
        }

        if(cnt < fn)
            pf[cnt++] = seq[i];
        else
        {
            int j = Find(seq, pf, pn, cnt, i + 1);
            pf[j] = seq[i];
        }
        result[fn][i] = -3;
        for(int j = 0; j < fn; j++)
                if(j < cnt)
                    result[j][i] = pf[j];
                else
                    result[j][i] = -1;
    }
    for(int i = 0; i < pn; i++)
        cout << seq[i] << " ";
    cout << '\n';
    for(int i = 0; i <= fn; i++)
    {
        for(int j = 0; j < pn; j++)
            if((result[i][j] == -1) || (result[i][j] == -2))
                cout << "  ";
            else
            if(result[i][j] == -3)
                cout << "* ";
            else
                cout << result[i][j] << " ";
        cout << endl;
    }

    cout << "Number of Page Fault: " << pn - hit << endl;
}
