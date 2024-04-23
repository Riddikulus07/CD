//INPUT: a+b*c-d/e

#include <stdio.h>
#include <string.h>

// Function prototypes
char* get_temp(void);
void generate_tac(char* op, char* arg1, char* arg2, char* result);
void print_quad(char* op, char* arg1, char* arg2, char* result);
void print_triple(char* op, char* arg1, char* arg2);

int main() {
  char var1[] = "a";
  char var2[] = "b";
  char var3[] = "c";
  char var4[] = "d";
  char var5[] = "e";


  char* temp1 = get_temp();
  char* temp2 = get_temp();
  char* temp3 = get_temp();

  generate_tac("*", var2, var3, temp1); // temp1 = b * c
  generate_tac("/", var4, var5, temp2); // temp2 = d / e
  generate_tac("+", temp1, temp2, temp3); // temp3 = temp1 + temp2
  generate_tac("+", var1, temp3, var1);  // a = a + temp3
printf("\n\nExpression : a+b*c-d/e\n\n");

  printf("Three Address Code:\n");
  printf("%s = %s * %s\n", temp1, var2, var3);
  printf("%s = %s / %s\n", temp2, var4, var5);
  printf("%s = %s + %s\n", temp3, temp1, temp2);
  printf("%s = %s + %s\n", var1, var1, temp3);

  printf("\nQuadruples:\n");
  print_quad("*", var2, var3, temp1);
  print_quad("/", var4, var5, temp2);
  print_quad("+", temp1, temp2, temp3);
  print_quad("+", var1, temp3, NULL);

  printf("\nTriples:\n");
  print_triple("*", var2, var3);
  print_triple("/", var4, var5);
  print_triple("+", temp1, temp2);
  print_triple("+", var1, temp3);

  return 0;
}

char* get_temp(void) {
  static int temp_count = 0;
  char temp_name[10];
  sprintf(temp_name, "t%d", temp_count++);
  return strdup(temp_name);
}


void generate_tac(char* op, char* arg1, char* arg2, char* result) {
  printf("%s = %s %s%s\n", result, arg1 ? arg1 : "", op, arg2 ? arg2 : "");
}


void print_quad(char* op, char* arg1, char* arg2, char* result) {
  printf("%s %s %s %s\n", op, arg1, arg2, result);
}


void print_triple(char* op, char* arg1, char* arg2) {
  printf("%s %s %s\n", op, arg1, arg2);
}