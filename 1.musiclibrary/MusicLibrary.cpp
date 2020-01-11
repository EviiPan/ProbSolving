#include<iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define STRMAX 100
#define SONGMAX 1024

/*
 *song struct
 */
struct Song{
	char title[STRMAX];
	char artist[STRMAX];
	int year_publish;
};

/*
 * globle variables
 */
struct Song music_library[SONGMAX];
int current_number_of_songs = 0;
const char* m_filename;
FILE* m_fp;

/*
 * get song title
 */
void get_title(char* song_title){
	printf("Title: ");
	getchar();
	fgets(song_title, STRMAX, stdin);
	char* p;
	if((p = strchr(song_title, '\n')) != NULL)
		*p = '\0';
}

/*
 * get song artist
 */
void get_artist(char* song_artist){
	printf("Artist: ");
	fgets(song_artist, STRMAX, stdin);
	char* p;
	if((p = strchr(song_artist, '\n')) != NULL)
		*p = '\0';
}

/*
 * get song year
 */
int get_year(){
	int song_year;
	printf("Year Published: ");
	scanf("%d", &song_year);
	return song_year;
}

/*
 * make song
 */
Song make_song(){
	Song song;
	get_title(song.title);
	get_artist(song.artist);
	song.year_publish = get_year();
	return song;
}

/*
 * write song to library
 */
void store_song(Song song){
	fprintf(m_fp, "Title: %s, Artist: %s, Year Published: %d\n", song.title, song.artist, song.year_publish);
}

void store_MusicLibrary(){
	for(int i = 0; i < current_number_of_songs; i++){
		store_song(music_library[i]);
	}
}

/*
 * print song
 */
void print_song(int i){
	printf("Title: %s, Artist: %s, Year Published: %d\n", music_library[i].title, music_library[i].artist, music_library[i].year_publish);
}

/*
 *p command
 */
void print_MusicLibrary(){
	for(int i = 0; i < current_number_of_songs; i++){
		print_song(i);
	}
}

/*
 * ============load music===========
 */
void read_title_artist(char* words){
	char ch;
	int count = 0;
	while((ch = fgetc(m_fp)) != ' '){}
	while((ch = fgetc(m_fp)) != ','){
		words[count++] = ch;
	}
	words[count] = '\0';
	printf("%s ", words);
}

int read_year(){
	int year;
	fscanf(m_fp, "%d", &year);
	printf("year %d\n", year);
	return year;
}

void read_song(){
	char title[STRMAX];
	char artist[STRMAX];
	read_title_artist(title);
	read_title_artist(artist);
	read_year();
}

void load_MusicLibrary(){
	char ch;
	while((ch = fgetc(m_fp)) != EOF){
		ungetc(ch, m_fp);
		read_song();
	}
}

/*=====================================
 *to lower case
 */
char* to_lower_case(const char* words, char* trans_words){
	strcpy(trans_words, words);
	for(int i = 0; trans_words[i] != '\0'; i++){
		if(trans_words[i] >= 65 && trans_words[i] <= 97)
			trans_words += 32;
	}
	return trans_words;
}

/*
 * binary search
 */
int binary_search(char* key_words, int min_val, int max_val){
	int mid = (min_val + max_val)/2;
	char lower_case_title[STRMAX], lower_case_key[STRMAX];
	int cmp = strcmp(to_lower_case(music_library[mid].title, lower_case_title), to_lower_case(key_words, lower_case_key));
	if(max_val < min_val)
		return min_val;
	else
		return cmp > 0 ? binary_search(key_words, min_val, mid-1) : 
			cmp < 0 ? binary_search(key_words, mid+1, max_val) : mid;
}

/*
 * find index
 */
int find_index_of_song_with_name(char* song_name){
	return binary_search(song_name, 0, current_number_of_songs-1);
}

/*
 * whether contain song
 */
int contain_song(char* key_words, int min_val, int max_val){
	int mid = (min_val + max_val)/2;
	char lower_case_title[STRMAX], lower_case_key[STRMAX];
	int cmp = strcmp(to_lower_case(music_library[mid].title, lower_case_title), to_lower_case(key_words, lower_case_key));
	if(max_val < min_val)
		return 0;
	else
		return cmp > 0 ? contain_song(key_words, min_val, mid-1) : 
			cmp < 0 ? contain_song(key_words, mid+1, max_val) : 1;
}
/*================================
 *crunch up
 *insert an item from the music list
 */
void crunch_up_from_index(int index){
	for(int i = current_number_of_songs-1; i >= index; i--){
		music_library[i+1] = music_library[i];
	}
}
/*
 *i command
 */
void insert_song(){
	Song new_song = make_song();
	int index = find_index_of_song_with_name(new_song.title);
	crunch_up_from_index(index);
	music_library[index] = new_song;
	current_number_of_songs ++;
}

/*===============================
 *crunch down
 *remove an item from the music list
 */
void crunch_down_from_index(int index){
	for(int i = index; i < current_number_of_songs; i++){
		music_library[i] = music_library[i+1];
	}
}

void remove_song_from_MusicLibrary_by_name(char* song_name){
	if(contain_song(song_name, 0, current_number_of_songs-1)){
		crunch_down_from_index(find_index_of_song_with_name(song_name));
		current_number_of_songs --;
	}
}
/*
 *d command
 */
void delete_song(){
	char title[STRMAX];
	get_title(title);
	remove_song_from_MusicLibrary_by_name(title);
}

/*=================================
 *look up song
 */
void look_up_song_with_name(char* song_name){
	if(contain_song(song_name, 0, current_number_of_songs-1)){
		print_song(find_index_of_song_with_name(song_name));
	}
}
/*
 *l command
 */
void look_up_song(){
	char title[STRMAX];
	get_title(title);
	look_up_song_with_name(title);
}

/*=================================
 *obtain filename
 */
const char* obtain_filename(char* name){
	return name == NULL ? "myMusic" : name;
}

/*
 * open file
 */
void open_file(const char* filename, const char* mode){
	m_fp = fopen(filename,mode);
	if(m_fp == NULL)
		m_fp = fopen(filename, "w");
}

/*================================
 * ensure valid command
 */
int valid_command(char cmd){
	switch(cmd){
		case 'i':
		case 'I':
		case 'p':
		case 'P':
		case 'd':
		case 'D':
		case 'l':
		case 'L':
		case 'q':
		case 'Q':
			return 1;
		default:
			break;
	}
	return 0;
}

/*
 * read command
 */
char read_command(){
	char cmd;
	scanf("%c*c", &cmd);
	return valid_command(cmd) ? cmd : '\0';
}
/*
 *evaluate command
 */
char evaluate_command(char cmd){
	switch(cmd){
		case 'i':
		case 'I':
			insert_song();
			break;
		case 'p':
		case 'P':
			print_MusicLibrary();
			break;
		case 'd':
		case 'D':
			delete_song();
			break;
		case 'l':
		case 'L':
			look_up_song();
			break;
		case 'q':
		case 'Q':
			store_MusicLibrary();
			fclose(m_fp);
			printf("quit...\n");
			return 'q';
		default:
			break;
	}
	return 'a';
}
/*
 * take command
 */
char command_loop(){	
	printf("prompt:\n");
	char ch = read_command();
	return evaluate_command(ch);
}

/*=======================================================
 *main
 */
int main(int argc, char* argv[]){
	m_filename = obtain_filename(argv[1]);
	open_file(m_filename, "r+");
	load_MusicLibrary();
	char ch;
	while(ch != 'q'){
		ch = command_loop();
	}
	return 0;
}
 




