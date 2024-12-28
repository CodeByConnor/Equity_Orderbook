# Equities Orderbook in C++

This project simulates a basic orderbook in C++, a critical component in financial trading systems. It manages buy and sell orders using a FIFO (First-In, First-Out) order matching algorithm. The program supports both market and limit orders, handles partial and full fills, and visually represents the state of the orderbook with real-time performance metrics.

***

# Author 
**Connor Pham**

***

## Features

- FIFO Queue Matching Algorithm
- Market & Limit Orders
- Partial and Full Fills
- Execution Timing
- Visualization

***

## Design Principles

This project is built using Object-Oriented Programming (OOP) principles to ensure modularity, maintainability, and scalability.

***

## Execution

To compile and run the program, follow these steps:

1. Clone the repository: `git clone https://github.com/CodeByConnor/Equity_Orderbook.git`
2. Navigate to the project directory: `cd Equity_Orderbook`
3. Compile the project: `g++ -std=c++17 -o main src/main.cpp src/orderbook.cpp src/helperFunctions.cpp`
4. Run the program with `./main`

***

## Expected Output:

### Initial Orderbook:
![Screenshot 1](ss/Screenshot%202024-12-28%20at%203.20.08%20PM.png)

### Partial Limit Buy:
![Screenshot 2](ss/Screenshot%202024-12-28%20at%203.25.30%20PM.png)

### Partial Market Buy:
![Screenshot 3](ss/Screenshot%202024-12-28%20at%203.25.54%20PM.png)
***

## Lessons Learned: 

- Efficient Algorithm
- Financial Systems Design
- Performance Optimization
- Edge Case Handling
- OOP Design

***
