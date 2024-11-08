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

//tiến trình 2, đọc mảng từ tiến trình 1, xử lý mảng và gửi lại kết quả cho tiến trình 1
int main() {
    int arr[5], sum = 0;
    int fd = open("sum", O_RDONLY);
    if(fd == -1) return 1;

    for(int i = 0; i < 5; ++i) {
        if(read(fd, &arr[i], sizeof(int)) == -1) {
            return 2;
        }
        printf("Received %d\n", arr[i]);
        sum += arr[i];
    }
    printf("Sum = %d\n", sum);
    close(fd);

    fd = open("sum", O_WRONLY);
    if(fd == -1) return 1;

    if(write(fd, &sum, sizeof(int)) == -1) return 2;
    printf("Sum writen\n");
    close(fd);
    return 0;
}
