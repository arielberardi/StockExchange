# Stock Exchange

Study case of a design and Implementation of a Stock Exchange application.

Consideration:
- It has to be fast (low-latency) and accurate in order to provide fairness to the traders.
- It needs to receive trading requests (bids and asks) from external application (FIX over TCP/IP)
- It needs to feed Market Data for external application to use (FAST over Multicast UDP)

Some useful information i used to build this:
- https://quant.stackexchange.com/questions/3783/what-is-an-efficient-data-structure-to-model-order-book
- https://github.com/Kautenja/limit-order-book/blob/master/notes/lob.md
- https://github.com/charles-cooper/itch-order-book
- https://chronicle.software/wp-content/uploads/2023/01/Chronicle-Matching-Engine.pdf
- https://www.youtube.com/watch?v=XeLWe0Cx_Lg
- https://www.youtube.com/watch?v=b1e4t2k2KJY


## Features

- **Modern C++ (C++20)**: Leverages C++20 features for enhanced code readability and performance.
- **Dependency Injection**: Enhances testability and modularity using Dependency Injection principles.
- **Unit Testing**: Uses Google Test and Google Mock frameworks for comprehensive unit testing.
- **Cross-Platform Build System**: Utilizes CMake for easy building and management of the project.
- **Boost and STL**: Incorporates Boost libraries and the Standard Template Library (STL) for efficient data structures and algorithms.

## Getting Started

### Prerequisites

To build and run, you will need:

- **C++20 compatible compiler**
- **CMake** (version 3.20 or higher)
- **Boost** (version 1.86 or higher)
- **Google Test** (automatically fetched via CMake if not present)

### Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/arielberardi/StockeExchange.git
   cd StockExchange
   ```

2. **Configure the project with CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the project**:
   ```bash
   cmake --build .
   ```

4. **Run Tests**:
   StockExchange uses Google Test for unit testing. To run the tests:
   ```bash
   ctest
   ```

### Running the Application

Once built, you can run the application from the `build` directory:

```bash
./StockExchange
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Disclaimer

**StockExchange is intended for educational and practical purposes only. It is not a professional application nor is it intended for use in real-world cases.**

## Contact

For any questions or suggestions, please reach out [Ariel Berardi](https://www.linkedin.com/in/aberardi95/).
