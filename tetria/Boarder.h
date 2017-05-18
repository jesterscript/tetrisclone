#ifndef BOARDER_H
#define BOARDER_H
#include "Helpers.h"
class TetrisBoard //main board class with singleton pattern.
{
public:
    static int tableAsNumbers [30][20];
    static TetrisBoard* getInstance()
    {
        if(instance == NULL)
          instance = new TetrisBoard();
        return instance;
    }
    int riis(int i)
    {
        for(int k = 0 ; k < 10 ; k++)
        {
           this->tableAsNumbers[k][i] = 0;
		}
        for(int j = i - 1 ; j >= 0 ; --j)
			 for(int k = 0 ; k < 10 ; k++)
				 {
					this->tableAsNumbers[k][j+1] = this->tableAsNumbers[k][j];
					this->tableAsNumbers[k][j] = 0;
				}


		return 1;
    }

private:
    static TetrisBoard* instance;
    TetrisBoard()
    {


    }
    std::vector<sf::Shape*> pieces;


};
#endif // BOARDER_H
