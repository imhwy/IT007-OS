#include<iostream>
#include<math.h>

using namespace std;

struct Process{
    string name;
    int burst, arr;
    int start, finish;
    int rp, wt, tat;
    bool completed;
};

int main(){
    int n;
    cout << "ENTER THE NUMBER OF PROCESS: "; cin >> n;
    Process *p = new Process[n];
    for(int i = 0; i < n; i++){
        cout << "----------------------\n";
        cout << "Enter the process name :";
        cin >> p[i].name;
        cout << "Enter arrival time :";
        cin >> p[i].arr;
        cout << "Enter burst time :";
        cin >> p[i].burst;
        p[i].completed = false;
    }

    int cur_t = 0, numProCompl = 0;
    while(numProCompl != n){
        int indBurstMin = -1;
        int burstMin = INT_MAX;
        for(int i = 0; i < n; i++)
            if(p[i].arr <= cur_t && p[i].completed == false){
                if(p[i].burst < burstMin){
                    indBurstMin = i;
                    burstMin = p[i].burst;
                }
                else
                if(p[i].burst == burstMin)
                    if(p[i].arr > p[indBurstMin].arr){
                        indBurstMin = i;
                        burstMin = p[i].burst;
                    }
            }
        if(indBurstMin == -1)
            cur_t += 1;
        else{
            p[indBurstMin].start = cur_t;
            p[indBurstMin].finish = cur_t + p[indBurstMin].burst;
            p[indBurstMin].rp = p[indBurstMin].start - p[indBurstMin].arr;
            p[indBurstMin].wt = p[indBurstMin].rp;
            p[indBurstMin].tat = p[indBurstMin].finish - p[indBurstMin].arr;
            p[indBurstMin].completed = true;
            numProCompl += 1;
            cur_t = p[indBurstMin].finish;
        }
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
