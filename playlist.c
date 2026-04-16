#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For using strcpy

// Define a struct for a node representing a song
struct node {
    int unique_ID; // Unique identifier for each song
    char title[100];
    char artist[100];
    int duration;  // in seconds
    struct node* prev;
    struct node* next;
};

// Define a struct for the Playlist
struct Playlist {
    struct node* head;
    struct node* tail;
    struct node* current;
};

// Function to create a new song node
struct node* create_song(int unique_ID, const char* title, const char* artist, int duration) {
    struct node* new_song = (struct node*)malloc(sizeof(struct node));
    new_song->unique_ID = unique_ID;

    // Using strcpy to copy strings
    strcpy(new_song->title, title);
    strcpy(new_song->artist, artist);

    new_song->duration = duration;
    new_song->prev = NULL;
    new_song->next = NULL;
    return new_song;
}

// Function to initialize a new playlist
struct Playlist* create_playlist() {
    struct Playlist* playlist = (struct Playlist*)malloc(sizeof(struct Playlist));
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
    return playlist;
}

// Function to add a song at the beginning of the playlist
void add_song_beginning(struct Playlist* playlist, int unique_ID, const char* title, const char* artist, int duration) {
    struct node* new_song = create_song(unique_ID, title, artist, duration);
    if (playlist->head == NULL) {
        // First song in the playlist
        playlist->head = playlist->tail = playlist->current = new_song;
    } else {
// Insert at the beginning
        new_song->next = playlist->head;
        playlist->head->prev = new_song;
        playlist->head = new_song;
    }
}

// Function to add a song at the end of the playlist
void add_song_end(struct Playlist* playlist, int unique_ID, const char* title, const char* artist, int duration) {
    struct node* new_song = create_song(unique_ID, title, artist, duration);
    if (playlist->tail == NULL) {
        // First song in the playlist
        playlist->head = playlist->tail = playlist->current = new_song;
    } else {
        // Insert at the end
        new_song->prev = playlist->tail;
        playlist->tail->next = new_song;
        playlist->tail = new_song;
    }
}

// Function to remove a song by its unique ID
void remove_song_by_id(struct Playlist* playlist, int unique_ID) {
    struct node* temp = playlist->head;
    while (temp) {
        if (temp->unique_ID == unique_ID) {
            // Update pointers of neighboring nodes
            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                // Removing the head
                playlist->head = temp->next;
            }

            if (temp->next) {
                temp->next->prev = temp->prev;
            } else {
                // Removing the tail
                playlist->tail = temp->prev;
            }

            // Update current if necessary
            if (playlist->current == temp) {
                playlist->current = playlist->head;  // Reset current to head if removed
            }

            free(temp);  // Free the memory
            printf("Removed song with ID: %d\n", unique_ID);
            return;
        }
        temp = temp->next;
    }
    printf("Song with ID %d not found.\n", unique_ID);
}
// Function to play the next song
struct node* play_next(struct Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->next != NULL) {
        playlist->current = playlist->current->next;
    } else {
        printf("No next song available.\n");
    }
    return playlist->current;
}

// Function to play the previous song
struct node* play_previous(struct Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;
    } else {
        printf("No previous song available.\n");
    }
    return playlist->current;
}

// Function to display the playlist in forward order
void display_forward(struct Playlist* playlist) {
    struct node* temp = playlist->head;
    if (temp == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    printf("Playlist (Forward Order):\n");
    while (temp) {
        printf("ID: %d, Title: %s, Artist: %s, Duration: %d seconds\n",
               temp->unique_ID, temp->title, temp->artist, temp->duration);
        temp = temp->next;
    }
}
// Function to display the playlist in backward order
void display_backward(struct Playlist* playlist) {
    struct node* temp = playlist->tail;
    if (temp == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    printf("Playlist (Backward Order):\n");
    while (temp) {
        printf("ID: %d, Title: %s, Artist: %s, Duration: %d seconds\n",
               temp->unique_ID, temp->title, temp->artist, temp->duration);
        temp = temp->prev;
    }
}
// Function to sort the playlist by song duration
void sort_by_duration(struct Playlist* playlist) {
    if (playlist->head == NULL || playlist->head->next == NULL) {
        return;  // No need to sort if playlist is empty or has one song
    }

    int swapped;
    struct node* current;
    do {
        swapped = 0;
        current = playlist->head;
        while (current->next != NULL) {
            if (current->duration > current->next->duration) {
                // Swap song details using strcpy for title and artist
                int temp_ID = current->unique_ID;
                char temp_title[100], temp_artist[100];
                int temp_duration = current->duration;

                strcpy(temp_title, current->title);
                strcpy(temp_artist, current->artist);

                current->unique_ID = current->next->unique_ID;
                strcpy(current->title, current->next->title);
                strcpy(current->artist, current->next->artist);
                current->duration = current->next->duration;

                current->next->unique_ID = temp_ID;
                strcpy(current->next->title, temp_title);
                strcpy(current->next->artist, temp_artist);
                current->next->duration = temp_duration;

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

int main() {
    struct Playlist* my_playlist = create_playlist();
    int choice;

    do {
        printf("\nPlaylist Management System\n");
        printf("1. Add Song\n");
        printf("2. Remove Song by ID\n");
        printf("3. Play Next Song\n");
        printf("4. Play Previous Song\n");
        printf("5. Display Playlist (Forward Order)\n");
        printf("6. Display Playlist (Backward Order)\n");
        printf("7. Sort Playlist by Duration\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id, duration;
                char title[100], artist[100];
                printf("Enter Unique ID: ");
                scanf("%d", &id);
                printf("Enter Title: ");
                scanf(" %[^\n]", title); // Read string with spaces
                printf("Enter Artist: ");
                scanf(" %[^\n]", artist); // Read string with spaces
                printf("Enter Duration (in seconds): ");
                scanf("%d", &duration);
                add_song_end(my_playlist, id, title, artist, duration);
                printf("Song added successfully.\n");
                break;
            }
            case 2: {
                int id;
                printf("Enter Unique ID of the song to remove: ");
                scanf("%d", &id);
                remove_song_by_id(my_playlist, id);
                break;
            }
            case 3: {
                struct node* next_song = play_next(my_playlist);
                if (next_song) {
                    printf("Now playing: %s by %s\n", next_song->title, next_song->artist);
                }
                break;
            }
            case 4: {
                struct node* prev_song = play_previous(my_playlist);
                if (prev_song) {
                    printf("Now playing: %s by %s\n", prev_song->title, prev_song->artist);
                }
                break;
            }
            case 5:
                display_forward(my_playlist);
                break;
            case 6:
                display_backward(my_playlist);
                break;
            case 7:
                sort_by_duration(my_playlist);
                printf("Playlist sorted by duration.\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    // Free memory and exit
    struct node* current = my_playlist->head;
    while (current != NULL) 
    {
        struct node* next = current->next;
        free(current);
    }
}
