all:a.out

a.out: main.o gameControl.o gameLogic.o hallways.o hero.o memory.o parseFile.o roomInfo.o
	gcc -std=c99 -Wall main.o gameControl.o gameLogic.o hallways.o hero.o memory.o parseFile.o roomInfo.o -g -lncurses -o a.out

main.o:src/main.c 
	gcc -c -Wall -std=c99 src/main.c -Iinclude

gameControl.o:src/gameControl.c
	gcc -c -Wall -std=c99 src/gameControl.c -Iinclude

gameLogic.o:src/gameLogic.c
	gcc -c -Wall -std=c99 src/gameLogic.c -Iinclude

hallways.o:src/hallways.c
	gcc -c -Wall -std=c99 src/hallways.c -Iinclude

hero.o:src/hero.c
	gcc -c -Wall -std=c99 src/hero.c -Iinclude

memory.o:src/memory.c
	gcc -c -Wall -std=c99 src/memory.c -Iinclude

parseFile.o:src/parseFile.c
	gcc -c -Wall -std=c99 src/parseFile.c -Iinclude 

roomInfo.o:src/roomInfo.c
	gcc -c -Wall -std=c99 src/roomInfo.c -Iinclude

clean:
	rm *.o -f
	rm a.out -f

