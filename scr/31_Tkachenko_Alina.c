#include "../headers/31_Tkachenko_Alina.h"
#include "copy.h"
#include <stdio.h>
#include <stdlib.h>

struct Spirmen insert(struct Spirmen this, int elem)
{
  const short std_add_size = 10;
  if(this.current_index == this.len_arr - 1)
  {
     int * arr = (int *)calloc(this.len_arr + std_add_size, sizeof(int));
     copy(arr, this.arr, this.len_arr, 0, 0);
     free(this.arr);
     this.arr = arr;
     arr = NULL;
     this.len_arr += std_add_size;
     this.arr[this.current_index] = elem;
     ++this.current_index;
  }
  else
  {
   this.arr[this.current_index] = elem;
   ++this.current_index;
  }
 
  return this;
}

struct Spirmen insert_struct(struct Spirmen this, struct Spirmen other)
{
   if(this.len_arr- this.current_index > other.len_arr)
   {
     copy(this.arr, other.arr, other.len_arr, ++this.current_index, 0);
   }
   else
   {
    int * other_arr = malloc(this.len_arr + other.len_arr);
    copy(other_arr, this.arr, this.len_arr, 0, 0);
    copy(other_arr, other.arr, this.len_arr, 0, 0);
    free(this.arr);
    this.arr = other_arr;
    other_arr = NULL;
    this.len_arr += other.len_arr;
   }
   return this;
}

struct Spirmen insert_arr(struct Spirmen this, int * addition_arr, int size_add_arr)
{
  if(this.len_arr- this.current_index > size_add_arr)
  {
    copy(this.arr, addition_arr, size_add_arr, ++this.current_index, 0);
  }
  else
  {
      for(size_t i = 0; i < size_add_arr; ++i)
      {
         insert(this, addition_arr[i]);
      }
  }
  return this;
}

struct Spirmen delete_elem(struct Spirmen this,int elem)
{
   int index;
   
   for(int i = 0; i < this.len_arr; ++i)
   {
     if(this.arr[i] == elem)
     {
        index = i;
	break;
     }
   }

   return delete_after_index(this, index);
         
}

struct Spirmen delete_after_index(struct Spirmen this, int index)
{
    if (index >= this.len_arr)
    {
        return this;
    }

   int * arr = (int *)calloc(this.len_arr,sizeof(int));
   copy(arr,this.arr,index,0,0);
   copy(arr,this.arr, this.len_arr, index, ++index);
   free(this.arr);
   this.arr = arr;
   arr = NULL;
   --this.current_index;
   return this;
}

struct Spirmen add_spirmen(struct Spirmen this, struct Spirmen other)
{
  const short std_size = 10;
  struct Spirmen spirmen;
  spirmen.current_index = 0;
  spirmen.len_arr = std_size;
  spirmen.arr = (int *)calloc(this.len_arr, sizeof(int));

  /*
    Виконуємо операцію перетину множин.
    Перевіряєм кожне число в множині, якщо воно є в іншій, то добавляємо це значення в spirmen
   */
  for(int i = 0; i < this.len_arr; ++i)
  {
	for(int j = 0; j < other.len_arr; ++j)
	{
		if(this.arr[i] != other.arr[j])
		{
            continue;
		}
		
		spirmen = insert(spirmen, this.arr[i]);
	}
  }

  return spirmen;
}

struct Spirmen sub_spirmen(struct Spirmen this, struct Spirmen other)
{
    const short std_size = 10;
    struct Spirmen spirmen;
    spirmen.current_index = 0;
    spirmen.len_arr = std_size;
    spirmen.arr = (int *)calloc(this.len_arr, sizeof(int));
    other = add_spirmen(this,other);

    /*
    Виконуємо операцію перетину множин.
    Перевіряєм кожне число в множині, якщо його немає в іншій, то добавляємо це значення в spirmen
   */
  
  for(int i = 0; i < this.len_arr; ++i)
  {
	for(int j = 0; j < other.len_arr; ++j)
	{
		if(this.arr[i] == other.arr[j])
		{
            continue;
		}
		
		insert(spirmen, this.arr[i]);
	}
  }

  return spirmen;
}

int input_spirmen(struct Spirmen* this)
{
   int i;
   printf("Enter number elements:", this->len_arr);
   scanf("%d", &this->len_arr);

   int a[this->len_arr];

   for(i = 0; i < this->len_arr; ++i)
   {
      printf("a[%d] = ", i);
      scanf("%d", &a[i]);
   }

   *this = insert(*this,a);
}
 
void output_spirmen(struct Spirmen this, int width)
{
   for(int i = 0; i < this.len_arr; ++i)
   {
     printf("a[%d] = %i", i, this.arr[i]);
     printf("%c",width);
   }
}
 
int input_binary_file_spirmen(char* file_name, struct Spirmen* this)
{
   FILE * file;
   char ch;
   char ch_arr[100];
   int elem;
   int i = 0;
   if((file = fopen(file_name, "rb")) == NULL)
   {
     printf("Cannot open file");
     return 0;
   }

   while(!feof(file))
   {
     ch = fgetc(file);

     if(ch == '\t')
     {
       elem = atoi(ch_arr);
       *this = insert(*this, elem);
       continue;
     }

     ch_arr[i] = ch; 
   }
   
   fclose(file);
   return 1;
} 

int output_binary_file_spirmen(char* file_name, struct Spirmen this)
{
  FILE * file = fopen(file_name, "wb");
  const short len = 100;
  char buf[len];

   for(int i = 0; i < this.len_arr; ++i)
   {
     snprintf(buf, len, "%i", this.arr[i]);
     fputs(buf, file);
     fputc('\t', file);
   }

   fclose(file);
   return 1;
}

int input_text_file_spirmen(char* file_name, struct Spirmen* this)
{
   FILE * file;
   char ch;
   char ch_arr[100];
   int elem;
   int i = 0;
   if((file = fopen(file_name, "r")) == NULL)
   {
     printf("Cannot open file");
     return 0;
   }

   while(!feof(file))
   {
     ch = fgetc(file);

     if(ch == '\t')
     {
       elem = atoi(ch_arr);
       *this = insert(*this, elem);
       continue;
     }

     ch_arr[i] = ch; 
   }
   
   fclose(file);
   return 1;
}

int output_text_file_spirmen(char* file_name, struct Spirmen this,  int width)
{
   FILE * file = fopen(file_name, "w");
   const short len = 100;
   char buf[len];

   for(int i = 0; i < this.len_arr; ++i)
   {
       snprintf(buf, len, "%i", this.arr[i]);
       fputs(buf, file);
       fputc('\t', file);
   }

   fclose(file);
   return 1;
}
