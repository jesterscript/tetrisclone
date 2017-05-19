#ifndef SHAPER_H
#define SHAPER_H
#include "Boarder.h"
#include "Helpers.h"
#include <algorithm>


class Shape
{
public:
    std::pair<int, int> findRotatePoint(std::vector<std::pair<int, int>> v) {
    int x = 0, y = 0;
    for(int i = 0; i < v.size(); ++i) {
        x += v[i].first;
        y += v[i].second;
    }
    return std::make_pair(x / v.size(), y / v.size());
}
    Shape(int TYPE)
    {
        _boost = true;
       type = TYPE;
       tb = TetrisBoard::getInstance();
       createPart();
    }
    std::vector<std::pair<int,int> > parts;
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
       for(int i = 0 ; i < parts.size() ; ++i)
        {
            tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
        }
    }

    void movePartDown()
    {   
            if(!pathIsClear())
                return;

            for(int i = 0 ; i < parts.size() ;++i)
            {

                tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
                parts[i].second +=1;

            }
            for(int i = 0 ; i < parts.size() ; ++i)
            {
                tb->tableAsNumbers[parts[i].first][parts[i].second] = type;

            }
    }

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
void rotatePartRight()
{   for (int i = 0; i < parts.size(); ++i) {
        tb->tableAsNumbers[parts[i].first][parts[i].second] = 0;
    }
    std::pair<int, int> rotatePoint = findRotatePoint(parts);
    for (int i = 0; i < parts.size(); ++i) {
        int first = parts[i].first;
        parts[i].first = -(parts[i].second - rotatePoint.second) + rotatePoint.first;
        parts[i].second = first - rotatePoint.first + rotatePoint.second;
    }
    for (int i = 0; i < parts.size(); ++i) {
        tb->tableAsNumbers[parts[i].first][parts[i].second] = type;
    }

}
bool pathIsClear()
{
    bool answer = true;
    for(int i = 0 ; i < parts.size();++i)
    {
        if((tb->tableAsNumbers[parts[i].first][parts[i].second + 1] != 0 && !ContainsIntPair(parts,parts[i].first,parts[i].second + 1)) || !(parts[i].second + 1 < 20))
        {
            answer = false;
            break;
        }
		else if(tb->tableAsNumbers[parts[i].first][parts[i].second + 1] == 0 && parts[i].second + 1 < 20 )
        {
            answer = true;
        }



    }
    return answer;
}
bool horizontalPathIsClear()
{
        bool answer = true;
    for(int i = 0 ; i < parts.size();++i)
    {
        if((tb->tableAsNumbers[parts[i].first - 1][parts[i].second] != 0 && !ContainsIntPair(parts,parts[i].first - 1,parts[i].second))||
            (tb->tableAsNumbers[parts[i].first + 1][parts[i].second] != 0 && !ContainsIntPair(parts,parts[i].first + 1,parts[i].second)))
        {
            answer = false;
            break;
        }
       

    }
    return answer;
}
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
int getType()
{
    return type;
}
bool hasBoost()
{
    return _boost;
}
void boost()
{
    _boost = false;
}
private:
    TetrisBoard* tb;
    int type;
    bool _boost;

};

#endif // SHAPER_H
