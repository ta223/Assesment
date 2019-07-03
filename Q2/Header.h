#pragma once
#include "String.h"

template <typename data_type> 
class Qsort_list{

private:
	/*the qsort function checks the return value of this function:
	return value == 0: means v = w
	return value > 0: means v > w
	else v < w*/
	static int compare_fn(const void *v, const void *w) {	

		data_type *a =(data_type *)(v);
		data_type *b = (data_type *)(w);

		if (sizeof(data_type) == sizeof(char *)) {  return strcmp((char *)a, (char *)b); }

		double diff = (double )(*a - *b);	//any integer type can  be converted to double
		/*if data_type is of type float or double then the absolute value of *a-*b might be between 0 and 1.
		If this is the case and we return that value as int, then the function will actually return zero (because of
		implicit conversion from double/float to int).
		Hence, we need to store *a-*b in a double variable, which is valid for all integral types and the value is analyzed
		by the next 2 if statements*/
		if (diff > -1 && diff < 0) return -1;
		if (diff > 0 && diff < 1) return 1;

		return (int )(*a - *b);	

	}

	static int reverse_compare_fn(const void *v, const void *w) {

		data_type *a = (data_type *)(v);
		data_type *b = (data_type *)(w);

		if (sizeof(data_type) == sizeof(char)) { return strcmp((char *)a, (char *)b); }

		double diff = (double)(*a - *b);	//any integer type can  be converted to double
		if (diff > -1 && diff < 0) return 1;
		if (diff > 0 && diff < 1) return -1;
		return -1*(int)(*a - *b);

	}

	
	static int string_case_cmp_fn(const void *v, const void *w){

		class String *a = (String *)v;
		class String *b = (String *)w;

		return String::string_case_compare(*a, *b);
	}

public:

	static void quick_sort(void *base, size_t nitems, bool reverse_compare = false) {	
		if(reverse_compare == false)
			qsort(base, nitems, sizeof(data_type), Qsort_list<data_type>::compare_fn);	
		else qsort(base, nitems, sizeof(data_type), Qsort_list<data_type>::reverse_compare_fn);
	}

	static data_type* binary_search(void *key, void *list, size_t nitems, bool reverse_compare = false) {
		if(reverse_compare == false)
			bsearch(key, list, nitems, sizeof(data_type), Qsort_list<data_type>::compare_fn); 
		else bsearch(key, list, nitems, sizeof(data_type), Qsort_list<data_type>::reverse_compare_fn);
	}

	static void create_unique_list(int *size, data_type *list, bool pre_sorted) {

		int i, j;

		if (*size<2)
			return;

		if (!pre_sorted)
			qsort(list, *size, sizeof(data_type), Qsort_list<data_type>::compare_fn);

		for (i = 1, j = 0; i< *size; i++)
		{
			if (Qsort_list<data_type>::compare_fn(&list[j], &list[i]))
				list[++j] = list[i];
		}
		*size = j + 1;

	}

	//this needs a definition, which was not provided in the original C code
	static int _bsearch_insert_location(void *key, int amount, 
		size_t size, void *list, int (Qsort_list<data_type>::*cmp_fn)(const void *v, const void *w));

	static void bsearch_insert_location(void *key, int amount, void *list) {
		bsearch(key, list, amount, sizeof(data_type), int_cmp_fn);
	}


};
