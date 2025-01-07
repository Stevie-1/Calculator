COMMON = DEBUG.h EXPRESSION_LENGTH.h Status.h

OBJS = ArrayStack/Stack.o CalculatorPackage/CalculatorPackage.o FileStream/FileStream.o main.o



Calculator1:$(OBJS)
	gcc $(OBJS) -o Calculator1

main.o:main.c CalculatorPackage/CalculatorPackage.h FileStream/FileStream.h
	gcc -c main.c -o main.o 

FileStream/FileStream.o:FileStream/FileStream.c FileStream/FileStream.h $(COMMON)
	gcc -c FileStream/FileStream.c -o FileStream/FileStream.o 

CalculatorPackage/CalculatorPackage.o:CalculatorPackage/CalculatorPackage.c CalculatorPackage/CalculatorPackage.h ArrayStack/Stack.h
	gcc -c CalculatorPackage/CalculatorPackage.c -o CalculatorPackage/CalculatorPackage.o 

ArrayStack/Stack.o:ArrayStack/Stack.c ArrayStack/Stack.h $(COMMON)
	gcc -c ArrayStack/Stack.c -o ArrayStack/Stack.o 

.PHONY:clean
clean:
	del CalculatorPackage\CalculatorPackage.o
	del ArrayStack\Stack.o
	del FileStream\FileStream.o 	
	del main.o Calculator1.exe