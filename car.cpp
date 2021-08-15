#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct rentInfo {
    char status;
    int ID;
    int price;
    int year;
    string make;
    string model;
    int days;
};

// customer && admin: view all available cars
void viewCars(vector<rentInfo> info, char carStatus) {
    for (rentInfo car : info) {
        if (car.status == carStatus) {
            cout << "ID: " << car.ID << ", " << car.year
            << " " << car.make << " " << car.model << ", $"
            << car.price;
            
            if (carStatus == 'U') {
                cout << ", available in " << car.days << " days";
            }
            cout << endl;
        }
    }
}

// customer: rents a car with input id
void rentCar(int ID, vector<rentInfo> &info) {
    for (rentInfo car : info) {
        if (car.ID == ID) {
            if (car.status != 'A') {
                cout << "This car cannot be rented!\n";
                return;
            }
            cout << "How many days are you renting it for? ";
            int days = 0;
            cin >> days;
            car.status = 'U';
            car.days = days;
            cout << "Your car has been rented! Thank you\n";
            return;
        }
    }
    cout << "Car cannot be found\n";
    return;
}

// customer: returns a car with the given id
void returnCar(int ID, vector<rentInfo> &info) {
    for (rentInfo car : info) {
        if (car.ID == ID) {
            if (car.status != 'U') {
                cout << "This car cannot be returned!\n";
                return;
            }
            car.status = 'A';
            car.days = 0;
            cout << "Your car has been returned! Thank you\n";
            return;
        }
    }
    cout << "Car cannot be found\n";
}

void addToStorage(int ID, vector<rentInfo> &info) {
    for (rentInfo car : info) {
        if (car.ID == ID) {
            if (car.status == 'S') {
                cout << "This car is already in storage!\n";
            } else if (car.status == 'A') {
                car.status = 'S';
                cout << "Car has been moved to storage\n";
            } else {
                cout << "Car is currently rented, cannot be moved to storage\n";
            }
            return;
        }
    }
    cout << "Car cannot be found\n";
}

void removeFromStorage(int ID, vector<rentInfo> &info) {
    for (rentInfo car : info) {
        if (car.ID == ID) {
            if (car.status != 'S') {
                cout << "This car is not in storage!\n";
            } else {
                car.status = 'A';
                cout << "Car has been removed from storage\n";
            }
            return;
        }
    }
    cout << "Car cannot be found\n";
    
}

void parse(string fileName, vector<rentInfo> &info) {
    ifstream infile(fileName);
    rentInfo holder;
    while (!infile.eof()) {
        infile >> holder.status >> holder.ID >> holder.price >> holder.year >> holder.make
        >> holder.model >> holder.days;
        info.push_back(holder);
    }
    infile.close();
}

void write(string fileName, vector<rentInfo> info) {
    ofstream outfile(fileName);
    for (int i = 0; i < info.size(); i++) {
        outfile << info[i].status << " " << info[i].ID << " " << info[i].price
        << " " << info[i].year << " " << info[i].make << " " << info[i].model
        << " " << info[i].days << "\n";
    }
    outfile.close();
}

int main() {
    vector<rentInfo> carsInfo;
    parse("cars.txt", carsInfo);
    
    int admin = 0;
    bool needToWrite = false;
    
    while (true) {
        cout << "Enter 0, 1 or 2\n0: Quit\n1: Admin\n2: Customer\n";
        cout << "Your choice: ";
        cin >> admin;
        cout << "\n";
        if (admin == 0) {
            cout << "Have a great day\n";
            break;
        } else if (admin == 1) {
            cout << "Welcome admin! ";
        } else if (admin == 2) {
            cout << "Welcome customer! ";
        } else {
            cout << "Did not understand input, try again\n";
            continue;
        }
        
        while (true) {
        	cout << "What would you like to do?" << endl;
        	cout << "1: View available cars\n";
        	cout << "2: View cars currently rented\n";
        	cout << "3: Rent a car\n";
        	cout << "4: Return a car\n";
        	if (admin == 1) {
        	    cout << "5: View cars in storage\n";
        	    cout << "6: Move cars into storage\n";
        	    cout << "7: Move cars out of storage\n";
        	}
        	cout << "0: quit" << endl; 
        	cout << "Your choice: ";
        	
        	int choice = 6;
        	int number = 0;
        	cin >> choice;
        	
        	cout << "\n";
        	if (choice == 0) {
        	    cout << "Have a good day\n" << endl;
        	    break;
        	} else if (choice == 1) {
        	    viewCars(carsInfo, 'A');
        	} else if (choice == 2) {
        	    viewCars(carsInfo, 'U');
        	} else if (choice == 3) {
        	    cout << "Enter ID of the car you want to rent: ";
        	    cin >> number;
        	    needToWrite = true;
        	    rentCar(number, carsInfo);
        	} else if (choice == 4) {
        	    cout << "Enter ID of the car you want to return: ";
        	    cin >> number;
        	    needToWrite = true;
        	    returnCar(number, carsInfo);
        	} else if (choice == 5 && admin == 1) {
        	    viewCars(carsInfo, 'S');
        	} else if (choice == 6 && admin == 1) {
        	    cout << "Enter ID of the car you want to move: ";
        	    cin >> number;
        	    addToStorage(number, carsInfo);
        	} else if (choice == 7 && admin == 1) {
        	    cout << "Enter ID of the car you want to move: ";
        	    cin >> number;
        	    removeFromStorage(number, carsInfo);
        	} else {
        	    cout << "Didn't quite catch your inpute\nEnter your input again\n";
        	}
        	cout << "\n";
        }
    }
    
    if (needToWrite) {
        write("temp.txt", carsInfo);
        rename("temp.txt", "cars.txt");
    }
}


