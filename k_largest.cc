#include <vector>
using namespace std;

//
// Partitions the array based on lo and hi indices
// returns the new index
//
int partition(int a[], int lo, int hi)
{
    int i = lo;
    int j = hi + 1;

    while (true) {
        //find item on the left to swap
        while (a[++i] > a[lo]) {
            if (i == hi) break;
        }

        //find item on the right to swap
        while (a[lo] > a[--j]) {
            if (j == lo) break;
        }

        if (i >= j) break;

        //swap
        swap(a[i], a[j]);
    }

    //swap with partitioning item
    swap(a[lo], a[j]);

    //return index of the item known to be in place
    return j;
}

/// Orders k largest elements at the begining of the array
void orderKLargestElements(int a[], size_t size, int k)
{
    vector<int> result;
    if ((a == nullptr) || size <= 0 || k <= 0 || k > size) {
        return;
    }
    
    int lo = 0;
    int hi = size - 1;

    while (hi > lo) {
        int j = partition(a, lo, hi);

        if (j < k) {
            lo = j + 1;
        }
        else if (j > k) {
            hi = j - 1;
        }
        else {
            break;
        }
    }
}
