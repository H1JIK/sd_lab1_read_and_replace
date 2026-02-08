#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* text;
char* from;
char* to;

int len_str(char* str) {
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

void readline(FILE* file, char** char_per) {
	*char_per = realloc(*char_per, sizeof(char));
	int cur_pos = 0;
	char cur_symb = getc(file);
	while (cur_symb != '\n' && cur_symb != EOF) {
		(*char_per)[cur_pos] = cur_symb;
		*char_per = realloc(*char_per, sizeof(char) * (++cur_pos + 1));
		cur_symb = getc(file);
	}
	(*char_per)[cur_pos] = '\0';
	//printf("%s\n", *char_per);
}

void find() {
	int cur_pos_text = 0;
	int cur_pos_from = 0;
	int start;
	while (text[cur_pos_text] != '\0') {
		if (text[cur_pos_from] == from[cur_pos_from]) {
			start = cur_pos_text;
			cur_pos_from++;
		}
		else if (cur_pos_from != 0 && text[cur_pos_text] == ' ') {
			cur_pos_text = replacement(start, cur_pos_text - 1);
			cur_pos_from = 0;
		}
		else {
		cur_pos_from = 0;
		}
		cur_pos_text++;

	}

}

int replacement(int start, int finish) {
	
	int razn = len_str(to) - (finish - start); // на сколько заменяемое больше исходного
	if (razn > 0) {
		text = realloc(text, sizeof(char) + razn);
		for (int i = len_str(text) - 1; i > finish; i--) {
			text[i] = text[i - 1];
		}
	}
	else if (razn < 0) {
		//for (int i = finish - razn; i < ){
		//
		//}
	}

	return;
	//for (int i = start; )


}

void main() {

	FILE* input_file, *from_file, *to_file, *complete_file;
	input_file = fopen("input.txt", "r");
	from_file = fopen("from.txt", "r");
	to_file = fopen("to.txt", "r");
	complete_file = fopen("output.txt", "r");



	//char* output = malloc(sizeof(char));
	
	
	//кол-во слов для замены
	int count_lines = 0;
	char cur_char = getc(from_file);
	while (cur_char != EOF) {
		if (cur_char == '\n')
		count_lines++;
		cur_char = getc(from_file);
	}
	count_lines++;

	//readzzzzz
	readline(input_file, &text);
		while (text[0] != NULL) {
			printf("%s\n", text);
			readline(input_file, &text);
	}

}