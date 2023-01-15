#include "SString.h"

char HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

SString* sstr_createcs(char* str)
{
    SString* sstring = (SString*)malloc(sizeof(SString));

    sstring->s_capacity = 16;
    sstring->s_size = 0;
    sstring->s_str = (char*) malloc(sstring->s_capacity);

    for(;*str != 0; str++)
    {
        _sstr_appendc(sstring, *str);
    }
    _sstr_appendc(sstring, null);
    sstring->s_size--;
    return sstring;
}

SString* sstr_creates(char* str, unsigned int size)
{
    SString* sstring = (SString*)malloc(sizeof(SString));

    sstring->s_capacity = size;
    sstring->s_size = size;
    sstring->s_str = (char*)malloc(size);
    memcpy(sstring->s_str, str, size);

    _sstr_appendc(sstring, null);
    sstring->s_size--;

    return sstring;
}

SString* sstr_createe()
{
    SString* sstring = (SString*)malloc(sizeof(SString));

    sstring->s_capacity = 2;
    sstring->s_size = 0;
    sstring->s_str = (char*) malloc(sstring->s_capacity);
    
    _sstr_appendc(sstring, null);
    sstring->s_size--;

    return sstring;
}

SString* sstr_clone(SString* str)
{
    SString* ret = (SString*)malloc(sizeof(SString));
    ret->s_size = str->s_size;
    ret->s_capacity = ret->s_size;
    ret->s_str = (char*)malloc(sizeof(SString));
    memcpy(ret->s_str, str->s_str, ret->s_size);
    return ret;
}

static inline void _sstr_appendc(SString* str, char ch)
{
    if(str->s_capacity == str->s_size)
    {
        str->s_capacity *= 2;
        str->s_str = (char*)realloc(str->s_str, str->s_capacity);
    }
    *(str->s_str + str->s_size) = ch;
    str->s_size++;
}

void sstr_appendc(SString* str, char ch)
{
    _sstr_appendc(str, ch);
}

void sstr_appendcs(struct _sstring* base, char* str)
{
    char* ch;
    for(ch = str;*ch != null;ch++)
    {
       _sstr_appendc(base, *ch);
    }
    
    _sstr_appendc(base, null);
    base->s_size--;
}

void sstr_appends(SString* base, char* str, unsigned int size)
{
    extend: if(base->s_capacity < base->s_size+size)
    {
        base->s_capacity *= 2;
        base->s_str = (char*)realloc(base->s_str, base->s_capacity);
        goto extend;
    }

    memcpy(base->s_str+base->s_size, str, size);
    base->s_size += size;
}

char sstr_equals(SString* base, char* str, unsigned int size)
{
    if(size != base->s_size)
        return 0;
    unsigned int i;
    for(i = 0; i < size; ++i)
    {
        if(*(base->s_str + i) != *(str + i))
            return 0;
    }
    return 1;
}

signed char sstr_equals_mo(SString* base, char opts, ...)
{
    va_list arguments;                     
    va_start ( arguments, opts );  
    unsigned int i = 0, size = 0; 
    _ch:if(i < opts)
    {
        ++i;
        char* str = va_arg(arguments, char*);
        size = va_arg(arguments, unsigned int);
        if(size != base->s_size)
            goto _ch;
        unsigned int i;
        for(i = 0; i < size; ++i)
        {
            if(*(base->s_str + i) != *(str + i))
                goto _ch;
        }
        va_end ( arguments );
        return i;
    }
    return -1;
}

char sstr_endswith(SString* base, char* end, unsigned int end_size)
{
    if(end_size > base->s_size)
        return 0;
    unsigned int sp = base->s_size - end_size;
    unsigned int i;
    for(i = 0; i < end_size; i++)
    {
        if(*(end+i) != *(base->s_str + sp + i))
        {
            return 0;
        }
    }
    return 1;
}

char sstr_startswith(SString* base, char* start, unsigned int start_size)
{
    if(start_size > base->s_size)
        return 0;
    unsigned int i;
    for(i = 0; i < start_size; i++)
    {
        if(*(base->s_str+i) != *(start + i))
        {
            return 0;
        }
    }
    return 1;
}

extern inline unsigned long long sstr_toLong(SString* str)
{
    unsigned long long ret = 1;
    int i;
    for(i = 0; i < str->s_size; ++i)
    {
        ret += *(str->s_str + i);
        ret <<= 1;
    }
    return ret;
}

extern inline unsigned long long sstr_cs_toLong(char* str)
{
    unsigned long long ret = 1;
    int i;
    for(;*str != 0;str++)
    {
        ret += *str;
        ret <<= 1;
    }
    return ret;
}

static inline char sstr_smallerth(SString* str1, SString* str2)
{
    int size = str1->s_size > str2->s_size ? str1->s_size : str2->s_size;
    int i;
    for(i = 0; i < size; ++i)
    {
        if(*(str1->s_str) > *(str2->s_str))
            return 0;
        else if(*(str1->s_str) < *(str2->s_str))
            return 1;
    }
    return 0;
}

char sstr_smaller(SString* str1, SString* str2)
{
    return sstr_smallerth(str1, str2);
}

char sstr_bigger(SString* str1, SString* str2)
{
    return sstr_smallerth(str2, str1);
}

void sstr_delete(SString* sstr)
{
    free(sstr->s_str);
    free(sstr);
}

static inline void sstr_remove(SString* str, unsigned int a, unsigned int b)
{
    //printf("%d %d\n", str->s_size, b);
    //printf("%d %d %d\n", str->s_str +a, str->s_str+b, str->s_size-b);
    memmove(str->s_str +a, str->s_str+b, str->s_size-b);
    str->s_size -= (b-a);

    _sstr_appendc(str, null);
    str->s_size--;
}

static inline void sstr_removeAll(SString* str, char* remove, unsigned int size)
{
    int p = 0;
    int end_p;
    loop: end_p = (str->s_size - size);
    unsigned int _i;
    for(_i = 0; _i < size; ++_i)
    {
        if(*(str->s_str + _i + p) != *(remove + _i))
            goto br;
    }
    sstr_remove(str, p, p + size);
    if(p < str->s_size)
    {
        goto loop;
    }
    br:if(p < end_p)
    {
        //printf("i%d\n",p);
        ++p;
        goto loop;
    }
    _sstr_appendc(str, null);
    str->s_size--;
}

void sstr_replaceAll(SString* str, char* target, unsigned int tsize, char* replacement, unsigned int rsize)
{
    if(rsize == 0)
    {
        sstr_removeAll(str, target, tsize);
        return;
    }
    unsigned int end_p = str->s_size - tsize;
    int i = 0;
    int _i;
    loop:for(_i = 0; _i < tsize; ++_i)
    {
        if(*(str->s_str + _i + i) != *(target + _i))
            goto br;
    }
    sstr_remove(str, i, i + tsize);
    sstr_insert(str, i, replacement, rsize);
    end_p+=rsize;
    i+=rsize-1;
    br:if(i < end_p)
    {
        ++i; goto loop;
    }
}

void sstr_print(SString* str)
{
    fwrite(str->s_str, str->s_size, 1, stdout);
    printf("\n");
}

void sstr_printf(SString* str)
{
    fwrite(str->s_str, str->s_size, 1, stdout); 
}

static inline void sstr_insert(SString* str, unsigned int pos, char* insert, unsigned int isize)
{
    extend: if(str->s_capacity < str->s_size+isize)
    {
        str->s_capacity *= 2;
        str->s_str = (char*)realloc(str->s_str, str->s_capacity);
        goto extend;
    }
    memmove(str->s_str + pos + isize, str->s_str + pos, str->s_size-pos);
    memcpy(str->s_str + pos, insert, isize);
    str->s_size += isize;
}

void sstr_write(SString* str, FILE* file)
{
    fwrite(str->s_str, str->s_size, 1, file);
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void sstr_appendh(struct _sstring* base, unsigned long long num)
{
    char* appe = (char*)__builtin_alloca(64);
    unsigned char i;
    for(i = 0; num != 0; i++)
    {
        *(appe + (63 -i)) = HEX[num % 16];
        num >>= 4;
    }
    sstr_appends(base, appe + (64-i), i);
}

void sstr_appendd(struct _sstring* base, long long num)
{
    if(num == 0)
    {
        sstr_appendc(base, '0');
        return;
    }
    char* appe = (char*)__builtin_alloca(64);
    if(((unsigned long long)num & 9223372036854775808) == 9223372036854775808)
    {
        sstr_appendc(base, '-');
        num *= (-1);
    }
    unsigned char i;
    for(i = 0; num != 0; i++)
    {
        *(appe + (63 -i)) = 48 + (num % 10);
        num /= 10;
    }
    sstr_appends(base, appe + (64-i), i);
}

extern inline char sstr_isEmpty(SString* str)
{
    return (str->s_size == 0);
}

#ifdef __cplusplus
    void sstr_clear(SString* str)
#else
    extern inline void sstr_clear(SString* str)
#endif
{
    str->s_size = 0;
    _sstr_appendc(str, null); // set to 0, that printf outputs an empty string
    str->s_size--;
}

extern inline unsigned int sstr_size(SString* str)
{
    return str->s_size;
}

void sstr_fill(SString* base, char ch, unsigned int amount)
{
    unsigned int c = base->s_size + amount;
    extend: if(base->s_capacity < c)
    {
        base->s_capacity *= 2;
        base->s_str = (char*)realloc(base->s_str, base->s_capacity);
        goto extend;
    }
    for(;base->s_size < c;base->s_size++)
    {
        *(base->s_str + base->s_size) = ch;
    }
}

void sstr_removeFromEndAfter(SString* str, char target)
{
    for(;(str->s_size > 0) && (*(str->s_str +str->s_size) != target); str->s_size--);
    str->s_size++;
    _sstr_appendc(str, null);
    str->s_size--;
}

void sstr_removeFromEnd(SString* string, unsigned int amount)
{
    string->s_size-=amount;
    _sstr_appendc(string, null);
    string->s_size--;
}