#include <bits/stdc++.h>
#include "json.hpp"
#include <fstream>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;


const string API_KEY = "8abc6fc818c6ec854111f146e52f87ea";


stack<string> favoriteCities;


string getWeatherCondition(const string &condition) {
    string cond = condition;
    transform(cond.begin(), cond.end(), cond.begin(), ::tolower);
    if (cond.find("cloud") != string::npos) return "Cloudy";
    if (cond.find("rain") != string::npos) return "Rain";
    if (cond.find("drizzle") != string::npos) return "Drizzle";
    if (cond.find("snow") != string::npos) return "Snow";
    if (cond.find("thunderstorm") != string::npos) return "Thunderstorm";
    if (cond.find("clear") != string::npos) return "Clear";
    if (cond.find("mist") != string::npos || cond.find("fog") != string::npos) return "Mist/Fog";
    return cond; 
}

// Convert Unix timestamp to human-readable time
string unixToTime(long timestamp, int timezoneOffset) {
    time_t t = timestamp + timezoneOffset;
    tm *lt = gmtime(&t);
    char buffer[10];
    strftime(buffer, sizeof(buffer), "%I:%M %p", lt);
    return string(buffer);
}

// Function to fetch and display weather by city
void getWeatherByCity(const string &cityNameInput = "") {
    string city = cityNameInput;
    if (city.empty()) {
        cout << "\nEnter city name: ";
        cin.ignore();
        getline(cin, city);
    }

    string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city +
                 "&appid=" + API_KEY + "&units=metric";

    string command = "curl -s \"" + url + "\" -o temp.json";
    system(command.c_str());

    ifstream fin("temp.json");
    if (!fin) {
        cout << "Failed to fetch data.\n";
        return;
    }

    json j;
    fin >> j;
    fin.close();

    if (j.contains("main") && j.contains("weather")) {
        double temp = j["main"]["temp"];
        double feels_like = j["main"]["feels_like"];
        double temp_min = j["main"]["temp_min"];
        double temp_max = j["main"]["temp_max"];
        int humidity = j["main"]["humidity"];
        double wind_speed = j["wind"]["speed"];
        int clouds = j["clouds"]["all"];
        string condition = j["weather"][0]["description"];
        string cityName = j["name"];

        long sunrise = j["sys"]["sunrise"];
        long sunset = j["sys"]["sunset"];
        int timezoneOffset = j["timezone"];

        cout << "\nWeather in " << cityName << ":\n";
        cout << "Temperature: " << temp << " C (Feels like: " << feels_like << " C)\n";
        cout << "Min: " << temp_min << " C, Max: " << temp_max << " C\n";
        cout << "Humidity: " << humidity << "%\n";
        cout << "Wind Speed: " << wind_speed << " m/s\n";
        cout << "Cloudiness: " << clouds << "%\n";
        cout << "Condition: " << condition << " (" << getWeatherCondition(condition) << ")\n";
        cout << "Sunrise: " << unixToTime(sunrise, timezoneOffset) << "\n";
        cout << "Sunset: " << unixToTime(sunset, timezoneOffset) << "\n";
    } else {
        cout << "Could not get weather data for '" << city << "'. Check city name.\n";
    }

    remove("temp.json");
}


void addFavoriteCity() {
    cout << "\nEnter city name to add to favorites: ";
    cin.ignore();
    string city;
    getline(cin, city);
    favoriteCities.push(city);
    cout << "Added '" << city << "' to favorite cities.\n";
}


void removeFavoriteCity() {
    if (favoriteCities.empty()) {
        cout << "No favorite cities to remove.\n";
        return;
    }
    cout << "Removed '" << favoriteCities.top() << "' from favorite cities.\n";
    favoriteCities.pop();
}


void viewFavoriteCities() {
    if (favoriteCities.empty()) {
        cout << "No favorite cities added yet.\n";
        return;
    }
    stack<string> temp = favoriteCities; 
    cout << "Favorite Cities (last added first):\n";
    while (!temp.empty()) {
        cout << "- " << temp.top() << "\n";
        temp.pop();
    }
}

int main() {
    int choice;
    do {
        cout << "\n========= Weather Tracker =========\n";
        cout << "1. Current weather by city\n";
        cout << "2. Add favorite city\n";
        cout << "3. Remove favorite city\n";
        cout << "4. View favorite cities\n";
        cout << "5. Exit\n";
        cout << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: getWeatherByCity(); break;
            case 2: addFavoriteCity(); break;
            case 3: removeFavoriteCity(); break;
            case 4: viewFavoriteCities(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n"; break;
        }
    } while(choice != 5);

    return 0;
}
