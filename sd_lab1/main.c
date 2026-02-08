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

int is_letter(char let) {
	if (('A' <= let && let <= 'Z') || ('a' <= let && let <= 'z')) return 1;
	return 0;
}

int readline(FILE* file, char** char_per) {
	*char_per = realloc(*char_per, sizeof(char));
	int cur_pos = 0;
	char cur_symb = getc(file);
	while (cur_symb != '\n' && cur_symb != EOF) {
		(*char_per)[cur_pos] = cur_symb;
		*char_per = realloc(*char_per, sizeof(char) * (++cur_pos + 1));
		cur_symb = getc(file);
	}
	(*char_per)[cur_pos] = '\0';
}

void find(int cur_pos_text) {
	int cur_pos_from = 0;
	int start;
	for (cur_pos_text; cur_pos_text <= len_str(text); cur_pos_text++) {
		if (cur_pos_text != len_str(text) && text[cur_pos_text] == from[cur_pos_from]) {
			if (cur_pos_from == 0) start = cur_pos_text;
			cur_pos_from++;
		}
		else if (cur_pos_from == len_str(from) && (cur_pos_text == len_str(text) || !is_letter(text[cur_pos_text])) && (start == 0 || !is_letter(text[start - 1]))) {
			find(replacement(start, cur_pos_text - 1));
			return;
		}
		else cur_pos_from = 0;
	}

}

int replacement(int start, int finish) {
	
	int to_len = len_str(to);
	int razn = to_len - len_str(from); // на сколько заменяемое больше исходного
	int txt_len = len_str(text) + razn;
	if (razn > 0) {
		text = realloc(text, sizeof(char) * (txt_len + 1));
		for (int i = (txt_len)-1; i > (finish + razn); i--) {
			text[i] = text[i - razn];
		}
	}
	else if (razn < 0) {
		for (int i = (finish + razn + 1); i < txt_len; i++) {
			text[i] = text[i + 1];
		}
		text[txt_len] = '\0';
		text = realloc(text, sizeof(char) * (txt_len + 1));
	}

	for (int i = 0; i < to_len; i++) {
		text[start + i] = to[i];
	}
	text[txt_len] = '\0';
	return finish + razn + 1;
}

void main() {

	FILE* input_file, *from_file, *to_file, *complete_file;
	input_file = fopen("input.txt", "r");
	from_file = fopen("from.txt", "r");
	to_file = fopen("to.txt", "r");
	complete_file = fopen("output.txt", "w");


	//кол-во слов для замены
	int count_lines = 0;
	char cur_char = getc(from_file);
	while (cur_char != EOF) {
		if (cur_char == '\n')
		count_lines++;
		cur_char = getc(from_file);
	}
	count_lines++;
	rewind(from_file);

	//readzzzzz
	readline(input_file, &text);

		while (text[0] != NULL) {
			for (int i = 0; i < count_lines; i++) {
				readline(from_file, &from);
				readline(to_file, &to);
				find(0);
			}
			fprintf(complete_file, "%s\n", text);
			readline(input_file, &text);
			rewind(from_file);
			rewind(to_file);
	}
		free(text); free(from); free(to);
		fclose(input_file); fclose(from_file); fclose(to_file); fclose(complete_file);
}