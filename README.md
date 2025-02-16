# CPP Project Bash Automator

A C++ program that fetches and matches bash scripts from a remote JSON file. It dynamically retrieves a collection of bash scripts, matches user queries to the script descriptions using flexible scoring, and outputs the best matching script(s) for your needs.

## Features

- **Dynamic Script Retrieval:**  
  Fetch a JSON file containing multiple bash scripts from a remote GitHub repository.
- **Flexible Query Matching:**  
  Enter partial queries (e.g., "sys info", "backup") to find the most relevant bash script.
- **Easy to Build and Package:**  
  Written in C++ with minimal dependencies and easy integration as an Arch Linux AUR package.
- **Simple and Extensible:**  
  Designed for easy customization and extension.

## Requirements

- **Compiler:**  
  `g++` (or any C++ compiler supporting C++11 or later)
- **Libraries:**  
  - [libcurl](https://curl.se/libcurl/) (for fetching remote JSON)
  - [nlohmann/json](https://github.com/nlohmann/json) (a single-header JSON library)
- **Arch Linux Users:**  
  Optional dependencies to build and package for the AUR.

## Installation

### Building from Source

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/TheExacc/Script_collection.git
    cd Script_collection
    ```

2. **Compile the Program:**

    Ensure that `libcurl` and the `nlohmann/json` header are available. Then run:

    ```bash
    g++ -std=c++11 -O2 script_fetcher.cpp -lcurl -o cpp-project-bash-automator
    ```

3. **Run the Program:**

    ```bash
    ./cpp-project-bash-automator
    ```

### Installing via AUR

A `PKGBUILD` is provided to package this project as an AUR package.

1. **Clone the AUR Package Repository:**

    ```bash
    git clone https://aur.archlinux.org/cpp-project-bash-automator.git
    cd cpp-project-bash-automator
    ```

2. **Build and Install the Package:**

    ```bash
    makepkg -si
    ```

    This command will clone the source, build the executable, and install it to `/usr/bin/cpp-project-bash-automator`.

## Usage

When you run the program, you'll be prompted to enter a query:

```bash
./cpp-project-bash-automator
Enter your query (e.g., sys info, backup, cleanup):

