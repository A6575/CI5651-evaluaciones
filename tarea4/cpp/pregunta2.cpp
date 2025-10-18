#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool is_disjoint(int i, int j, int k) {
    if (k == 0) {
        return true;
    }

    if (i + k - 1 < j || j + k - 1 < i) {
        return true;
    }

    return false;
}

int max_family_subarrays(const vector<int>& A) {
    int n = A.size();
    if (n == 0) {
        return 0;
    }

    vector<int> prev(n, 0);
    vector<int> curr(n, 0);

    int max_length_global = 0;
    int k_prev, k;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == j){
                curr[j] = 0;
            } else if (gcd(A[i], A[j]) == 1) {
                k_prev = 0;
                if (j + 1 < n) {
                    k_prev = prev[j + 1];
                }

                k = 1 + k_prev;

                if (is_disjoint(i, j, k)) {
                    curr[j] = k;
                } else {
                    curr[j] = 1;
                }
            } else {
                curr[j] = 0;
            }
            max_length_global = max(max_length_global, curr[j]);
        }
        prev = curr;
    }
    return max_length_global;
}

int main() {
    vector<int> A = {3, 10, 1, 8, 4, 5, 3, 6, 9, 2};
    cout << max_family_subarrays(A) << endl;
    return 0;
}