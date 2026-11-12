
#include <iostream>
#include <string>
using namespace std;

// ===============================
// ABSTRACT MEDIA CLASS
// ===============================
class Media {
protected:
    string title;

public:
    Media(string t) {
        title = t;
    }

    virtual void displayInfo() const = 0;
    virtual void play() const = 0;

    string getTitle() const {
        return title;
    }

    // Overloaded equality operator
    bool operator==(const Media& other) const {
        return title == other.title;
    }

    virtual ~Media() {}
};

// ===============================
// SONG CLASS
// ===============================
class Song : public Media {
public:
    Song(string t) : Media(t) {}

    void displayInfo() const override {
        cout << title << " [Song]" << endl;
    }

    void play() const override {
        cout << "Now playing: " << title << endl;
    }
};

// ===============================
// PODCAST CLASS
// ===============================
class Podcast : public Media {
public:
    Podcast(string t) : Media(t) {}

    void displayInfo() const override {
        cout << title << " [Podcast]" << endl;
    }

    void play() const override {
        cout << "Playing podcast: " << title << endl;
    }
};

// ===============================
// AUDIOBOOK CLASS
// ===============================
class Audiobook : public Media {
public:
    Audiobook(string t) : Media(t) {}

    void displayInfo() const override {
        cout << title << " [Audiobook]" << endl;
    }

    void play() const override {
        cout << "Playing audiobook: " << title << endl;
    }
};

// ===============================
// FUNCTION OVERLOADING
// ===============================
Media* searchMedia(Media* library[], int size, string title) {
    for (int i = 0; i < size; i++) {
        if (library[i]->getTitle() == title) {
            return library[i];
        }
    }

    return nullptr;
}

Media* searchMedia(Media* library[], int size, int index) {
    if (index < 0 || index >= size) {
        return nullptr;
    }

    return library[index];
}

// ===============================
// PLAYLIST CLASS TEMPLATE
// ===============================
template <typename T>
class Playlist {
private:
    T items[10];
    int count;

public:
    Playlist() {
        count = 0;
    }

    bool isFull() const {
        return count == 10;
    }

    bool addItem(T item) {
        if (isFull()) {
            return false;
        }

        items[count] = item;
        count++;

        return true;
    }

    bool removeItem(int index) {
        if (index < 0 || index >= count) {
            return false;
        }

        for (int i = index; i < count - 1; i++) {
            items[i] = items[i + 1];
        }

        count--;
        return true;
    }

    int getCount() const {
        return count;
    }

    T getItem(int index) const {
        if (index < 0 || index >= count) {
            return T();
        }

        return items[index];
    }

    void displayPlaylist() const {
        for (int i = 0; i < count; i++) {
            items[i]->displayInfo();
        }

        cout << "Total items: " << count << endl;
    }
};

// ===============================
// MAIN PROGRAM
// ===============================
int main() {

    cout << "========== RECMIX FINAL ==========" << endl;

    // Create media library
    Media* song1 = new Song("Blinding Lights");
    Media* podcast1 = new Podcast("Tech Talk");
    Media* audiobook1 = new Audiobook("The Time Machine");
    Media* song2 = new Song("Midnight City");

    Media* library[] = {
        song1,
        podcast1,
        audiobook1,
        song2
    };

    int librarySize = 4;

    // Display media library
    cout << "\n=== MEDIA LIBRARY ===" << endl;

    for (int i = 0; i < librarySize; i++) {
        cout << i + 1 << ". ";
        library[i]->displayInfo();
    }

    // Search by title
    cout << "\n=== SEARCH DEMONSTRATION ===" << endl;

    cout << "Searching for: Tech Talk" << endl;

    Media* result = searchMedia(library, librarySize, "Tech Talk");

    if (result != nullptr) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found." << endl;
    }

    // Search by index
    cout << "\nSearching index: 2" << endl;

    result = searchMedia(library, librarySize, 2);

    if (result != nullptr) {
        cout << "Found: " << result->getTitle() << endl;
    } else {
        cout << "Invalid index." << endl;
    }

    // Operator overloading demonstration
    cout << "\n=== MEDIA COMPARISON ===" << endl;

    cout << "Comparing two media items..." << endl;

    if (*song1 == *song2) {
        cout << "Titles are the same." << endl;
    } else {
        cout << "Titles are different." << endl;
    }

    // Create favorites playlist
    cout << "\n=== FAVORITES PLAYLIST ===" << endl;

    Playlist<Media*> favorites;

    favorites.addItem(song1);
    favorites.addItem(podcast1);
    favorites.addItem(audiobook1);
    favorites.addItem(song2);

    favorites.displayPlaylist();

    // Playlist management
    cout << "\n=== PLAYLIST MANAGEMENT ===" << endl;

    cout << "Removing item at index 1..." << endl;

    if (favorites.removeItem(1)) {
        cout << "Item removed successfully." << endl;
    }

    cout << "\nUpdated playlist:" << endl;

    favorites.displayPlaylist();

    // Invalid removal
    cout << "\nAttempting invalid removal..." << endl;

    if (!favorites.removeItem(10)) {
        cout << "Invalid index." << endl;
    }

    // Check playlist capacity
    cout << "\nPlaylist full? "
         << (favorites.isFull() ? "Yes" : "No")
         << endl;

    // Playback demonstration
    cout << "\n=== PLAYBACK TEST ===" << endl;

    for (int i = 0; i < favorites.getCount(); i++) {
        favorites.getItem(i)->play();
    }

    // Clean up dynamically allocated objects
    delete song1;
    delete podcast1;
    delete audiobook1;
    delete song2;

    cout << "\n=== RECMIX COMPLETE ===" << endl;

    return 0;
}