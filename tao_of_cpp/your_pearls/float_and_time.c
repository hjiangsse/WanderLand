#include <stdio.h>
#include <sys/time.h>

typedef void (*PFuncType)(int);

void float_adds(int);
void double_adds(int);

void float_divs(int);
void double_divs(int);
void report_func_exec_time(const char*,PFuncType ,int);

int main() {
    report_func_exec_time("float_adds", float_adds, 10000000);
    report_func_exec_time("double_adds", double_adds, 10000000);

    report_func_exec_time("float_divs", float_divs, 10000000);
    report_func_exec_time("double_divs", double_divs, 10000000);
    return 0;
}

void report_func_exec_time(const char *fname, PFuncType pfunc, int n) {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    (*pfunc)(n);
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("(%d)%s: %f ms.\n", n, fname, elapsedTime);
}

void float_adds(int n) {
    int i;
    float r;
    float left = 342.224;
    float right = 356.222;
    
    for(i = 0; i < n; i++) {
	r = left + right;
    }
}

void float_divs(int n) {
    int i;
    float r;
    float left = 342.224;
    float right = 356.222;
    
    for(i = 0; i < n; i++) {
	r = left / right;
    }
}

void double_adds(int n) {
    int i;
    double r;
    double left = 342.224;
    double right = 356.222;
    
    for(i = 0; i < n; i++) {
	r = left + right;
    }
}

void double_divs(int n) {
    int i;
    double r;
    double left = 342.224;
    double right = 356.222;
    
    for(i = 0; i < n; i++) {
	r = left / right;
    }
}

