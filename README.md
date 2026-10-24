# MP3 Tag Reader and Editor in C

## Description
This project is developed using C programming to read and edit metadata in MP3 audio files using ID3v2 tags.

## Features
- View MP3 metadata.
- Edit song title.
- Edit artist name.
- Edit album name.
- Edit year.
- Edit genre.
- Edit comment.
- Handle invalid arguments and file-opening errors.

## Technologies Used
- C Programming
- File Handling
- Pointers
- Strings
- Functions
- Dynamic Memory Allocation
- ID3v2 Tags

## Project Files
- `main.c` – Handles command-line arguments.
- `view.c` – Reads and displays MP3 metadata.
- `edittt.c` – Edits MP3 metadata.
- `view.h` – Contains function declarations.

## Compilation
Compile using GCC:

```bash
gcc *.c
```

## Usage

### View MP3 Details
```bash
./a.out -v Sooreede.mp3
```

### Edit Song Title
```bash
./a.out -e -t "Sooreede" Sooreede.mp3
```

### Supported Editing Options
- `-t` – Title
- `-a` – Artist
- `-A` – Album
- `-y` – Year
- `-g` – Genre
- `-c` – Comment

## Author
Suguri Srikanth
