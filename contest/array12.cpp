
#include <iostream>
#include<algorithm>
#include<climits>

using namespace std;
 
int partition(int arr[], int l, int r, int k);

int findMedian(int arr[], int n)
{
    sort(arr, arr+n);
    return arr[n/2];   
}
 
int kthSmallest(int arr[], int l, int r, int k)
{
    
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;
        int i, median[(n+4)/5]; 
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5); 
            i++;
        }    
 
        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);
 
        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);
 
        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);
 
        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
 
    // If k is more than number of elements in array
    return INT_MAX;
}
 
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// It searches for x in arr[l..r], and partitions the array 
// around x.
int partition(int arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
 
    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}
 
// Driver program to test above methods
int main()
{
    int arr[] = {0,12, 3, 5, 7, 4, 19, 26};
    int n = 8, k = 3+1;
    cout << "K'th smallest element is "
         << kthSmallest(arr, 0, n, k);
    return 0;
}