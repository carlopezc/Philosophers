# 🚀 Philosophers

> A C program that simulates the "Dining Philosophers" problem, a classic concurrency challenge.

---

## 🎯 Project Goals

This project is a deep dive into **multithreading** and **synchronization**. The main goal is to learn how to create and manage multiple threads (`pthreads`) that access shared resources (the "forks") without causing errors. It's a crucial exercise in preventing **deadlocks** (where everyone is stuck waiting) and **race conditions** (where threads interfere with each other).

## 🛠️ Technical Details

* **Multithreading:** Uses `pthreads` (POSIX threads) to create one thread for each philosopher.
* **Synchronization:** Implements **mutexes** to represent the forks. A philosopher must "lock" both forks (mutexes) before they can eat, preventing two philosophers from grabbing the same fork.
* **State Monitoring:** A separate thread (or logic within each philosopher) constantly monitors the state. If a philosopher hasn't eaten in `time_to_die` milliseconds, they "die," and the simulation stops.
* **Time Management:** Uses `gettimeofday()` to get precise timestamps for tracking when each philosopher last ate, when they started sleeping, etc.
* **Challenge:** The main challenge is designing a locking mechanism that avoids a deadlock. A simple "everyone grab left, then right" approach will fail. The solution requires a more robust system, like having odd/even philosophers pick up forks in a different order.

## ⚙️ How to Compile & Run

1.  Clone the repository:
    ```bash
    git clone [https://github.com/carlopezc/Philosophers.git](https://github.com/carlopezc/Philosophers.git)
    cd Philosophers
    ```
2.  Compile the project:
    ```bash
    make
    ```
    This will create the executable `philo`.

3.  Run the program with 4 or 5 arguments:
    ```bash
    ./philo [num_philo] [time_to_die] [time_to_eat] [time_to_sleep] [optional: num_meals]
    ```
    * `num_philo`: The number of philosophers (and forks).
    * `time_to_die`: Time (in ms) a philosopher can go without eating before dying.
    * `time_to_eat`: Time (in ms) it takes to eat.
    * `time_to_sleep`: Time (in ms) it takes to sleep.
    * `num_meals`: (Optional) If set, the simulation stops after all philosophers have eaten this many times.

    **Example:**
    ```bash
    ./philo 5 800 200 200
    ```
