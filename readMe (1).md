![image](https://github.com/user-attachments/assets/bf6aeb1a-0e5e-4d77-845b-3f4ccc4c374f)

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

<img width="617" alt="Screenshot 2024-12-28 at 3 20 08 PM" src="https://github.com/user-attachments/assets/c9ab1a32-37d0-4148-b59a-ab50256c93c1" />

### Partial Limit Buy:

<img width="658" alt="Screenshot 2024-12-28 at 3 25 30 PM" src="https://github.com/user-attachments/assets/5ff2e916-9ff5-4d6a-b973-39682f514e82" />

### Partial Market Sell:

<img width="368" alt="Screenshot 2024-12-28 at 3 25 54 PM" src="https://github.com/user-attachments/assets/9224ca08-1628-44ce-85b1-3db468e32681" />

***

## Lessons Learned: 

- Efficient Algorithm
- Financial Systems Design
- Performance Optimization
- Edge Case Handling
- OOP Design

***
