#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#define THREAD_NUM 30
void *thread_calc() {
	int i, j, k;
	char *p;
	for (i = 0, j = 0; i < 1000000; i++) {
		do { j = i + j; k = ((double)(j + 501) * 3.14); } while (j < i * 100);
		p = (char *)malloc(100);
		sprintf(p, "%d", k);
		free(p);
	}
	return NULL;
}
int main () {
	struct timeval start_time, end_time;
	long long usec;
	int i, j, k;
	char *p;
	FILE *fp;
	char buf[20];
	size_t s;
	pthread_t tids[THREAD_NUM];
	gettimeofday(&start_time, NULL);
	for (i = 0, j = 0; i < 1000000; i++) {
		do { j = i + j; k = ((double)(j + 501) * 3.14); } while (j < i * 100);
		p = (char *)malloc(100);
		sprintf(p, "%d", k);
		free(p);
	}
	gettimeofday(&end_time, NULL);
	usec = ((long long)(end_time.tv_sec - start_time.tv_sec) * 1000000L) +
		(long long)(end_time.tv_usec - start_time.tv_usec);
	printf("CPU time: %lld (usec)\n", usec);
	printf("CPU score: %f\n", 6482716.0 / ((float)usec));

	gettimeofday(&start_time, NULL);
	for (i = 0; i < THREAD_NUM; i++) {
		pthread_create(&(tids[i]), NULL, thread_calc, NULL);
	}
	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(tids[i], NULL);
	}
	gettimeofday(&end_time, NULL);
	usec = ((long long)(end_time.tv_sec - start_time.tv_sec) * 1000000L) +
		(long long)(end_time.tv_usec - start_time.tv_usec);
	printf("Thread CPU time: %lld (usec)\n", usec);
	printf("Thread CPU score: %f\n", 64827160.0 / (float)THREAD_NUM / ((float)usec));	

	gettimeofday(&start_time, NULL);
	for (i = 0, j = 0; i < 100000; i++) {
		fp = fopen("aaa1.dat", "a+");
		fprintf(fp, "north¥n");
		fflush(fp);
		fprintf(fp, "west¥n");
		fflush(fp);
		fclose(fp);
	}
	fp = fopen("aaa1.dat", "a+");
	for (i = 0, j = 0; i < 100000; i++) {
		s = fread(buf, 1, 10, fp);
		sprintf(buf, "%d", (int)s);
	}
	fclose(fp);
	unlink("aaa1.dat");
	gettimeofday(&end_time, NULL);
	usec = ((long long)(end_time.tv_sec - start_time.tv_sec) * 1000000L) +
		(long long)(end_time.tv_usec - start_time.tv_usec);
	printf("Filesystem time: %lld (usec)\n", usec);
	printf("Filesystem score: %f\n", 10000000.0 / ((float)usec));
	return 0;
}
