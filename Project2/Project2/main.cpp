// Joseph Klebba
// COSC 2030 Spring 2018
// 24 April 2018

// Project 2, Sorting

#include<iostream>
#include<vector>

using namespace std;


//------------------------------------Functions are implemented below-------------------------------

//----------------------------------QUICKSORT----------------------------------------
//This function uses the quicksort algorithm to sort a vector of ints----------------------
// vec1 is the vector to be sorted
// found help for this algorithem from: https://rosettacode.org/wiki/Sorting_algorithms/Quicksort
vector<int> QuickSort(vector<int>& vec1) {
	vector<int> less, equal, greater;
	int holder;

	if (vec1.size() > 1)
	{
		int pivot = vec1[0];

		// sort the values into appropriate arrays
		for (int i = 0; i < vec1.size(); i++)
		{
			holder = vec1[i];
			if (holder < pivot)
			{
				less.push_back(holder); continue;
			}

			if (holder == pivot)
			{
				equal.push_back(holder); continue;
			}

			if (holder > pivot)
			{
				greater.push_back(holder);
			}
		}

		//call the function recursively
		QuickSort(less);
		QuickSort(greater);
	}

	//concatenate the less, equal, greater vectors into vec1
	int index = 0;
	for (int i = 0; i < less.size(); i++)
	{
		vec1[index] = less[i];
		index++;
	}

	for (int i = 0; i < equal.size(); i++)
	{
		vec1[index] = equal[i];
		index++;
	}

	for (int i = 0; i < greater.size(); i++)
	{
		vec1[index] = greater[i];
		index++;
	}

	return vec1;
}

//-----------------------------------Binary Search------------------------------
//This function uses a binary Search to return the index of a target element in a sorted array
// vec1 is a vector of ints
// target is the value to search for
// left is the leftmost index of the vector sub-segment, 
// right is the rightmost index of the vector sub-segment
// found help for this algorithm from: https://www.geeksforgeeks.org/binary-search/
int BinarySearch(const vector<int>& vec1, int target, int left, int right)
{
	//if subsection has atleast 1 element
	if (right >= left)
	{
		//get index of a middle element in the range
		int mid = left + ((right - left) / 2);

		//check if target is the middle element, return index if so
		if (target == vec1[mid])
		{
			return mid;
		}

		//if middle element is smaller than mid then the element is present in subsection left of middle
		if (vec1[mid] > target)
		{
			return BinarySearch(vec1, target, left, mid - 1);
		}

		//otherwise the element will be in the subsection right of middle
		return BinarySearch(vec1, target, mid + 1, right);
	}

	// if function gets to here it means the element is not in the vector. Return -1.
	return -1;
	}

void merge(vector<int>& vec1, int left, int mid, int right)
{
	// Now we need to merge the halves
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// create arrays for the right and left sections
	//int leftArr[n1], rightArr[n2];

	int * leftArr = new int[n1];
	int * rightArr = new int[n2];

	// populate vectors with appropriate values
	for (i = 0; i < n1; i++)
	{
		leftArr[i] = vec1[left + i];
	}

	for (j = 0; j < n2; j++)
	{
		rightArr[j] = vec1[mid + 1 + j];
	}

	// set intitial indexes of vectors for the merge
	i = 0;
	j = 0;
	k = 0;

	while (i < n1 && j < n2)
	{
		if (leftArr[i] <= rightArr[j])
		{
			vec1[k] = leftArr[i];
			i++;
		}
		else
		{
			vec1[k] = rightArr[j];
		}
		k++;
	}

	// copy remaining elements if there are any
	while (i < n1)
	{
		vec1[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		vec1[k] = rightArr[j];
		j++;
		k++;
	}

	delete[] leftArr;
	delete[] rightArr;
}

// https://www.geeksforgeeks.org/merge-sort/
void MergeSort(vector<int>& vec1, int left, int right)
{
	if (left < right)
	{
		// get index of a middle element
		int mid = left + (right - left) / 2;

		// Sort first and second halves
		MergeSort(vec1, left, mid);
		MergeSort(vec1, (mid + 1), right);

		merge(vec1, left, mid, right);
		
	}
}





// print function
void print(const vector<int>& vec1)
{
	for (int i = 0; i < vec1.size(); i++)
	{
		cout << vec1[i] << "  ";
	}
}

//-------------------------------------------------------main---------------------------------------------------------
int main()
{
	vector<int> v = { 14, 4, 9, 5, 8, 8, 0, -7};

	print(v);

	//QuickSort(v);
	MergeSort(v,0,(v.size()-1));


	print(v);

	cout << endl << BinarySearch(v, -7, 0, (v.size() - 1)) << endl;


	return 0;
}