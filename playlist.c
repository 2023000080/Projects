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
