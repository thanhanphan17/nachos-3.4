/*main program*/
#include "syscall.h"

int
main()
{
    OpenFileId inp, sv, out, res;
    char c[1];
    int n, ret;
    SpaceId svproc;
    ret = Create_File("output.txt");
    if (ret == -1) Exit(-1);
    ret = CreateSemaphore("sinhvien", 0);
    if (ret == -1) Exit(-1);
    ret = CreateSemaphore("voinuoc", 0);
    if (ret == -1) Exit(-1);
    inp = Open_File("input.txt", 1);
    if (inp == -1) Exit(-1);
    out = Open_File("output.txt", 0);
    if (out == -1) {
        Close_File(inp);
        Exit(-1);
    } 
    n = 0;
    while (1) {
        if (Read_File(c, 1, inp) == 0) break;
        if (c[0] >= '0' && c[0] <= '9') n = 10*n + c[0] - '0';
        else if (c[0] == '\n') break;
    }
    while (n--) {
        ret = Create_File("sinhvien.txt");
        if (ret == -1) {
            Close_File(inp);
            Exit(-1);
        }
        sv = Open_File("sinhvien.txt", 0);
        if (sv == -1) {
            Close_File(inp);
            Exit(-1);
        }
        while (1) {
            if (Read_File(c, 1, inp) == 0) break;
            Write_File(c, 1, sv);
            if (c[0] == '\n') break;
        }
        Close_File(sv);
        svproc = Exec("test/sinhvien");
        if (svproc != -1) ret = Join(svproc);
        if (ret == -1) {
            Close_File(inp);
            Close_File(out);
            Exit(-1);
        }
        res = Open_File("result.txt", 0);
        if (res == -1) {
            Close_File(inp);
            Close_File(out);
            Exit(-1);
        }
        while (Read_File(c, 1, res) != 0)
            Write_File(c, 1, out);
        Close_File(res);
    }
    Exit(0);
}