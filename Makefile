APP = snake

SRC = src
BIN = bin
OBJ = $(BIN)/obj

DIRS = $(BIN)
DIRS += $(OBJ)


CXXFLAGS = -std=c++11
LDLIBS = -lSDL2 -lSDL2_ttf
SOURCES  = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)

$(BIN)/$(APP): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@ $(LDLIBS)

$(OBJECTS): $(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build: $(APP)

clean:
	rm -f $(OBJECTS)
	
$(info $(shell mkdir -p $(DIRS)))