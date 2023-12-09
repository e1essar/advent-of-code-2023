#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

void reverseArray(int arr[], size_t size) {
    size_t start = 0;
    size_t end = size - 1;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

int isAllZeros(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (array[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int func(int* nums, int amount) {
    int count = 0;
    while(!isAllZeros(nums, amount)) {
        for (int i = 0; i < amount - 1; i++) {
            nums[i] = nums[i + 1] - nums[i];
        }
        count += nums[amount-1];
        amount--;
        
    }
    return count;
}

int main() {
    FILE *file;
    char line[MAX_LENGTH];
    int **numbers = NULL; 
    size_t row = 0;
    size_t rowAmount[MAX_LENGTH];
    int size = 0;

    file = fopen("day09.txt", "r");
    
    if (file == NULL) {
        perror("Open Error");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, " ");
        size_t count = 0;

        numbers = realloc(numbers, (row + 1) * sizeof(int*));

        rowAmount[row] = 0;
        numbers[row] = NULL;

        while (token != NULL) {
            numbers[row] = realloc(numbers[row], (count + 1) * sizeof(int*));
            numbers[row][count] = atoi(token);
            count++;

            token = strtok(NULL, " ");
        }

        rowAmount[row] = count;
        row++;
        size++;
    }

    fclose(file);

    int result = 0;
    for(int i = 0; i < size;i++) {
        reverseArray(numbers[i], rowAmount[i]);
        result += func(numbers[i], rowAmount[i]);
    }
    printf("%d", result);
    free(numbers);

    return 0;
}
