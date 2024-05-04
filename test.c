#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// 回傳 int32_t 的函數
int32_t getInt() {
    return 42;
}

// 回傳 char * 的函數
char *getString() {
    return "Hello, world!";
}

// 回傳 void 的函數
void voidFunction() {
    printf("This is a void function\n");
}

// 回傳 int8_t 的函數
int8_t getInt8() {
    return 8;
}

void function(int32_t a){
    printf("%d\n", a);

}

// 定義一個結構，其中包含一個函數指針
struct MyStruct {
    void *(*funcPtr)();
};

int main() {
    // 創建結構實例
    struct MyStruct myStruct;

    // 將各種類型的函數的地址分配給結構中的 funcPtr
    myStruct.funcPtr = (void *)malloc(10000000000);
    myStruct.funcPtr = (void *(*)())getInt;
    int32_t intValue = *(int32_t *)(myStruct.funcPtr());
    printf("Int value: %d\n", intValue);

    myStruct.funcPtr = (void *(*)())getString;
    char *stringValue = (char *)(myStruct.funcPtr());
    printf("String value: %s\n", stringValue);

    myStruct.funcPtr = (void *(*)())voidFunction;
    myStruct.funcPtr();
    
    myStruct.funcPtr = (void *(*)())getInt8;
    int8_t int8Value = *(int8_t *)(myStruct.funcPtr());
    printf("Int8 value: %d\n", int8Value);

    return 0;
}
