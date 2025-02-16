# CPP Project Bash Automator

A C++ program that fetches and matches bash scripts from a remote JSON file. It dynamically retrieves a collection of bash scripts, matches user queries to the script descriptions using flexible scoring, and outputs the best matching script(s) for your needs.

## Features

- **Dynamic Script Retrieval:** Fetch a JSON file containing multiple bash scripts from a remote GitHub repository.
- **Flexible Query Matching:** Enter partial queries (e.g., "sys info", "backup") to find the most relevant bash script.
- **Easy Build & Packaging:** Minimal dependencies and simple integration as an Arch Linux AUR package.

## Requirements

- **Compiler:** `g++` (supporting C++11 or later)
- **Libraries:**  
  - [libcurl](https://curl.se/libcurl/)
  - [nlohmann/json](https://github.com/nlohmann/json)

## Installation

### Building from Source

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/TheExacc/Script_collection.git
    cd Script_collection
    ```

2. **Compile the Program:**

    ```bash
    g++ -std=c++11 -O2 script_fetcher.cpp -lcurl -o script_fetcher_cpp
    ```

3. **Run the Program:**

    ```bash
    ./script_fetcher_cpp
    ```

### Installing via AUR

You can install the package from the AUR:

[script_fetcher_cpp on AUR](https://aur.archlinux.org/packages/script_fetcher_cpp)
