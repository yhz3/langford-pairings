#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Style conventions
- snake case
- tabs for spacing

To convert all leading spaces to tabs:
1. F1
2. indentationToTabs
3. Enter
Solution taken from https://stackoverflow.com/questions/33974681/how-can-i-convert-tabs-to-spaces-and-vice-versa-in-an-existing-file

Notes:
- Do we need malloc for check in main??
*/

// Populates an array. Assumes that start will be the first term if start < end.
void generate_sequence(int *sequence, int start, int end) {
	if (end < start) {
		return;
	}
	int i = 0;	
	for (int term = start; term <= end; term += 2) {
		sequence[i] = term;
		printf("generate_sequence: the %dth term of the sequence is %d\n", i , sequence[i]);
		i ++;
	}
	return;
}

// Populates destination_sequence with the contents of source_sequence, but in reversed order. Assumes that the sizes of both arrays are size.
void generate_reversed_sequence(int *destination_sequence, const int *source_sequence, int size) {
	for (int i = 0; i < size; i++) {
		destination_sequence[i] = source_sequence[size - i - 1];
		printf("generate_reversed_sequence: the %dth term of the sequence is %d\n", i , destination_sequence[i]);
	}
	return;
}

// Adds the contents of source_array to destination_array starting at destination_array[index]. Assumes source_array contents will be contained within destination_array.
int add_to_array(int *destination_array, const int *source_array, int index, int source_size) {
	for (int i = 0; i < source_size; i++) {
		destination_array[index + i] = source_array[i];
		printf("add_to_array: the %dth term of the langford pairing is %d\n", index + i, destination_array[index + i]);
	}
	return source_size;
}

// Prints a langford pairing if one exists for [1, 1, 2, 2, ..., n, n].
// Algorithm from https://www.youtube.com/watch?v=Lju6aYms2EA
void create_langford_pairing(int n) {
	// Valid solutions do not exist under the conditions below
	if (n % 4 == 1 || n % 4 == 2 || n < 1) {
		printf("No results found.\n");
		return;
	}
	printf("Generating solution...\n");

	// Since n % 4 != 1 && n % 4 != 2, we know n % 4 == 0 || n % 4 == 3
	// We have 2 subcases: n % 4 == 0 and n % 4 == 3
	int x;
	// x = ceil(n / 4)
	if (n % 4 == 0) {
		printf("n = 0 (mod 4)\n");
		x = n / 4; 
	} else {
		printf("n = 3 (mod 4)\n");
		x = (n + 1) / 4;
	}
	printf("x is %d\n", x); // Checking that x was assigned properly

	// Creating a, b, c, d
	int a = (2 * x) - 1;
	printf("a initialized: %d\n", a);
	int b = (4 * x) - 2;
	printf("b initialized: %d\n", b);
	int c = (4 * x) - 1;
	printf("c initialized: %d\n", c);
	int d = 4 * x;
	printf("d initialized: %d\n", d);

	// For any sequence, the number of terms is end - start + 1

	// Creating p
	printf("Creating p\n");
	printf("p = odds in [1, ..., %d]\n", a - 1);
	// We know [1, ..., a - 1] has an even number of terms since a - 1 is even
	// So, we know n_p is exactly half the number of terms in [1, ..., a - 1]
	int n_p;
	if (1 > a - 1) {
		n_p = 0;
	} else {
		n_p = (a - 1 - 1 + 1) / 2;
	}
	printf("n_p = %d\n", n_p);
	int p[n_p];
	generate_sequence(p, 1, a - 1);
	for (int i = 0; i < n_p; i++) {
		printf("The %dth term of p is %d\n", i, p[i]);
	}

	// Creating q
	printf("Creating q\n");
	printf("q = evens in [2, ..., %d]\n", a - 1);
	// [2, ..., a - 1] starts with an even number and ends with an even number
	int n_q;
	if (2 > a - 1) {
		n_q = 0;
	} else {
		n_q = ((a - 1 - 2 + 1) / 2) + 1;
	}
	printf("n_q = %d\n", n_q);
	int q[n_q];
	generate_sequence(q, 2, a - 1);
	for (int i = 0; i < n_q; i++) {
		printf("The %dth term of q is %d\n", i, q[i]);
	}

	// Creating r
	printf("Creating r\n");
	printf("r = odds in [%d, ..., %d]\n", a + 2, b - 1);
	// [a + 2, ..., b - 1] starts with an odd number and ends with an odd number
	int n_r;
	if (a + 2 > b - 1) {
		n_r = 0;
	} else {
		n_r = ((b - 1 - (a + 2) + 1) / 2) + 1;
	}
	printf("n_r = %d\n", n_r);
	int r[n_r];
	generate_sequence(r, a + 2, b - 1);
	for (int i = 0; i < n_r; i++) {
		printf("The %dth term of r is %d\n", i, r[i]);
	}

	// Creating s
	printf("Creating s\n");
	printf("s = evens in [%d, ..., %d]\n", a + 1, b - 1);
	// [a + 1, ..., b - 1] starts with an even number and ends with an odd number
	int n_s;
	if (a + 1 > b - 1) {
		n_s = 0;
	} else {
		n_s = (b - 1 - (a + 1) + 1) / 2;
	}
	printf("n_s = %d\n", n_s);
	int s[n_s];
	generate_sequence(s, a + 1, b - 1);
	for (int i = 0; i < n_s; i++) {
		printf("The %dth term of s is %d\n", i, s[i]);
	}

	// Creating R[p]
	printf("Creating R[p]\n");
	int r_p[n_p];
	generate_reversed_sequence(r_p, p, n_p);
	for (int i = 0; i < n_p; i++) {
		printf("The %dth term of r_p is %d\n", i, r_p[i]);
	}

	// Creating R[q]
	printf("Creating R[q]\n");
	int r_q[n_q];
	generate_reversed_sequence(r_q, q, n_q);
	for (int i = 0; i < n_q; i++) {
		printf("The %dth term of r_q is %d\n", i, r_q[i]);
	}

	// Creating R[r]
	printf("Creating R[r]\n");
	int r_r[n_r];
	generate_reversed_sequence(r_r, r, n_r);
	for (int i = 0; i < n_r; i++) {
		printf("The %dth term of r_r is %d\n", i, r_r[i]);
	}

	// Creating R[s]
	printf("Creating R[s]\n");
	int r_s[n_s];
	generate_reversed_sequence(r_s, s, n_s);
	for (int i = 0; i < n_s; i++) {
		printf("The %dth term of r_s is %d\n", i, r_s[i]);
	}

	// Initializing langford_pairing array
	int langford_pairing[2 * n];

	// By the nature of how we will be combing the sequences together, we need a, b, c, and d as arrays
	int a_arr[] = {a};
	int b_arr[] = {b};
	int c_arr[] = {c};
	int d_arr[] = {d};

	// Utilize an index to keep track of where to insert the arrays into langford_pairing
	int index = 0;

	index += add_to_array(langford_pairing, r_s, index, n_s);
	index += add_to_array(langford_pairing, r_p, index, n_p);
	index += add_to_array(langford_pairing, b_arr, index, 1);
	index += add_to_array(langford_pairing, p, index, n_p);
	index += add_to_array(langford_pairing, c_arr, index, 1);
	index += add_to_array(langford_pairing, s, index, n_s);

	// Case where n % 4 == 0
	if (n % 4 == 0) {
		index += add_to_array(langford_pairing, d_arr, index, 1);
	// Case where n % 4 == 3
	} else {
		index += add_to_array(langford_pairing, a_arr, index, 1);
	}

	index += add_to_array(langford_pairing, r_r, index, n_r);
	index += add_to_array(langford_pairing, r_q, index, n_q);
	index += add_to_array(langford_pairing, b_arr, index, 1);
	index += add_to_array(langford_pairing, a_arr, index, 1);
	index += add_to_array(langford_pairing, q, index, n_q);
	index += add_to_array(langford_pairing, c_arr, index, 1);
	index += add_to_array(langford_pairing, r, index, n_r);
	
	// If n % 4 == 0 then we need these extra two
	if (n % 4 == 0) {
		index += add_to_array(langford_pairing, a_arr, index, 1);
		index += add_to_array(langford_pairing, d_arr, index, 1);
	}

	if (index > 2 * n) {
		fprintf(stderr, "ERROR: too many items inserted into langford pairing array\n");
	} else if (index < 2 * n) {
		fprintf(stderr, "ERROR: too few items inserted into langford pairing array\n");
	}

	// Printing out the langford pairing
	printf("[");
	for (int i = 0; i < 2 * n - 1; i++) {
		printf("%d, ", langford_pairing[i]);
	}
	printf("%d]\n", langford_pairing[2 * n - 1]);

	return;
}

// Returns a boolean stating whether sequence is a langford pairing.
bool is_langford_pairing(int size, const int sequence[]) {
	
	// Each index will represent the number of times we encounter a number.
	// number_count[i - 1] will represent the number of times we encounter the number i.
	int number_count[size / 2];
	printf("creating a counting array of size %d\n", size/2);
	for (int i = 0; i < size / 2; i++) {
		number_count[i] = 0;
	}

	// Iterating through the sequence to count the occurences of each number
	for (int i = 0; i < size; i++) {
		// Checking if sequence[i] is a valid number in the sequence
		if (0 >= sequence[i] || sequence[i] > size / 2) {
			printf("invalid sequence number!\n");
			return false;
		}
		number_count[sequence[i] - 1] += 1;
		printf("observed one occurence of %d\n", sequence[i]);
		printf("total occurences of %d: %d\n", sequence[i], number_count[sequence[i] - 1]);
	}

	// Iterating through number_count to ensure there are exactly two copies of each number
	for (int i = 0; i < size / 2; i++) {
		if (number_count[i] != 2) {
			printf("less than two copies of each!");
			return false;
		}
	} 
	printf("two copies of each exist!\n");

	// Iterating through the sequence to ensure proper spacing in the sequence
	for (int i = 0; i < size; i++) {
		bool left_pair = false;
		bool right_pair = false;
		// Checking that a pairing with a term on the left would be valid
		if (0 <= i - sequence[i] - 1) {
			printf("Checking for a left pairing of %d (root index %d): %d\n", sequence[i], i, i - sequence[i] - 1);
			left_pair = (sequence[i] == sequence[i - sequence[i] - 1]);
		}
		// Checking that a pairing with a term on the right would be valid
		if (i + sequence[i] + 1 <= size) {
			printf("Checking for a right pairing of %d (root index %d): %d\n", sequence[i], i, i + sequence[i] + 1);
			right_pair = (sequence[i] == sequence[i + sequence[i] + 1]);
		}
		if (!left_pair && !right_pair) {
			return false;
		}
	}

	return true;
}

int main(int argc, char **argv) {
	// Checking if the first argument is -h or empty 
	if (argc == 1 || strcmp(argv[1], "-h") == 0) {
		fprintf(stderr, "usage: %s [-h] -c n | num... \n", argv[0]);
		// On Piazza we are told that this specific error should return 0 https://piazza.com/class/lr04m5y3web1yr/post/485
		return 0;
	// Create mode
	} else if (strcmp(argv[1], "-c") == 0) {
		// Checking if not enough arguments
		if (argc < 3) {
			fprintf(stderr, "%s: -c option requires an argument.\n", argv[0]);
			return 1;
		// Checking if too many arguments
		} else if (argc >3) {
			fprintf(stderr, "%s: -c option received too many arguments.\n", argv[0]);
			return 1;
		} 
		// Checking if the argument is an integer
		// Attempting to convert argument from string to int
		char *endptr;
		int value = (int)strtol(argv[2], &endptr, 10); // Typecasting since strtol converts strings to longs, not ints
		if (endptr && endptr[0] != '\0') {
			fprintf(stderr, "error: %s is not an integer.\n", argv[2]);
			return 1;
		} else {
			fprintf(stdout, "Creating a langford pairing with n=%d\n", value);
			create_langford_pairing(value);
		}
	// Check mode
	} else {
		// Creating the integer array and allocating memory
		int sequence[argc - 1];
//		int *sequence = malloc(sizeof(int) * argc - 1);
		for (int i = 1; i < argc; i ++) {
			char * endptr; // Code copied from A1
			int value = strtol(argv[i], &endptr, 10);
			if (endptr && endptr[0] != '\0') {
				fprintf(stderr, "error: %s is not an integer.\n", argv[i]);
				return 1;
			}
			sequence[i - 1] = value;
			printf("sequence index %d: %d\n", i - 1, sequence[i - 1]); // Checking if the array is being populated properly
		}
		// Printing the sequence out
		printf("Your sequence: ["); 
		for (int i = 0; i < argc - 2; i++) {
			printf("%d, ", sequence[i]);
		}
		printf("%d]\n", sequence[argc - 2]);
		// Checking if the array is a Langford pairing
		if (is_langford_pairing(argc - 1, sequence))  {
			printf("It is a langford pairing!\n");
		} else {
			printf("It is NOT a langford pairing.\n"); 
		}
//		free(sequence);
	}
	return 0;
}
