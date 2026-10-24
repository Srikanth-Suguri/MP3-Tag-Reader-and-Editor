#include <stdio.h>
#include <string.h>
#include "view.h"
#include <stdlib.h>
void edit_title(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
    {
        return;
    }

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame = find_frame(tag_data, tag_size, "TIT2", version);
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 1;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    get_text_data(new_value, new_data);
    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
    {
        fwrite(tag_data, 1, tag_size, fp);
    }

    free(new_data);
    free(tag_data);
    fclose(fp);
}

void edit_artist(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
        return;

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame = find_frame(tag_data, tag_size, "TPE1", version);
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 1;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    get_text_data(new_value, new_data);
    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
    {
        fwrite(tag_data, 1, tag_size, fp);
    }

    free(new_data);
    free(tag_data);
    fclose(fp);
}

void edit_album(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
    {
        return;
    }

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame = find_frame(tag_data, tag_size, "TALB", version);
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 1;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    get_text_data(new_value, new_data);
    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
    {
        fwrite(tag_data, 1, tag_size, fp);
    }

    free(new_data);
    free(tag_data);
    fclose(fp);
}

void edit_year(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
    {
        return;
    }

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    if (version == 4)
    {
        frame = find_frame(tag_data, tag_size, "TDRC", version);
    }
    else
    {
        frame = find_frame(tag_data, tag_size, "TYER", version);
    }
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 1;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    get_text_data(new_value, new_data);
    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
        fwrite(tag_data, 1, tag_size, fp);

    free(new_data);
    free(tag_data);
    fclose(fp);
}

void edit_genre(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
    {
        return;
    }

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame = find_frame(tag_data, tag_size, "TCON", version);
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 1;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    get_text_data(new_value, new_data);
    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
        fwrite(tag_data, 1, tag_size, fp);

    free(new_data);
    free(tag_data);
    fclose(fp);
}

void edit_comment(char *new_value, char *filename)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char *tag_data, *frame, *new_data;
    unsigned int tag_size, frame_size, new_size;
    int version;

    fp = fopen(filename, "r+b");
    if (fp == NULL)
        return;

    if (read_id3_header(fp, header) == 0)
    {
        fclose(fp);
        return;
    }

    version = get_id3_version(header);
    if (version == 0)
    {
        fclose(fp);
        return;
    }

    tag_size = get_tag_size(header);
    tag_data = malloc(tag_size);

    if (tag_data == NULL)
    {
        fclose(fp);
        return;
    }

    if (fread(tag_data, 1, tag_size, fp) != tag_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame = find_frame(tag_data, tag_size, "COMM", version);
    if (frame == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    frame_size = get_frame_size(frame + 4, version);
    new_size = strlen(new_value) + 5;

    if (new_size > frame_size)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data = calloc(frame_size, 1);
    if (new_data == NULL)
    {
        free(tag_data);
        fclose(fp);
        return;
    }

    new_data[0] = 0;
    new_data[1] = 'e';
    new_data[2] = 'n';
    new_data[3] = 'g';
    new_data[4] = 0;
    strcpy((char *)&new_data[5], new_value);

    memcpy(frame + 10, new_data, frame_size);

    if (fseek(fp, 10, SEEK_SET) == 0)
    {
        fwrite(tag_data, 1, tag_size, fp);
    }

    free(new_data);
    free(tag_data);
    fclose(fp);
}


unsigned int get_frame_size(unsigned char b[], int version)
{
    unsigned int size;

    if (version == 4)
    {
        size = (b[0] << 21) | (b[1] << 14) | (b[2] << 7) | b[3];
    }
    else
    {
        size = (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
    }

    return size;
}

int read_id3_header(FILE *fp, unsigned char header[])
{
    if (fread(header, 1, 10, fp) != 10)
    {
        return 0;
    }

    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3')
    {
        return 0;
    }

    return 1;
}

int get_id3_version(unsigned char header[])
{
    int version = header[3];

    if (version != 3 && version != 4)
    {
        return 0;
    }

    return version;
}

unsigned int get_tag_size(unsigned char header[])
{
    unsigned int size = header[6];

    size = (size << 7) | header[7];
    size = (size << 7) | header[8];
    size = (size << 7) | header[9];

    return size;
}

unsigned char *find_frame(unsigned char tag_data[], unsigned int tag_size,char frame_id[], int version)
{
    unsigned int i = 0, size;

    while (i + 10 <= tag_size)
    {
        if (tag_data[i] == 0)
        {
            break;
        }

        if (memcmp(&tag_data[i], frame_id, 4) == 0)
        {
            return &tag_data[i];
        }

        size = get_frame_size(&tag_data[i + 4], version);

        if (size > tag_size - i - 10)
        {
            break;
        }

        i += 10 + size;
    }

    return NULL;
}

void get_text_data(char *new_value, unsigned char data[])
{
    data[0] = 0;
    strcpy((char *)&data[1], new_value);
}