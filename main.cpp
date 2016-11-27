/*
    This program simulates the temperature change across a plate as it's heated with a constant temperature of
    100 degrees Fahrenheit on two opposite ends of the plate.
*/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int PLATE_SIZE = 20; 
const int PLATE_COLUMNS = 20;
const int PLATE_ROWS = 20;
const double CORNER = 0;
const int ARRAY_SIZE = 19;
const double BOUNDARY_TEMPERATURE = 100;
const int NUMBER_OF_SURROUNDING_TEMPERATURES = 4;
const double INITIAL_TEMPERATURE = 100;
const double MAX_TEMP_CHANGE = 0.1;

/*
    Create the plate by initializing an array to the given specifications
    @param plate - An empty 20X20 array
*/
void initialize_plate(double plate[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            if (i == CORNER && j == CORNER || i == CORNER && j == ARRAY_SIZE || i == ARRAY_SIZE && j == CORNER || i == ARRAY_SIZE && j == ARRAY_SIZE) {
                plate[i][j] = CORNER;
            }
            else if (i == CORNER && j != CORNER || i == CORNER && j != ARRAY_SIZE || i == ARRAY_SIZE && j != CORNER || i == ARRAY_SIZE && j != ARRAY_SIZE) {
                plate[i][j] = BOUNDARY_TEMPERATURE;
            }
            else {
                plate[i][j] = CORNER;
            }
        }
        cout << endl;
    }
}

/*
    Print the array
    @param array - The array to be printed
*/
void print_array(const double array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            cout << fixed << setprecision(4) << setw(10) << array[i][j];
        }
        cout << endl;
    }
}

/*
    Copy values from the new array back to the old array so we can calculate the next iteration
    @param old_array - The array before the latest iteration
    @param new_array - The array after new temperatures have been calculated for the current iteration
*/
void copy_array(double old_array[][PLATE_SIZE], const double new_array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            old_array[i][j] = new_array[i][j];
        }
    }
}

/*
    Check whether or not the temperature change at all points on the plate is greater than 0.1
    @param old_array - The array before the latest iteration
    @param new_array - The array after new temperatures have been calculated for the current iteration
    @param largest_temp_change - The largest temperature change observed between any two corresponding cells in the old and new arrays
    @return largest_temp_change
*/
double check_temp_change(const double old_array[][PLATE_SIZE], const double new_array[][PLATE_SIZE], double& largest_temp_change) {
    for (int i = 1; i < ARRAY_SIZE; i++) {
        for (int j = 1; j < ARRAY_SIZE; j++) {
            if (new_array[i][j] != CORNER) {
                double temp_change = new_array[i][j] - old_array[i][j];
                if (new_array[i][j] - old_array[i][j] < largest_temp_change) {
                    largest_temp_change = temp_change;
                }
            }
        }
    }
    return largest_temp_change;
}

/*
    Calculate new temperatures on the plate
    @param old_array - The array that we're using to calculate the new temperatures for each cell
    @param new_array - The new array that contains the newly calculated temperatures
*/
void calculate_new_temperatures(const double old_array[][PLATE_SIZE], double new_array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            if (i == CORNER || i == ARRAY_SIZE || j == CORNER || j == ARRAY_SIZE) {
                new_array[i][j] = old_array[i][j];
            }
            else {
                new_array[i][j] = (old_array[i - 1][j] + old_array[i][j - 1] + old_array[i + 1][j] + old_array[i][j + 1]) / NUMBER_OF_SURROUNDING_TEMPERATURES;
            }
        }
    }
}

/*
    Write the final plate values to a .csv file
    @param final_array - The final iteration of the plate where no values changed by more than 0.1 degree from the previous iteration
*/
void save_to_csv(const double final_array[][PLATE_SIZE]) {
    ofstream output;
    output.open("output.csv");
    cout << "Writing values to .csv file..." << endl;

    for (int i = 0; i < PLATE_SIZE; i++) {
        for (int j = 0; j < PLATE_SIZE; j++) {
            output << fixed << setprecision(4) << final_array[i][j] << ",";
        }
        output << endl;
    }
}

int main() {
    double largest_temp_change = INITIAL_TEMPERATURE;
    double temperatures[PLATE_ROWS][PLATE_COLUMNS];
    initialize_plate(temperatures);
    
    cout << "Printing initial plate..." << endl;
    print_array(temperatures);
    cout << endl;

    cout << "Printing plate after one iteration..." << endl;
    double new_temperatures[PLATE_ROWS][PLATE_COLUMNS];
    calculate_new_temperatures(temperatures,new_temperatures);
    print_array(new_temperatures);
    cout << endl;

    do {
        calculate_new_temperatures(temperatures, new_temperatures);
        check_temp_change(temperatures, new_temperatures, largest_temp_change);
        copy_array(temperatures, new_temperatures);
    }
    while (largest_temp_change > MAX_TEMP_CHANGE);
    
    cout << "Printing final plate..." << endl;
    print_array(new_temperatures);
    cout << endl;

    save_to_csv(new_temperatures);
   
    system("pause");
    return 0;
}
