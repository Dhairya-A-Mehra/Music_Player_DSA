#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

class Song {
public:
    Song(const std::string& title, const std::string& artist) : title(title), artist(artist) {
        nextSong = NULL;
        prevSong = NULL;
    }

    std::string title;
    std::string artist;
    Song* nextSong;
    Song* prevSong;
};

class MusicPlayer {
public:
    MusicPlayer() : firstSong(NULL), currentSong(NULL) {}

    void addSong(const std::string& title, const std::string& artist) {
        if (isDuplicate(title, artist)) {
            std::cout << "The song '" << title << " by " << artist << "' is already in the playlist." << std::endl;
            return;
        }

        Song* newSong = new Song(title, artist);
        if (!firstSong) {
            firstSong = newSong;
            currentSong = newSong; 
        } else {
            Song* lastSong = firstSong;
            while (lastSong->nextSong) {
                lastSong = lastSong->nextSong;
            }
            lastSong->nextSong = newSong;
            newSong->prevSong = lastSong;
        }
    }

    bool isDuplicate(const std::string& title, const std::string& artist) {
        Song* current = firstSong;
        while (current) {
            if (current->title == title && current->artist == artist) {
                return true;  
            }
            current = current->nextSong;
        }
        return false;
    }

    void play() {
        if (currentSong) {
            std::cout << "Now Playing: " << currentSong->title << " by " << currentSong->artist << std::endl;
        } else {
            std::cout << "No songs in the playlist." << std::endl;
        }
    }

    void selectSong(int index) {
        Song* selectedSong = firstSong;
        int songIndex = 0;
        while (selectedSong && songIndex < index) {
            selectedSong = selectedSong->nextSong;
            songIndex++;
        }

        if (selectedSong) {
            currentSong = selectedSong;
            std::cout << "Selected: " << currentSong->title << " by " << currentSong->artist << std::endl;
        } else {
            std::cout << "Invalid song index." << std::endl;
        }
    }

    void deleteSong(int songIndex) {
        Song* selectedSong = firstSong;
        int index = 0;
        while (selectedSong && index < songIndex) {
            selectedSong = selectedSong->nextSong;
            index++;
        }

        if (selectedSong) {
            
            if (selectedSong->prevSong) {
                selectedSong->prevSong->nextSong = selectedSong->nextSong;
            } else {
                firstSong = selectedSong->nextSong;
            }
            if (selectedSong->nextSong) {
                selectedSong->nextSong->prevSong = selectedSong->prevSong;
            }

            std::cout << "Deleted: " << selectedSong->title << " by " << selectedSong->artist << std::endl;
            delete selectedSong;
        } else {
            std::cout << "Invalid song index." << std::endl;
        }
    }

    void searchSong(const std::string& query) {
        if (!firstSong) {
            std::cout << "No songs in the playlist." << std::endl;
            return;
        }

        std::vector<Song*> searchResults;
        Song* current = firstSong;
        int index = 0;
        while (current) {
            if (current->title.find(query) != std::string::npos || current->artist.find(query) != std::string::npos) {
                searchResults.push_back(current);
            }
            current = current->nextSong;
            index++;
        }

        if (searchResults.empty()) {
            std::cout << "No matching songs found." << std::endl;
        } else {
            std::cout << "Search Results:" << std::endl;
            for (size_t i = 0; i < searchResults.size(); i++) {
                std::cout << "Index: " << i << " - " << searchResults[i]->title << " by " << searchResults[i]->artist << std::endl;
            }

            // Ask if you want to play or delete a song from the search results
            std::cout << "Do you want to play or delete a song from the search results? (p/d/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'p' || choice == 'P') {
                int selectedSongIndex;
                std::cout << "Enter the index of the song to play: ";
                std::cin >> selectedSongIndex;
                if (selectedSongIndex >= 0 && selectedSongIndex < searchResults.size()) {
                    currentSong = searchResults[selectedSongIndex];
                    std::cout << "Now Playing: " << currentSong->title << " by " << currentSong->artist << std::endl;
                } else {
                    std::cout << "Invalid song index." << std::endl;
                }
            } else if (choice == 'd' || choice == 'D') {
                int selectedSongIndex;
                std::cout << "Enter the index of the song to delete: ";
                std::cin >> selectedSongIndex;
                if (selectedSongIndex >= 0 && selectedSongIndex < searchResults.size()) {
                    deleteSong(selectedSongIndex);
                } else {
                    std::cout << "Invalid song index." << std::endl;
                }
            }
        }
    }

    void nextSong() {
        if (currentSong && currentSong->nextSong) {
            currentSong = currentSong->nextSong;
            std::cout << "Switched to the next song: " << currentSong->title << " by " << currentSong->artist << std::endl;
        } else {
            std::cout << "No next song in the playlist." << std::endl;
        }
    }

    void previousSong() {
        if (currentSong && currentSong->prevSong) {
            currentSong = currentSong->prevSong;
            std::cout << "Switched to the previous song: " << currentSong->title << " by " << currentSong->artist << std::endl;
        } else {
            std::cout << "No previous song in the playlist." << std::endl;
        }
    }

    void displayPlaylist() {
        if (!firstSong) {
            std::cout << "No songs in the playlist." << std::endl;
            return;
        }

        std::cout << "Playlist:" << std::endl;
        std::cout << std::left << std::setw(30) << "Song Title" << std::setw(30) << "Artist" << std::endl;
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::setfill(' ') << std::endl;
        Song* current = firstSong;
        int index = 0;
        while (current) {
            std::cout << std::left << std::setw(30) << current->title << std::setw(30) << current->artist << std::endl;
            current = current->nextSong;
            index++;
        }
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::setfill(' ') << std::endl;
    }

private:
    Song* firstSong;
    Song* currentSong;
};

int main() {
    MusicPlayer player;

    while (true) {
        std::cout << "\nMusic Player Menu:" << std::endl;
        std::cout << "1. Add a Song" << std::endl;
        std::cout << "2. Play Current Song" << std::endl;
        std::cout << "3. Select a Song" << std::endl;
        std::cout << "4. Search for a Song" << std::endl;
        std::cout << "5. Play Next Song" << std::endl;
        std::cout << "6. Play Previous Song" << std::endl;
        std::cout << "7. Display Playlist" << std::endl;
        std::cout << "8. Quit" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string title, artist, query;
        int songIndex;
        switch (choice) {
            case 1:
                std::cout << "Enter song title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter artist: ";
                std::getline(std::cin, artist);
                player.addSong(title, artist);
                break;
            case 2:
                player.play();
                break;
            case 3:
                player.displayPlaylist();
                std::cout << "Enter the index of the song to select: ";
                std::cin >> songIndex;
                player.selectSong(songIndex);
                break;
            case 4:
                std::cout << "Enter a keyword to search for: ";
                std::cin.ignore();
                std::getline(std::cin, query);
                player.searchSong(query);
                break;
            case 5:
                player.nextSong();
                break;
            case 6:
                player.previousSong();
                break;
            case 7:
                player.displayPlaylist();
                break;
            case 8:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    }

    return 0;
}

