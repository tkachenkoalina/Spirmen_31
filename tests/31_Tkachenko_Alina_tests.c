#include "../headers/31_Tkachenko_Alina.h"
#include <stdio.h>
#include <stdlib.h>

struct Spirmen * test_input_from_console()
{
   int val;
   struct Spirmen * spirmen = (struct Spirmen *)malloc(sizeof(struct Spirmen));
   spirmen->current_index = 0;
   printf("Enter the amount of input:");
   scanf("%i", &val);
   spirmen->len_arr = val/2; 
   spirmen->arr = (int*)calloc(spirmen->len_arr, sizeof(int));

   printf("Test insert_struct for number\n");
   printf("Input number: ");
   scanf("%i", &val);
   *spirmen = insert(*spirmen, val);
   printf("Ok\n");
   
   printf("Test insert_struct for arr\n");

   if(!input_spirmen(spirmen))
   {
     printf("Some wrong\n");
   }

   printf("Ok\n");

   struct Spirmen * this = (struct Spirmen *)malloc(sizeof(struct Spirmen));;
   this->current_index = 0;
   this->len_arr = val/2; 
   this->arr = (int*)calloc(this->len_arr, sizeof(int));

   printf("Test insert_struct for other structure\n");
   
   if(!input_spirmen(spirmen))
   {
     printf("Some wrong\n");
   } 

   *spirmen = insert(*spirmen, this);
   free(this);
   printf("Ok\n");

   return spirmen;  
}

struct Spirmen * test_input_from_textfile()
{
  struct Spirmen *this = (struct Spirmen *)malloc(sizeof(struct Spirmen));
  this->current_index = 0;
  this->len_arr = 10;
  this->arr = (int*)calloc(this->len_arr, sizeof(int));
  
  char in[100];
  printf("Input filename: ");
  scanf("%s", in);
  
  if(!input_text_file_spirmen(in, this))
  {
    printf("Some wrong\n");
  }
  printf("Ok\n");

  return this;
}

struct Spirmen * test_input_from_binary_file()
{
  struct Spirmen *this = (struct Spirmen *)malloc(sizeof(struct Spirmen));
  this->current_index = 0;
  this->len_arr = 10;
  this->arr = (int*)calloc(this->len_arr, sizeof(int));
  
  char in[100];
  printf("Input filename: ");
  scanf("%s", in);
  
  if(!input_binary_file_spirmen(in, this))
  {
    printf("Some wrong\n");
    free(this->arr);
    this->arr = NULL;
    this = NULL;
    return this;
  }
  printf("Ok\n");

  return this;
}

void test_delete_elem(struct Spirmen * this)
{
  int std_size = this->len_arr;
  int elem;
  printf("Test delete elem module\nInput elem: ");
  scanf("%i", &elem);
  *this = delete_elem(*this, elem);
   
//  if(std_size == this->len_arr)
//  {
//    printf("Some wrong\n");
//    return;
//  }
  
  printf("Ok\n");
}

void test_delete_after_index(struct Spirmen * this)
{
  int std_size = this->len_arr;
  int index;
  printf("Test delete after index module\nInput index: ");
  scanf("%i", &index);
  *this = delete_after_index(*this, index);
   
/*  if(std_size == this->len_arr)
  {
    printf("Some wrong\n");
    return;
  } */
  
  printf("Ok\n");
}


struct Spirmen test_add_spirmen(struct Spirmen *one, struct Spirmen *two)
{
   return add_spirmen(*one, *two);
}

struct Spirmen test_sub_spirmen(struct Spirmen *one, struct Spirmen *two)
{
   return sub_spirmen(*one, *two);
}


void test_c_spirmen()
{
  struct Spirmen * spirmen;
  char out[] = 
  { "Enter data entry option:\n1. Read data from console\n2. Read data from textfile\n3. Read data from binary file\nOption number: "};
  printf(out);
  int option;
  scanf("%i", &option);

  if(option == 1)
  {
    spirmen = test_input_from_console();
  }
  else if(option == 2)
  {
    spirmen = test_input_from_textfile();
  }
  else if(option == 3)
  {
    spirmen = test_input_from_binary_file();
  }

  if(spirmen == NULL)
     return;

  test_delete_elem(spirmen);
  test_delete_after_index(spirmen);  

  struct Spirmen * spirmen_test = (struct Spirmen *)malloc(sizeof(struct Spirmen));
  spirmen_test->len_arr = 10;
  spirmen_test->arr = (int *)calloc(spirmen_test->len_arr, sizeof(int));

  printf("Test add and sub methods\n");
  char out_1[] = {"Enter data entry option:\n1. Read data from console\n2. Read data from textfile\n3. Read data from binary file\nOption number: "};
  printf(out_1);
  scanf("%i", &option);

  if(option == 1)
  {
    input_spirmen(spirmen_test);
  }
  else if(option == 2)
  {
    printf("Input file name: ");
    scanf("%s", &out_1);

    if(!input_text_file_spirmen(out_1,spirmen_test))
    {
      printf("Some wrong with reading file\n");
      return;
    }
  }
  else if(option == 3)
  {
    printf("Input file name: ");
    scanf("%s", &out_1);
    if(!input_binary_file_spirmen(out_1, spirmen_test))
    {
      printf("Some wrong with reading file\n");
      return;
    }
  }

  struct Spirmen spirmen_res_1 = test_add_spirmen(spirmen, spirmen_test);
  struct Spirmen spirmen_res_2 = test_sub_spirmen(spirmen, spirmen_test);

  for(int i = 0; i < spirmen_res_1.len_arr; i++)
  {
   for(int j = 0; j < spirmen_res_2.len_arr; j++)
     {
         if(spirmen_res_1.arr[i] == spirmen_res_2.arr[i])
          {
             printf("Testing wrong");
             option = 0;
             break;
          }
     } 
     if(!option)
        break;
 }
  
  printf("Output result of sub operation\n");
  output_spirmen(spirmen_res_2, '\n');
  printf("Write to text file result of sub operation\nEnter file name: ");
  scanf("%s", &out);
  
  if(!output_text_file_spirmen(out, spirmen_res_2, '\t'))
  { 
    printf("Some wrong when write data to file\n");  
  }

  printf("Ok\n");

  printf("Write to binary file result of sub operation\nEnter file name: ");
  scanf("%s", &out);
  
  if(!output_binary_file_spirmen(out, spirmen_res_2))
  { 
    printf("Some wrong when write data to file\n");  
  }

  printf("Ok\n");
}

int main()
{
  test_c_spirmen();
}
