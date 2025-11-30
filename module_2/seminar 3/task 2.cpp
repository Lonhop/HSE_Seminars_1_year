#include <iostream>
#include <vector>
#include <string>

struct Time {
    int hours;
    int minutes;
    int seconds;

    Time subtract(const Time& t) const {
        int totalSeconds1 = hours * 3600 + minutes * 60 + seconds;
        int totalSeconds2 = t.hours * 3600 + t.minutes * 60 + t.seconds;
        int diffSeconds = totalSeconds1 - totalSeconds2;
        if (diffSeconds < 0) return Time{0,0,0};

        int h = diffSeconds / 3600;
        diffSeconds %= 3600;
        int m = diffSeconds / 60;
        int s = diffSeconds % 60;
        return Time {h,m,s};
    }
};

std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << t.hours << "h " << t.minutes << "m " << t.seconds << "s";
    return os;
}

struct Flight {
    std::string flightID;
    std::string departureAirport;
    std::string destinationAirport;
    Time departureTime;
};

void displayFlightsByAirport(const std::vector<Flight>& flights, const std::string& airportName) {
    std::cout << "Flights arriving at " << airportName << ":\n";
    for (const auto& flight : flights) {
        if (flight.destinationAirport == airportName) {
            std::cout << "Flight " << flight.flightID
                      << " from " << flight.departureAirport
                      << " departs at " << flight.departureTime << "\n";
        }
    }

    std::cout << "\nFlights departing from " << airportName << ":\n";
    for (const auto& flight : flights) {
        if (flight.departureAirport == airportName) {
            std::cout << "Flight " << flight.flightID
                      << " to " << flight.destinationAirport
                      << " departs at " << flight.departureTime << "\n";
        }
    }
}

int main() {
    std::vector<Flight> flights = {
        {"AA101", "JFK", "LAX", {8, 30, 0}},
        {"DL202", "LAX", "ORD", {12, 15, 0}},
        {"UA303", "ORD", "JFK", {15, 45, 0}},
        {"SW404", "JFK", "MIA", {9, 0, 0}},
        {"BA505", "MIA", "JFK", {18, 20, 0}}
    };

    displayFlightsByAirport(flights, "JFK");
}