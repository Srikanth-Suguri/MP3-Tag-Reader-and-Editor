
#include <stdio.h>
#include <string.h>
#include "view.h"
#include<stdlib.h>

// Open MP3 file
FILE *open_mp3_file(char *filename)
{
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        perror("Error opening MP3 file");
    }

    return fp;
}

// Check ID3 header
int check_id3_header(FILE *fp)
{
    char header[3];
    rewind(fp);
    if (fread(header, 1, 3, fp) != 3)
    {
        return 0;
    }
    if (strncmp(header, "ID3", 3) == 0)
    {
        return 1;
    }
    return 0;
}

// Print heading
void print_view_details(void)
{
    printf("\n");
    printf("-------------------- SELECTED VIEW DETAILS --------------------\n");
    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("             MP3 TAG READER AND EDITOR FOR ID3v2               \n");
    printf("---------------------------------------------------------------\n");
}

// Read frame ID
int read_frame_id(FILE *fp, char *frame_id)
{
    if (fread(frame_id, 1, 4, fp) != 4)
    {
        return 0;
    }
    frame_id[4] = '\0';
    return 1;
}

// Read frame size (ID3v2.3 uses big-endian)

unsigned int read_frame_size(FILE *fp, int version)
{
    unsigned char b[4];

    if (fread(b, 1, 4, fp) != 4)
        return 0;

    unsigned int size;

    if (version == 4)
    {
        size = ((unsigned int)b[0] << 21) |
               ((unsigned int)b[1] << 14) |
               ((unsigned int)b[2] << 7)  |
               (unsigned int)b[3];
    }
    else
    {
        size = ((unsigned int)b[0] << 24) |
               ((unsigned int)b[1] << 16) |
               ((unsigned int)b[2] << 8)  |
               (unsigned int)b[3];
    }

    return size;
}


// Print basic single-byte text frame data
void print_frame_data(FILE *fp, unsigned int size, char *frame_id)
{
    if (size <= 1)
        return;

    unsigned char encoding;

    if (fread(&encoding, 1, 1, fp) != 1)
        return;

    size--;

    char *data = malloc(size + 1);

    if (data == NULL)
        return;

    if (fread(data, 1, size, fp) == size)
    {
        data[size] = '\0';

        if (encoding == 1)
        {
            // Skip the 2-byte BOM
            if (size >= 2)
            {
                memmove(data, data + 2, size - 2);
                size -= 2;
            }

            // Convert UTF-16 ASCII characters to normal text
            for (unsigned int i = 0; i + 1 < size; i += 2)
            {
                data[i / 2] = data[i];
            }

            data[size / 2] = '\0';
        }

        if (strcmp(frame_id, "TIT2") == 0)
        {
            char *p = strstr(data, " (");
            if (p != NULL)
                *p = '\0';
        }

        printf("%s\n", data);
    }

    free(data);
}






// void view_mp3_tagreader(char *filename)
// {
//     FILE *fp = open_mp3_file(filename);

//     if (fp == NULL)
//     {
//         return;
//     }

//     if (!check_id3_header(fp))
//     {
//         printf("ID3 header not found\n");
//         fclose(fp);
//         return;
//     }

//     unsigned char header[10];
//     rewind(fp);
//     if (fread(header, 1, 10, fp) != 10)
//     {
//         fclose(fp);
//         return;
//     }

//     int version = header[3];

//     print_view_details();

//     while (1)
//     {
//         char frame_id[5] = {0};

//         if (!read_frame_id(fp, frame_id))
//             break;

//         if (frame_id[0] == '\0')
//             break;

//         unsigned int size = read_frame_size(fp, version);

//         fseek(fp, 2, SEEK_CUR);

//         if (size == 0)
//         {
//             break;
//         }

//         if (strcmp(frame_id, "TIT2") == 0)
//         {
//             printf("TITLE   : ");
//         }
//         else if (strcmp(frame_id, "TPE1") == 0)
//         {
//             printf("ARTIST  : ");
//         }
//         else if (strcmp(frame_id, "TALB") == 0)
//         {
//             printf("ALBUM   : ");
//         }
//         else if (strcmp(frame_id, "TYER") == 0)
//         {
//             printf("YEAR    : ");
//         }
//         else if (strcmp(frame_id, "TCON") == 0)
//         {
//             printf("MUSIC   : ");
//         }
//         else if (strcmp(frame_id, "COMM") == 0)
//         {
//             printf("COMMENT : ");
//         }
//         else
//         {
//             fseek(fp, size, SEEK_CUR);
//             continue;
//         }

//         if (strcmp(frame_id, "COMM") == 0)
//             print_comment_data(fp, size);
//         else
//             print_frame_data(fp, size, frame_id);
//     }

//     printf("---------------------------------------\n");
//     printf("DETAILS DISPLAYED SUCCESSFULLY\n");

//     fclose(fp);
// }





void help_menu()
{
    printf("---------------HELP MENU---------------\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("        2.1. -t -> to edit song title\n");
    printf("        2.2. -a -> to edit artist name\n");
    printf("        2.3. -A -> to edit album name\n");
    printf("        2.4. -y -> to edit year\n");
    printf("        2.5. -m -> to edit content\n");
    printf("        2.6. -c -> to edit comment\n");

    printf("---------------------------------------\n");
}





void print_comment_data(FILE *fp, unsigned int size)
{
    if (size <= 4)
    {
        return;
    }

    unsigned char encoding;

    if (fread(&encoding, 1, 1, fp) != 1)
    {
        return;
    }

    fseek(fp, 3, SEEK_CUR);  // Skip language
    size -= 4;

    // Skip comment description
    if (encoding == 1 || encoding == 2)
    {
        while (size >= 2)
        {
            int a = fgetc(fp);
            int b = fgetc(fp);
            size -= 2;

            if (a == 0 && b == 0)
            {
                break;
            }
        }
    }
    else
    {
        while (size > 0)
        {
            int ch = fgetc(fp);
            size--;

            if (ch == 0)
            {
                break;
            }
        }
    }

    char *data = malloc(size + 1);

    if (data == NULL)
        return;

    if (fread(data, 1, size, fp) == size)
    {
        if (encoding == 1 || encoding == 2)
        {
            unsigned int start = 0;
            unsigned int j = 0;

            // Skip UTF-16 BOM
            if ((unsigned char)data[0] == 0xFF ||(unsigned char)data[0] == 0xFE)
            {
                 start = 2;
            }

            for (unsigned int i = start; i + 1 < size; i += 2)
            {
                data[j++] = data[i];
            }

            data[j] = '\0';
        }
        else
        {
            data[size] = '\0';
        }

        printf("%s\n", data);
    }

    free(data);
}



void view_mp3_tagreader(char *filename)
{
    FILE *fp = open_mp3_file(filename);

    if (fp == NULL)
    {
        return;
    }

    if (!check_id3_header(fp))
    {
        printf("ID3 header not found\n");
        fclose(fp);
        return;
    }

    unsigned char header[10];

    rewind(fp);

    if (fread(header, 1, 10, fp) != 10)
    {
        fclose(fp);
        return;
    }

    int version = header[3];

    print_view_details();

    while (1)
    {
        char frame_id[5] = {0};

        if (!read_frame_id(fp, frame_id))
            break;


        if (frame_id[0] == '\0')
            break;

        unsigned int size = read_frame_size(fp, version);

        fseek(fp, 2, SEEK_CUR);

        if (size == 0)
        {
            break;
        }

        if (strcmp(frame_id, "TIT2") == 0)
        {
            printf("TITLE   : ");
        }
        else if (strcmp(frame_id, "TPE1") == 0)
        {
            printf("ARTIST  : ");
        }
        else if (strcmp(frame_id, "TALB") == 0)
        {
            printf("ALBUM   : ");
        }
        else if (strcmp(frame_id, "TYER") == 0)
        {
            printf("YEAR    : ");
        }
        else if (strcmp(frame_id, "TCON") == 0)
        {
            printf("MUSIC   : ");
        }
        else if (strcmp(frame_id, "COMM") == 0)
        {
            printf("COMMENT : ");
        }
        else
        {
            fseek(fp, size, SEEK_CUR);
            continue;
        }

        if (strcmp(frame_id, "COMM") == 0)
            print_comment_data(fp, size);
        else
            print_frame_data(fp, size, frame_id);
    }

    printf("---------------------------------------\n");
    printf("DETAILS DISPLAYED SUCCESSFULLY\n");

    fclose(fp);
}
