#include <iostream>
#include <fstream>

void merge(int*, int, int, int);		// merges sorted subarrays
void sort(int*, int, int);				// merge sort on unsorted array
int binSearch(int*, int, int, int);		// binary search on sorted array

int main(int argc, char*argv[]){
	if(argc < 3){
		std::cout << "Provide a file name of data to be searched ";
		std::cout << "and the target value.\n";
		return 1;
	}
	// create fstream to read file & check file validity
	std::ifstream datfile(argv[1], std::ios::in);
	if(!datfile.good()){
		std::cout << "Unable to open file " << argv[1] << ".\n";
		return 1;
	}

	int count = 0;						// number of int in datafile
	
	while(datfile.good()){
		int temp;						// temp var to store read val from file
		datfile >> temp;				// reads from stream & store in temp
		if(datfile.good())				// if we haven't reached EOF, inc count var
			count++;
	}
	datfile.clear();					// clears EOF status
	datfile.seekg(0, std::ios::beg);	// go back to beginning of the file
	
	int* data = new int[count];			// data array size count
	for(int i=0; i<count; i++)
		datfile >> data[i];
	datfile.close();					// close the fstream

	std::cout << "Read " << count << " integers from the datafile.\n";
	sort(data, 0, count-1);				// last index is num elements - 1

	for(int i=0; i<count; i++)
		std::cout << data[i];
	std::cout << "\n";

	int target = atoi(argv[2]);			// get the target value
	int retval = binSearch(data, target, 0, count);

	if(retval == -1)
		std::cout << target << " does not appear in the data.\n";
	else
		std::cout << target << " appears at index " << retval << ".\n";
	delete[] data;						// delete allocated memory
	return 0;
}

/***************************************************
 * function: merge
 * purpose: this function performs the merging of two subarrays
 *		and ensures that the resulting array is in order
 * parameters: low, medium, and high indexes of subarrays
 *		data array of integers
 * return: nothing
****************************************************/
void merge(int* data, int low, int med, int high){
	int temp[high+1];					// temporary storage array
	int i;
	int l1 = low;						// initialize to first index for left subarray
	int l2 = med + 1;					// initialize to first index for right subarray
	
	// this for loop has two counters: one for the left & another for right
	// subarrays. If we reach the end of one of the subarrays, that means the
	// returning array is sorted and the loop can break.
	for(i=low; l1<=med && l2<=high; i++){
		// if the current index @ left subarray less/equal to the current
		// index @ right subarray, increment the index of left subarray
		if(data[l1] <= data[l2])
			temp[i] = data[l1++];
		// if current index @ left subarray greater, then swap & increment
		// index on right subarray
		else
			temp[i] = data[l2++];
	}

	while(l1 <= med)
		temp[i++] = data[l1++];			// fill temp array w/ remaining of left subarray

	while(l2 <= high)
		temp[i++] = data[l2++];			// fill temp array w/ remaining of right subarray

	for(i=low; i<=high; i++)			// update the array we're interested in sorting
		data[i] = temp[i];
}

/***************************************************
 * function: sort
 * purpose: performs the merge sort algorithm on unsorted
 *		array so binary search can be performed
 * parameters: low and high indexes for the (sub)array
 *		and data array
 * return: nothing
****************************************************/
void sort(int* data, int low, int high){
	if(low < high){						// if the subarray is not of size 1
		int mid = (low+high)/2;			// compute mid (applying it for any index)
		sort(data, low, mid);			// lower half will sort until subarray size 1
		sort(data, mid+1, high);		// upper half will sort until subarray size 1
		merge(data, low, mid, high);	// merge adjacent subarrays
	}
	else								// return when subarray size is 1
		return;							// once sorted, begin merging adjacent subarrays
}

/***************************************************
 * function: binSearch
 * purpose: performs binary search on sorted array
 * parameters: data array, target value, start & end indexes
 * return: indicator of search success
****************************************************/
int binSearch(int* data, int target, int low, int high){
	int midpt = low + (high-low)/2;		// midpoint for subarray
	if(low == midpt){					// case for subarray of size 1
		if(target == data[midpt])		// if last option is target, target exists
			return midpt;
		return -1;						// if last option is not, target doesn't exist
	}
	else{
		if(target == data[midpt])		// if we find target in subarray size > 1
			return midpt;
		else if(target < data[midpt])	// if target < middle, binSearch on lower half
			return binSearch(data, target, low, midpt);
		else							// binSearch on upper half of array
			return binSearch(data, target, midpt+1, high);
	}
}