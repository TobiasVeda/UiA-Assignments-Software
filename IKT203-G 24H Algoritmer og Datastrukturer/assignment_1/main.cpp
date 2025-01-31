#include <iostream>
#include <string>

using namespace std;

// Struct to represent a Song in the playlist
struct Song {
    int id;
    string title;
    string artist;
    Song* next;                          // Pointer to the next song in the list
    Song* prev;                          // Pointer to the previous song in the list

    // Constructor to initialize a new song
    Song(int id, string title, string artist) {
        this->id = id;                   // Set song ID
        this->title = title;             // Set song title
        this->artist = artist;           // Set song artist
        this->next = nullptr;            // Initialize next pointer to nullptr
        this->prev = nullptr;            // Initialize prev pointer to nullptr
    }
};

// Class to manage the playlist using a doubly linked list
class Playlist {
private:
    Song* head;                          // Pointer to the first song in the playlist
    Song* tail;                          // Pointer to the last song in the playlist
    Song* current;                       // Pointer to the currently playing song

    // Function to check if a song with a given ID exists in the playlist
    bool songExists(int id) {
        Song* temp = head;               // Start from the head
        while (temp) {                   // Traverse the list
            if (temp->id == id) {        // Check if current song has matching ID
                return true;             // Song with this ID exists
            }
            temp = temp->next;           // Move to the next song
        }
        return false;
    }

public:
    // Constructor to initialize an empty playlist
    Playlist() {
        head = nullptr;                  // Initialize head to nullptr
        tail = nullptr;                  // Initialize tail to nullptr
        current = nullptr;               // Initialize current to nullptr
    }

    // Destructor to free up memory when the playlist is destroyed
    ~Playlist() {
        Song* temp;                      // Temporary pointer for deletion
        while (head) {                   // Loop through the list
            temp = head;                 // Set temp to head
            head = head->next;           // Move head to the next song
            delete temp;                 // Delete the current song
        }
    }

    // Function to add a new song to the end of the playlist
    void addSong(int id, string title, string artist) {
        if (songExists(id)) {            // Check if song with the same ID exists
            cout << "Error: Song with ID " << id << " already exists." << endl;
            return;
        }
        Song* newSong = new Song(id, title, artist); // Create new song
        if (!head) {                     // If the playlist is empty
            head = tail = newSong;       // Set both head and tail to the new song
        } else {                         // If the playlist is not empty
            tail->next = newSong;        // Add new song at the end
            newSong->prev = tail;        // Set the previous pointer
            tail = newSong;              // Update the tail to the new song
        }
        cout << "Song added: " << title << " by " << artist << endl; // Confirm song addition
    }

    // Function to remove a song from the playlist by its ID
    void removeSong(int id) {
        Song* temp = head;                                     // Start from the head
        while (temp) {                                         // Traverse the list
            if (temp->id == id) {                              // Check if current song has matching ID
                if (temp->prev) temp->prev->next = temp->next; // Update previous song's next
                if (temp->next) temp->next->prev = temp->prev; // Update next song's prev
                if (temp == head) head = head->next;           // Update head if necessary
                if (temp == tail) tail = tail->prev;           // Update tail if necessary
                delete temp;                                   // Delete the song
                cout << "Song removed." << endl;               // Confirm removal
                return;                                        // Exit the function
            }
            temp = temp->next;
        }
        cout << "Song not found." << endl;
    }

    // Function to display all songs in the playlist in order
    void displayPlaylist() {
        if (!head) {                        // Check if the playlist is empty
            cout << "The playlist is empty." << endl;
            return;
        }
        Song* temp = head;                  // Start from the head
        while (temp) {                      // Traverse the list
            cout << temp->id << ": " << temp->title << " by " << temp->artist << endl;
            temp = temp->next;              // Move to the next song
        }
    }

    // Function to display all songs in the playlist in reverse order
    void displayReverse() {
        if (!tail) {                        // Check if the playlist is empty
            cout << "The playlist is empty." << endl;
            return;
        }
        Song* temp = tail;                  // Start from the tail
        while (temp) {                      // Traverse the list in reverse
            cout << temp->id << ": " << temp->title << " by " << temp->artist << endl;
            temp = temp->prev;              // Move to the previous song
        }
    }

    // Function to play the first song in the playlist
    void play() {
        if (!head) {                        // Check if the playlist is empty
            cout << "The playlist is empty." << endl;
            return;
        }
        current = head;
        cout << "Playing: " << current->title << " by " << current->artist << endl;
    }

    // Function to play the next song in the playlist
    void next() {
        if (!current) {                     // Check if any song is currently playing
            cout << "No song is currently playing. Use 'p' to play a song first." << endl;
            return;
        }
        if (current->next) {                // Check if there is a next song
            current = current->next;        // Move to the next song
            cout << "Playing: " << current->title << " by " << current->artist << endl;
        } else {
            cout << "Reached the end of the playlist." << endl; // End of playlist
        }
    }

    // Function to play the previous song in the playlist
    void previous() {
        if (!current) {                     // Check if any song is currently playing
            cout << "No song is currently playing. Use 'p' to play a song first." << endl;
            return;
        }
        if (current->prev) {
            current = current->prev;        // Move to the previous song
            cout << "Playing: " << current->title << " by " << current->artist << endl; // Show currently playing song
        } else {
            cout << "Reached the beginning of the playlist." << endl;
        }
    }

    // Function to search for a song by its ID
    void searchSong(int id) {
        Song* temp = head;                  // Start from the head
        while (temp) {                      // Traverse the list
            if (temp->id == id) {           // Check if current song has matching ID
                cout << "Found: " << temp->title << " by " << temp->artist << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found." << endl;
    }
};

int main() {
    Playlist playlist;                      // Create a Playlist object
    char choice;                            // Variable to store user choice
    int id;                                 // Variable to store song ID
    string title, artist;                   // Variables to store song details

    // Display menu options
    cout << "Playlist Management System\n";
    cout << "Commands:\n";
    cout << "  a - Add a new song\n";
    cout << "  d - Delete a song\n";
    cout << "  p - Play the first song\n";
    cout << "  n - Next song\n";
    cout << "  b - Previous song\n";
    cout << "  l - Display playlist\n";
    cout << "  r - Display playlist in reverse\n";
    cout << "  s - Search a song\n";
    cout << "  q - Quit\n";

    // Main loop to accept user commands
    do {
        cout << "\nEnter command: ";
        cin >> choice;

        switch (choice) {
            case 'a':                        // Add a new song
                cout << "Enter song ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter song artist: ";
                getline(cin, artist);
                playlist.addSong(id, title, artist);
                break;

            case 'd':                       // Delete a song by ID
                cout << "Enter song ID to remove: ";
                cin >> id;
                playlist.removeSong(id);
                break;

            case 'p':                       // Play the first song
                playlist.play();
                break;

            case 'n':                       // Play the next song
                playlist.next();
                break;

            case 'b':                       // Play the previous song
                playlist.previous();
                break;

            case 'l':                       // Display all songs in order
                playlist.displayPlaylist();
                break;

            case 'r':                       // Display all songs in reverse order
                playlist.displayReverse();
                break;

            case 's':                       // Search for a song by ID
                cout << "Enter song ID to search: ";
                cin >> id;
                playlist.searchSong(id);
                break;

            case 'q':                       // Quit the program
                cout << "Quitting...\n";
                break;

            default:                        // Handle invalid input
                cout << "Invalid command. Please try again.\n";
        }
    } while (choice != 'q');

    return 0;
}
