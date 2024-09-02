#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <array>

// Constants
constexpr int TOTAL_SEATS = 100;

// Flight class definition
class Flight {
public:
    Flight() : reserve_seats(0), cancel_tickets(0) {
        seats.fill(0);
    }
    
    void book_ticket();
    void cancel_ticket();
    void change_reservation();
    void passenger_details();
    void get_booking_details();
    void clear_input_buffer();

private:
    struct Passenger {
        std::string fname;
        std::string lname;
        std::string ID;
        std::string phone_number;
        std::string food_menu;
        int seat_number;
        int reservation_number;
    };

    std::vector<std::unique_ptr<Passenger>> passengers;
    std::array<int, TOTAL_SEATS> seats;
    int reserve_seats;
    int cancel_tickets;

    void allocate_seat_number(int snumber);
};

// Clear input buffer function
void Flight::clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Seat allocation function
void Flight::allocate_seat_number(int snumber) {
    if (snumber < 1 || snumber > TOTAL_SEATS) {
        std::cout << "Invalid seat number. Please choose a number between 1 and " << TOTAL_SEATS << "." << std::endl;
        return;
    }
    
    if (seats[snumber - 1] == -1) {
        std::cout << "The seat is already taken. Please choose another seat." << std::endl;
        return;
    }

    std::cout << "Available seats: ";
    for (int i = 1; i <= TOTAL_SEATS; ++i) {
        if (seats[i - 1] == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Book ticket function
void Flight::book_ticket() {
    auto temp_passenger = std::make_unique<Passenger>();
    std::cout << "Enter your first name: ";
    std::cin >> temp_passenger->fname;
    std::cout << "Enter your last name: ";
    std::cin >> temp_passenger->lname;
    std::cout << "Enter your ID: ";
    std::cin >> temp_passenger->ID;
    std::cout << "Enter your phone number: ";
    std::cin >> temp_passenger->phone_number;

    int snumber;
    do {
        std::cout << "Enter the seat number: ";
        std::cin >> snumber;
        clear_input_buffer();
        allocate_seat_number(snumber);

        if (seats[snumber - 1] == 0) {
            seats[snumber - 1] = -1;
            temp_passenger->seat_number = snumber;
            temp_passenger->reservation_number = ++reserve_seats;
            break;
        }
    } while (true);

    std::cout << "Enter your food choice preference: \n1. Veg\n2. Non-Veg\n3. No Food\nYour choice: ";
    int choice;
    std::cin >> choice;
    clear_input_buffer();
    while (choice < 1 || choice > 3) {
        std::cout << "Invalid choice, enter again: ";
        std::cin >> choice;
        clear_input_buffer();
    }
    temp_passenger->food_menu = (choice == 1) ? "Veg" : (choice == 2) ? "Non-Veg" : "No Food";

    passengers.push_back(std::move(temp_passenger));
    std::cout << "Your reservation number is: " << reserve_seats << std::endl;
}

// Cancel ticket function
void Flight::cancel_ticket() {
    int reservation_number;
    std::cout << "Enter your reservation number: ";
    std::cin >> reservation_number;
    clear_input_buffer();

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [reservation_number](const auto& p) { return p->reservation_number == reservation_number; });

    if (it != passengers.end()) {
        seats[(*it)->seat_number - 1] = 0;
        passengers.erase(it);
        ++cancel_tickets;
        std::cout << "Ticket canceled successfully." << std::endl;
    } else {
        std::cout << "Reservation number not found." << std::endl;
    }
}

// Change reservation function
void Flight::change_reservation() {
    int current_seat_number, next_seat_number;
    std::cout << "Please enter your current seat number: ";
    std::cin >> current_seat_number;
    clear_input_buffer();

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [current_seat_number](const auto& p) { return p->seat_number == current_seat_number; });

    if (it == passengers.end()) {
        std::cout << "Current seat number not found." << std::endl;
        return;
    }

    std::cout << "Available seats: ";
    for (int i = 1; i <= TOTAL_SEATS; ++i) {
        if (seats[i - 1] == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "Please choose a new seat number: ";
    std::cin >> next_seat_number;
    clear_input_buffer();
    if (next_seat_number < 1 || next_seat_number > TOTAL_SEATS || seats[next_seat_number - 1] == -1) {
        std::cout << "Invalid seat number." << std::endl;
        return;
    }

    seats[(*it)->seat_number - 1] = 0;
    (*it)->seat_number = next_seat_number;
    seats[next_seat_number - 1] = -1;
    std::cout << "Reservation changed successfully." << std::endl;
}

// Passenger details function
void Flight::passenger_details() {
    int reservation_number;
    std::cout << "Enter your reservation number: ";
    std::cin >> reservation_number;
    clear_input_buffer();

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [reservation_number](const auto& p) { return p->reservation_number == reservation_number; });

    if (it != passengers.end()) {
        std::cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tFood Menu" << std::endl;
        const auto& p = *it;
        std::cout << p->reservation_number << "\t\t" << p->fname << "\t\t" << p->lname << "\t\t" << p->ID << "\t"
                  << p->phone_number << "\t" << p->seat_number << "\t\t" << p->food_menu << std::endl;
    } else {
        std::cout << "Reservation number not found." << std::endl;
    }
}

// Get booking details function
void Flight::get_booking_details() {
    std::cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tFood Menu" << std::endl;
    for (const auto& p : passengers) {
        std::cout << p->reservation_number << "\t\t" << p->fname << "\t\t" << p->lname << "\t\t" << p->ID << "\t"
                  << p->phone_number << "\t" << p->seat_number << "\t\t" << p->food_menu << std::endl;
    }
}

// Welcome function
void welcome() {
    std::cout << "\t\t|---------------------------------------------------------------|" << std::endl;
    std::cout << "\t\t|        WELCOME TO AIRLINE FLIGHT RESERVATION SYSTEM           |" << std::endl;
    std::cout << "\t\t|---------------------------------------------------------------|" << std::endl;
    std::cout << "\t\t| 1) BOOK TICKET                                                |" << std::endl;
    std::cout << "\t\t| 2) CANCEL TICKET                                              |" << std::endl;
    std::cout << "\t\t| 3) CHANGE RESERVATION                                         |" << std::endl;
    std::cout << "\t\t| 4) PASSENGER DETAILS                                          |" << std::endl;
    std::cout << "\t\t| 5) GET BOOKING DETAILS                                        |" << std::endl;
    std::cout << "\t\t| 6) EXIT                                                       |" << std::endl;
    std::cout << "\t\t|---------------------------------------------------------------|" << std::endl;

    Flight flight;
    int choice;
    do {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        flight.clear_input_buffer();
        switch (choice) {
            case 1:
                flight.book_ticket();
                break;
            case 2:
                flight.cancel_ticket();
                break;
            case 3:
                flight.change_reservation();
                break;
            case 4:
                flight.passenger_details();
                break;
            case 5:
                flight.get_booking_details();
                break;
            case 6:
                std::cout << "Exiting program." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
        }
    } while (true);
}

int main() {
    welcome();
    return 0;
}