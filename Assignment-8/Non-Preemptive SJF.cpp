#include <iostream>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    bool completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time (AT) for P" << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time (BT) for P" << p[i].pid << ": ";
        cin >> p[i].bt;
        p[i].completed = false;
    }

    int completed = 0, currentTime = 0;
    int totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++;   // CPU idle
            continue;
        }

        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].completed = true;
        completed++;

        totalTAT += p[idx].tat;
        totalWT += p[idx].wt;
    }

    cout << "\nNon-Preemptive SJF Scheduling Result:\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    cout << "\nTotal TAT = " << totalTAT;
    cout << "\nTotal WT = " << totalWT;
    cout << "\nAverage TAT = " << (float)totalTAT / n;
    cout << "\nAverage WT = " << (float)totalWT / n;

    return 0;
}
