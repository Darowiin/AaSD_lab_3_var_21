#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#define SIZE 1000

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

stats insertion_sort(vector<int>& arr) {
	stats result;
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            ++result.comparison_count;

			swap(arr[j - 1], arr[j]);

            ++result.copy_count;
		}
	}
	return result;
}

template <typename Iterator>
stats insertion_sort(Iterator begin, Iterator end) {
    stats result;
    for (auto i = begin; i != end; ++i) {
        for (auto j = i; j != begin && *(j - 1) > *j; --j) {
            ++result.comparison_count;

            iter_swap(j - 1, j);

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
            ++result.comparison_count;
            if (arr[i] > arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                flag = 1;
                ++result.copy_count;
            }
        }
        right--; 
        for (int i = right; i > left; i--) {
            ++result.comparison_count;
            if (arr[i - 1] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
                flag = 1;
                ++result.copy_count;
            }
        }
        ++left;
    }
    return result;
}

template <typename Iterator>
stats sheker_sort(Iterator begin, Iterator end) {
    stats result;
    auto left = begin, right = end - 1;
    int flag = 1;
    while ((left < right) && flag > 0) {
        flag = 0;
        for (auto i = left; i != right; ++i) {
            ++result.comparison_count;
            if (*i > *(i + 1)) {
                iter_swap(i, i + 1);
                flag = 1;
                ++result.copy_count;
            }
        }
        --right;
        for (auto i = right; i != left; --i) {
            ++result.comparison_count;
            if (*(i - 1) > *i) {
                iter_swap(i - 1, i);
                flag = 1;
                ++result.copy_count;
            }
        }
        ++left;
    }
    return result;
}

void heapify(vector<int>& arr, size_t size, int i, stats& result) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    ++result.comparison_count;
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }
    ++result.comparison_count;
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
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

template <typename Iterator>
void heapify(Iterator begin, Iterator end, Iterator it, stats& result) {
    auto size = distance(begin, end);
    auto i = distance(begin, it);
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;
    ++result.comparison_count;
    if (left < size && *(begin + left) > *(begin + largest)) {
        largest = left;
    }
    ++result.comparison_count;
    if (right < size && *(begin + right) > *(begin + largest)) {
        largest = right;
    }

    if (largest != i) {
        iter_swap(it, begin + largest);
        ++result.copy_count;
        heapify(begin, end, begin + largest, result);
    }
}

template <typename Iterator>
stats heap_sort(Iterator begin, Iterator end) {
    stats result;
    auto size = distance(begin, end);

    for (auto i = size / 2 - 1; i >= 0; --i)
        heapify(begin, end, begin + i, result);

    for (auto i = size - 1; i >= 0; --i) {
        iter_swap(begin, begin + i);
        ++result.copy_count;
        heapify(begin, begin + i, begin, result);
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
    //checking sort methods for 1 array
    {
        cout << "sort methods for 1 array " << endl;
        vector<int> arr = { 1,3,5,7,3,2,19,40,32 };
        cout << "array: ";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }

        stats result = insertion_sort(arr);
        cout << "\ncomparison count: " << result.comparison_count << "\n" << "copy count: " << result.copy_count << endl;

        cout << "sorted array: ";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        vector<int> arr2 = { 1,3,5,7,3,2,19,40,32 };
        cout << "\n\narray: ";
        for (int i = 0; i < arr2.size(); ++i) {
            cout << arr2[i] << " ";
        }

        stats result2 = sheker_sort(arr2);
        cout << "\ncomparison count: " << result2.comparison_count << "\n" << "copy count: " << result2.copy_count << endl;

        cout << "sorted array: ";
        for (int i = 0; i < arr2.size(); ++i) {
            cout << arr2[i] << " ";
        }
        vector<int> arr3 = { 1,3,5,7,3,2,19,40,32 };
        cout << "\n\narray: ";
        for (int i = 0; i < arr3.size(); ++i) {
            cout << arr3[i] << " ";
        }

        stats result3 = heap_sort(arr3);
        cout << "\ncomparison count: " << result3.comparison_count << "\n" << "copy count: " << result3.copy_count << endl;

        cout << "sorted array: ";
        for (int i = 0; i < arr3.size(); ++i) {
            cout << arr3[i] << " ";
        }
        cout << endl << endl;
    }
    //Insertion sort for 100 random arrays, 1 sorted and 1 inverted 
    {
        cout << "Insertion sort for 100 random arrays, 1 sorted and 1 inverted" << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = insertion_sort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = insertion_sort(sorted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = insertion_sort(inverted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl;
    }
    //Sheker sort for 100 random arrays, 1 sorted and 1 inverted
    {
        cout << "Sheker sort for 100 random arrays, 1 sorted and 1 inverted" << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = sheker_sort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = sheker_sort(sorted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = sheker_sort(inverted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl;
    }
    //Heap sort for 100 random arrays, 1 sorted and 1 inverted
    {
        cout << "Heap sort for 100 random arrays, 1 sorted and 1 inverted" << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = heap_sort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = heap_sort(sorted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = heap_sort(inverted);
        cout << "size: " << SIZE << endl;
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl;
    }
    //Implementation for iterators
    // Insertion sort for 100 random arrays, 1 sorted, and 1 inverted
    {
        std::cout << "Insertion sort(iterators) for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = generate_random_vector(SIZE);
            stats tmp = insertion_sort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = insertion_sort(sorted.begin(), sorted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = insertion_sort(inverted.begin(), inverted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }

    // Sheker sort for 100 random arrays, 1 sorted, and 1 inverted
    {
        std::cout << "Sheker sort(iterators) for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = generate_random_vector(SIZE);
            stats tmp = sheker_sort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = sheker_sort(sorted.begin(), sorted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = sheker_sort(inverted.begin(), inverted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }

    // Heap sort for 100 random arrays, 1 sorted, and 1 inverted
    {
        std::cout << "Heap sort(iterators) for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = generate_random_vector(SIZE);
            stats tmp = heap_sort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = heap_sort(sorted.begin(), sorted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = heap_sort(inverted.begin(), inverted.end());
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }

    return 0;
}