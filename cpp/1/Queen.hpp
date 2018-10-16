#define N 8

class Queen {
    int **desk;
    
    // arrange queens (by row/col)
    void setRow();
    void setCol();
        
    // get free rows/cols
    void freeRows(int[], int[N][2]);
    void freeCols(int[], int[N][2]);
    
    // move functions
    void move(int, int, int, int);
    bool moveRow(int, int, int);
    bool moveCol(int, int, int);
    
    public:
        // constructors
        Queen();
        ~Queen();
        
        // helper functions
        void save();
        void show();
        int argmin(int[]);
        void info();
        
        // main algorithm
        int conflicts(int, int, int); // (ROW, COL, X), queen in (X, COL)
        bool solve(int); // num iterations as parameter
        bool solved(int[N][2]);
        bool attacks(int, int, int, int);// check if queen (x1, y1) attacks (x2, y2)
};
