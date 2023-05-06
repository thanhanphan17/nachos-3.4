/*voinuoc program*/
#include "syscall.h"

int main() {
    int n, v1, v2;
    OpenFileId vn, res;
    char c[1];
    Create_File("result.txt");
    res = Open_File("result.txt", 0);
    n = -1;
    v1 = v2 = 0;
    while (1) {
        if (n == 0) break;
        Wait("voinuoc");
        vn = Open_File("voinuoc.txt", 1);
        n = 0;
        while (1) {
            if (Read_File(c, 1, vn) == 0) break;
            if (c[0] >= '0' && c[0] <= '9')
                n = 10 * n + c[0] - '0';
            else
                break;
        }
        Close_File(vn);
        if (n != 0) {
            if (v1 <= v2) {
                v1 += n;
                if (res != -1) Write_File("1 ", 2, res);
            } else {
                v2 += n;
                if (res != -1) Write_File("2 ", 2, res);
            }
        }
        Signal("sinhvien");
    }
    if (res != -1) {
        Write_File("\n", 1, res);
        Close_File(res);
    }
    Exit(0);
}