GPP = g++
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
EXEC= main
FLAG = -Wall -Wextra -Wpointer-arith -Wcast-qual -Wcast-align

%.o :%.cpp
	$(GPP) $(FLAG) -o $@ -c $< 

main : $(OBJ) 
	$(GPP) $(FLAG) -o $@ $^

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
