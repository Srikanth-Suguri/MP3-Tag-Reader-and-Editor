/*
NAME: SUGURI SRIKANTH
BATCH ID: 26015_B
DATE: 24/10/2026
DESCRIPTION:
MP3 Tag Reader and Editor
This is a C language project used to read and edit metadata in MP3 audio files. Users can view and modify the title, artist, album, year, genre, and comment of an MP3 file. The project uses ID3 tags to access and update audio metadata and includes validation for command-line arguments and file handling errors.

Technologies Used: C, Structures, Pointers, Strings, Functions, Dynamic Memory Allocation, File Handling, and ID3v2 Tags.
*/

#include<stdio.h>
#include<string.h>
#include "view.h"

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("Error: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE:\n");
        printf("To view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/ -a/ -A/ -m/ -y/ -c changing_text mp3filename\n");
        printf("To get help pass like : ./a.out --help\n");
        return 0;
    }

    if(strcmp(argv[1],"--help")==0)
    {
        help_menu();
    }
    else if (strcmp(argv[1], "-v") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: ./a.out -v filename.mp3\n");
            return 1;
        }
        view_mp3_tagreader(argv[2]);
    }
    else if(strcmp(argv[1],"-e")==0)
    {
        if(argc!=5)
        {
            printf("Usage: ./a.out -e new_title file_name\n");
            return 1;
        }
        if (strcmp(argv[2], "-t") == 0)
        {
            edit_title(argv[3], argv[4]);
        }
        else if (strcmp(argv[2], "-a") == 0)
        {
            edit_artist(argv[3], argv[4]);
        }
        else if (strcmp(argv[2], "-A") == 0)
        {
            edit_album(argv[3], argv[4]);
        }
        else if (strcmp(argv[2], "-y") == 0)
        {

            edit_year(argv[3], argv[4]);
        }
        else if (strcmp(argv[2], "-g") == 0)
        {
            edit_genre(argv[3], argv[4]);
        }

        else if (strcmp(argv[2], "-c") == 0)
        {

            edit_comment(argv[3], argv[4]);
        }
        else
        {

            printf("Invalid editing option\n");
        }
    }
    else
    {
        printf("Invalid option: %s\n", argv[1]);
        return 1;
    }
}
