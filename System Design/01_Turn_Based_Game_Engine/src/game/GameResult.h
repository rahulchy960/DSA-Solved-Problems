class GameResult{
    bool isOver;
    string winner;
    public:
    GameResult(bool flag, string w){
        isOver = flag;
        winner = w;
    }
};