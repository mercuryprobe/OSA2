q1: threadScheduling.out processScheduling.out

threadScheduling.out: threadScheduling.c
	gcc threadScheduling.c -o threadScheduling.out

processScheduling.out: processScheduling.c
	gcc processScheduling.c -o processScheduling.out