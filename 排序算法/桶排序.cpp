#include <iostream>
#include<vector>
using namespace std;

vector<int> bucketSort(vector<int>&arr,int bucketSize) {
    if (arr.size() == 0) {
        return arr;
    }

    int i;
    int minValue = arr[0];
    int maxValue = arr[0];
    for (i = 1; i < arr.size(); i++) {
        if (arr[i] < minValue) {
            minValue = arr[i];                // 输入数据的最小值
        }
        else if (arr[i] > maxValue) {
            maxValue = arr[i];                // 输入数据的最大值
        }
    }

    // 桶的初始化
    int DEFAULT_BUCKET_SIZE = 5;            // 设置桶的默认数量为5
    bucketSize = bucketSize || DEFAULT_BUCKET_SIZE;
    int bucketCount = (maxValue - minValue) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);

    // 利用映射函数将数据分配到各个桶中
    for (i = 0; i < arr.size(); i++) {
        buckets[(arr[i] - minValue) / bucketSize].push_back(arr[i]);
    }

    arr.clear();
    for (i = 0; i < buckets.size(); i++) {
        insertionSort(buckets[i]);                      // 对每个桶进行排序，这里使用了插入排序
        for (int j = 0; j < buckets[i].size(); j++) {
            arr.push_back(buckets[i][j]);
        }
    }

    return arr;
}