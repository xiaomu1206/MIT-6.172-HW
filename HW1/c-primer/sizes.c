// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PRINT_TYPES(type)  \
  printf("size of %s : %zu bytes \n", #type, sizeof(type));

typedef struct {
  int id;
  int year;
} Student;

int main() {
  // Please print the sizes of the following types:
  // int, short, long, char, float, double, unsigned int, long long
  // uint8_t, uint16_t, uint32_t, and uint64_t, uint_fast8_t,
  // uint_fast16_t, uintmax_t, intmax_t, __int128, and student

    /* 基本类型 */
    PRINT_TYPES(int);
    PRINT_TYPES(short);
    PRINT_TYPES(long);
    PRINT_TYPES(char);
    PRINT_TYPES(float);
    PRINT_TYPES(double);
    PRINT_TYPES(unsigned int);
    PRINT_TYPES(long long);

    /* 固定宽度整数 */
    PRINT_TYPES(uint8_t);
    PRINT_TYPES(uint16_t);
    PRINT_TYPES(uint32_t);
    PRINT_TYPES(uint64_t);

    /* fastest / max 类型 */
    PRINT_TYPES(uint_fast8_t);
    PRINT_TYPES(uint_fast16_t);
    PRINT_TYPES(uintmax_t);
    PRINT_TYPES(intmax_t);

    /* GCC/Clang 扩展 */
    PRINT_TYPES(__int128);

    /* 自定义类型 */
    PRINT_TYPES(Student);

  // Composite types have sizes too.
  typedef struct {
    int id;
    int year;
  } student;

  student you;
  you.id = 12345;
  you.year = 4;


  // Array declaration. Use your macro to print the size of this.
  int x[5];
  printf("size of %s : %zu bytes \n", "x", sizeof(x));
  // You can just use your macro here instead: PRINT_TYPES("student", you);
  printf("size of %s : %zu bytes \n", "student", sizeof(you));

  return 0;
}
