#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<wait.h>

#include<bits/stdc++.h>
using namespace std;


//tiến trình 1, khởi tạo mảng, ghi mảng vào pipe và nhờ tiến trình 2 xử lý, đọc kết quả được xử lý từ tiến trình 2
int main() {
    mkfifo("sum", 0777);
    //khai báo, khởi tạo phần tử của mảng với công thức i^3
    int arr[5];
    for(int i = 0; i < 5; ++i) {
        arr[i] = i * i * i;
    }
 
    //mở pipe ở chế độ chỉ ghi
    int fd = open("sum", O_WRONLY);
    if(fd == -1) return 1;

    //ghi mảng vào file descriptor chứa pipe
    for(int i = 0; i < 5; ++i) {
        if(write(fd, &arr[i], sizeof(int)) == -1) {
            return 2;
        }
        printf("Wrote %d\n", arr[i]);
    }
    close(fd); //đóng file descriptor, tránh rò rỉ tài nguyên

    //mở pipe ở chế độ chỉ đọc
    fd = open("sum", O_RDONLY);
    if(fd == -1) return 1;

    int sum;
    //đọc từ file, ghi vào biến sum
    if(read(fd, &sum, sizeof(int)) == -1) return 2;

    printf("Sum calculated by another process = %d\n", sum);
    close(fd); //đóng file
    return 0;
}
