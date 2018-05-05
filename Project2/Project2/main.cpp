// Joseph Klebba
// COSC 2030 Spring 2018
// 24 April 2018

// Project 2, Sorting

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>   //this is used for testing

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


// https://codereview.stackexchange.com/questions/167680/merge-sort-implementation-with-vectors

//-------------------------------MERGE SORT---------------------------------

// this function is called in MergeSort to merge left and right vectors into vec1
// inputs: 
// left = the lefthand sub-vector
// right = the righthand sub-vector
// vec1 = the original vector to be sorted
void merge(vector<int>&left, vector<int>& right, vector<int>& vec1)
{
	//get the number of elements in the left and right vectors
	int numLeft = left.size();
	int numRight = right.size();

	//create indexing variables
	int i = 0, j = 0, k = 0;

	// while not all the way through atleast one of the vectors
	while (j < numLeft && k < numRight)
	{
		// put the lesser element from left and right in vec1, increment index appropriately
		if (left[j] < right[k]) 
		{
			vec1[i] = left[j];
			j++;
		}
		else 
		{
			vec1[i] = right[k];
			k++;
		}
		
		// increment the vec1 index
		i++;
	}

	//copy in the leftover values in left or right if there are any
	while (j < numLeft) {
		vec1[i] = left[j];
		j++; 
		i++;
	}
	while (k < numRight) {
		vec1[i] = right[k];
		k++; 
		i++;
	}
}

// this function uses merge sort to sort a vector of one or more ints
// input:
// vec1 = the vector to be sorted
void MergeSort(vector<int> & vec1) {
	// if vector is of size 1 or less we have reached the stopping point
	if (vec1.size() <= 1)
	{
		return;
	}

	//otherwise get half the number of elements, rounded down
	int mid = vec1.size() / 2;

	//create a vector for the left subsection and right subsection
	vector<int> left;
	vector<int> right;

	//populate the left and right vectors with the appropriate elements
	for (size_t j = 0; j < mid; j++)
	{
		left.push_back(vec1[j]);
	}

	for (size_t j = 0; j < (vec1.size()) - mid; j++)
	{
		right.push_back(vec1[mid + j]);
	}

	// call MergeSort recursively to continue to subdivide the vectors
	MergeSort(left);
	MergeSort(right);

	//call merge to merge the pieces together
	merge(left, right, vec1);

}


//---------------------------- Custom Hashing Function-----------------------------

// Custom hashing function
// input:
// input = either an int or a string
// output = the resultant int value from hashing the input
template <class Type>
unsigned int CustomHash(Type input)
{
	//convert the input to a string
	string hashMe = makeString(input);

	//variables for hashing
	unsigned int hash = 0;
	unsigned int a = 2;

	//hash the string
	for (std::size_t i = 0; i < hashMe.length(); i++)
	{
		hash = hash + hashMe[i] * a;
		a = hashMe[i];
	}

	//return the hash
	return hash;
}

// These two functions are used to convert the CustomHash input to a string
string makeString(int input)
{
	int output = input;
	std::string str = std::to_string(output);
	return str;
}
//see above
string makeString(string input)
{
	return input;
}


//------------------------------------------------- BLOOM FILTER ------------------------------
// I spent a long time searching for stl hash functions besides std::hash, and didn't find anything concrete.
// So I just used APHash from lab 10 for one of my hash functions.
unsigned int APHash(const std::string& str)
{
	unsigned int hash = 0xAAAAAAAA;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] * (hash >> 3)) :
			(~((hash << 11) + (str[i] ^ (hash >> 5))));
	}

	return hash;
}

struct BloomFilter
{
	//member variables
	unsigned int size;
	vector<bool> bits;

	//constructor
	BloomFilter(unsigned int sizeOf)
		:bits(sizeOf),
		size(sizeOf)
	{
		//make sure all the bits in the vector are set to false
		for (int i = 0; i < bits.size(); i++)
		{
			bits[i] = false;
		}
	}

	
	//function to add an input to bloom filter
	//input = a string
	void add(const string& str)
	{
		cout << "aphash index is  " << APHash(str) % size << endl;
		bits[(APHash(str) % size)] = true;
		cout << "std::hash index is  " << std::hash<std::string>{}(str) % size << endl;
		bits[(std::hash<std::string>{}(str)) % size] = true;
	}

	// function to check if the bloom filter may contain an input already
	// input = the string to check for
	// output = true if bloomfilter may contain, false if bloomfilter does not contain
	bool mayContain(const string& str)
	{
		// if both bit locations corresponding to the string are set to true
		if ((bits[APHash(str) % size]) && (bits[std::hash<std::string>{}(str) % size]))
		{
			//then return true
			return true;
		}
		else
		{
			//otherwise return false
			return false;
		}
	}
	
};



// print function
void print(const vector<int>& vec1)
{
	for (size_t i = 0; i < vec1.size(); i++)
	{
		cout << vec1[i] << "  ";
	}
}

//-------------------------------------------------------main---------------------------------------------------------
int main()
{

	BloomFilter filter(999);
	filter.add("appleg54g45g45hg5j564kj476jh76jh57h5h6656656grthb35h46jnh6unmj6ujn7jn6ujmn467uyjn67uyjn66j46ju76j67ss");
	cout << endl << "maycontain?:  " << filter.mayContain("appleg54g45g45hg5j564kj476jh76jh57h5h6656656grthb35h46jnh6unmj6ujn7jn6ujmn467uyjn67uyjn66j46ju76j67ss") << endl;

	return 0;
	int smash = APHash("appleg54g45g45hg5j564kj476jh76jh57h5h6656656grthb35h46jnh6unmj6ujn76jn6ujmn467uyjn67uyjn66j46ju76j67ss");
	cout << "smash is:   " << smash << endl;


	return 0;
	vector<int> v = { 14, 4, 9, 5, 8, 8, 0, -7};

	print(v);

	//QuickSort(v);
	MergeSort(v);

	cout << endl;
	print(v);
	cout << endl;

	vector<int> test;

	for (int i = 0; i < 30; i++)
	{
		test.push_back(rand() % 100);
	}
	 
	vector<int> test2 = test;
	print(test);
	
	MergeSort(test);
	std::sort(test2.begin(), test2.end());
	cout << endl;
	print(test2);
	cout << endl;
	print(test);

	cout << endl << BinarySearch(v, -7, 0, (v.size() - 1)) << endl;


	return 0;
}