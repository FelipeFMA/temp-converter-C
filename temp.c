#include <stdio.h>
#include <stdbool.h>

/* Constants for physical values */
#define KELVIN_OFFSET 273.15
#define FAHRENHEIT_FACTOR (9.0/5.0)
#define FAHRENHEIT_OFFSET 32.0

/* Constants for temperature limits */
#define MIN_KELVIN 0.0
#define MIN_CELSIUS -273.15
#define MIN_FAHRENHEIT -459.67

/* Error codes */
#define SUCCESS 0
#define ERROR_INVALID_CHOICE 1
#define ERROR_INVALID_TEMPERATURE 2

/* Checks if the temperature is within physical limits */
bool isValidTemperature(float temp, int type) {
    switch (type) {
        case 1: return temp >= MIN_CELSIUS;
        case 2: return temp >= MIN_FAHRENHEIT;
        case 3: return temp >= MIN_KELVIN;
        default: return false;
    }
}

/* Converts Celsius temperature to other scales */
void celsiusToOther(float celsius) {
    float fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    float kelvin = celsius + KELVIN_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f °C = %.2f °F\n", celsius, fahrenheit);
    printf("%.2f °C = %.2f K\n", celsius, kelvin);
}

/* Converts Fahrenheit temperature to other scales */
void fahrenheitToOther(float fahrenheit) {
    float celsius = (fahrenheit - FAHRENHEIT_OFFSET) / FAHRENHEIT_FACTOR;
    float kelvin = celsius + KELVIN_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f °F = %.2f °C\n", fahrenheit, celsius);
    printf("%.2f °F = %.2f K\n", fahrenheit, kelvin);
}

/* Converts Kelvin temperature to other scales */
void kelvinToOther(float kelvin) {
    float celsius = kelvin - KELVIN_OFFSET;
    float fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f K = %.2f °C\n", kelvin, celsius);
    printf("%.2f K = %.2f °F\n", kelvin, fahrenheit);
}

/* Clears the input buffer */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Displays the options menu */
void displayMenu() {
    printf("\nTemperature Converter\n");
    printf("------------------------\n");
    printf("1. Celsius\n");
    printf("2. Fahrenheit\n");
    printf("3. Kelvin\n");
    printf("------------------------\n");
}

int main() {
    int choice;
    float temp;
    
    displayMenu();
    printf("Enter the option number: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid input!\n");
        return ERROR_INVALID_CHOICE;
    }
    
    clearInputBuffer();
    
    if (choice < 1 || choice > 3) {
        printf("Error: Invalid option! Choose between 1 and 3.\n");
        return ERROR_INVALID_CHOICE;
    }
    
    printf("Enter the temperature: ");
    if (scanf("%f", &temp) != 1) {
        printf("Error: Invalid temperature!\n");
        return ERROR_INVALID_TEMPERATURE;
    }
    
    if (!isValidTemperature(temp, choice)) {
        printf("Error: Temperature below absolute zero is not possible!\n");
        return ERROR_INVALID_TEMPERATURE;
    }
    
    switch (choice) {
        case 1:
            celsiusToOther(temp);
            break;
        case 2:
            fahrenheitToOther(temp);
            break;
        case 3:
            kelvinToOther(temp);
            break;
    }
    
    return SUCCESS;
}
