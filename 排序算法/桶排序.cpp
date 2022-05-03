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
            minValue = arr[i];                // �������ݵ���Сֵ
        }
        else if (arr[i] > maxValue) {
            maxValue = arr[i];                // �������ݵ����ֵ
        }
    }

    // Ͱ�ĳ�ʼ��
    int DEFAULT_BUCKET_SIZE = 5;            // ����Ͱ��Ĭ������Ϊ5
    bucketSize = bucketSize || DEFAULT_BUCKET_SIZE;
    int bucketCount = (maxValue - minValue) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);

    // ����ӳ�亯�������ݷ��䵽����Ͱ��
    for (i = 0; i < arr.size(); i++) {
        buckets[(arr[i] - minValue) / bucketSize].push_back(arr[i]);
    }

    arr.clear();
    for (i = 0; i < buckets.size(); i++) {
        insertionSort(buckets[i]);                      // ��ÿ��Ͱ������������ʹ���˲�������
        for (int j = 0; j < buckets[i].size(); j++) {
            arr.push_back(buckets[i][j]);
        }
    }

    return arr;
}