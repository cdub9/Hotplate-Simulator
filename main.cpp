#include <iostream>
#include <iomanip>

using namespace std;

const int PLATE_SIZE = 20;
const int PLATE_COLUMNS = 20;
const int PLATE_ROWS = 20;
const double CORNER = 0;
const int ARRAY_SIZE = 19;
const double BOUNDARY_TEMPERATURE = 100;
const int NUMBER_OF_SURROUNDING_TEMPERATURES = 4;

void print_array(double array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            cout << fixed << setprecision(4) << setw(10) << array[i][j];
        }
        cout << endl;
    }
}

//Copy values from the new array back to the old array so we can find the next iteration
void sync_arrays(double old_array[][PLATE_SIZE], double new_array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            old_array[i][j] = new_array[i][j];
        }
    }
}

//Check whether or not the temperature change at all points on the plate is greater than 0.1
bool is_temp_change_finished(double old_array[][PLATE_SIZE], double new_array[][PLATE_SIZE]) {
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            if (new_array[i][j] - old_array[i][j] > 0.1) {
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

//Calculate new temperatures on the plate
void calculate_new_temperatures(double old_array[][PLATE_SIZE], double new_array[][PLATE_SIZE]) {
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

int main() {
    double temperatures[PLATE_ROWS][PLATE_COLUMNS];
    for (int i = 0; i < PLATE_ROWS; i++) {
        for (int j = 0; j < PLATE_COLUMNS; j++) {
            if (i == CORNER && j == CORNER || i == CORNER && j == ARRAY_SIZE || i == ARRAY_SIZE && j == CORNER || i == ARRAY_SIZE && j == ARRAY_SIZE) {
                temperatures[i][j] = CORNER;
            }
            else if (i == CORNER && j != CORNER || i == CORNER && j != ARRAY_SIZE || i == ARRAY_SIZE && j != CORNER || i == ARRAY_SIZE && j != ARRAY_SIZE) {
                temperatures[i][j] = BOUNDARY_TEMPERATURE;
            }
            else {
                temperatures[i][j] = CORNER;
            }
        }
        cout << endl;
    }
    
    cout << "Printing initial plate..." << endl;
    print_array(temperatures);
    cout << endl;

    cout << "Printing plate after one iteration..." << endl;
    double new_temperatures[PLATE_ROWS][PLATE_COLUMNS];
    calculate_new_temperatures(temperatures,new_temperatures);
    print_array(new_temperatures);

    do {
        calculate_new_temperatures(temperatures, new_temperatures);
        is_temp_change_finished(temperatures, new_temperatures);
        cout << is_temp_change_finished;
        sync_arrays(temperatures, new_temperatures); 
    }
    while (is_temp_change_finished == false);
    
    print_array(new_temperatures);

    /*
    //Check to see if the iterations are finished
    bool finished = is_temp_change_finished(old_array, new_array);
    if (finished == true) {
        return true;
    }
    */

    //is_temp_change_finished(temperatures, new_temperatures);
    //if (is_temp_change_finished == true) {
    //    cout << "The "
    //}





    // Make function to check for change in values between old/new arrays
     
    system("pause");
    return 0;
}
