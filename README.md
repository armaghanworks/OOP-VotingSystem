# 🗳️ Constituency-Based Voting System (C++ OOP)

A console-based Voting System developed in C++ that simulates a simplified electoral process. The system maps voters to specific constituencies based on their CNIC (Computerized National Identity Card) prefix and enforces one-person-one-vote using file-based persistence.

## 🌟 Key Features

### 👤 Voter Mode

- **CNIC Length Check:** Requires the entered CNIC to be exactly 13 characters (digits are not separately validated — non-numeric input of the correct length is currently accepted).
- **Constituency Mapping:** Automatically assigns the voter to a constituency (NA-52 to NA-56) based on the first 3 digits of their CNIC (352–356).
- **Duplicate Prevention:** Checks a persistent text file (`voted.txt`) to ensure a CNIC cannot vote twice.
- **Targeted Voting:** Voters can only see and vote for candidates registered in their specific constituency.

### 🛡️ Administrator Mode (Password Protected)

- **Candidate Management:** Add or remove candidates from specific constituencies.
- **Live Results:** View real-time vote counts for all candidates, or filter by constituency.
- **Election Reset:** Admin can reset all votes and clear the voter history file to start a fresh election.

## 💻 OOP & Technical Concepts Applied

This project was built to demonstrate core C++ and Object-Oriented Programming concepts:

- **Inheritance:** `Candidate` class inherits from the base `Person` class.
- **Encapsulation:** Private data members (`candidates`, `numCandidates`, `adminPassword`) inside `VotingSystem`, with public methods controlling access.
- **File Handling (I/O Streams):** Persistent storage of candidate data (`candidates.txt`) and voter logs (`voted.txt`) using custom `|`-delimited parsing logic.
- **Templates:** A generic `Display<T>` class used for uniform console output of formatted strings.
- **Data Validation:** Checks for CNIC length, prefix-to-constituency mapping, and array boundary limits (max 50 candidates).

## 🛠️ Tech Stack

- **Language:** C++ (Object-Oriented Programming)
- **Environment:** Console / CLI
- **Data Storage:** Local text files (`.txt`)

## ⚠️ Known Limitations

- `clearScreen()` calls `system("cls")`, which is **Windows-only**. On Linux/macOS the screen won't actually clear, though the program will still run.
- CNIC validation only checks length (13 characters), not that all characters are digits.
- Candidate list is fixed-size (`maxCandidates = 50`); attempting to add beyond this limit is blocked with a message.

## 🚀 How to Run

### Using an IDE (Visual Studio, VS Code, Code::Blocks)

1. Open `main.cpp` in your preferred C++ IDE.
2. Compile and run the program.
3. *Note: The program automatically generates `candidates.txt` and `voted.txt` in the same directory on first run.*

### Using Terminal / Command Prompt

```
g++ main.cpp -o VotingSystem
./VotingSystem    # On Linux/Mac (screen-clear will not work, see Limitations)
VotingSystem.exe  # On Windows
```

## 📂 Files

- `main.cpp` — full source code
- `candidates.txt` — generated on first run; stores candidate data
- `voted.txt` — generated on first run; stores CNICs that have already voted

## About

A constituency-based voting system in C++ utilizing OOP principles (Inheritance, Encapsulation), file handling for data persistence, and CNIC-based voter verification. Developed for Bahria University OOP coursework.
