Equities Orderbook in C++

Overview

This project implements an Equities Orderbook in C++, a core component of financial trading systems. It facilitates the management of buy and sell orders using efficient algorithms, ensuring accurate and fast order execution. The program is designed to handle both market and limit orders, support partial and full fills, and provide a clear visual representation of the orderbook.

Features

FIFO Queue Matching Algorithm: Ensures fair and efficient order matching.

Market & Limit Orders: Handles both order types seamlessly.

Partial and Full Fills: Supports order execution with precise quantity management.

Execution Timing: Measures and displays the time taken to execute orders in nanoseconds.

Visualization: Displays the current state of the orderbook with color-coded bars.

Design Principles

The project is built on Object-Oriented Programming (OOP) principles to ensure modularity, reusability, and maintainability. Key design aspects include:

Modular Components

main.cpp:

Handles user interaction.

Demonstrates the addition and execution of orders.

Measures execution times for orders.

Orderbook:

Core class that manages buy and sell orders.

Implements logic for order matching using a FIFO algorithm.

Visualizes the current state of the orderbook.

Order:

Represents individual orders with attributes like price, quantity, and side (buy or sell).

Helpers:

Provides utility functions, including timing and custom output formatting.

Efficiency

Optimized data structures ensure fast and accurate order processing.

Execution times as low as 4 nanoseconds, demonstrating high performance.

User Experience

Visual representation of the orderbook with color-coded bars for bids (green) and asks (red).

Displays detailed execution statistics, including total cost and average price.

How to Run

Prerequisites

Ensure you have a C++17 compatible compiler installed.

Steps

Clone the repository:
