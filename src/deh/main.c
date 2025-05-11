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

smartphone smartphones[MAX_SMARTPHONES];
int smartphone_count = 0;

// Function prototypes
void display_smartphones(smartphone smartphones[], int smartphone_count) {
    // Display all smartphones
    for (int i = 0; i < smartphone_count; i++) {
        printf("Brand: %s\n", smartphones[i].brand);
        printf("Model: %s\n", smartphones[i].model);
        printf("Year: %d\n", smartphones[i].year);
        printf("Memory: %d GB\n", smartphones[i].memory_capacity);
        printf("Price: %.2f\n", smartphones[i].price);
        printf("\n");
    }
}

void display_brand(smartphone smartphones[], int smartphone_count) {
    printf("Enter the brand of the smartphone you want to find:\n");
    // Create a temporary brand variable to hold user input
    char temp_brand[MAX_BRAND];
    fgets(temp_brand, MAX_BRAND, stdin);
    temp_brand[strcspn(temp_brand, "\n")] = '\0';  // Remove newline character

    int found = 0;  // Flag to track if the brand is found

    for (int i = 0; i < smartphone_count; i++) {
        if (strcmp(temp_brand, smartphones[i].brand) == 0) {
            // If brand matches, display the smartphone details
            printf("Brand: %s\n", smartphones[i].brand);
            printf("Model: %s\n", smartphones[i].model);
            printf("Year: %d\n", smartphones[i].year);
            printf("Memory: %d GB\n", smartphones[i].memory_capacity);
            printf("Price: %.2f\n", smartphones[i].price);
            printf("\n");
            found = 1;  // Set flag to true since we found a match
        }
    }

    // If no matching brand was found
    if (!found) {
        printf("No smartphones found for brand: %s\n", temp_brand);
    }
}

void display_by_price_range(smartphone smartphones[], int smartphone_count) {
    // Function to display smartphones by price range (to be implemented)
}

void insert_new_smartphone(smartphone smartphones[], int *smartphone_count) {
    // Temporary smartphone to be inserted
    smartphone temp_smartphone;
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
    if (*smartphone_count < MAX_SMARTPHONES) {
        int i;
        // Start from the last inserted smartphone in the array
        for (i = *smartphone_count - 1; i >= 0 && smartphones[i].price > temp_smartphone.price; i--) {
            smartphones[i + 1] = smartphones[i];  // Shift the smartphone to the right
        }
        smartphones[i + 1] = temp_smartphone;  // Insert the new smartphone at the correct position
        (*smartphone_count)++;  // Increment the count
    } else {
        printf("Error: Cannot add more smartphones, maximum limit reached.\n");
    }

    // Display the updated list
    printf("Updated list of smartphones:\n");
    for (int i = 0; i < *smartphone_count; i++) {
        printf("Brand: %s\n", smartphones[i].brand);
        printf("Model: %s\n", smartphones[i].model);
        printf("Year: %d\n", smartphones[i].year);
        printf("Memory: %d GB\n", smartphones[i].memory_capacity);
        printf("Price: %.2f\n", smartphones[i].price);
        printf("\n");
}

void remove_smartphone_by_memory(smartphone smartphones[], int *smartphone_count) {
    // Function to remove smartphones by memory (to be implemented)
}

void exit_program() {
    // Function to exit program (to be implemented)
}

int main() {
    FILE *file = fopen("smartphones.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Loop to read all records from the file
    while (fgets(smartphones[smartphone_count].brand, MAX_BRAND, file) != NULL) {
        if (fgets(smartphones[smartphone_count].model, MAX_MODEL, file) == NULL) {
            break;  // If we can't read the model, break out of the loop
        }

        fscanf(file, "%i", &smartphones[smartphone_count].year);
        fgetc(file);  // Consume the '\n' left by fscanf after reading 'year'

        fscanf(file, "%i", &smartphones[smartphone_count].memory_capacity);
        fgetc(file);  // Consume the '\n' left by fscanf after reading 'memory_capacity'

        fscanf(file, "%f", &smartphones[smartphone_count].price);
        fgetc(file);  // Consume the '\n' left by fscanf after reading 'price'

        smartphone_count++; // Increment the counter

        if (smartphone_count >= MAX_SMARTPHONES) {
            break;  // Prevent reading past the limit
        }
    }
    fclose(file);

    while (1) {
        // Present the menu to the user
        printf("Menu:\n");
        printf("1. Display all smartphones\n");
        printf("2. Display smartphones by brand\n");
        printf("3. Display smartphones within a price range\n");
        printf("4. Add a new smartphone\n");
        printf("5. Remove smartphones with memory below a threshold\n");
        printf("6. Exit\n");
        printf("Choose an option: ");

        int option;
        scanf("%d", &option);
        getchar();  // to consume newline left by scanf

        switch (option) {
            case 1:
                display_smartphones(smartphones, smartphone_count);
                break;
            case 2:
                display_brand(smartphones, smartphone_count);
                break;
            case 3:
                display_by_price_range(smartphones, smartphone_count);
                break;
            case 4:
                insert_new_smartphone(smartphones, &smartphone_count);
                break;
            case 5:
                remove_smartphone_by_memory(smartphones, &smartphone_count);
                break;
            case 6:
                exit_program();
                return 0;  // Exit the program
            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    }
}
