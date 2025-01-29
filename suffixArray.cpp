#include <iostream>
using namespace std;

class SuffixArray
{
public:
    char s[256];
    int n;
    int *suffixArray;
    int *suffixClass;

    SuffixArray(const char *_s)
    {
        n = 0;
        while (_s[n] != '\0')
        {
            s[n] = _s[n];
            n++;
        }
        s[n] = '\0';

        suffixArray = new int[n];
        suffixClass = new int[n];
    }

    void ConstructUsingPrefixDoubling()
    {
        pair<char, int> *Kth_Suffix = new pair<char, int>[n];
        for (int i = 0; i < n; i++)
            Kth_Suffix[i] = {s[i], i};

        mergeSort(Kth_Suffix, 0, n - 1);

        for (int i = 0; i < n; i++)
            suffixArray[i] = Kth_Suffix[i].second;

        suffixClass[suffixArray[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (Kth_Suffix[i].first == Kth_Suffix[i - 1].first)
                suffixClass[suffixArray[i]] = suffixClass[suffixArray[i - 1]];
            else
                suffixClass[suffixArray[i]] = suffixClass[suffixArray[i - 1]] + 1;
        }

        delete[] Kth_Suffix;

        int k = 0;
        while ((1 << k) < n)
        {
            pair<pair<int, int>, int> *NextKth_Suffix = new pair<pair<int, int>, int>[n];
            for (int i = 0; i < n; i++)
            {
                NextKth_Suffix[i] = {
                    {suffixClass[i],
                     suffixClass[(i + (1 << k)) % n]},
                    i};
            }

            mergeSort(NextKth_Suffix, 0, n - 1);

            for (int i = 0; i < n; i++)
                suffixArray[i] = NextKth_Suffix[i].second;

            suffixClass[suffixArray[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                if (NextKth_Suffix[i].first == NextKth_Suffix[i - 1].first)
                    suffixClass[suffixArray[i]] = suffixClass[suffixArray[i - 1]];
                else
                    suffixClass[suffixArray[i]] = suffixClass[suffixArray[i - 1]] + 1;
            }

            delete[] NextKth_Suffix;
            k++;
        }
    }

    ~SuffixArray()
    {
        delete[] suffixArray;
        delete[] suffixClass;
    }
    void merge(pair<char, int> *arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        pair<char, int> *L = new pair<char, int>[n1];
        pair<char, int> *R = new pair<char, int>[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
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

        delete[] L;
        delete[] R;
    }

    void mergeSort(pair<char, int> *arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    void merge(pair<pair<int, int>, int> *arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        pair<pair<int, int>, int> *L = new pair<pair<int, int>, int>[n1];
        pair<pair<int, int>, int> *R = new pair<pair<int, int>, int>[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
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

        delete[] L;
        delete[] R;
    }

    void mergeSort(pair<pair<int, int>, int> *arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    void print()
    {
        for (int i = 0; i < n; i++)
            cout << suffixArray[i] << " ";
        cout << endl;
    }
};

int main()
{
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.print(); // Expected output: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5

    return 0;
}
