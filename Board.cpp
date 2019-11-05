#include "Board.h"

//コンストラクター
Board::Board(){
    const int initdata[BOARD_SIZE][BOARD_SIZE]=
        {{Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside},
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  White,  Black,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Black,  White,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside,  Space,  Space,  Space,  Space,  Space,  Space,  Space,  Space, Outside}, 
         {Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside, Outside}};
    memcpy(board,initdata,sizeof(initdata));
}
Board::~Board(){
}

//表示
void Board::show(){
    /* boardをprintで表示する */
    int r, c; //row,column
    printf("   a b c d e f g h \n");
    printf("  -----------------\n");
    for (r = BOARD_FIRST; r <= BOARD_LAST; r++) {
        printf("%d|", r);		
        for (c = BOARD_FIRST; c <= BOARD_LAST; c++) {
            printf("%1s"," ");
            switch (board[r][c])
            {
            case Black:
                printf("%1s","○");
                break;
            case White:
                printf("%1s","●");
                break;
            default:
                printf("%1s"," ");
                break;
            }   
        }
        printf(" |\n");
    }
    printf("  -----------------\n");

}
//盤面操作
int  Board::count_turn_over(int stone_num,int row,int column,int v_down,int v_right){
    /* 
    一方向について相手の石がどれくらい続いているか数える関数
    引数にあるv_down,v_rightは下方向、右方向をさしており1ならば正の向き-1ならば負の向き0ならば無視を表す
    */
    int next; /* 隣にどれだけ進むか */
    for (next = 1; board[row+next*v_down][column+next*v_right]==opponent(stone_num); next++);//相手の石が続く限りnextを増やす
    //次に来たところが空白もしくはハジでなく自分の石であれば続いた相手の石の数を返す
    if(board[row+next*v_down][column+next*v_right]==stone_num){
        return next-1;
    }else
    {
        return 0;
    }
}
void Board::turn_over(int stone_num,int row,int column){
    /*
    ひっくり返せるところをひっくり返す関数
    8近傍についてv_down,v_rightの(-1,0,1)の組み合わせで(0,0)を除いたものとして確かめていく
    やや複雑な書き方になっているので下のis_legal_actionを見るとやっていることがわかりやすい（同じ挙動）
    */
    int v_down,v_right,count,next;
    for(v_down=NegativeDirection;v_down<=PositiveDirection;v_down++){
        for(v_right=NegativeDirection;v_right<=PositiveDirection;v_right++){
            if(v_down==NonDirection&&v_right==NonDirection) continue;
            count=count_turn_over(stone_num,row,column,v_down,v_right);
            for(next=1;next<=count;next++){
                board[row+next*v_down][column+next*v_right]=stone_num;
            }
        }
    }
    board[row][column]=stone_num;
}
bool Board::is_legal_action(int stone_num,int row,int column){
    /*
    [row][column]がplayerにとって打つことが可能な手か確認する関数
    [row][column]の全方向についてcount_turn_overを実行。
     */
    int v_down,v_right;
    if (board[row][column]==Space){
        for (v_down = NegativeDirection; v_down <= PositiveDirection; v_down++) {
            for (v_right = NegativeDirection; v_right <= PositiveDirection; v_right++) {
                if (count_turn_over(stone_num,row,column,v_down,v_right)) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Board::is_exist_action(int stone_num){
    /* 打つことが可能な手が存在するか確認する。全行列についてis_legal_actionを実行 */
    for (int row = BOARD_FIRST; row <= BOARD_LAST; row++){
        for (int column = BOARD_FIRST; column <= BOARD_LAST; column++){
            if (is_legal_action(stone_num,row,column)) {
                return true;
            }
        }
    }
    return false;
}
//結果の表示
int  Board::calc_result(int stone_num){
    /* playerの石の数の合計を返す */
    int sum = 0;
    for(int i=BOARD_FIRST;i<=BOARD_LAST;i++){
        for(int j=BOARD_FIRST;j<=BOARD_LAST;j++){
            if(board[i][j]==stone_num) {sum+=1;}
        }
    }
    return sum;
}