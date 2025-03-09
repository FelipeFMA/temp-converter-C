#include <stdio.h>
#include <stdbool.h>

/* Constants for menu options */
#define MENU_OPTION_CELSIUS 1
#define MENU_OPTION_FAHRENHEIT 2
#define MENU_OPTION_KELVIN 3

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
#define ERROR_INVALID_INPUT 3

/**
 * Validates if the temperature is within physical limits
 * 
 * @param temp The temperature value to validate
 * @param type The temperature scale (1=Celsius, 2=Fahrenheit, 3=Kelvin)
 * @return true if temperature is valid, false otherwise
 */
bool isValidTemperature(float temp, int type) {
    switch (type) {
        case MENU_OPTION_CELSIUS: return temp >= MIN_CELSIUS;
        case MENU_OPTION_FAHRENHEIT: return temp >= MIN_FAHRENHEIT;
        case MENU_OPTION_KELVIN: return temp >= MIN_KELVIN;
        default: return false;
    }
}

/**
 * Converts Celsius temperature to other scales
 * 
 * @param celsius The temperature in Celsius to convert
 */
void celsiusToOther(float celsius) {
    float fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    float kelvin = celsius + KELVIN_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f °C = %.2f °F\n", celsius, fahrenheit);
    printf("%.2f °C = %.2f K\n", celsius, kelvin);
}

/**
 * Converts Fahrenheit temperature to other scales
 * 
 * @param fahrenheit The temperature in Fahrenheit to convert
 */
void fahrenheitToOther(float fahrenheit) {
    float celsius = (fahrenheit - FAHRENHEIT_OFFSET) / FAHRENHEIT_FACTOR;
    float kelvin = celsius + KELVIN_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f °F = %.2f °C\n", fahrenheit, celsius);
    printf("%.2f °F = %.2f K\n", fahrenheit, kelvin);
}

/**
 * Converts Kelvin temperature to other scales
 * 
 * @param kelvin The temperature in Kelvin to convert
 */
void kelvinToOther(float kelvin) {
    float celsius = kelvin - KELVIN_OFFSET;
    float fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    
    printf("\nConversion results:\n");
    printf("%.2f K = %.2f °C\n", kelvin, celsius);
    printf("%.2f K = %.2f °F\n", kelvin, fahrenheit);
}

/**
 * Clears the input buffer to prevent scanf issues
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Displays the temperature conversion menu
 */
void displayMenu() {
    printf("\nTemperature Converter\n");
    printf("------------------------\n");
    printf("1. Celsius\n");
    printf("2. Fahrenheit\n");
    printf("3. Kelvin\n");
    printf("------------------------\n");
}

/**
 * Validates and reads an integer input
 * 
 * @param prompt The message to display to the user
 * @param value Pointer to store the input value
 * @return true if input is valid, false otherwise
 */
bool readIntInput(const char* prompt, int* value) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

/**
 * Validates and reads a floating-point input
 * 
 * @param prompt The message to display to the user
 * @param value Pointer to store the input value
 * @return true if input is valid, false otherwise
 */
bool readFloatInput(const char* prompt, float* value) {
    printf("%s", prompt);
    if (scanf("%f", value) != 1) {
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

int main() {
    int choice;
    float temp;
    bool isValid;
    
    displayMenu();
    
    // Validate menu choice
    isValid = readIntInput("Enter the option number: ", &choice);
    if (!isValid) {
        printf("Error: Invalid input! Please enter a number.\n");
        return ERROR_INVALID_INPUT;
    }
    
    if (choice < MENU_OPTION_CELSIUS || choice > MENU_OPTION_KELVIN) {
        printf("Error: Invalid option! Choose between 1 and 3.\n");
        return ERROR_INVALID_CHOICE;
    }
    
    // Validate temperature input
    isValid = readFloatInput("Enter the temperature: ", &temp);
    if (!isValid) {
        printf("Error: Invalid temperature! Please enter a number.\n");
        return ERROR_INVALID_INPUT;
    }
    
    if (!isValidTemperature(temp, choice)) {
        printf("Error: Temperature below absolute zero is not possible!\n");
        return ERROR_INVALID_TEMPERATURE;
    }
    
    // Perform conversion based on user choice
    switch (choice) {
        case MENU_OPTION_CELSIUS:
            celsiusToOther(temp);
            break;
        case MENU_OPTION_FAHRENHEIT:
            fahrenheitToOther(temp);
            break;
        case MENU_OPTION_KELVIN:
            kelvinToOther(temp);
            break;
    }
    
    return SUCCESS;
}
