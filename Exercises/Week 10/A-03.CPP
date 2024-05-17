Hãy chạy chương trình thử nghiệm đoạn lệnh sau.Chạy thử và cho biết lệnh in cerr nào không chạy như mong muốn. Đó là vì lỗi gì? (cerr là để báo lỗi ra màn hình, nó tương tự như cout nhưng khác với cout ở chỗ cerr sẽ in ngay lập tức, còn cout có thể trễ và có thể mất phần cuối nếu chương trình crash trước khi nó kịp in )
char* a = new char[10];
char* c = a + 3;
for (int i = 0; i < 9; i++) a[i] = 'a'; 
a[9] = '\0';
cerr <<"a: " << "-" << a << "-" << endl;
cerr <<"c: " << "-" << c << "-" << endl;
delete c;
cerr << "a after deleting c:" << "-" << a << "-" << endl;

Lệnh cerr thứ 3 sẽ chạy không như ý, vì lệnh delete c đã giải phòng vùng nhớ
mà c trỏ vào, khi truy cập vào đây thông qua con trỏ a sẽ gây lỗi, chương trình
có thể họa động sai cách
