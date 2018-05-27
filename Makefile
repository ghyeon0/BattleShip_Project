CC = g++
CFLAGS = -std=c++14
TARGET = battleship
SOURCES = Main.cpp \
		BattleShipApp.cpp \
		BattleShipMap.cpp \
		InputPane.cpp \
		Pane.cpp \
		StatPane.cpp
LDFLAGS = -lncursesw

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf *.o $(TARGET)