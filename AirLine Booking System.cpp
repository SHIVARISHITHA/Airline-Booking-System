#include<bits/stdc++.h>
using namespace std;

/*
Airline flight reservation system: Allows online booking of tickets, cancellation, seat selection, food preference, and reservation changes.
*/

// Constants
const int TOTAL_SEATS = 100;

// Flight class definition
class Flight {
public:
    Flight() : start(nullptr), reserve_seats(0), cancel_tickets(0) {
        fill(begin(seats), end(seats), 0);
    }
    
    void book_ticket();
    void cancel_ticket();
    void change_reservation();
    void passenger_details();
    void get_booking_details();

private:
    struct Passenger {
        string fname;
        string lname;
        string ID;
        string phone_number;
        string food_menu;
        int seat_number;
        int reservation_number;
        Passenger* next;
    };

    Passenger* start;
    Passenger* temp_passenger;
    Passenger* temp1;
    int seats[TOTAL_SEATS];
    int reserve_seats;
    int cancel_tickets;

    void allocate_seat_number(int snumber);
};

// Seat allocation function
void Flight::allocate_seat_number(int snumber) {
    if (snumber < 1 || snumber > TOTAL_SEATS) {
        cout << "Invalid seat number. Please choose a number between 1 and " << TOTAL_SEATS << "." << endl;
        return;
    }
    
    if (seats[snumber - 1] == -1) {
        cout << "The seat is already taken. Please choose another seat." << endl;
        return;
    }

    cout << "Available seats: ";
    for (int i = 1; i <= TOTAL_SEATS; ++i) {
        if (seats[i - 1] == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Book ticket function
void Flight::book_ticket() {
    temp_passenger = new Passenger;
    cout << "Enter your first name: ";
    cin >> temp_passenger->fname;
    cout << "Enter your last name: ";
    cin >> temp_passenger->lname;
    cout << "Enter your ID: ";
    cin >> temp_passenger->ID;
    cout << "Enter your phone number: ";
    cin >> temp_passenger->phone_number;

    int snumber;
    do {
        cout << "Enter the seat number: ";
        cin >> snumber;
        allocate_seat_number(snumber);

        if (seats[snumber - 1] == 0) {
            seats[snumber - 1] = -1;
            temp_passenger->seat_number = snumber;
            temp_passenger->reservation_number = ++reserve_seats;
            break;
        }
    } while (true);

    cout << "Enter your food choice preference: \n1. Veg\n2. Non-Veg\n3. No Food\nYour choice: ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 3) {
        cout << "Invalid choice, enter again: ";
        cin >> choice;
    }
    temp_passenger->food_menu = (choice == 1) ? "Veg" : (choice == 2) ? "Non-Veg" : "No Food";

    temp_passenger->next = nullptr;
    if (start == nullptr) {
        start = temp_passenger;
    } else {
        Passenger* temp = start;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = temp_passenger;
    }
    cout << "Your reservation number is: " << reserve_seats << endl;
}

// Cancel ticket function
void Flight::cancel_ticket() {
    int reservation_number;
    cout << "Enter your reservation number: ";
    cin >> reservation_number;

    temp_passenger = start;
    temp1 = nullptr;
    while (temp_passenger != nullptr) {
        if (temp_passenger->reservation_number == reservation_number) {
            if (temp_passenger == start) {
                start = start->next;
            } else {
                temp1->next = temp_passenger->next;
            }
            seats[temp_passenger->seat_number - 1] = 0;
            delete temp_passenger;
            ++cancel_tickets;
            cout << "Ticket canceled successfully." << endl;
            return;
        }
        temp1 = temp_passenger;
        temp_passenger = temp_passenger->next;
    }
    cout << "Reservation number not found." << endl;
}

// Change reservation function
void Flight::change_reservation() {
    int current_seat_number, next_seat_number;
    cout << "Please enter your current seat number: ";
    cin >> current_seat_number;

    temp_passenger = start;
    while (temp_passenger != nullptr) {
        if (temp_passenger->seat_number == current_seat_number) {
            break;
        }
        temp_passenger = temp_passenger->next;
    }

    if (temp_passenger == nullptr) {
        cout << "Current seat number not found." << endl;
        return;
    }

    cout << "Available seats: ";
    for (int i = 1; i <= TOTAL_SEATS; ++i) {
        if (seats[i - 1] == 0) {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Please choose a new seat number: ";
    cin >> next_seat_number;
    if (next_seat_number < 1 || next_seat_number > TOTAL_SEATS || seats[next_seat_number - 1] == -1) {
        cout << "Invalid seat number." << endl;
        return;
    }

    seats[temp_passenger->seat_number - 1] = 0;
    temp_passenger->seat_number = next_seat_number;
    seats[next_seat_number - 1] = -1;
    cout << "Reservation changed successfully." << endl;
}

// Passenger details function
void Flight::passenger_details() {
    int reservation_number;
    cout << "Enter your reservation number: ";
    cin >> reservation_number;

    temp_passenger = start;
    while (temp_passenger != nullptr) {
        if (temp_passenger->reservation_number == reservation_number) {
            cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tFood Menu" << endl;
            cout << temp_passenger->reservation_number << "\t\t" << temp_passenger->fname << "\t\t" << temp_passenger->lname << "\t\t" << temp_passenger->ID << "\t" << temp_passenger->phone_number << "\t" << temp_passenger->seat_number << "\t\t" << temp_passenger->food_menu << endl;
            return;
        }
        temp_passenger = temp_passenger->next;
    }
    cout << "Reservation number not found." << endl;
}

// Get booking details function
void Flight::get_booking_details() {
    cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tFood Menu" << endl;
    temp_passenger = start;
    while (temp_passenger != nullptr) {
        cout << temp_passenger->reservation_number << "\t\t" << temp_passenger->fname << "\t\t" << temp_passenger->lname << "\t\t" << temp_passenger->ID << "\t" << temp_passenger->phone_number << "\t" << temp_passenger->seat_number << "\t\t" << temp_passenger->food_menu << endl;
        temp_passenger = temp_passenger->next;
    }
}

// Welcome function
void welcome() {
    cout << "\t\t|---------------------------------------------------------------|" << endl;
    cout << "\t\t|        WELCOME TO AIRLINE FLIGHT RESERVATION SYSTEM          |" << endl;
    cout << "\t\t|---------------------------------------------------------------|" << endl;
    cout << "\t\t| 1) BOOK TICKET                                              |" << endl;
    cout << "\t\t| 2) CANCEL TICKET                                            |" << endl;
    cout << "\t\t| 3) CHANGE RESERVATION                                       |" << endl;
    cout << "\t\t| 4) PASSENGER DETAILS                                        |" << endl;
    cout << "\t\t| 5) GET BOOKING DETAILS                                      |" << endl;
    cout << "\t\t| 6) EXIT                                                     |" << endl;
    cout << "\t\t|---------------------------------------------------------------|" << endl;

    Flight flight;
    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                system("CLS");
                flight.book_ticket();
                break;
            case 2:
                system("CLS");
                flight.cancel_ticket();
                break;
            case 3:
                system("CLS");
                flight.change_reservation();
                break;
            case 4:
                system("CLS");
                flight.passenger_details();
                break;
            case 5:
                system("CLS");
                flight.get_booking_details();
                break;
            case 6:
                system("CLS");
                cout << "Exiting program." << endl;
                exit(0);
            default:
                system("CLS");
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);
}

int main() {
    welcome();
    return 0;
}