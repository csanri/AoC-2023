#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 256
#define MAX_LINES_LEN 256

typedef struct {
	int red;
	int green;
	int blue;
} Cubes;

typedef struct {
	Cubes *cubes;
} Set;

void trim_whitespace(char *str) {
	if (str == NULL)
		return;
	char *end;

	while (isspace((unsigned char)*str)) str++;
	if (*str == 0)
		return;

	end = str + strlen(str) - 1;

	while (end > str && isspace((unsigned char)*end)) end--;
	*(end + 1) = '\0';
}

int ReadFile(const char *file_name, char lines[MAX_LINES][MAX_LINES_LEN], int *line_count) {
	FILE *file = fopen(file_name, "r");

	if (!file) {
		perror("error opening .txt");
		return 1;
	}
	
	char buffer[MAX_LINES_LEN];

	while (*line_count < MAX_LINES && fgets(buffer, sizeof(buffer), file)) {
		buffer[strcspn(buffer, "\n")] = '\0';
		strcpy(lines[*line_count], buffer);
		(*line_count)++;
	}

	return 0;
}

int PartOne(char *file_name) {
	char lines[MAX_LINES][MAX_LINES_LEN];
	int line_count = 0;

	ReadFile(file_name, lines, &line_count);

	for (int i = 0; i < line_count; i++) {
		char* game_id = strtok(lines[i], ":");
		trim_whitespace(game_id);

		char *cube_data = strtok(NULL, "");
		trim_whitespace(cube_data);

		char *subset = strtok(cube_data, ";");
		while (subset != NULL) {
			printf("Before: %s\n", subset);
			trim_whitespace(subset);
			subset = strtok(NULL, ";");
			printf("After: %s\n", subset);
		}
	}

	return 0;
}

int main() {
	PartOne("day2_test.txt");
	return 0;
}
