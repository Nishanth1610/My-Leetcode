#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> numbers;
        int fact = 1;

        for (int i = 1; i <= n; i++) {
            numbers.push_back(i);
        }

        for (int i = 1; i < n; i++) {
            fact *= i;
        }

        k--;

        string result = "";

        while (true) {
            result += to_string(numbers[k / fact]);
            numbers.erase(numbers.begin() + k / fact);

            if (numbers.empty()) {
                break;
            }

            k %= fact;
            fact /= numbers.size();
        }

        return result;
    }
};