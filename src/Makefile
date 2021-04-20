CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c
LFLAGS = $(DFLAG) $(GFLAGS)

all: SumSquaresPipeline SievePipeline DoublePipeline FactorialPipeline SimplePipeline TestPipeline

SumSquaresPipeline: SumSquaresPipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SumSquaresPipeline.o Pipeline.o ListNode.o -o SumSquaresPipeline

SievePipeline: SievePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SievePipeline.o Pipeline.o ListNode.o -o SievePipeline

DoublePipeline: DoublePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) DoublePipeline.o Pipeline.o ListNode.o -o DoublePipeline

FactorialPipeline: FactorialPipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) FactorialPipeline.o Pipeline.o ListNode.o -o FactorialPipeline

SimplePipeline: SimplePipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) SimplePipeline.o Pipeline.o ListNode.o -o SimplePipeline

TestPipeline: TestPipeline.o Pipeline.o ListNode.o
	$(CC) $(LFLAGS) TestPipeline.o Pipeline.o ListNode.o -o TestPipeline


SievePipeline.o: SievePipeline.c
	$(CC) $(CFLAGS) SievePipeline.c

SumSquaresPipeline.o: SumSquaresPipeline.c
	$(CC) $(CFLAGS) SumSquaresPipeline.c

DoublePipeline.o: DoublePipeline.c
	$(CC) $(CFLAGS) DoublePipeline.c

FactorialPipeline.o: FactorialPipeline.c
	$(CC) $(CFLAGS) FactorialPipeline.c

SimplePipeline.o: SimplePipeline.c
	$(CC) $(CFLAGS) SimplePipeline.c

TestPipeline.o: TestPipeline.c
	$(CC) $(CFLAGS) TestPipeline.c



Pipeline.o: Pipeline.c Pipeline.h
	$(CC) $(CFLAGS) Pipeline.c

ListNode.o: ListNode.c ListNode.h
	$(CC) $(CFLAGS) ListNode.c


clean:
	$(RM) SumSquaresPipeline SievePipeline DoublePipeline FactorialPipeline SimplePipeline TestPipeline *.o
