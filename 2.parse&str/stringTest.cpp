//
//  main.cpp
//  stringTest
//
//  Created by Evii Pan on 10/9/19.
//  Copyright © 2019 Evii Pan. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>

#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)

//strlen, strcpy, strcat, strcmp, strncmp, strchr, strpbrk, strstr, strspn, strtok


/* strlen
 * size_t strlen(const char* str) computes the length of the string str up to, but not including the terminating null character.
 */
size_t strlen(const char* str){
    size_t count;
    for(count  = 0; str[count] != '\0'; count++);
    return count;
}

/* strcpy
 * char *strcpy(char *dest, const char *src) copies the string pointed to, by src to dest.
 */
char* strcpy(char* dest, const char* src){
    int i;
    for(i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

/* strcat
 * char *strcat(char *dest, const char *src) appends the string pointed to by src to the end of the string pointed to by dest.
 */
char *strcat(char *dest, const char *src){
    int len = strlen(dest);
    for(int i = 0; src[i] != '\0'; i++)
        dest[len+i] = src[i];
    return dest;
}

/* strcmp
 * int strcmp(const char *str1, const char *str2) compares the string pointed to, by str1 to the string pointed to by str2.
 */
int strcmp(const char *str1, const char *str2){
    
    while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2){
        str1++;
        str2++;
    }
    
    return *str1 - *str2;
}

/* strncmp
 * int strncmp(const char *str1, const char *str2, size_t n) compares at most the first n bytes of str1 and str2.
 */
int strncmp(const char *str1, const char *str2, size_t n){
    
    while(n-- && *str1 != '\0' && *str2 != '\0' && *str1 == *str2){
        str1++;
        str2++;
    }
    
    return *str1 - *str2;
}
/* strchr
 * char *strchr(const char *str, int c) searches for the first occurrence of the character c (an unsigned char) in the string
 * pointed to by the argument str.
 */
const char *strchr(const char *str, int c){
    if(str == NULL)
        return NULL;
    while(*str != '\0'){
        if(*str == c)
            return (char*)str;
        str++;
    }
    return NULL;
}
/*
char *strchr2(const char *str, int c){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == c)
            return (char*)str + i;
    }
    return NULL;
}
*/

/* strpbrk
 * char *strpbrk(const char *str1, const char *str2) finds the first character in the string str1 that matches any character
 * specified in str2. This does not include the terminating null-characters.
 */
const char *strpbrk(const char *str1, const char *str2){
    const char* ch = str2;
    for(; *str1 != '\0'; str1 ++){
        for(; *ch != '\0'; ch++){
            if(*str1 == *ch)
                return (char*) str1;
        }
        ch = str2;
    }
    return NULL;
}

/* strstr
 * char *strstr(const char *haystack, const char *needle) function finds the first occurrence of the substring needle in the
 * string haystack. The terminating '\0' characters are not compared.
 */
const char *strstr(const char *haystack, const char *needle){
    int n;
    if(*needle){
        while(*haystack){
            for(n = 0; *(haystack + n) == *(needle + n); n++){
                if(! *(needle + n + 1))
                    return (char*)haystack;
            }
            haystack++;
        }
        return NULL;
    }
    else
        return (char*) haystack;
}

/* strspn
 * size_t strspn(const char *str1, const char *str2) calculates the length of the initial segment of str1 which consists entirely
 * of characters in str2.
 */
size_t strspn(const char *str1, const char *str2){
    size_t cnt = 0;
    const char *temp = str2;
    for(; *str1 != '\0'; str1++){
        str2 = temp;
        for(; *str2 != '\0'; str2++){
            if(*str1 == *str2)
                break;
        }
        if(*str2 == '\0')
            return cnt;
        cnt++;
    }
    return cnt;
}

/* strtok
 * char *strtok(char *str, const char *delim) breaks string str into a series of tokens using the delimiter delim.
 */
char *strtok(char *str, const char *delim){
    static char *temp_str = NULL;
    const char *delim_cp = delim;
    int flag = 1, index = 0;
    
    char *res = NULL;
    if(str == NULL)
        str = temp_str;
    
    for(; *str; str++){
        delim = delim_cp;
        for(; *delim; delim++){
            if(*str == *delim){
                *str = '\0';
                index = 1;
                break;
            }
        }
        if(*str != '\0' && flag == 1){
            res = str;//记录第一个非分隔符的位置
            flag = 0;
        }
        if(*str != '\0' && flag == 0 && index == 1){
            temp_str = str; //第二次出现非分隔符的位置 存在temp_str中
            return res;
        }
    }
    temp_str = str;
    return res;
}

//===================test=======================================

void test_strlen()
{
    require(strlen("") == 0);
    require(strlen("hello") == 5);
    require(strlen("welcome") == 7);
    require(strlen("chocolate") == 9);
    require(strlen("october") == 7);
}
void test_strcpy(){
    char dest[20];
    require(strcmp(strcpy(dest, "algorithm"),"algorithm") == 0);
    require(strcmp(strcpy(dest, "holiday"), "holiday")==0);
    require(strcmp(strcpy(dest, "tomato"), "tomato")==0);
}

void test_strcat(){
    char dest_a[20] = "hello ";
    require(strcmp(strcat(dest_a, "world"), "hello world")==0);
    char dest_b[20] = "egg";
    require(strcmp(strcat(dest_b, "plant"), "eggplant")==0);
    char dest_c[20] = "spider";
    require(strcmp(strcat(dest_c, " man"), "spider man")==0);
    
}

void test_strcmp()
{
    const char *r = "hello", *s = "hello", *t = "he";
    require(strcmp(r,s) == 0);
    require(strcmp(t,r) < 0);
    require(strcmp(s,t) > 0);
    
    const char *fir = "prim", *sec = "amazon", *thir = "prim";
    require(strcmp(fir,sec) > 0);
    require(strcmp(fir,thir) == 0);
    require(strcmp(sec,thir) < 0);
}

void test_strncmp(){
    const char *r = "hello", *s = "helloworld", *t = "he";
    require(strncmp(r,s,3) == 0);
    require(strncmp(t,r,4) < 0);
    require(strncmp(s,t,3) > 0);
    
}

void test_strchr(){
    char str[] = "elevator pitch practice";
    require(strcmp(strchr(str, 'o'), "or pitch practice") == 0);
    require(strcmp(strchr(str, 'p'), "pitch practice") == 0);
    require(strcmp(strchr(str, 't'), "tor pitch practice") == 0);
    
}

void test_strpbrk(){
    char str[] = "university of california, irvine";
    char key[] = "aeiou";
    char * p;
    p = strpbrk (str, key);
    require(strcmp(p, "university of california, irvine") == 0);
    
    p = strpbrk (p+1,key);
    require(strcmp(p, "iversity of california, irvine") == 0);
    
    p = strpbrk (p+1,key);
    require(strcmp(p, "ersity of california, irvine") == 0);

    p = strpbrk (p+1,key);
    require(strcmp(p, "ity of california, irvine") == 0);
}

void test_strstr(){
    require(strcmp(strstr("helloworld", "llo"), "lloworld") == 0);
    require(strcmp(strstr("youaremydestiney", "my"), "mydestiney") == 0);
    require(strcmp(strstr("trader joes", "der"), "der joes") == 0);
}

void test_strspn(){
    //require(strspn("2019abc10jue11", "1234567890") == 4);
    //require(strspn("19961112oyw", "1234567890") == 8);
    //require(strspn("2456ad7e", "1234") == 2);
    require(strspn("19d846afpajfij9499", "1234567890") == 2);
    require(strspn("19846afpajfij9499", "1234567890") == 5);
    require(strspn("198646afpajfij9499", "1234567890") == 6);
}


void test_strtok()
{
    char str[] = "hello@my!name:is David";
    require(strcmp(strtok(str, "@"), "hello") == 0);
    require(strcmp(strtok(NULL, "!"), "my") == 0);
    require(strcmp(strtok(NULL, ":"), "name") == 0);
    require(strcmp(strtok(NULL, " "), "is") == 0);
    require(strcmp(strtok(NULL, " "), "David") == 0);
}


int main()
{
    test_strlen();
    test_strcpy();
    test_strcat();
    test_strcmp();
    test_strncmp();
    test_strchr();
    test_strpbrk();
    test_strstr();
    test_strspn();
    test_strtok();

    return 0;
}

