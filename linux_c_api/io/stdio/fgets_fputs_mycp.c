#include <stdio.h>
#include <errno.h>
#include <string.h>

// gcc fgetc_fputc_mycp.c -o fgets_fputs_mycp

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s src_file dst_file\n", argv[0]);
        return -1;
    }
    int ec = 0;
    int ch = 0;
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
            argv[2], ec, strerror(ec));
        goto cleanup;
    }

    while (1) {
        ch = fgetc(rfp);
        if (EOF == ch) {
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
        if (EOF == fputc(ch, wfp)) {
            ec = ferror(rfp);
            fprintf(stderr, "fputc err, ec = [%d][%s]\n", 
                ec, strerror(ec));
            goto cleanup;
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