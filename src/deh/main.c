#include <stdio.h>
#include <string.h>

#define MAX_BRAND 20  // max 20 characters for brand
#define MAX_MODEL 30  // max 30 characters for model
#define MAX_SMARTPHONES 40  // max number of smartphones

typedef struct {
    char brand[MAX_BRAND];
    char model[MAX_MODEL];
    int year;
    int memory_capacity;
    float price;
} smartphone;

int main() {
    FILE *file = fopen("smartphones.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    smartphone smartphones[MAX_SMARTPHONES];
    int smartphone_count = 0;

    // Loop to read all records from the file
    while (fgets(smartphones[smartphone_count].brand, MAX_BRAND, file) != NULL && fgets(smartphones[smartphone_count].model, MAX_MODEL, file) != NULL) {
        // 1) Read string data-fgets
        smartphones[smartphone_count].brand[strcspn(smartphones[smartphone_count].brand, "\n")] = '\0';
        smartphones[smartphone_count].model[strcspn(smartphones[smartphone_count].model, "\n")] = '\0';
        // Read numeric data-fscanf
        fscanf(file, "%i", &smartphones[smartphone_count].year);
        fscanf(file, "%i", &smartphones[smartphone_count].memory_capacity);
        fscanf(file, "%f", &smartphones[smartphone_count].price);

        smartphone_count++; // increment the counter to indicate the next position in the array

        // Prevent reading past the limit
        if (smartphone_count >= MAX_SMARTPHONES) {
            break;
        }
    }
    // Display the smartphones read from the file
    for (int i = 0; i < smartphone_count; i++) {
        printf("Brand: %s\n", smartphones[i].brand);
        printf("Model: %s\n", smartphones[i].model);
        printf("Year: %d\n", smartphones[i].year);
        printf("Memory: %d GB\n", smartphones[i].memory_capacity);
        printf("Price: %.2f\n", smartphones[i].price);
        printf("\n");
    }

    // Temporary smartphone to be inserted
    smartphone temp_smartphone;
    // Read the new smartphone data (this could be from user input or a new file line)
    printf("Enter new smartphone data:\n");
    printf("Brand: ");
    fgets(temp_smartphone.brand, MAX_BRAND, stdin);
    printf("Model: ");
    fgets(temp_smartphone.model, MAX_MODEL, stdin);
    printf("Year: ");
    scanf("%d", &temp_smartphone.year);
    printf("Memory (GB): ");
    scanf("%d", &temp_smartphone.memory_capacity);
    printf("Price: ");
    scanf("%f", &temp_smartphone.price);

    // Remove the newline character that fgets() may leave behind
    temp_smartphone.brand[strcspn(temp_smartphone.brand, "\n")] = '\0';
    temp_smartphone.model[strcspn(temp_smartphone.model, "\n")] = '\0';

    // Insert the new smartphone in asked order by their price
    if (smartphone_count < MAX_SMARTPHONES) {
        int i;
        // Start from the last inserted smartphone in the array
        for (i = smartphone_count - 1; i >= 0 && smartphones[i].price > temp_smartphone.price; i--) {
            smartphones[i + 1] = smartphones[i];  // Shift the smartphone to the right
        }
        smartphones[i + 1] = temp_smartphone;  // Insertion of the new smartphone at the correct position
        smartphone_count++;  // Increment the count
    } else {
        printf("Error: Cannot add more smartphones, maximum limit reached.\n");
    }

    // Display the updated list
    printf("Updated list of smartphones:\n");
    for (int i = 0; i < smartphone_count; i++) {
        printf("Brand: %s\n", smartphones[i].brand);
        printf("Model: %s\n", smartphones[i].model);
        printf("Year: %d\n", smartphones[i].year);
        printf("Memory: %d GB\n", smartphones[i].memory_capacity);
        printf("Price: %.2f\n", smartphones[i].price);
        printf("\n");
    }
    fclose(file);
    return 0;
}
