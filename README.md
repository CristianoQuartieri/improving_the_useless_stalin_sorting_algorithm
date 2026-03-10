# improving_the_stalin_sort_algorithm

This project implements an adaptive sorting algorithm inspired by the (useless) 'Stalin Sort'.

The idea behind the 'Stalin Sort' is to create an O(n) sorting algorithm, and to do so we iterate through the unordered array just one time, and starting from the first element we only keep the number if it is greater or equal to the previous, else it is sent to the 'Gulag' (it's thrown away). Obviously this creates a problem, we are not ordering the array, but rather eliminating the numbers that make it unordered, giving us a new array that is always smaller than the starting one (except in the case the array is already ordered).

To actually create a sorting algorithm, instead of eliminating out‑of‑order elements, we collect them, sort them, and finally merge them with the result of the stalin sort.
This guarantees O(n log n) worst-case complexity.

The new algorithm that we've created consists of three simple phases:
1) Stalin Scan (Greedy Extraction)
    Traverse the array from left to right, keeping a non‑decreasing subsequence.
    Runs in O(n) time.
    - The first element is always kept
    - Each subsequent element that is ≥ the last kept element is added to the ordered subsequence
    - All other elements are placed into a “remaining” list
2) Sort the Remaining Elements
    The remaining list is sorted using any efficient comparison‑based sort (in our C code, qsort).
    The complexity is O(m log m), where m is the number of remaining elements.
3) Merge
    Because both the ordered subsequence and the (now sorted) remaining list are individually sorted,
    we merge them in O(n) time using a two‑pointer technique (like in Merge Sort).
The result is a new array containing all original elements in sorted order.

What's the point in all of this?
Nothing, just the 'mission' of trying to make something useful out of an algorithm that doesn't have any real application, because it doesn't really sort any array. The mst important part in my opinion is that to make something out of it we are using an approach similar to the one of the Tim Sort (https://en.wikipedia.org/wiki/Timsort), searching for an ordered array inside our array, obviously in a simpler way.
