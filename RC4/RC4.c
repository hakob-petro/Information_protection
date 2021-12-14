/*
    robin verton, dec 2015
    implementation of the RC4 algo
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

#define N 256   // 2^8

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                    group_fd, flags);
    return ret;
}

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(char *key, unsigned char *S) {

    int len = strlen(key);
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }

    return 0;
}

int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];

    }

    return 0;
}

int RC4(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, ciphertext);

    return 0;
}

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Usage: %s <key> <plaintext>", argv[0]);
        return -1;
    }

    struct perf_event_attr pe;
    long long count;
    int fd;

    unsigned char *ciphertext = malloc(sizeof(int) * strlen(argv[2]));

    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = PERF_COUNT_HW_INSTRUCTIONS;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    // Don't count hypervisor events.
    pe.exclude_hv = 1;

    fd = perf_event_open(&pe, 0, -1, -1, 0);
    if (fd == -1) {
        fprintf(stderr, "Error opening leader %llx\n", pe.config);
        exit(EXIT_FAILURE);
    }

    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

    RC4(argv[1], argv[2], ciphertext);

    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    read(fd, &count, sizeof(long long));

    for(size_t i = 0, len = strlen(argv[2]); i < len; i++)
        printf("%02hhX", ciphertext[i]);

    printf("\nUsed %lld instructions\n", count);
    close(fd);

    return 0;
}