#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

const int MAX_ROOMS = 100;

struct Room {
    int roomNumber;
    bool isReserved;
    string guestName;
    int guestAge;
    string gender;
    string checkInTime;
    string checkOutTime;
    string mobileNumber;
    string idProof;
};

class Hotel {
    Room rooms[MAX_ROOMS];
    int reservationCount;

public:
    Hotel() {
        reservationCount = 0;
        loadFromFile();
    }

    string getCurrentTime() const {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buf);
    }

    void loadFromFile() {
        ifstream file("hotel_data.txt");
        if (file.is_open()) {
            for (int i = 0; i < MAX_ROOMS; i++) {
                file >> rooms[i].roomNumber >> rooms[i].isReserved;
                file.ignore();
                getline(file, rooms[i].guestName, ',');
                file >> rooms[i].guestAge >> rooms[i].gender >> rooms[i].checkInTime >> rooms[i].checkOutTime >> rooms[i].mobileNumber >> rooms[i].idProof;
                if (rooms[i].isReserved) {
                    reservationCount++;
                }
            }
            cout << "Data loaded from file successfully.\n";
            file.close();
        } else {
            for (int i = 0; i < MAX_ROOMS; i++) {
                rooms[i].roomNumber = i + 1;
                rooms[i].isReserved = false;
            }
            cout << "No previous data found. Initializing rooms.\n";
        }
    }

    void reserveRoom() {
        if (reservationCount >= MAX_ROOMS) {
            cout << "All rooms are reserved!" << endl;
            return;
        }

        int roomNum;
        Room newReservation;
        cout << "Enter room number (1-100): ";
        cin >> roomNum;
        cin.ignore();

        if (roomNum < 1 || roomNum > MAX_ROOMS || rooms[roomNum - 1].isReserved) {
            cout << "Room not available!" << endl;
            return;
        }

        cout << "Enter guest name: ";
        getline(cin, newReservation.guestName);
        cout << "Enter guest age: ";
        cin >> newReservation.guestAge;
        cin.ignore();
        cout << "Enter gender (Male/Female): ";
        getline(cin, newReservation.gender);
        cout << "Enter mobile number: ";
        getline(cin, newReservation.mobileNumber);
        cout << "Enter ID proof (e.g., Passport, License): ";
        getline(cin, newReservation.idProof);

        newReservation.roomNumber = roomNum;
        newReservation.isReserved = true;
        newReservation.checkInTime = getCurrentTime();

        rooms[roomNum - 1] = newReservation;
        reservationCount++;
        cout << "Room " << roomNum << " reserved for " << newReservation.guestName << "." << endl;
        writeToFile();
    }

    void checkOutRoom() {
        int roomNum;
        cout << "Enter room number to check out: ";
        cin >> roomNum;

        if (roomNum < 1 || roomNum > MAX_ROOMS || !rooms[roomNum - 1].isReserved) {
            cout << "Room is either empty or not available!" << endl;
            return;
        }

        rooms[roomNum - 1].isReserved = false;
        rooms[roomNum - 1].checkOutTime = getCurrentTime();
        cout << "Room " << roomNum << " checked out for guest " << rooms[roomNum - 1].guestName << "." << endl;

        writeToFile();
    }

    void displayEmptyRooms() const {
        cout << "Empty rooms: ";
        bool found = false;
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (!rooms[i].isReserved) {
                cout << rooms[i].roomNumber << " ";
                found = true;
            }
        }
        if (!found) {
            cout << "None";
        }
        cout << endl;
    }

    void displayRoomInfo() const {
        cout << "Room Information:" << endl;
        for (int i = 0; i < MAX_ROOMS; i++) {
            cout << "Room " << rooms[i].roomNumber << ": ";
            if (rooms[i].isReserved) {
                cout << "Reserved by " << rooms[i].guestName;
            } else {
                cout << "Available";
            }
            cout << endl;
        }
    }

    void writeToFile() const {
        ofstream file("hotel_data.txt");
        if (file.is_open()) {
            file << left << setw(12) << "Room No." 
                 << setw(20) << "Guest Name" 
                 << setw(8) << "Age" 
                 << setw(10) << "Gender" 
                 << setw(25) << "Check-In Time" 
                 << setw(25) << "Check-Out Time" 
                 << setw(15) << "Mobile No." 
                 << setw(15) << "ID Proof" << endl;

            file << string(150, '=') << endl;

            for (int i = 0; i < MAX_ROOMS; i++) {
                if (rooms[i].isReserved || !rooms[i].checkOutTime.empty()) {
                    file << left 
                         << setw(12) << rooms[i].roomNumber
                         << setw(20) << rooms[i].guestName
                         << setw(8) << rooms[i].guestAge
                         << setw(10) << rooms[i].gender
                         << setw(25) << (rooms[i].checkInTime.empty() ? "N/A" : rooms[i].checkInTime)
                         << setw(25) << (rooms[i].checkOutTime.empty() ? "N/A" : rooms[i].checkOutTime)
                         << setw(15) << rooms[i].mobileNumber
                         << setw(15) << rooms[i].idProof
                         << endl;
                }
            }
            cout << "Reserved rooms saved to file successfully.\n";
            file.close();
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

int main() {
    Hotel hotel;
    int choice;

    do {
        cout << "\nHotel Management System\n";
        cout << "1. Reserve Room\n";
        cout << "2. Display Empty Rooms\n";
        cout << "3. Display Room Information\n";
        cout << "4. Check Out Room\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                hotel.reserveRoom();
                break;
            case 2:
                hotel.displayEmptyRooms();
                break;
            case 3:
                hotel.displayRoomInfo();
                break;
            case 4:
                hotel.checkOutRoom();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
