#define _POSIX_C_SOURCE 200112L  
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 100
#define MAX_LINES_LEN 256

// Helper function: trim leading and trailing whitespace.
void trim_whitespace(char *str) {
    if (str == NULL)
        return;
    char *end;

    // Trim leading space.
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0)
        return;

    // Trim trailing space.
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

// Reads the file into an array of strings.
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
    fclose(file);
    return 0;
}

int PartOne(char *file_name) {
    char lines[MAX_LINES][MAX_LINES_LEN];
    int line_count = 0;

    if (ReadFile(file_name, lines, &line_count)) {
        return 1;
    }

    int answer = 0;
    const int red_limit = 12, green_limit = 13, blue_limit = 14;

    for (int i = 0; i < line_count; i++) {
        // Save game id
        char *save_ptr1;
        char *game_id_str = strtok_r(lines[i], ":", &save_ptr1);
        trim_whitespace(game_id_str);

        char *id_token = strtok(game_id_str, " ");
        id_token = strtok(NULL, " ");
        int id = atoi(id_token);

        // The remainder of the line contains the cube data.
        char *cube_data = strtok_r(NULL, ":", &save_ptr1);
        trim_whitespace(cube_data);

        int is_valid_game = 1;

        // Save subset
        char *subset_save_ptr;
        char *subset = strtok_r(cube_data, ";", &subset_save_ptr);
        while (subset != NULL) {
            trim_whitespace(subset);

            int redCount = 0, greenCount = 0, blueCount = 0;

            // Save pair
            char *pair_save_ptr;
            char *pair = strtok_r(subset, ",", &pair_save_ptr);
            while (pair != NULL) {
                trim_whitespace(pair);
                // Parse the count and the color.
                char *inner_save_ptr;
                char *count_str = strtok_r(pair, " ", &inner_save_ptr);
                char *color = strtok_r(NULL, " ", &inner_save_ptr);
                
                int count = atoi(count_str);
                trim_whitespace(color);

                if (strcmp(color, "red") == 0) {
                    redCount += count;
                } else if (strcmp(color, "green") == 0) {
                    greenCount += count;
                } else if (strcmp(color, "blue") == 0) {
                    blueCount += count;
                }
                pair = strtok_r(NULL, ",", &pair_save_ptr);
            }

            if (redCount > red_limit || greenCount > green_limit || blueCount > blue_limit) {
                is_valid_game = 0;
            }
            subset = strtok_r(NULL, ";", &subset_save_ptr);
        }

        if (is_valid_game) {
            answer += id;
        }
    }

    return answer;
}

int main() {
    clock_t start_p1 = clock();
    int part_one = PartOne("day2.txt");
    clock_t end_p1 = clock();
    int execution_time_p1 = (int)(end_p1 - start_p1);

    /*
        clock_t start_p2 = clock();
        int part_two = PartTwo("day2.txt");
        clock_t end_p2 = clock();
        int execution_time_p2 = (int)(end_p2 - start_p2);
    */

    printf("Solution for day 1 part one: %d\nexecution time: %d ms\n", part_one, execution_time_p1);
    // printf("Solution for day 1 part two: %d\nexecution time: %d ms\n", part_two, execution_time_p2);

    return 0;
}

