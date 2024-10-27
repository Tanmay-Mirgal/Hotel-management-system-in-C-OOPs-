

# Hotel Management System

This Hotel Management System is a C++ application that allows users to manage hotel room reservations, including checking in and checking out guests, displaying room availability, and storing reservation data in a text file. 

## Features

- **Reserve Room:** Users can reserve available rooms by entering guest details.
- **Check Out Room:** Users can check out guests from their rooms.
- **Display Empty Rooms:** The application lists all currently available (unreserved) rooms.
- **Display Room Information:** Users can view the reservation status of all rooms.
- **Persistent Storage:** Room reservation data is saved in a text file (`hotel_data.txt`), allowing data persistence across program runs.

## Requirements

- C++ Compiler (e.g., g++, clang++)
- C++ Standard Library
- Basic knowledge of C++ and command line usage

## How to Compile and Run

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Tanmay-Mirgal/Hotel-management-system-in-C-OOPs-.git
   cd <repository-directory>
   ```

2. **Compile the Code:**
   ```bash
   g++ main.cpp -o main
   ```

3. **Run the Application:**
   ```bash
   ./main
   ```

## File Structure

- **hotel_management_system.cpp:** The main source file containing the implementation of the hotel management system.
- **hotel_data.txt:** A text file that stores reservation data. This file will be created automatically upon running the program.

## Usage

1. **Menu Options:**
   - Enter `1` to reserve a room.
   - Enter `2` to display empty rooms.
   - Enter `3` to display room information.
   - Enter `4` to check out a room.
   - Enter `5` to exit the program.

2. **Room Reservation:**
   - Users are prompted to enter the room number, guest name, age, gender, mobile number, and ID proof.
   - The application will confirm the reservation and save the data to `hotel_data.txt`.

3. **Check-Out:**
   - Users can check out by entering the room number, which updates the reservation status and saves the check-out time.



