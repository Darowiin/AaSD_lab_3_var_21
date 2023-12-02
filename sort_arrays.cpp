#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

stats insertion_sort(vector<int>& arr) {
	stats result;
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
			result.comparison_count++;

			swap(arr[j - 1], arr[j]);

			result.copy_count++;
		}
	}
	return result;
}

stats sheker_sort(vector<int>& arr) {
    stats result;
    int left = 0, right = arr.size() - 1;
    int flag = 1;
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; i++) {
            result.comparison_count++;
            if (arr[i] > arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                flag = 1;
                result.copy_count++;
            }
        }
        right--; 
        for (int i = right; i > left; i--) {
            result.comparison_count++;
            if (arr[i - 1] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
                flag = 1;
                result.copy_count++;
            }
        }
        left++;
    }
    return result;
}

void heapify(vector<int>& arr, size_t size, int i, stats& result) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest]) {
        largest = left;
        ++result.comparison_count;
    }

    if (right < size && arr[right] > arr[largest]) {
        largest = right;
        ++result.comparison_count;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        ++result.copy_count;
        heapify(arr, size, largest, result);
    }
}

stats heap_sort(vector<int>& arr)
{
    stats result;
    size_t size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i, result);

    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        ++result.copy_count;
        heapify(arr, i, 0, result);
    }
    return result;
}

vector<int> generate_random_vector(size_t n) {
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(rand() % 100);
    }
    return result;
}

vector<int> generate_sorted_vector(size_t n) {
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_inverted_vector(size_t n) {
    vector<int> result;
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}

int main() {
	vector<int> arr = { 1,3,5,7,3,2,19,40,32 };
    cout << "Array: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }

	stats result = insertion_sort(arr);
	cout << "\nComparison count: " << result.comparison_count << "\n" << "Copy count: " << result.copy_count << endl;

    cout << "Sorted Array: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    ////////////////////////////////////////////
    vector<int> arr2 = { 1,3,5,7,3,2,19,40,32 };
    cout << "\n\nArray: ";
    for (int i = 0; i < arr2.size(); ++i) {
        cout << arr2[i] << " ";
    }

    stats result2 = sheker_sort(arr2);
    cout << "\nComparison count: " << result2.comparison_count << "\n" << "Copy count: " << result2.copy_count << endl;

    cout << "Sorted Array: ";
    for (int i = 0; i < arr2.size(); ++i) {
        cout << arr2[i] << " ";
    }
    ////////////////////////////////////////////
    vector<int> arr3 = { 1,3,5,7,3,2,19,40,32 };
    cout << "\n\nArray: ";
    for (int i = 0; i < arr3.size(); ++i) {
        cout << arr3[i] << " ";
    }

    stats result3 = heap_sort(arr3);
    cout << "\nComparison count: " << result3.comparison_count << "\n" << "Copy count: " << result3.copy_count << endl;

    cout << "Sorted Array: ";
    for (int i = 0; i < arr3.size(); ++i) {
        cout << arr3[i] << " ";
    }
}