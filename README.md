# LunaRTOS

LunaRTOS is a lightweight, custom Real-Time Operating System (RTOS) designed for embedded systems. It offers a flexible and extensible scheduler supporting multiple scheduling algorithms, making it suitable for various real-time applications. The project includes a Board Support Package (BSP) developed from scratch to provide low-level hardware interfacing and initialization.

## Features

- **Scheduler** with multiple scheduling algorithms:
  - **Round-Robin**: Time-sliced scheduling for equal priority tasks.
  - **Cooperative**: Tasks yield control manually, suitable for low-latency applications.
  - **Periodic Scheduling**: Handles periodic tasks with predictable timing.
  - **First-Come, First-Served (FCFS)**: Simple scheduling based on task arrival order.
  - **Rate Monotonic Scheduling (RMS)**: Optimal fixed-priority scheduling for periodic tasks.
- **Custom BSP**: Developed from scratch to ensure full hardware control and compatibility.
- **Modular Design**: Easily extendable for new scheduling algorithms and platform-specific features.

## Getting Started

### Prerequisites

- C/C++ Compiler (GCC or equivalent)
- Make or CMake build system
- Debugging tools (GDB, OpenOCD, etc.)
- Target hardware: STM32F4

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/LunaRTOS.git
   cd LunaRTOS
   ```

2. Build the project:

   ```bash
   make all
   ```

3. Flash the firmware to your target hardware:

   ```bash
   make flash
   ```

### Configuration

TBD

## Usage

- TBD

## Supported Scheduling Algorithms

- **Round-Robin**: Provides equal CPU time slices to tasks.
- **Cooperative**: Tasks must explicitly yield control to allow context switching.
- **Periodic**: Ideal for real-time systems with regular task intervals.
- **First-Come, First-Served**: Executes tasks in the order they arrive.
- **Rate Monotonic**: Prioritizes tasks based on their periodic rates.

## BSP (Board Support Package)

The BSP provides low-level drivers and initialization routines for target hardware. It includes:

- Clock initialization
- GPIO configuration
- Timer setup for RTOS tick
- UART for debugging

You can extend the BSP by adding new drivers or hardware interfaces as needed.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with a detailed description of your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For any inquiries or support, please contact [me@katlab.io](mailto:me@katlab.io).

---
