// Joseph Klebba
// COSC 2030 Spring 2018
// 24 April 2018

// Project 2, Sorting, Hashing, Bloom filter

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>      //this is used for testing
#include <ctime>		// used to seed random number generator

using namespace std;


//------------------------------------ FUNCTIONS IMPLEMENTED BELOW -------------------------------

//----------------------------------QUICKSORT----------------------------------------

//This function uses the quicksort algorithm to sort a vector of one or more ints
//input = vec1 is the vector to be sorted
//output = returns the sorted vector
//found help for this algorithem from: https://rosettacode.org/wiki/Sorting_algorithms/Quicksort
vector<int> QuickSort(vector<int>& vec1) {
	//needed variables
	vector<int> less, equal, greater;
	int holder;

	//stopping criterion
	if (vec1.size() > 1)
	{
		//choose a pivot
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







//----------------------------------- BINARY SEARCH ------------------------------

//This function uses a binary Search to return the index of a target element in a sorted array
// inputs:
//			vec1 is a vector of one or more ints
//		    target is the value to search for
//          left is the leftmost index of the vector sub-segment, 
//          right is the rightmost index of the vector sub-segment
// output = returns the index of the target element (returns -1 if target is not present)
// if the target occurs multiple times it will return the index of the first found target
// found help for this algorithm from: https://www.geeksforgeeks.org/binary-search/
int BinarySearch(const vector<int>& vec1, int target, int left, int right)
{
	//if subsection has atleast 1 element
	if (right >= left)
	{
		//get index of a middle element in the range
		int mid = left + ((right - left) / 2);

		//check if target is the middle element, return index if it is
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









//-------------------------------MERGE SORT---------------------------------

// this function is called in MergeSort to merge left and right vectors into vec1
// inputs: 
//		left = the lefthand sub-vector
//		right = the righthand sub-vector
//		vec1 = the original vector to be sorted
// got help from https://codereview.stackexchange.com/questions/167680/merge-sort-implementation-with-vectors
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
// input = vec1 is the vector to be sorted
// takes in the vector as a reference and sorts
// got help with this algorithm from: https://codereview.stackexchange.com/questions/167680/merge-sort-implementation-with-vectors
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
// input = either an int or a string
// output = the resultant int value from hashing the input
// referenced some material from lab10
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


//BloomFilter is a structure that allows you to very efficiently check if you
//previously added an input.
//it may return false positives, but never false negatives
// got help with bloomfilter from here: http://blog.michaelschmatz.com/2016/04/11/how-to-write-a-bloom-filter-cpp/
struct BloomFilter
{
	//member variables
	unsigned int size;
	vector<bool> bits;

	//constructor
	// input = integer for the size of bloomfilter
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
		//hash the input to get index values and set the bits to true there
		
		bits[(APHash(str) % size)] = true;
		
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





// PRINT FUNCTION
void print(const vector<int>& vec1)
{
	for (size_t i = 0; i < vec1.size(); i++)
	{
		cout << vec1[i] << "  ";
	}
	cout << endl;
}



int main()
{
	//seed random number generator
	srand(time(0));



	//----------------------------------TEST QUICKSORT-----------------------------------
	cout << "-------TEST QUICKSORT-------" << endl;
	//Test some hand-picked cases:
	vector<int> t1 = { 0 };
	vector<int> t2 = { 0, 0, 0, 0, 0 };
	vector<int> t3 = { -4 };
	vector<int> t4 = { -7, -7,-7, -7 };

	cout << "Vectors before sorting: " << endl;
	print(t1); print(t2); print(t3); print(t4);

	QuickSort(t1); QuickSort(t2); QuickSort(t3); QuickSort(t4);
	cout << "Vectors after sorting: " << endl;
	print(t1); print(t2); print(t3); print(t4);

	cout << "Compare above vectors visually" << endl << endl;

	cout << "Test QuickSort for 99 randomized vectors: " << endl;
	int quicksortFailCount = 0;
	
	// test further by generating around 99 vectors of varying length with random elements
		for (int i = 1; i < 100; i++)
		{
			vector<int> test;
			vector<int> compare;
			for (int j = 0; j < i; j++)
			{
				int rando = (rand() % 205) - 100;
				test.push_back(rando);
				compare.push_back(rando);
			}

			//sort both the vectors, one with QuickSort and one with std::sort
			QuickSort(test);
			std::sort(compare.begin(), compare.end());

			// count the number of times the vectors are not the same
			if (compare != test)
			{
				quicksortFailCount++;
			}
		}
	
		cout << "	During Testing QuickSort Failed " << quicksortFailCount << " times." << endl << endl;
	//-----------------------------------------------END QUICKSORT---------------------------------------
		






	//-------------------------------TEST MERGESORT------------------------------
		cout << endl << endl << "--------TEST MERGESORT-------" << endl;
		//Test some hand-picked cases:
		vector<int> tt1 = { 0 };
		vector<int> tt2 = { 0, 0, 0, 0, 0 };
		vector<int> tt3 = { -4 };
		vector<int> tt4 = { -7, -7,-7, -7 };

		cout << "Vectors before sorting: " << endl;
		print(tt1); print(tt2); print(tt3); print(tt4);


		MergeSort(tt1); MergeSort(tt2); MergeSort(tt3); MergeSort(tt4);
		cout << "Vectors after sorting: " << endl;
		print(tt1); print(tt2); print(tt3); print(tt4);

		cout << "Compare above vectors visually" << endl << endl;

		cout << "Test MergeSort for 99 randomized vectors: " << endl;
		int mergesortFailCount = 0;

		// test further by generating around 99 vectors of varying length with random elements
		for (int i = 1; i < 100; i++)
		{
			vector<int> test;
			vector<int> compare;
			for (int j = 0; j < i; j++)
			{
				int rando = (rand() % 205) - 100;
				test.push_back(rando);
				compare.push_back(rando);
			}

			//sort both the vectors, one with MergeSort and one with std::sort
			MergeSort(test);
			std::sort(compare.begin(), compare.end());

			// count the number of times the vectors are not the same
			if (compare != test)
			{
				mergesortFailCount++;
			}
		}

		cout << "	During Testing MergeSort Failed " << mergesortFailCount << " times." << endl << endl;
		//---------------------------------------END MERGESORT------------------------------------------







	//----------------------------------TEST BINARY SEARCH-------------------------------
		cout << endl << endl << "-------TEST BINARYSEARCH-------" << endl;
		cout << "I will print a sorted vector and then print result of BinarySearch for a given target" << endl;
		cout << "Visually verify that the index is correct. (-1 if target not present) " << endl << endl;
		cout << "Vector:   ";
		vector<int> v1 = { -34, -3, 0, 0, 2, 9, 9 , 11};
		print(v1);

		cout << endl << "BinarySearch for -3, result should be 1: " << endl;
		cout << "	result:   " << BinarySearch(v1, -3, 0, v1.size() - 1) << endl << endl;

		cout << "BinarySearch for 0, result should be 2 or 3: " << endl;
		cout << "	result:   " << BinarySearch(v1, 0, 0, v1.size() - 1) << endl << endl;

		cout << "BinarySearch for -34, result should be 0: " << endl;
		cout << "	result:   " << BinarySearch(v1, -34, 0, v1.size() - 1) << endl << endl;

		cout << "BinarySearch for 11, result should be 7: " << endl;
		cout << "	result:   " << BinarySearch(v1, 11, 0, v1.size() - 1) << endl << endl;

		cout << "BinarySearch for -10, result should be -1: " << endl;
		cout << "	result:   " << BinarySearch(v1, -10, 0, v1.size() - 1) << endl << endl << endl << endl;
	//--------------------------------END BINARYSEARCH-----------------------------------------




	
	
	//--------------------------------TEST CUSTOMHASH-----------------------------------
		cout << "------TEST CUSTOMHASH------" << endl;
		cout << "I will specify an input and print the resultant hash." << endl << endl;
		
		int inn = -43434434;
		cout << "input an integer:   " << inn << endl;
		cout << "	the output is:   " << CustomHash(inn) << endl << endl;

		inn = 199999434;
		cout << "input an integer:   " << inn << endl;
		cout << "	the output is:   " << CustomHash(inn) << endl << endl;

		inn = -5;
		cout << "input an integer:   " << inn << endl;
		cout << "	the output is:   " << CustomHash(inn) << endl << endl;

		string str("yjjkkfDF35h45h");
		cout << "input a string:   " << str << endl;
		cout << "	the output is:   " << CustomHash(str) << endl << endl;

		str = "jk32FGJ#J$fgg3jgj35jgj54jgj4j5gjJ$3jjjjfkdsjfd;sjlkviop;4jhtuh45gthjj;rjflkjJJJJJ43jkljglj45jgt54lkgj4";
		cout << "input a string:   " << str << endl;
		cout << "	the output is:   " << CustomHash(str) << endl << endl << endl << endl;
		//--------------------------END CUSTOMHASH------------------------------------







		//----------------------------TEST BLOOMFILTER-------------------------------
		cout << "------TEST BLOOMFILTER-------" << endl;
		cout << "Create a large bloomfilter with size 100,000" << endl;
		BloomFilter bigFilter(100000);
		cout << "Add the following strings:" << endl << "	'applesauce'  'apples'  'charlie'  'kf878djFj4j3f3ffh6h5h65^$Hr4'  " << endl << endl;

		string s1 = "applesauce"; string s2 = "apples"; string s3 = "charlie"; string s4 = "kf878djFj4j3f3ffh6h5h65^$Hr4"; string s5 = "gatorade";

		bigFilter.add(s1); bigFilter.add(s2); bigFilter.add(s3); bigFilter.add(s4);
		
		cout << "Check if the bloomfilter may contain a string we added: '" << s1 << "'" << endl << "(Result will be 1 if true, 0 if false)" << endl;
		cout << "	result:   " << bigFilter.mayContain(s1) << endl << endl;

		cout << "Check if the bloomfilter may contain a string we added: '" << s4 << "'" << endl;
		cout << "	result:   " << bigFilter.mayContain(s4) << endl << endl;

		cout << "Check if the bloomfilter may contain a string we didn't add: '" << s5 << "'" << endl;
		cout << "	result:   " << bigFilter.mayContain(s5) << endl << endl;


		cout << "----------------------------------------------------------" << endl;
		cout << "Bloomfilter works as expected with a large, size now make a bloomfilter with size 3 and check for false positives:" << endl;
		cout << "Add the same strings to the small bloomfilter as before." << endl;
		BloomFilter smallFilter(3);
		smallFilter.add(s1); smallFilter.add(s2); smallFilter.add(s3); smallFilter.add(s4);

		cout << "Check if the bloomfilter may contain a string we added: '" << s1 << "'" << endl << "(Result will be 1 if true, 0 if false)" << endl;
		cout << "	result:   " << smallFilter.mayContain(s1) << endl << endl;

		cout << "Check if the bloomfilter may contain a string we added: '" << s4 << "'" << endl;
		cout << "	result:   " << smallFilter.mayContain(s4) << endl << endl;

		cout << "Check if the bloomfilter may contain a string we didn't add: '" << s5 << "'" << endl;
		cout << "	result:   " << smallFilter.mayContain(s5) << endl << endl;

		cout << "We experience a false positive." << endl;
		//---------------------------------------------END BLOOMFILTER------------------------------------

	return 0;
}
