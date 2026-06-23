# 🗳️ Constituency-Based Voting System (C++ OOP)

A robust, console-based Voting System developed in C++ that simulates a real-world electoral process. The system maps voters to specific constituencies based on their CNIC (Computerized National Identity Card) and ensures secure, one-person-one-vote enforcement using file handling.

## 🌟 Key Features

### 👤 Voter Mode
- **CNIC Verification:** Validates 13-digit CNIC formats.
- **Constituency Mapping:** Automatically assigns the voter to a constituency (NA-52 to NA-56) based on the first 3 digits of their CNIC.
- **Duplicate Prevention:** Checks a persistent text file (`voted.txt`) to ensure a CNIC cannot vote twice.
- **Targeted Voting:** Voters can only see and vote for candidates registered in their specific constituency.

### 🛡️ Administrator Mode (Password Protected)
- **Candidate Management:** Add or remove candidates from specific constituencies.
- **Live Results:** View real-time vote counts for all candidates or filter by constituency.
- **Election Reset:** Admin can reset all votes and clear the voter history file to start a fresh election.

## 💻 OOP & Technical Concepts Applied
This project was built to demonstrate advanced C++ and Object-Oriented Programming concepts:
- **Inheritance:** `Candidate` class inherits from the base `Person` class.
- **Encapsulation:** Private data members and secure admin authentication.
- **File Handling (I/O Streams):** Persistent storage of candidate data (`candidates.txt`) and voter logs (`voted.txt`) using custom parsing logic.
- **Templates:** Implementation of a generic `Display<T>` template class for uniform console output.
- **Data Validation:** Strict checks for CNIC length, prefix mapping, and array boundary limits.

## 🛠️ Tech Stack
- **Language:** C++ (Object-Oriented Programming)
- **Environment:** Console / CLI
- **Data Storage:** Local Text Files (`.txt`)

## 🚀 How to Run

### Using an IDE (VS Code, Visual Studio, Code::Blocks)
1. Open the `main.cpp` file in your preferred C++ IDE.
2. Compile and run the program.
3. *Note: The program will automatically generate `candidates.txt` and `voted.txt` in the same directory upon first run.*

### Using Terminal / Command Prompt
```bash
g++ main.cpp -o VotingSystem
./VotingSystem   # On Linux/Mac
VotingSystem.exe # On Windows