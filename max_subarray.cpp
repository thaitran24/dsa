// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct SubarrayInfo {
    int left;
    int right;
    int sum;
    SubarrayInfo() : left(0), right(0), sum(0) {}
    SubarrayInfo(int _left, int _right, int _sum) : 
                left(_left), right(_right), sum(_sum) {}
    bool operator>=(SubarrayInfo & sub) {
        return sum >= sub.sum;
    }
};

SubarrayInfo maxSubarray(int* arr, int size);

int main() {
    int arr[10] = {1, 5, -2, 3, -4, 7, -9, 9, 10, -12};
    int arr1[5] = {-1, -2, -3, -4, -5};
    SubarrayInfo info = maxSubarray(arr, 10);   
    for (int i = info.left; i <= info.right; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl << info.sum << endl;
}

SubarrayInfo findMaxcross(int* arr, int left, int mid, int right) {
    int sum = 0;
    int left_sum = INT_MIN, right_sum = INT_MIN;
    int index_left = 0, index_right = 0;
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            index_left = i;
        }
    }
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            index_right = i;
        }
    }
    return SubarrayInfo(index_left, index_right, left_sum + right_sum);
}

SubarrayInfo maxSubarray(int *arr, int left, int right) {
    if (left == right) return SubarrayInfo(left, right, arr[left]);
    int mid = (left + right) / 2;
    SubarrayInfo leftInfo = maxSubarray(arr, left, mid);
    SubarrayInfo rightInfo = maxSubarray(arr, mid + 1, right);
    SubarrayInfo crossInfo = findMaxcross(arr, left, mid, right);
    if (leftInfo >= rightInfo && leftInfo >= crossInfo) return leftInfo;
    if (rightInfo >= leftInfo && rightInfo >= crossInfo) return rightInfo;
    return crossInfo;
}

SubarrayInfo maxSubarray(int *arr, int size) {
    return maxSubarray(arr, 0, size - 1);
}