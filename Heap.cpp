#include <bits/stdc++.h>
using namespace std;
template <typename T>
class MaxHeap
{
public:
  vector<T> arr;
  MaxHeap(vector<T> &a)
  {
    arr = a;
    buildMaxHeap(arr);
  }
  void buildMaxHeap(vector<T> &arr)
  {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
      max_heapify(i);
  }
  void heapSort(vector<T> &arr)
  {
    buildMaxHeap(arr);
    int n = arr.size();
    for (int i = n - 1; i > 0; i--)
    {
      swap(arr[0], arr[i]);
      max_heapify(i);
    }
  }
  void max_heapify(int i)
  {
    int largest = i;
    int n = arr.size();
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
      largest = l;

    if (r < n && arr[r] > arr[largest])
      largest = r;

    if (largest != i)
    {
      swap(arr[i], arr[largest]);
      max_heapify(largest);
    }
  }
  int extractTop()
  {
    if (arr.size() < 1)
      throw runtime_error("Heap is empty");
    int root = arr[0];
    swap(arr[arr.size() - 1], arr[0]);
    arr.pop_back();
    max_heapify(0);
    return root;
  }
  void insert(int val)
  {
    arr.push_back(val);
    int i = arr.size() - 1;
    max_heapify(i);
  }
  T getTop()
  {
    return arr[0];
  }
};
template <typename T>
class MinHeap
{
public:
  vector<T> arr;
  MinHeap(vector<T> &a)
  {
    arr = a;
    buildMinHeap(arr);
  }
  void buildMinHeap(vector<T> &arr)
  {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
      min_heapify(i);
  }
  void heapSort(vector<T> &arr)
  {
    buildMinHeap(arr);
    int n = arr.size();

    for (int i = n - 1; i > 0; i--)
    {
      swap(arr[0], arr[i]);
      min_heapify(i);
    }
  }
  void min_heapify(int i)
  {
    int smallest = i;
    int n = arr.size();
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] < arr[smallest])
      smallest = l;

    if (r < n && arr[r] < arr[smallest])
      smallest = r;

    if (smallest != i)
    {
      swap(arr[i], arr[smallest]);
      min_heapify(smallest);
    }
  }
  T extractTop()
  {
    if (arr.size() < 1)
      throw runtime_error("Heap is empty");
    T root = arr[0];
    arr[0] = arr[arr.size() - 1];
    arr.pop_back();
    min_heapify(0);
    return root;
  }
  T getTop()
  {
    return arr[0];
  }
  void insert(int val)
  {
    arr.push_back(val);
    int i = arr.size() - 1;
    min_heapify(i);
  }
};

int main()
{
  vector<string> arr = {"as", "ae", "be", "wg"};
  MinHeap h(arr);
  cout << h.extractTop() << endl;
  cout << h.extractTop() << endl;
  cout << h.extractTop() << endl;

  return 0;
}