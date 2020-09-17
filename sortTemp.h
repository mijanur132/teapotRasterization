#pragma once
#include <iostream>
using namespace std;

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

/* Function to print an array */

void randGen(int arr[], int nx){
	int max;
	max = 100; //set the upper bound to generate the random number
	srand(time(0));
	for (int i = 0; i < nx; i++) 
	{ //generate 10 random numbers
		arr[i] = rand() % max;
	}
}



void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// A function to implement bubble sort  
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				//printArray(arr, n);
			}
				
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		//cout << "i:" << i << endl;
		//cout << "key:" << key << "; ";
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			//cout << "j:" << j << endl;
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		
	//	printArray(arr, n);
	}
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray  
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
			//	printArray(arr, n);
				cout << "j:" << j << ";" << "minIndex:" << min_idx << endl;
			}
		}

		// Swap the found minimum element with the first element  
		swap(&arr[min_idx], &arr[i]);
		printArray(arr, n);
	}
}