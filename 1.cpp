#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b) {
    if (a[1] == b[1]) {
        return a[0] < b[0];  // x 오름차순
    }

    return a[1] > b[1];      // y 내림차순
}

void dfs(vector<vector<int>>& tmp, vector<int>& left, vector<int>& right, int cur_idx, vector<int>& first_ans) {
    
    first_ans.push_back(tmp[cur_idx][2]);
    
    if(left[cur_idx] != -1){
        int next_idx = left[cur_idx];
        dfs(tmp, left, right, next_idx, first_ans);
    }
    
    if(right[cur_idx] != -1){
        int next_idx = right[cur_idx];
        dfs(tmp, left, right, next_idx, first_ans);
    }
    
    return;
}

void reverse_dfs(vector<vector<int>>& tmp, vector<int>& left, vector<int>& right, int cur_idx, vector<int>& second_ans) {
    
    if(left[cur_idx] != -1){
        int next_idx = left[cur_idx];
        reverse_dfs(tmp, left, right, next_idx, second_ans);
    }
    
    if(right[cur_idx] != -1){
        int next_idx = right[cur_idx];
        reverse_dfs(tmp, left, right, next_idx, second_ans);
    }
    
    second_ans.push_back(tmp[cur_idx][2]);
    
    return;
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<vector<int>> tmp = nodeinfo;

    for (int i = 0; i < tmp.size(); i++) {
        tmp[i].push_back(i + 1);
    }

    sort(tmp.begin(), tmp.end(), cmp);

    int n = tmp.size();

    // 정렬된 tmp의 인덱스를 저장
    vector<int> left(n, -1);
    vector<int> right(n, -1);

    // tmp[0]은 루트
    for (int child = 1; child < n; child++) {
        int current = 0;

        while (true) {
            // 왼쪽으로 이동
            if (tmp[child][0] < tmp[current][0]) {
                if (left[current] == -1) {
                    left[current] = child;
                    break;
                }

                current = left[current];
            }
            // 오른쪽으로 이동
            else {
                if (right[current] == -1) {
                    right[current] = child;
                    break;
                

                current = right[current];
            }
        }
    }

    vector<int>first_ans;
    dfs(tmp, left, right, 0, first_ans);  
    
    vector<int>second_ans;
    reverse_dfs(tmp, left, right, 0, second_ans);  
    
    answer.push_back(first_ans);
    answer.push_back(second_ans);
    
    return answer;
}