#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 256

typedef struct {
	char* key;
	int value;
} KeyValue;

typedef struct {
	KeyValue* items;
	size_t size;
	size_t capacity;
} Dictionary;

// Initialize dictionary
void dict_init(Dictionary* dict, size_t initial_size) {
	dict->items = malloc(initial_size * (sizeof(KeyValue)));
	dict->size = 0;
	dict->capacity = initial_size;
}

// Add element to dictionary
void dict_add(Dictionary* dict, const char* key, int value) {
	
	// Check if we need to expand size	
	if (dict->size >= dict->capacity) {
		dict->capacity *= 2;
		dict->items = realloc(dict->items, dict->capacity * sizeof(KeyValue));
	}

	// Allocate memory for key and store
	dict->items[dict->size].key = malloc(strlen(key) + 1);
	strcpy(dict->items[dict->size].key, key);

	// Store value
	dict->items[dict->size].value = value;
	dict->size++;
}

// Get value by key
int dict_get(Dictionary* dict, const char* key) {
	for (size_t i = 0; i < dict->size; i++) {
		if (strcmp(key, dict->items[i].key) == 0) {
			return dict->items[i].value;	
		}	
	}
	return 0;
}

int ReadFile(char* file_name, char lines[MAX_LINES][MAX_LINE_LEN], int *line_count) {
	FILE *file = fopen(file_name, "r");
	if (!file) {
		perror("error reading .txt");
		return 1;
	}

	char buffer[MAX_LINE_LEN];

	while (*line_count <= MAX_LINES && fgets(buffer, sizeof(buffer), file)) {
		buffer[strcspn(buffer, "\n")] = '\0';
		strcpy(lines[*line_count], buffer);
		(*line_count)++;
	}

	fclose(file);
	return 0;
}

int PartOne(char* file_name) {
	char lines[MAX_LINES][MAX_LINE_LEN];
	int line_count = 0;

	if (ReadFile(file_name, lines, &line_count) != 0) {
		return 1;
	}

	int answer = 0;

	for (int i = 0; i < line_count; i++) {
		char first = '\0';
		char last = '\0';
		int len = strlen(lines[i]);

		// Checkeing for numbers from the left side
		for (size_t j = 0; j < strlen(lines[i]); j++) {
			if (isdigit(lines[i][j])) {
				first = lines[i][j];
				break;
			}
		}	

		// Checking for numbers from the right side
		for (int j = (int)len - 1; j >= 0; j--) {
			if (isdigit(lines[i][j])) {
				last = lines[i][j];
				break;
			}
		}

		// Making chars to numbers using ASCII
		if (first && last) {
			int num = (first - '0') * 10 + (last - '0');
			answer += num;
		}
	}

	return answer;
}

int PartTwo(char* file_name) {
	char lines[MAX_LINES][MAX_LINE_LEN];
	int line_count;

	if (ReadFile(file_name, lines, &line_count) != 0) {
		return 1;
	}

	Dictionary dict;
	dict_init(&dict, 9);

	const char* number_words[] = {
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine",
		NULL
	};

	for (int i = 0; number_words[i] != NULL; i++) {
		dict_add(&dict, number_words[i], i + 1);
	}

	int answer = 0;

	for (int i = 0; i < line_count; i++) {
		int len = strlen(lines[i]);
		int first = -1, last = -1;

		for (size_t j = 0; j < strlen(lines[i]); j++) {
			int value = 0;

			// Skip if is digit
			if (isdigit(lines[i][j])) {
				value = lines[i][j] - '0';
			} else {
				// Numbers are 3-5 lentgh strings
				for (size_t k = 3; k <= 5 && j <= len - k; k++) {
					char buffer[6] = {0};
					strncpy(buffer, &lines[i][j], k);

					// Store the value in temp if match is found
					int val = dict_get(&dict, buffer);
					if (val > 0) {
						value = val;
						break;
					}
				}	
			}

			// Store values
			if (value > 0) {
				// Stores first value
				if (first == -1) 
					first = value;
				// Stores the last value in the loop so the last number
				last = value;
			}
		}

		if (first != -1 && last != -1) {
			answer += first * 10 + last;
		}
	}

	// Cleanup dictionary memory
    for (size_t i = 0; i < dict.size; i++) {
        free(dict.items[i].key);
    }
    free(dict.items);

	return answer;
}

int main() {
	clock_t start_p1 = clock();
	int part_one = PartOne("day1.txt");
	clock_t end_p1 = clock();
	int execution_time_p1 = (int)(end_p1 - start_p1);

	clock_t start_p2 = clock();
	int part_two = PartTwo("day1.txt");
	clock_t end_p2 = clock();
	int execution_time_p2 = (int)(end_p2 - start_p2);

	printf("Solution for day 1 part one: %d\nexecution time: %d ms\n", part_one, execution_time_p1);
	printf("Solution for day 1 part two: %d\nexecution time: %d ms\n", part_two, execution_time_p2);

	return 0;
}

