#include <iostream>
using namespace std;

int* createPointer() {
    int localVar = 10;
    int* ptr = &localVar;
    return ptr;
}

int main() {
    int* dynamicPtr = createPointer(); 
    delete dynamicPtr; 
    // Chương trình lỗi khi giải phóng vùng nhớ đã được giải 
    // phóng tự động khi hàm CreatePointer dừng

    return 0;
}