#include <stdio.h>
#include <errno.h>
#include <string.h>

// gcc fread_fwrite_mycp.c -o mycopy

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s src_file dst_file\n", argv[0]);
        return -1;
    }
    int ec = 0;
    char buf[256];
    int rlen = 0;
    int wlen = 0;
    int offset = 0;
    int remain = 0;
    FILE *rfp = NULL;
    FILE *wfp = NULL;
    rfp = fopen(argv[1], "r");
    if (NULL == rfp) {
        fprintf(stderr, "fopen [%s] err, errno = [%d][%s]\n", 
            argv[1], errno, strerror(errno));
        goto cleanup;
    }

    wfp = fopen(argv[2], "w");
    if (NULL == wfp) {
        fprintf(stderr, "fopen [%s] err, errno = [%d][%s]\n", 
            argv[2], errno, strerror(errno));
        goto cleanup;
    }

    while (1) {
        rlen = fread(buf, 1, sizeof(buf), rfp);
        if (0 == rlen) {
            if (feof(rfp) != 0) {
                // 读到文件末尾
                goto cleanup;
            } else {
                ec = ferror(rfp);
                if (ec != 0) {
                    fprintf(stderr, "fgetc err, ec = [%d][%s]\n", 
                        ec, strerror(ec));
                }
                goto cleanup;
            }
        }
        offset = 0;
        remain = rlen;
        while (remain != 0) {
            wlen = fwrite(buf + offset, 1, remain, wfp);
            if (0 == wlen) {
                ec = ferror(wfp);
                fprintf(stderr, "fputc err, ec = [%d][%s]\n", 
                    ec, strerror(ec));
                goto cleanup;
            }
            offset += wlen;
            remain -= wlen;
        }
    }
cleanup:
    if (rfp) {
        fclose(rfp);
    }
    if (wfp) {
        fclose(wfp);
    }
    return 0;
}