bool fieldIsValid(struct square** field, int sizeX, int sizeY);
void printField(struct square** field, int sizeX, int sizeY);
bool solve(struct square** field, int sizeX, int sizeY);

struct square {
    int shapeID;
    int value;
} ;