#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wchar.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 256

int ReadFile(char* file_name, char lines[MAX_LINES][MAX_LINE_LEN], int *line_count) {
	FILE *file = fopen(file_name, "r");
	if (!file) {
		perror("error reading .txt");
		return 1;
	}

	*line_count = 0;
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

		for (size_t j = 0; j < strlen(lines[i]); j++) {
			if (isdigit(lines[i][j])) {
				first = lines[i][j];
				break;
			}
		}	

		for (size_t j = len - 1; j >= 0; j--) {
			if (isdigit(lines[i][j])) {
				last = lines[i][j];
				break;
			}
		}

		if (first && last) {
			int num = (first - '0') * 10 + (last - '0');
			answer += num;
		}
	}

	return answer;
}

int main() {
	clock_t start = clock();

	int part_one = PartOne("day1.txt");

	clock_t end = clock();
	int execution_time = (int)(end - start);

	printf("Solution for day 1 part one: %d\nexecution time: %d ms\n", part_one, execution_time);

	return 0;
}

