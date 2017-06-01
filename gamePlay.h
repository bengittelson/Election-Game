typedef struct {
	int y;
	int x;
	int width;
	int height;
	//int size;
	unsigned short color;
} RECTANGLE;

typedef struct {
	unsigned int y;
	unsigned int x;
	int width;
	int height;

	//change from constant if necessary?
	const u16* image;
} PLAYER;

//--------------FUNCTION Prototypes--------------
void moveObj(unsigned int* x, unsigned int* y, int height, int width, u16 backgroundColor);
int collision(RECTANGLE* rect1, RECTANGLE* rect2);
int detectCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
