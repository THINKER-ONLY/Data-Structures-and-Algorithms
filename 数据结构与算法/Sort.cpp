#include <iostream>

void Swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void SelectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        Swap(arr[i], arr[minIndex]);
    }

}

void InsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void BInsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int low = 0;
        int high = i - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (arr[mid] > temp)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= high + 1; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[high + 1] = temp;
    }
}

void ShellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j -gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void MergeSort(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int *temp = new int[n];

}

int Partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low;
    for (int j = low + 1; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            Swap(arr[++i], arr[j]);
        }
    }
    Swap(arr[++i], arr[low]);
    return i;
}

void QuickSort(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    if (low < high)
    {
        int pivot = Partition(arr, low, high);
        QuickSort(arr, pivot);
        QuickSort(arr + pivot + 1, high - pivot - 1);
    }
}

void HeapSort(int arr[], int n)
{

}

int main()
{
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // BubbleSort(arr, n);
    // SelectionSort(arr, n);
    // InsertionSort(arr, n);
    // BInsertionSort(arr, n);
    // ShellSort(arr, n);
    // MergeSort(arr, n); 
    // QuickSort(arr, n);  // 有错误
    // HeapSort(arr, n);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}