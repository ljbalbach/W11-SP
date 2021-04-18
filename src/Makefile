CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c
LFLAGS = $(DFLAG) $(GFLAGS)

all: SumSquaresPipeline SievePipeline DoublePipeline SimplePipeline

SumSquaresPipeline: SumSquaresPipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SumSquaresPipeline.o Pipeline.o ListNode.o -o SumSquaresPipeline

SievePipeline: SievePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SievePipeline.o Pipeline.o ListNode.o -o SievePipeline

DoublePipeline: DoublePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) DoublePipeline.o Pipeline.o ListNode.o -o DoublePipeline

SimplePipeline: SimplePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SimplePipeline.o Pipeline.o ListNode.o -o SimplePipeline


SievePipeline.o: SievePipeline.c
	$(CC) $(CFLAGS) SievePipeline.c

SumSquaresPipeline.o: SumSquaresPipeline.c
	$(CC) $(CFLAGS) SumSquaresPipeline.c

DoublePipeline.o: DoublePipeline.c
	$(CC) $(CFLAGS) DoublePipeline.c

SimplePipeline.o: SimplePipeline.c
	$(CC) $(CFLAGS) SimplePipeline.c



Pipeline.o: Pipeline.c Pipeline.h
	$(CC) $(CFLAGS) Pipeline.c

ListNode.o: ListNode.c ListNode.h
	$(CC) $(CFLAGS) ListNode.c


clean:
	$(RM) SumSquaresPipeline SievePipeline DoublePipeline SimplePipeline *.o
