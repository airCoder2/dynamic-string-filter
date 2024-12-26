/*Bismillah*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct my_array {
  char (*array)[10];
  int number;
};

typedef struct my_array MyArray;


MyArray *length_filter(MyArray *input_struct){ // This is a function that returns the filtered struct


  MyArray *length_struct = malloc(sizeof(MyArray));

  if (length_struct == NULL) {
    perror("Failed to allocate memory to length_struct");
    exit(1);
  }

  length_struct->array = malloc(sizeof(char[10]));

  if (length_struct->array == NULL) {
    perror("Failed to allocate memory to length_struct->array");
    exit(1);
  }

  length_struct->number = 0;
  char (*temp_array)[10]; 

  
  for (int i = 0; i < input_struct->number; i++) {
    if (strlen(input_struct->array[i]) <= 5) {

      strcpy(length_struct->array[length_struct->number], input_struct->array[i]);
      length_struct->number++;

      temp_array = realloc(length_struct->array, sizeof(char[10])*(length_struct->number+1));

      if (temp_array == NULL) {
        perror("Failed to reallocate memory to length_struct->array");
        exit(1);
      }

      length_struct->array = temp_array;

    }

  }
  
  return length_struct;
}

MyArray *callback_function(MyArray *(*function_pointer)(MyArray *), MyArray *to_be_filtered){

  MyArray *first_filter = function_pointer(to_be_filtered);



  return first_filter;
}




int main(int argc, char *argv[])
{

  MyArray *input_struct = malloc(sizeof(MyArray));

  if (input_struct == NULL) {
    perror("Failed to allocate memory to input_struct");
    exit(1);
  }

  puts("\nEnter at most 10 characters");
  puts("Enter \"end\" to  exit\n");


  input_struct->array = malloc(sizeof(char[10])); //allocating memory for the array of strings of 10 bt

  if (input_struct->array == NULL) {
    perror("Error allocating memory");
    exit(1);
  }
  printf("allocated 10 bytes\n");

  char the_word[10];
  input_struct->number = 0;
  char (*temp_array)[10];

  while (1) {

    fputs(">> ", stdout);   
    scanf("%s", the_word); //storing the word entered by the user in a temp array

    if (strcmp(the_word, "end") == 0) { // checking if user is done with entering words
      break;
    }

    strcpy(input_struct->array[input_struct->number], the_word); // copy the word to our array
    input_struct->number++;

    temp_array = realloc(input_struct->array, sizeof(char[10])*(input_struct->number +1)); 

    if (temp_array == NULL) {
      perror("Error allocating memory");
      exit(1);
    } 

    input_struct->array = temp_array;
  } 

  MyArray *first_filtered_input_struct = callback_function(length_filter,input_struct);



  printf("Total number of words: %d\n", input_struct->number);
  printf("Words with more than 5 letters: %d\n", first_filtered_input_struct->number);

 return 0;
}
