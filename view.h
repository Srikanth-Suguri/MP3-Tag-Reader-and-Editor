
#ifndef MP3_H
#define MP3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help_menu(void);
void view_mp3_tagreader(char *filename);
FILE *open_mp3_file(char *filename);
int check_id3_header(FILE *fp);
void print_view_details(void);
int read_frame_id(FILE *fp, char *frame_id);
unsigned int read_frame_size(FILE *fp, int version);
void print_frame_data(FILE *fp, unsigned int size, char *frame_id);
void print_comment_data(FILE *fp, unsigned int size);


//Function Declarations for EDITITING



unsigned int get_frame_size(unsigned char b[], int version);

char *get_frame_id(char *option);

void get_text_data(char *new_value, unsigned char data[]);

int read_id3_header(FILE *fp, unsigned char header[]);

int get_id3_version(unsigned char header[]);

unsigned int get_tag_size(unsigned char header[]);

unsigned char *find_frame(unsigned char tag_data[], unsigned int tag_size,char frame_id[], int version);




void edit_title(char *new_value, char *filename);
void edit_artist(char *new_value, char *filename);
void edit_album(char *new_value, char *filename);
void edit_year(char *new_value, char *filename);
void edit_genre(char *new_value, char *filename);
void edit_comment(char *new_value, char *filename);
#endif


