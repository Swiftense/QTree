#ifndef SSTRING_H
    #define SSTRING_H
    #ifdef __cplusplus
        extern "C" {
    #endif
    #include <stdlib.h>
    #include <string.h>
    #include <stdarg.h>
    #include <stdio.h>

    #include "null.h"

    typedef struct _sstring SString;
    struct _sstring
    {
        int s_size, s_capacity;
        char* s_str;
    };

    // create String from C string
    struct _sstring* sstr_createcs(char* str);
    // create String from C string
    struct _sstring* sstr_creates(char* str, unsigned int size);
    // create empty String
    struct _sstring* sstr_createe();
    struct _sstring* sstr_clone(struct _sstring* str);
    static inline void _sstr_appendc(SString* str, char ch);
    // appends char to string
    void sstr_appendc(struct _sstring* base, char ch);
    // appends C string to SString
    void sstr_appends(struct _sstring* base, char* str, unsigned int size);
    // appends C string without given size to SString, last char of str has to be \0
    // is way slower than sstr_appends(), only used for readability of code
    void sstr_appendcs(struct _sstring* base, char* str);
    // appends hexadecimal to string
    void sstr_appendh(struct _sstring* base, unsigned long long num);
    // appends decimal to string
    void sstr_appendd(struct _sstring* base, long long num);
    char sstr_equals(SString* base, char* str, unsigned int size);
    // checks for multiple equals at the same time
    signed char sstr_equals_mo(SString* base, char opts, ...);
    char sstr_endswith(SString* base, char* end, unsigned int end_size);
    char sstr_startswith(SString* base, char* start, unsigned int start_size);
    void sstr_delete(SString* sstr);
    // converts string to long, is relevant for search algorithms
    extern inline unsigned long long sstr_toLong(SString* str);
    extern inline unsigned long long sstr_cs_toLong(char* str);
    char sstr_smaller(SString* str1, SString* str2);
    char sstr_bigger(SString* str1, SString* str2);
    static inline void sstr_removeAll(SString* str, char* replace, unsigned int size);
    // doesnt work bug free at the moment
    void sstr_replaceAll(SString* str, char* target, unsigned int tsize, char* replacement, unsigned int rsize);
    // clears section between a and b from string
    static inline void sstr_remove(SString* str, unsigned int a, unsigned int b);
    static inline void sstr_insert(SString* str, unsigned int pos, char* insert, unsigned int isize);
    // writes ssstring to file
    void sstr_write(SString* str, FILE* file);
    void printBits(size_t const size, void const * const ptr);
    void sstr_print(SString* str);
    // just like sstr_print without the \n at the end
    void sstr_printf(SString* str);  
    extern inline char sstr_isEmpty(SString* str);
    #ifdef __cplusplus
        void sstr_clear(SString* str);
    #else
        extern inline void sstr_clear(SString* str);
    #endif
    extern inline unsigned int sstr_size(SString* str);
    // appends char ch a certain amount to str
    void sstr_fill(SString* str, char ch, unsigned int amount);
    // starts parsing at end of <str>
    // removes everything after <target>
    void sstr_removeFromEndAfter(SString* str, char target);
    void sstr_removeFromEnd(SString* string, unsigned int amount);

    #ifdef __cplusplus
        }
    #endif
#endif