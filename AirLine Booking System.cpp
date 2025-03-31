#include <bits/stdc++.h>
using namespace std;

const int TOTAL_SEATS = 100;

class Flight {
public:
    Flight() : start(nullptr), reserve_seats(0), cancel_tickets(0) {
        fill(begin(seats), end(seats), 0);
    }

    ~Flight();  // Destructor to free memory

    void book_ticket();
    void cancel_ticket();
    void change_reservation();
    void passenger_details();
    void get_booking_details();

private:
    struct Passenger {
        string fname, lname, ID, phone_number, food_menu;
        int seat_number, reservation_number;
        Passenger* next;
    };

    Passenger* start;
    int seats[TOTAL_SEATS];
    int reserve_seats;
    int cancel_tickets;

    void show_available_seats();
};

// Destructor to free memory
Flight::~Flight() {
    Passenger* temp;
    while (start) {
        temp = start;
        start = start->next;
        delete temp;
    }
}

// Display available seats
void Flight::show_available_seats() {
    cout << "Available seats: ";
    for (int i = 1; i <= TOTAL_SEATS; ++i) {
        if (seats[i - 1] == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Book Ticket
void Flight::book_ticket() {
    Passenger* temp_passenger = new Passenger;
    cout << "Enter your first name: ";
    cin >> temp_passenger->fname;
    cout << "Enter your last name: ";
    cin >> temp_passenger->lname;
    cout << "Enter your ID: ";
    cin >> temp_passenger->ID;
    cout << "Enter your phone number: ";
    cin >> temp_passenger->phone_number;

    int snumber;
    show_available_seats();
    while (true) {
        cout << "Enter the seat number: ";
        cin >> snumber;

        if (snumber < 1 || snumber > TOTAL_SEATS || seats[snumber - 1] == -1) {
            cout << "Invalid or already taken seat. Choose another." << endl;
        } else {
            seats[snumber - 1] = -1;
            temp_passenger->seat_number = snumber;
            temp_passenger->reservation_number = ++reserve_seats;
            break;
        }
    }

    cout << "Choose food preference: \n1. Veg\n2. Non-Veg\n3. No Food\nYour choice: ";
    int choice;
    cin >> choice;
    temp_passenger->food_menu = (choice == 1) ? "Veg" : (choice == 2) ? "Non-Veg" : "No Food";

    temp_passenger->next = start;
    start = temp_passenger;

    cout << "Booking successful! Your reservation number is: " << reserve_seats << endl;
}

// Cancel Ticket
void Flight::cancel_ticket() {
    int reservation_number;
    cout << "Enter your reservation number: ";
    cin >> reservation_number;

    Passenger *temp = start, *prev = nullptr;
    while (temp) {
        if (temp->reservation_number == reservation_number) {
            if (prev) {
                prev->next = temp->next;
            } else {
                start = temp->next;
            }

            seats[temp->seat_number - 1] = 0;
            delete temp;
            ++cancel_tickets;
            cout << "Ticket canceled successfully.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Reservation number not found.\n";
}

// Change Reservation
void Flight::change_reservation() {
    int current_seat_number, next_seat_number;
    cout << "Enter your current seat number: ";
    cin >> current_seat_number;

    Passenger* temp = start;
    while (temp) {
        if (temp->seat_number == current_seat_number) {
            break;
        }
        temp = temp->next;
    }

    if (!temp) {
        cout << "Current seat not found.\n";
        return;
    }

    show_available_seats();
    cout << "Enter new seat number: ";
    cin >> next_seat_number;

    if (next_seat_number < 1 || next_seat_number > TOTAL_SEATS || seats[next_seat_number - 1] == -1) {
        cout << "Invalid or already taken seat.\n";
        return;
    }

    seats[temp->seat_number - 1] = 0;
    temp->seat_number = next_seat_number;
    seats[next_seat_number - 1] = -1;

    cout << "Reservation updated successfully.\n";
}

// Passenger Details
void Flight::passenger_details() {
    int reservation_number;
    cout << "Enter reservation number: ";
    cin >> reservation_number;

    Passenger* temp = start;
    while (temp) {
        if (temp->reservation_number == reservation_number) {
            cout << "Name: " << temp->fname << " " << temp->lname
                 << "\nID: " << temp->ID
                 << "\nPhone: " << temp->phone_number
                 << "\nSeat: " << temp->seat_number
                 << "\nFood: " << temp->food_menu << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Reservation not found.\n";
}

// Get All Bookings
void Flight::get_booking_details() {
    cout << "Reservations List:\n";
    Passenger* temp = start;
    while (temp) {
        cout << temp->reservation_number << " - " << temp->fname << " " << temp->lname
             << " | Seat: " << temp->seat_number
             << " | Food: " << temp->food_menu << endl;
        temp = temp->next;
    }
}

// Welcome Menu
void welcome() {
    Flight flight;
    int choice;

    do {
        cout << "\n-------------------------------\n";
        cout << "WELCOME TO AIRLINE RESERVATION\n";
        cout << "1) BOOK TICKET\n";
        cout << "2) CANCEL TICKET\n";
        cout << "3) CHANGE RESERVATION\n";
        cout << "4) PASSENGER DETAILS\n";
        cout << "5) GET BOOKING DETAILS\n";
        cout << "6) EXIT\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: flight.book_ticket(); break;
            case 2: flight.cancel_ticket(); break;
            case 3: flight.change_reservation(); break;
            case 4: flight.passenger_details(); break;
            case 5: flight.get_booking_details(); break;
            case 6: cout << "Exiting...\n"; return;
            default: cout << "Invalid choice.\n";
        }
    } while (true);
}

int main() {
    welcome();
    return 0;
}
