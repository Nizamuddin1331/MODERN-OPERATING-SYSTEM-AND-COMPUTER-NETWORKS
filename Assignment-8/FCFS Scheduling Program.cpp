#include <iostream>
using namespace std;

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
};

// Function to sort processes by arrival time
void sortByArrival(Process p[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[j].at < p[i].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    // Input
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time (AT) for P" << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time (BT) for P" << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    // Sort processes by Arrival Time
    sortByArrival(p, n);

    int currentTime = 0;
    int totalTAT = 0, totalWT = 0;

    // Calculate CT, TAT, WT
    for(int i = 0; i < n; i++) {
        if(currentTime < p[i].at) {
            currentTime = p[i].at;   // CPU idle
        }

        p[i].ct = currentTime + p[i].bt;
        currentTime = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Output
    cout << "\nFCFS Scheduling Result:\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {
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
