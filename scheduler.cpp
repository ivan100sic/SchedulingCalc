#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    int id, run_t, priority;

    Task(int id, int run_t, int priority):
            id(id), run_t(run_t), priority(priority) {}
};

enum SchedulerType {
    FCFS,
    SJF,
    PRIORITY
};

template<SchedulerType>
bool compare(const Task& a, const Task& b){
    return false;
}

template<>
bool compare<FCFS>(const Task& a, const Task& b){
    return a.id < b.id;
}

template<>
bool compare<SJF>(const Task& a, const Task& b){
    return a.run_t < b.run_t;
}

/* proveriti da li veci broj znaci da ce ranije da se izvrsi task */
template<>
bool compare<PRIORITY>(const Task& a, const Task& b){
    return a.priority > b.priority;
}

template<SchedulerType S_T>
void solve(vector<Task> tasks){
    sort(tasks.begin(), tasks.end(), compare<S_T>);
    int tt = 0;
    for (Task task : tasks){
        cout << "Task " << task.id << ": wt = " << tt;
        tt += task.run_t;
        cout << "; rt = " << tt << endl;
    }
}

int main(){
    int N;
    vector<Task> tasks;
    cin >> N;
    while (N--){
        int id, run_t, priority;
        cin >> id >> run_t >> priority;
        tasks.push_back(Task(id, run_t, priority));
    }
    cout << "FCFS" << endl;
    solve<FCFS>(tasks);
    cout << "SJF" << endl;
    solve<SJF>(tasks);
    cout << "Priority" << endl;
    solve<PRIORITY>(tasks);

    return 0;
}
