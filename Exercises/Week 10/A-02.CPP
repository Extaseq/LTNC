int* p = new int;
int* p2 = p;
*p = 10;
delete p; 
*p2 = 100; // Ghi vào bộ nhớ đã bị xóa
cout << *p2;
delete p2; // Lỗi double delete xóa vùng nhớ tại 1 địa chỉ 2 lần
