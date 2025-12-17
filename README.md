# 🌦️ Weather Tracker (C++)

A command-line based Weather Tracker application written in **C++** that fetches real-time weather data using the **OpenWeatherMap API**.  
The project allows users to check current weather details of any city and manage a list of favorite cities.

---

## 🚀 Features

- 🌍 Get current weather by city name  
- 🌡️ Displays temperature, feels-like temperature, min & max temperature  
- 💧 Humidity, wind speed, and cloud percentage  
- 🌅 Sunrise & 🌇 sunset time (local timezone)  
- ⭐ Add, remove, and view favorite cities  
- 🧠 Weather condition classification (Clear, Cloudy, Rain, Snow, etc.)

---

## 🛠️ Technologies Used

- **C++**
- **OpenWeatherMap API**
- **nlohmann/json** (for JSON parsing)
- **curl** (for API requests)
- **Git & GitHub**

---
weather--tracker/
│
├── src/
│ └── neww.cpp
│
├── include/
│ └── json.hpp
│
├── favorites.txt
├── README.md




---

## ⚙️ How to Compile and Run

### 🔹 Prerequisites
- g++ compiler
- Internet connection
- curl installed
- msyn terminal

### 🔹 Compile
```bash
g++ src/neww.cpp -o weather

## 📂 Project Structure

