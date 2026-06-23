#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple template to display any type of information
template <typename T>
class Display {
public:
    void show(const T& data) {
        cout << data << endl;
    }
};

const int maxCandidates = 50;
const int numConstituencies = 5;

string constituencies[numConstituencies] = { "NA-52", "NA-53", "NA-54", "NA-55", "NA-56" };
string cnicPrefix[numConstituencies] = { "352", "353", "354", "355", "356" };

class Person {
public:
    string name;
    Person() : name("") {}
    Person(string name) : name(name) {}
};

class Candidate : public Person {
public:
    string constituency;
    int votes;

    Candidate() : Person(), constituency(""), votes(0) {}
    Candidate(string name, string constituency, int votes = 0) : Person(name), constituency(constituency), votes(votes) {}
};

class VotingSystem {
private:
    Candidate candidates[maxCandidates];
    int numCandidates;
    const string adminPassword = "admin123";
    const string candidatesFile = "candidates.txt";
    const string votedFile = "voted.txt";

    void clearScreen() {
        system("cls");
    }

    void pause() {
        cout << "\n\t\t\t\t\tPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    void saveCandidatesToFile() {
        ofstream write(candidatesFile);
        if (!write.is_open()) {
            cout << "Error saving candidates to file.\n";
            return;
        }

        for (int i = 0; i < numCandidates; i++) {
            write << candidates[i].name << "|" << candidates[i].constituency << "|" << candidates[i].votes << "\n";
        }

        write.close();
    }


    void loadCandidatesFromFile() {
        ifstream read(candidatesFile);
        if (!read.is_open()) {
            preloadCandidates();
            saveCandidatesToFile();
            return;
        }

        string line;
        numCandidates = 0;

        // Read each line from the file
        while (getline(read, line)) {
            string name = "";
            string constituency = "";
            string votesText = "";
            int part = 0;  // This keeps track of which part we are filling (0=name, 1=constituency, 2=votes)

            // Go through each character in the line
            for (int i = 0; i < line.length(); i++) {
                char ch = line[i];

                if (ch == '|') {
                    part++; // Move to next part when we find '|'
                }
                else {
                    // Add characters to the correct variable
                    if (part == 0) {
                        name += ch;
                    }
                    else if (part == 1) {
                        constituency += ch;
                    }
                    else if (part == 2) {
                        votesText += ch;
                    }
                }
            }

            // Convert votesText (string) to integer votes
            int votes = 0;
            for (int i = 0; i < votesText.length(); i++) {
                votes = votes * 10 + (votesText[i] - '0');
            }

            // Add candidate to the list
            if (numCandidates < maxCandidates) {
                candidates[numCandidates] = Candidate(name, constituency, votes);
                numCandidates++;
            }
        }

        read.close();
    }


    bool hasVoted(string cnic) {
        ifstream read(votedFile);
        string line;
        while (getline(read, line)) {
            if (line == cnic)
                return true;
        }
        return false;
    }

    void markAsVoted(string cnic) {
        ofstream write(votedFile, ios::app);
        if (write.is_open()) {
            write << cnic << "\n";
            write.close();
        }
    }

    void preloadCandidates() {
        numCandidates = 0;
        // NA-52
        candidates[numCandidates++] = Candidate("Shahbaz Sharif", "NA-52");
        candidates[numCandidates++] = Candidate("Maryam Nawaz", "NA-52");

        // NA-53
        candidates[numCandidates++] = Candidate("Imran Khan", "NA-53");
        candidates[numCandidates++] = Candidate("Asad Umar", "NA-53");

        // NA-54
        candidates[numCandidates++] = Candidate("Bilawal Bhutto", "NA-54");
        candidates[numCandidates++] = Candidate("Shazia Marri", "NA-54");

        // NA-55
        candidates[numCandidates++] = Candidate("Sheikh Rasheed Ahmed", "NA-55");
        candidates[numCandidates++] = Candidate("Daniyal Aziz", "NA-55");

        // NA-56
        candidates[numCandidates++] = Candidate("Hanif Abbasi", "NA-56");
        candidates[numCandidates++] = Candidate("Tariq Fazal Chaudhry", "NA-56");
    }

public:
    VotingSystem() {
        loadCandidatesFromFile();
    }

    void start() {
        clearScreen();
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t******************************************" << endl;
        cout << "\t\t\t\t\t*                                        *" << endl;
        cout << "\t\t\t\t\t*   ***       Voting Machine         *** *" << endl;
        cout << "\t\t\t\t\t*                                        *" << endl;
        cout << "\t\t\t\t\t******************************************" << endl;
        cout << "\n\t\t\t\t\t===================================================" << endl;
        cout << "\t\t\t\t\t|  Made by: Muhammad Armaghan Khan (052)          |" << endl;
        cout << "\t\t\t\t\t|           Muhammad Omer (064)                   |" << endl;
        cout << "\t\t\t\t\t|           Taha Ali (086)                        |" << endl;
        cout << "\t\t\t\t\t===================================================" << endl;
        cout << "\n \t\t\t\t\t  Press Enter To Continue...";
        cin.get();
    }

    string getConstituencyFromCNIC(string cnic) {
        if (cnic.length() < 3) return "";

        // Manually extract first 3 characters
        string prefix = "";
        prefix += cnic[0];
        prefix += cnic[1];
        prefix += cnic[2];

        for (int i = 0; i < numConstituencies; i++) {
            if (prefix == cnicPrefix[i]) {
                return constituencies[i];
            }
        }
        return "";
    }

    void viewCandidates(string constituency = "", bool showVotes = false) {
        clearScreen();
        cout << "\n\t\t\t\t\t======== Candidates ========\n\n";
        bool found = false;
        for (int i = 0; i < numCandidates; i++) {
            if (constituency == "" || candidates[i].constituency == constituency) {
                
                string output = "\t\t\t\t\t" + to_string(i + 1) + ". " + candidates[i].name + " (" + candidates[i].constituency + ")";
                if (showVotes)
                    output += " - Votes: " + to_string(candidates[i].votes);

                Display<string> dis;
                dis.show(output);
                cout << endl;

                found = true;
            }
        }
        if (!found) {
            cout << "\t\t\t\t\tNo candidates found.\n";
        }
        pause();
    }

    void addCandidate() {
        clearScreen();
        if (numCandidates >= maxCandidates) {
            cout << "\n\t\t\t\t\tMaximum number of candidates reached.\n";
            pause();
            return;
        }

        cout << "\n\t\t\t\t\tEnter candidate name: ";
        cin.ignore();
        string name;
        getline(cin, name);

        cout << "\n\t\t\t\t\tSelect constituency:\n";
        for (int i = 0; i < numConstituencies; i++) {
            cout << "\t\t\t\t\t" << i + 1 << ". " << constituencies[i] << endl;
        }
        int choice;
        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        if (choice < 1 || choice > numConstituencies) {
            cout << "\n\t\t\t\t\tInvalid constituency selection.\n";
            pause();
            return;
        }

        string chosenConstituency = constituencies[choice - 1];
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].name == name && candidates[i].constituency == chosenConstituency) {
                cout << "\n\t\t\t\t\tThis candidate is already added in this constituency.\n";
                pause();
                return;
            }
        }

        candidates[numCandidates++] = Candidate(name, chosenConstituency);
        saveCandidatesToFile();
        cout << "\n\t\t\t\t\tCandidate added to " << chosenConstituency << " successfully.\n";
        pause();
    }

    void removeCandidate() {
        clearScreen();
        cout << "\n\t\t\t\t\tRemove candidate from which constituency?\n";
        for (int i = 0; i < numConstituencies; i++) {
            cout << "\t\t\t\t\t" << i + 1 << ". " << constituencies[i] << endl;
        }
        int choice;
        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        if (choice < 1 || choice > numConstituencies) {
            cout << "\n\t\t\t\t\tInvalid choice.\n";
            pause();
            return;
        }
        string chosenConstituency = constituencies[choice - 1];

        cout << "\n\t\t\t\t\tCandidates in " << chosenConstituency << ":\n";
        int indexes[maxCandidates], count = 0;
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].constituency == chosenConstituency) {
                cout << "\t\t\t\t\t" << (count + 1) << ". " << candidates[i].name << " - Votes: " << candidates[i].votes << endl;
                indexes[count++] = i;
            }
        }

        if (count == 0) {
            cout << "\n\t\t\t\t\tNo candidates to remove in this constituency.\n";
            pause();
            return;
        }

        int removeChoice;
        cout << "\n\t\t\t\t\tEnter candidate number to remove: ";
        cin >> removeChoice;
        if (removeChoice < 1 || removeChoice > count) {
            cout << "\n\t\t\t\t\tInvalid candidate number.\n";
            pause();
            return;
        }

        int removeIndex = indexes[removeChoice - 1];
        for (int i = removeIndex; i < numCandidates - 1; i++) {
            candidates[i] = candidates[i + 1];
        }
        numCandidates--;

        saveCandidatesToFile();

        cout << "\n\t\t\t\t\tCandidate removed successfully.\n";
        pause();
    }
    void resetVotes() {

        for (int i = 0; i < numCandidates; i++) {
            candidates[i].votes = 0;
        }
        saveCandidatesToFile();
        ofstream clearCnic("voted.txt", ios::trunc); // trunc mode empties the file
        clearCnic.close();
        cout << " \nVotes reset successfully.\nAll CNICs cleared from voting history.";
        pause();
    }
    void castVote() {
        clearScreen();
        cout << "\nFirst 3 digits of CNIC for Constituency";
        cout << "\n352 for NA-52";
        cout << "\n353 for NA-53";
        cout << "\n354 for NA-54";
        cout << "\n355 for NA-55";
        cout << "\n356 for NA-56";
        cout << "\n\t\t\t\t\tEnter your CNIC (13 digits): ";
        string cnic;
        cin >> cnic;

        if (cnic.length() != 13) {
            cout << "\n\t\t\t\t\tInvalid CNIC format.\n";
            pause();
            return;
        }

        if (hasVoted(cnic)) {
            cout << "\n\t\t\t\t\tYou have already voted. Duplicate voting not allowed.\n";
            pause();
            return;
        }

        string voterConstituency = getConstituencyFromCNIC(cnic);
        if (voterConstituency == "") {
            cout << "\n\t\t\t\t\tInvalid CNIC prefix. No constituency found.\n";
            pause();
            return;
        }

        Display<string> dis;
        dis.show("\n\t\t\t\t\tYou belong to constituency: " + voterConstituency);
        cout << "\n\n\t\t\t\t\tAvailable candidates:\n";

        int validIndexes[10], count = 0;
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].constituency == voterConstituency) {
                cout << "\t\t\t\t\t" << (count + 1) << ". " << candidates[i].name << endl;
                validIndexes[count++] = i;
            }
        }

        if (count == 0) {
            cout << "\n\t\t\t\t\tNo candidates found in your constituency.\n";
            pause();
            return;
        }

        int voteChoice;
        cout << "\n\t\t\t\t\tEnter the number of your candidate choice: ";
        cin >> voteChoice;
        if (voteChoice < 1 || voteChoice > count) {
            cout << "\n\t\t\t\t\tInvalid candidate choice.\n";
            pause();
            return;
        }

        int candidateIndex = validIndexes[voteChoice - 1];
        candidates[candidateIndex].votes++;

        markAsVoted(cnic);
        saveCandidatesToFile();

        cout << "\n\t\t\t\t\tThank you for voting!\n";
        pause();
    }

    void adminMenu() {
        while (true) {
            clearScreen();
            cout << "\n\t\t\t\t\t=== Admin Menu ===\n";
            cout << "\t\t\t\t\t1. Add Candidate\n";
            cout << "\t\t\t\t\t2. Remove Candidate\n";
            cout << "\t\t\t\t\t3. View All Candidates and Results\n";
            cout << "\t\t\t\t\t4. View Candidates by Constituency\n";
            cout << "\t\t\t\t\t5. Reset Votes\n";
            cout << "\t\t\t\t\t6. Exit Admin Menu\n";
            cout << "\n\t\t\t\t\tEnter choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) addCandidate();
            else if (choice == 2) removeCandidate();
            else if (choice == 3) viewCandidates("", true);
            else if (choice == 4) {
                cout << "\n\t\t\t\t\tEnter Constituency (e.g., NA-53): ";
                string c;
                cin >> c;
                viewCandidates(c, true);
            }
            else if (choice == 5) resetVotes();
            else if (choice == 6) break;
            else {
                cout << "\n\t\t\t\t\tInvalid choice.\n";
                pause();
            }
        }
    }

    void mainMenu() {
        while (true) {
            clearScreen();
            cout << "\n\t\t\t\t\t===== Voting System =====\n";
            cout << "\t\t\t\t\t1. Cast Vote\n";
            cout << "\t\t\t\t\t2. View Candidates\n";
            cout << "\t\t\t\t\t3. Admin Login\n";
            cout << "\t\t\t\t\t4. Exit\n";
            cout << "\n\t\t\t\t\tEnter choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) castVote();
            else if (choice == 2) viewCandidates("", false);
            else if (choice == 3) {
                cout << "\n\t\t\t\t\tEnter admin password: ";
                string pass;
                cin >> pass;
                if (pass == adminPassword) {
                    adminMenu();
                }
                else {
                    cout << "\n\t\t\t\t\tIncorrect password.\n";
                    pause();
                }
            }
            else if (choice == 4) {
                cout << "\n\t\t\t\t\tExiting program. Goodbye!\n";
                break;
            }
            else {
                cout << "\n\t\t\t\t\tInvalid choice.\n";
                pause();
            }
        }
    }
};

int main() {
    VotingSystem votingSystem;
    votingSystem.start();
    votingSystem.mainMenu();
    return 0;
}