/*!
 *\brief This class defines Shape objects which are made of 2D coordinates.
 *\details Every Shape object has unique type which defines their color and actual shape. (T,I,O,S,Z,L etc.)
 * These coordinates represent the position(row,column) of the shape.
 * in the TetrisBoard.
 * Shapes assign their type into those indexes so assigned numbers seem as shapes in the matrix.Therefore
 * when TetrisBoard values are rendered , indexes become squares and together a shape.
 */

#ifndef SHAPER_H
#define SHAPER_H
#include "Boarder.h"
#include "Helpers.h"
#include <algorithm>


class Shape
{
public:
    /*!\brief In game mechanics players are able to rotate shapes to fit them into patterns.
     *\details findRotatePoint() calculates rotating point of the shape according to its indexes.
     * This calculation is used in rotatePartLeft() and rotatePartRight().
    */
    std::pair<int, int> findRotatePoint(std::vector<std::pair<int, int>> v) 
    {
    int x = 0, y = 0;
    for(int i = 0; i < v.size(); ++i) {
        x += v[i].first;
        y += v[i].second;
    }
    return std::make_pair(x / v.size(), y / v.size());
    }
    /*!\brief Constructor of a Shape.Takes int value as a parameter.
     *\details According to parameter type , a Shape gets created into the TetrisBoard.
     * Contains createPart() method.
    */
    Shape(int TYPE)
    {
        //Initializing variables.
       _boost = true;
       type = TYPE;
       tb = TetrisBoard::getInstance();
       createPart();
    }
    std::vector<std::pair<int,int> > parts;//!< Vector of pairs which represent Shape's coordinates (parts as squares).A Shape consists of 4 parts.
    
    /*!\brief Creates a Shape into the TetrisBoard.
     *\details According to 'type' variable ,initial coordinates (where Shape is spawned first) of Shape's parts created.
     *Into those indexes(coordinates) type variable is assigned.Therefore,in rendering phase
     * a shape is created.
    */
    void createPart()
    {
        switch(type)
        {
            case 1: //O Shape
                {
                    std::pair<int,int> tP;
                    tP = std::make_pair(5,1);
                    parts.push_back(tP);
                    tP = std::make_pair(4,1);
                    parts.push_back(tP);
                    tP = std::make_pair(4,0);
                    parts.push_back(tP);
                    tP = std::make_pair(5,0);
                    parts.push_back(tP);
                    std::cout << "square created " << std::endl;
                    break;
                }
            case 2: //T Shape
                {
                    std::pair<int,int> tp;
                    tp = std::make_pair(4,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,0);
                    parts.push_back(tp);
                    tp = std::make_pair(6,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,1);
                    parts.push_back(tp);
                    break;

                }
            case 3: // I SHAPE
                {
                    std::pair<int,int> tp;
                    tp = std::make_pair(4,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,0);
                    parts.push_back(tp);
                    tp = std::make_pair(6,0);
                    parts.push_back(tp);
                    tp = std::make_pair(7,0);
                    parts.push_back(tp);
                    break;

                }
            case 4: // J SHAPE
                {
                    std::pair<int,int> tp;
                    tp = std::make_pair(4,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,0);
                    parts.push_back(tp);
                    tp = std::make_pair(6,0);
                    parts.push_back(tp);
                    tp = std::make_pair(6,1);
                    parts.push_back(tp);
                    break;

                }
            case 5: //S SHAPE
                {
                    std::pair<int,int> tp;
                    tp = std::make_pair(5,0);
                    parts.push_back(tp);
                    tp = std::make_pair(6,0);
                    parts.push_back(tp);
                    tp = std::make_pair(4,1);
                    parts.push_back(tp);
                    tp = std::make_pair(5,1);
                    parts.push_back(tp);
                    break;

                }
            case 6: // Z SHAPE
                {
                    std::pair<int,int> tp;
                    tp = std::make_pair(4,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,0);
                    parts.push_back(tp);
                    tp = std::make_pair(5,1);
                    parts.push_back(tp);
                    tp = std::make_pair(6,1);
                    parts.push_back(tp);
                    break;
                }



        }
       //Assign type into the TetrisBoard.
       for(int i = 0 ; i < parts.size() ; ++i)
        {
            tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
        }
    }

    /*!\brief If the Shape is not blocked, then moves the part vertically to bottom.
     *\details For rendering phase , before every movement last position of parts is erased.
     * This method used in Game class  in checkBlasts() and checkInputs().
    */
    void movePartDown()
    {   
            if(!pathIsClear())
                return;

            for(int i = 0 ; i < parts.size() ;++i) // Clear current positions.
            {

                tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
                parts[i].second +=1;

            }
            for(int i = 0 ; i < parts.size() ; ++i) // Redraw.
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = type;

            }
    }
    /*!\brief If the Shape is not blocked horizontally, then moves the part horizontally to the right.
     *\details For rendering phase , before every movement last position of parts is erased.
     * This method used in Game class  in checkInputs().
    */
    void movePartRight()
    {

		if (!atHorizontalBordersRight() || !horizontalPathIsClear())
			return;

            for(int i = 0 ; i < parts.size() ;++i)
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;

                parts[i].first +=1;

            }
            for(int i = 0 ; i < parts.size() ;++i)
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
            }
    }
     /*!\brief If the Shape is not blocked horizontally, then moves the part horizontally to the left.
     *\details For rendering phase , before every movement last position of parts is erased.
     * This method used in Game class  in checkInputs().
    */
    void movePartLeft()
    {
			if (!atHorizontalBordersLeft() || !horizontalPathIsClear())
				return;
            for(int i = 0 ; i < parts.size() ;++i)
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
                parts[i].first -=1;

            }
            for(int i = 0 ; i < parts.size() ;++i)
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
            }
    }
     /*!\brief This method rotates the part 90 degrees left.
     *\details Previously mentioned findRotatePoint() method used here.
     * This method is general for all types of Shapes so it can deviate by going to the up.
     * Therefore , movePartDown() method is used to achieve some balance.
    */
void rotatePartLeft()
{
    for (int i = 0; i < parts.size(); ++i) {
        tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
    }
    std::pair<int, int> rotatePoint = findRotatePoint(parts);
	for (int i = 0; i < parts.size(); ++i) {
		int first = parts[i].first;
		parts[i].first = parts[i].second - rotatePoint.second + rotatePoint.first;
        parts[i].second = -(first - rotatePoint.first) + rotatePoint.second;
    }
    for (int i = 0; i < parts.size(); ++i) {
        tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
    }
    movePartDown();


}
     /*!\brief This method rotates the part 90 degrees right.
     *\details Previously mentioned findRotatePoint() method used here.
     */
void rotatePartRight()
{  
   
    for (int i = 0; i < parts.size(); ++i) {// Clear current positions.
        tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
    }
    std::pair<int, int> rotatePoint = findRotatePoint(parts); //Find rotation point
    for (int i = 0; i < parts.size(); ++i) { //Then generate new position.
        int first = parts[i].first;
        parts[i].first = -(parts[i].second - rotatePoint.second) + rotatePoint.first;
        parts[i].second = first - rotatePoint.first + rotatePoint.second;
    }
    for (int i = 0; i < parts.size(); ++i) { //Redraw
        tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
    }

}
     /*!\brief This method is used to check if vertically path is not blocked by another Shape or the Frame border.
     *\details If down below is empty for all coordinates and the Shape still not next to the Frame borders.Then path is clear.
     *ContainsIntPair() method from Helpers.h used here.
     */
bool pathIsClear()
{
    bool answer = true;
    for(int i = 0 ; i < parts.size();++i)
    {
        //If there is a part of a Shape down below and that part does not belongs the current part.Then path is not clear.
        if((tb->tableAsNumbers[parts[i].first][parts[i].second + 1] != 0 && !ContainsIntPair(parts,parts[i].first,parts[i].second + 1)) || !(parts[i].second + 1 < 20))
        {
            answer = false;
            break;
        }
        //If down below is empty for all coordinates and the Shape still not next to down border of the frame.Then path is clear.
		else if(tb->tableAsNumbers[parts[i].first][parts[i].second + 1] == 0 && parts[i].second + 1 < 20 )
        {
            answer = true;
        }

    }
    return answer;
}
     /*!\brief This method is used to check if vertically path is not blocked by another Shape.
     *\details If there is a Shape at the left/right side of the current Shape,then horizontal path is not clear.
     * ContainsIntPair() method from Helpers.h used here.
     */
bool horizontalPathIsClear()
{
        bool answer = true;
    for(int i = 0 ; i < parts.size();++i)
    {
        //If there is a Shape at the left/right side of the current Shape,then horizontal path is not clear.
        if((tb->tableAsNumbers[parts[i].first - 1][parts[i].second] != 0 && !ContainsIntPair(parts,parts[i].first - 1,parts[i].second))||
            (tb->tableAsNumbers[parts[i].first + 1][parts[i].second] != 0 && !ContainsIntPair(parts,parts[i].first + 1,parts[i].second)))
        {
            answer = false;
            break;
        }
       

    }
    return answer;
}
     /*!\brief This method is used to check if vertically path is not blocked by left border of the frame..
     *\details ContainsIntPair() method from Helpers.h used here.
     */
bool atHorizontalBordersLeft()
{
	bool answer = true;
	for (int i = 0; i < parts.size(); i++)
	{
		
		if ((parts[i].first - 1 < 0) && !ContainsIntPair(parts, parts[i].first - 1, parts[i].second))
		{
			answer = false;
			break;
		}
		
	}
	return answer;
}
     /*!\brief This method is used to check if vertically path is not blocked by right border of the frame..
     *\details ContainsIntPair() method from Helpers.h used here.
     */
bool atHorizontalBordersRight()
{
	bool answer = true;
	for (int i = 0; i < parts.size(); i++)
	{
		if ((parts[i].first + 1 > 9) && !ContainsIntPair(parts, parts[i].first + 1, parts[i].second))
		{
			answer = false;
			break;
		}
	}
	return answer;
}
/*!\brief Accessor for 'type' variable.
*/
int getType()
{
    return type;
}
/*!\brief Accessor for '_boost' variable.
*/
bool hasBoost()
{
    return _boost;
}
/*!\brief Makes a Shape use ability to wait for a shorttime after it touches the ground.
*/
void boost()
{
    _boost = false;
}
private:
    TetrisBoard* tb; //!< A pointer to the unique TetrisBoard instance.
    int type; //!< Type of a Shape.
    bool _boost; //!< Ability to wait for a shorttime after it touches the ground.

};

#endif // SHAPER_H
