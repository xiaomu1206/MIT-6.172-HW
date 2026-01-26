// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PRINT_TYPES(type)  \
  printf("size of %s : %zu bytes \n", #type, sizeof(type))

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

  // Composite types have sizes too.
  typedef struct {
    int id;
    int year;
  } student;

  student you;
  you.id = 12345;
  you.year = 4;
  printf("size of %s : %zu bytes \n", "student", sizeof(you));

    int *p_int;
    short *p_short;
    long *p_long;
    char *p_char;
    float *p_float;
    double *p_double;
    unsigned int *p_uint;
    long long *p_ll;
    uint8_t *p_u8;
    uint16_t *p_u16;
    uint32_t *p_u32;
    uint64_t *p_u64;
    uint_fast8_t *p_uf8;
    uint_fast16_t *p_uf16;
    uintmax_t *p_umax;
    intmax_t *p_imax;
    __int128 *p_i128;
    student *p_student;
    int x;
    int *p_x = &x;

    printf("size of int* : %zu bytes\n", sizeof(p_int));
    printf("size of short* : %zu bytes\n", sizeof(p_short));
    printf("size of long* : %zu bytes\n", sizeof(p_long));
    printf("size of char* : %zu bytes\n", sizeof(p_char));
    printf("size of float* : %zu bytes\n", sizeof(p_float));
    printf("size of double* : %zu bytes\n", sizeof(p_double));
    printf("size of unsigned int* : %zu bytes\n", sizeof(p_uint));
    printf("size of long long* : %zu bytes\n", sizeof(p_ll));
    printf("size of uint8_t* : %zu bytes\n", sizeof(p_u8));
    printf("size of uint16_t* : %zu bytes\n", sizeof(p_u16));
    printf("size of uint32_t* : %zu bytes\n", sizeof(p_u32));
    printf("size of uint64_t* : %zu bytes\n", sizeof(p_u64));
    printf("size of uint_fast8_t* : %zu bytes\n", sizeof(p_uf8));
    printf("size of uint_fast16_t* : %zu bytes\n", sizeof(p_uf16));
    printf("size of uintmax_t* : %zu bytes\n", sizeof(p_umax));
    printf("size of intmax_t* : %zu bytes\n", sizeof(p_imax));
    printf("size of __int128* : %zu bytes\n", sizeof(p_i128));
    printf("size of student* : %zu bytes\n", sizeof(p_student));
    printf("size of &x : %zu bytes\n", sizeof(p_x));
    printf("size of x : %zu bytes\n", sizeof(x));

  return 0;
}
