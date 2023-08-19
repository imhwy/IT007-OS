#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

struct Process{
    string name;
    int burst, arr;
    int start, finish;
    int arrNew;
    int rp, wt, tat;
    bool flag;
    int burstRemain;
};

bool cmp(Process a, Process b){
    return a.arr < b.arr;
}

int main(){
    int n, qtTime;
    cout << "ENTER QUANTUM TIME: "; cin >> qtTime;
    cout << "ENTER THE NUMBER OF PROCESS: "; cin >> n;
    Process *p = new Process[n];
    for(int i = 0; i < n; i++){
        cout << "----------------------\n";
        cout << "Enter the process name :";cin >> p[i].name;
        cout << "Enter arrival time :";cin >> p[i].arr;
        cout << "Enter burst time :";cin >> p[i].burst;
        p[i].burstRemain = p[i].burst;
        p[i].arrNew = p[i].arr;
        p[i].flag = false;
    }

    int cur_t = INT_MAX, i = 0, numProCompl = 0, check = 0;

    for(int tmp = 0; tmp < n; tmp++)
        if(cur_t > p[tmp].arr)
            cur_t = p[tmp].arr;

    while(numProCompl != n){
        int p_arrMin = INT_MAX;

        for(int tmp = 0; tmp < n; tmp++)
            if(p[tmp].arrNew < p_arrMin)
                i = tmp, p_arrMin = p[tmp].arrNew;
        if(p_arrMin > cur_t)
            cur_t = p_arrMin;
        if(p[i].burstRemain <= qtTime && p[i].burstRemain > 0)
        {
            if(!p[i].flag)
                p[i].flag = true, p[i].start = cur_t;
            cur_t = cur_t + p[i].burstRemain;
            p[i].burstRemain = 0;
            p[i].arrNew = INT_MAX;
            check = 1;
        }
        else
        if(p[i].burstRemain > 0){
            if(!p[i].flag)
                p[i].flag = true, p[i].start = cur_t;
            p[i].burstRemain -= qtTime;
            cur_t += qtTime;
            p[i].arrNew = cur_t;
        }

        if(p[i].burstRemain == 0 && check){
            numProCompl++;
            p[i].finish = cur_t;
            check = 0;
        }
    }

    for(int i = 0; i < n; i++)
    {
        p[i].rp = p[i].start - p[i].arr;
        p[i].tat = p[i].finish - p[i].arr;
        p[i].wt = p[i].tat - p[i].burst;
    }

    float rpt_avg = 0;
    float wt_avg = 0;
    float tat_avg = 0;
    for(int i = 0; i < n; i++){
        rpt_avg += p[i].rp;
        wt_avg += p[i].wt;
        tat_avg += p[i].tat;
    }
    rpt_avg /= n;
    wt_avg /= n;
    tat_avg /= n;
    cout << '\n';
    for(int i = 0; i < n; i++){
        cout << "Process Name: " <<p[i].name << '\n';
        cout << "\t\t- Waiting time: " << p[i].wt << '\n';
        cout << "\t\t- Reponse time: " << p[i].rp << '\n';
        cout << "\t\t- Turn Around time: " << p[i].tat << '\n';
    }
    cout << "--------------SUMMARY--------------\n";
    cout << "- Average Waiting time: " << wt_avg << '\n';
    cout << "- Average Reponse time: " << rpt_avg << '\n';
    cout << "- Average Turn Around time: " << tat_avg << '\n';
}
