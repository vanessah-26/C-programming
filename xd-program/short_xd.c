#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BS     16
#define st     ssize_t
#define c      char
#define P(...) printf(__VA_ARGS__)
void pa(c *b, int s, int i) {
    P("%08x: ", i);
    for (int j = 0; j < s; j++)
        P("%02x%s", (unsigned c) b[j],
            (j + 1) % 4 == 0 && j + 1 != s ? " "
            : (j + 1) % 2 == 0             ? " "
                                           : "");
    for (int j = s; j < BS; j++)
        P("  %s", (j + 1) % 2 == 0 ? " " : "");
    P(" ");
    for (int j = 0; j < s; j++)
        P("%c", (b[j] >= 32 && b[j] <= 126) ? b[j] : '.');
    P("\n");
}
int main(int a, c *v[]) {
    int fd, t = 0, i = 0;
    c b[BS];
    st r;
    fd = (a == 1) ? 0 : ((fd = open(v[1], O_RDONLY)) == -1 ? exit(1), 0 : fd);
    while ((r = read(fd, b + t, (size_t) (BS - t))) > 0)
        (t += r) >= BS ? (pa(b, BS, i), i += BS, t = 0) : 0;
    if (t > 0)
        pa(b, t, i);
    close(fd);
    return 0;
}
