<<<<<<< HEAD
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_LINE_LEN 100

int main() {
	FILE *file = fopen("day1_test.txt", "r");
	if (!file) {
		perror("error reading .txt");
		return 1;
	}

	char lines[MAX_LINES][MAX_LINE_LEN];
	int line_count = 0;

	char buffer[MAX_LINE_LEN];
	while (line_count <= MAX_LINES && fgets(buffer, sizeof(buffer), file)) {
		buffer[strcspn(buffer, "\n")] = '\0';

		strcpy(lines[line_count], buffer);
		line_count++;
	}

	fclose(file);

	for (int i = 0; i < line_count; i++) {
		for (size_t j = 0; j < strlen(lines[i]); j++) {
			printf("Token: %c\n", lines[i][j]);
		}	
	}
	return 0;
}

=======
#include <stdio.h>
>>>>>>> 9a4729ca2436b267becae0c3c0264ffd8f97ab4b
