#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
char *remove_newline_if_exists(char *line) {
  size_t len = strlen(line); // check string length
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0'; // remove newline
  }
  return line;
}

/// Reads lines from filename, creates nodes, and inserts into list.
Node **load_file(const char *filename, Node **list) {
  FILE *f = fopen(filename, "r"); // YOUR CODE HERE
  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (fgets(line, TRACK_TITLE_SIZE, f)) { // YOUR CODE HERE
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    Data *data = (Data *)malloc(sizeof(Data));
    new_node->data = data;

    strcpy((char *)new_node->data, line); // copy string to node
    insert_at(list, list_len(*list), new_node); // append at end
  }
  fclose(f);
  return list;
}

/// Saves list contents to a file.
void save_file(const char *filename, Node *list) {
  FILE *f = fopen(filename, "w"); // YOUR CODE HERE

  Node *current = playlist;
  while (current) { // YOUR CODE HERE
    fprintf(f, "%s\n", (char *)current->data);
    current = current->next;
  }

  fclose(f);
}

void print_tracks(const Node *const playlist) {
  Node *current = (Node *)playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2ld: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  puts("Loaded tracks:");
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = NULL};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}
