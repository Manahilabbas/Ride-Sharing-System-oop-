# Ride-Sharing-System-oop-


## Compile and Run

To compile the project using `g++`, run the following command in your terminal:

```bash
g++ main.cpp auth_manager.cpp review_manager.cpp driver.cpp rider.cpp premium_rider.cpp user.cpp ride.cpp driver_review.cpp subscription.cpp -o ride_booking
```

Then, execute the program with:

```bash
./ride_booking
```

Make sure all `.cpp` and `.h` files are in the same directory or properly linked, and you have `g++` installed.

## Enable Emoji and Unicode Output in VS Code Terminal

To ensure proper display of emojis and Unicode characters in your C++ terminal output, follow these steps:

### 1️⃣ Set Console to UTF-8 Encoding

Add the following line at the top of your main() function:

```bash
system("chcp 65001"); // Sets console code page to UTF-8 
```
This sets your terminal to use UTF-8 encoding.

### 2️⃣ Set Font That Supports Emojis

1. Open VS Code and go to:
File > Preferences > Settings

2. Search for:
Terminal › Integrated: Font Family

3. Set the value to:

```bash
Consolas, 'Segoe UI Emoji', monospace
```
This allows fallback to emoji-supporting fonts.



