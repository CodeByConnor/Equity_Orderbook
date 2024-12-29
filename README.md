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
<img width="617" alt="Screenshot 2024-12-28 at 3 20 08 PM" src="https://github.com/user-attachments/assets/bc362be6-82ff-4a47-a39b-2f9661e91553" />


### Partial Limit Buy:
<img width="658" alt="Screenshot 2024-12-28 at 3 25 30 PM" src="https://github.com/user-attachments/assets/2532e1d0-b624-46e7-97f6-d9fcb6552246" />

### Partial Market Buy:
<img width="368" alt="Screenshot 2024-12-28 at 3 25 54 PM" src="https://github.com/user-attachments/assets/b22e6086-39cb-4172-ac11-29830ac6c4ad" />
***

## Lessons Learned: 

- Efficient Algorithm
- Financial Systems Design
- Performance Optimization
- Edge Case Handling
- OOP Design

***


