#include <iostream>
#include <vector>

using namespace std;

void printArray(int[], int);
int partition(int arr[], int low, int high)
{
    int i = low-1, pivot = arr[high];
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m+1+j];
    
    i = j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r-l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--)
    {
        swap(arr[i], arr[0]);
        heapify(arr, i, 0);
    }
}

void selectionSort(int arr[], int n)
{
    int min_idx;
    for (int i = 0; i < n; i++)
    {
        min_idx = i;
        for (int j = i+1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i-1, key = arr[i];
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void countingSort(int arr[], int n, int k)
{
    int count[k+1];
    int output[n];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    for (int i = 1; i <= k; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--)
        output[--count[arr[i]]] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix_countingSort(int arr[], int n, int exp)
{
    int count[10] = {0};
    int output[n];

    for (int i = 0; i < n; i++)
        count[arr[i] / exp % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--)
        output[--count[arr[i] / exp % 10]] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    printArray(arr, n);
    
}

void radixSort(int arr[], int n)
{
    int m = *max_element(arr, arr+n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        radix_countingSort(arr, n, exp);
}

void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i], j;
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
void bucketSort(float arr[], int n)
{
    vector<float> bucket[n];
    for (int i = 0; i < n; i++)
    {
        int bi = n * arr[i];
        bucket[bi].push_back(arr[i]);
    }
    for (int i = 0; i < n; i++)
        sort(bucket[i].begin(), bucket[i].end());
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < bucket[i].size(); j++)
            arr[index++] = bucket[i][j];
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printArray(float arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    float farr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    cout << "1. Quick sort\n"
            "2. Selection sort\n"
            "3. Bubble sort\n"
            "4. Insertion sort\n"
            "5. Merge sort\n"
            "6. Heap sort\n"
            "7. Counting sort\n"
            "8. Radix sort\n"
            "9. Bucket sort\n"
            "10. Shell sort\n\n"
            "Choose a sorting algorithm: ";
    cin >> i;
    
    switch (i)
    {
    case 1:
        quickSort(arr, 0, n - 1);
        break;
    case 2:
        selectionSort(arr, n);
        break;
    case 3:
        bubbleSort(arr, n);
        break;
    case 4:
        insertionSort(arr, n);
        break;
    case 5:
        mergeSort(arr, 0, n-1);
        break;
    case 6:
        heapSort(arr, n);
        break;
    case 7:
        countingSort(arr, n, 10);
        break;
    case 8:
        radixSort(arr, n);
        break;
    case 9:
        bucketSort(farr, n);
        break;
    case 10:
        shellSort(arr, n);
        break;
    default:
        break;
    }
    
    cout << "\nSorted array: \n";
    if (i != 9)
        printArray(arr, n);
    else
        printArray(farr, n);
    return 0;
}