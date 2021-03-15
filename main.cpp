#include <iostream>
#include <random>
#include <sstream>
#include <thread>
#include <chrono>
//#include "myprofile.h"

using namespace std;

#define DEF_COLS 40
#define DEF_ROWS 25
#define MIN_ROWS 5
#define MAX_ROWS 40
#define CELL_STR "()"

struct ROW{
    unsigned char part[5];
};
class Field{
    const int _cols = DEF_COLS;
    const int _rows;
    ROW* cells;
    ROW* tmp_cells;

public:
    Field(const int& rows = DEF_ROWS)
        : _rows(rows<MIN_ROWS?MIN_ROWS:(rows>MAX_ROWS?MAX_ROWS:rows))
    {
        try {
            cells = new ROW [_rows];
        } catch (...) {
            throw;
        }
        try {
            tmp_cells = new ROW [_rows];
        } catch (...) {
            delete [] cells;
            throw;
        }
        resetTMP();
        xchgCells();
        resetTMP();
        // init first generation
        for(int i = 0;i<_rows;i++){
            tmp_cells[i].part[0] = rand()%256;
            tmp_cells[i].part[1] = rand()%256;
            tmp_cells[i].part[2] = rand()%256;
            tmp_cells[i].part[3] = rand()%256;
            tmp_cells[i].part[4] = rand()%256;
        }

        // end generation
        xchgCells();
    }
    ~Field(){
        delete [] cells;
        delete [] tmp_cells;
    }
    void resetTMP(){
        for(int i = 0;i<_rows;i++){
            tmp_cells[i].part[0] = 0x00;
            tmp_cells[i].part[1] = 0x00;
            tmp_cells[i].part[2] = 0x00;
            tmp_cells[i].part[3] = 0x00;
            tmp_cells[i].part[4] = 0x00;
        }
    }
    void xchgCells(){
        ROW* tmp_cell_ptr;
        tmp_cell_ptr = tmp_cells;
        tmp_cells = cells;
        cells = tmp_cell_ptr;
    }
    void setStatus(int row, int col, const bool Alive){
        if(row < -1 || row > _rows || col < -1 || col > _cols){
            //throw
            return;
        }
        if(row==-1)
            row = _rows-1;
        else if(row==_rows)
            row = 0;
        if(col==-1)
            col = _cols-1;
        else if(col==_cols)
            col = 0;
        unsigned short _tmp = 0x01;
        _tmp <<= col%8;
        if(Alive == true)
            tmp_cells[row].part[col/8] |= _tmp;
        else
            tmp_cells[row].part[col/8] &= ~_tmp;
    }
    bool isAlive(int row, int col){
        if(row < -1 || row > _rows || col < -1 || col > _cols){
            //throw
            return false;
        }
        if(row==-1)
            row = _rows-1;
        else if(row==_rows)
            row = 0;
        if(col==-1)
            col = _cols-1;
        else if(col==_cols)
            col = 0;
        unsigned short _tmp = 0x01;
        _tmp <<= col%8;
        if(cells[row].part[col/8] & _tmp)
            return true;
        else
            return false;
    }
    void getNewField(){
        int _neighbours;
        for(int i = 0;i<_rows;i++){
            for(int j = 0;j<_cols;j++){
                _neighbours = 0;
                if(isAlive(i-1,j-1)){_neighbours++;}
                if(isAlive(i-1,j  )){_neighbours++;}
                if(isAlive(i-1,j+1)){_neighbours++;}
                if(isAlive(i  ,j-1)){_neighbours++;}
                if(isAlive(i  ,j+1)){_neighbours++;}
                if(isAlive(i+1,j-1)){_neighbours++;}
                if(isAlive(i+1,j  )){_neighbours++;}
                if(isAlive(i+1,j+1)){_neighbours++;}

                if(!isAlive(i,j) && _neighbours == 3)
                    setStatus(i,j,true);
                else if(isAlive(i,j) && (_neighbours == 2 || _neighbours == 3))
                    setStatus(i,j,true);
            }
        }
        xchgCells();
        resetTMP();
    }
    void Print(){
        stringstream _str("");
        for(int i = 0;i<_rows;i++){
            for(int j = 0;j<_cols;j++){
                if(isAlive(i,j))
                    _str << CELL_STR;
                else
                    _str << "  ";
            }
        }
        for(int i = 0;i<_cols;i++)
            _str << "--";
        system("cls");
        cout << _str.str();
    }
};

int main()
{
    Field f(25);
    while(true){
        f.Print();
        f.getNewField();
        this_thread::sleep_for(40ms);
    }
    return 0;
}
//----------------------------------------
