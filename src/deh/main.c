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
    // struct variable to store the smartphones [size]
    smartphone smartphones[MAX_SMARTPHONES];
    int smartphone_count = 0;

    // Loop 1= Read all records from the file
    while (fgets(smartphones[smartphone_count].brand, MAX_BRAND, file) != NULL && fgets(smartphones[smartphone_count].model, MAX_MODEL, file) != NULL) {

        // 1) Read string data and remove newline
        smartphones[smartphone_count].brand[strcspn(smartphones[smartphone_count].brand, "\n")] = '\0';
        smartphones[smartphone_count].model[strcspn(smartphones[smartphone_count].model, "\n")] = '\0';

        // Read numeric data
        fscanf(file, "%i", &smartphones[smartphone_count].year);
        fscanf(file, "%i", &smartphones[smartphone_count].memory_capacity);
        fscanf(file, "%f", &smartphones[smartphone_count].price);

        smartphone_count++;  // increment the counter to indicate the next position in the array

        // Prevent reading past the limit
        if (smartphone_count >= MAX_SMARTPHONES) {
            break;
        }

        // Consume the newline left by fscanf
        fgetc(file);
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

    // Here you would typically read the data for the new smartphone into temp_smartphone.
    // For this example, I'll assume the new smartphone is already filled with data manually.
    strcpy(temp_smartphone.brand, "NewBrand");
    strcpy(temp_smartphone.model, "NewModel");
    temp_smartphone.year = 2025;
    temp_smartphone.memory_capacity = 128;
    temp_smartphone.price = 1500.00;

    // Start from the last inserted smartphone in the array
    for (int i = smartphone_count - 1; i >= 0 && smartphones[i].price > temp_smartphone.price; i--) {
        smartphones[i + 1] = smartphones[i];  // Shift the smartphone to the right
    }
    // Insert the new smartphone at the correct position
    smartphones[smartphone_count] = temp_smartphone;  // Insert the new smartphone
    smartphone_count++;  // Increment the count of smartphones

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

