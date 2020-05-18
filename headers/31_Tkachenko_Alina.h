#include <stdio.h>

struct Spirmen
{ 
  int * arr;
  int current_index;
  int len_arr;
};

struct Spirmen insert(struct Spirmen this, int elem);
struct Spirmen insert_struct(struct Spirmen this, struct Spirmen other);
struct Spirmen insert_arr(struct Spirmen this, int * addition_arr, int size_add_arr);
struct Spirmen delete_elem(struct Spirmen this, int elem);
struct Spirmen delete_after_index(struct Spirmen this, int index);
struct Spirmen add_spirmen(struct Spirmen this, struct Spirmen other);
struct Spirmen sub_spirmen(struct Spirmen this, struct Spirmen other);
int input_spirmen(struct Spirmen *this);
void output_spirmen(struct Spirmen this, int width);
int input_binary_file_spirmen(char* file_name, struct Spirmen *this);
int output_binary_file_spirmen(char* file_name, struct Spirmen this);
int input_text_file_spirmen(char* file_name, struct Spirmen *this);
int output_text_file_spirmen(char* file_name, struct Spirmen this, int width);
