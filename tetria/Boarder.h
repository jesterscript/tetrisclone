/*!
 *\brief The class which represents a tetrisboard.
 *\details Game logic is built over this class.2D int array contains numbers which represent current game screen.
 * According to those numbers , those values are rendered as squares in Game class.
 * This class is implemented with Singleton pattern.
 */


#ifndef BOARDER_H
#define BOARDER_H
#include "Helpers.h"
class TetrisBoard //main board class with singleton pattern.
{
public:
    static int tableAsNumbers [30][20]; //!< 2D arrey which represents the screen.In fact,the TetrisBoard covers only [10][20] but this array is extended for displaying upcoming pieces.
 
    /*!\brief Returns unique instance of the class.
    *\details Singleton implementation.
    */
    static TetrisBoard* getInstance()
    {
        if(instance == NULL)
          instance = new TetrisBoard();
        return instance;
    }
    /*!\brief Takes a parameter as row index whic is full and ready to be destroyed.Then destroys the line and make all the parts above fall.
    */
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
    static TetrisBoard* instance; //!< Unique PiecePusher instance.
     /*!\brief Private constructor.
     */
    TetrisBoard(){};
    


};
#endif // BOARDER_H
