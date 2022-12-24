#ifndef LUIGI_H
#define LUIGI_H
class Luigi : public Champion
{

    // idea :  in whatever direction luigi moves we clean
    //  the hypothetical place he was gonna move into ,that way we preserve the obstacles that are before him
    //  if the ability was called, by cleaning I mean we just replace everything by dots or whatever the symbol of tile is
    // defensive programming for luigi not to "clean himself" off the "lain" or not to clean mario as well so no cleaning
    //  champions , also cleaning will save the point object thingies but remove obstacles
    //  and we need to define what is front , I am guessing whateever last move he makes is the front so if he moved right
    //  then the whole right direction will be clean
    // IF luigi is somewhere and he moved in the another somewhere direction
    //  useABility()
    //  and we can use ability while in spawn as well and probably he will spawn somewhere else
    //  and mario will be the original champion
public:
    void useAbility()
    {
        cout << "Luigi Ability is called" << endl;

        for (int i = 0; i < 10; i++)
        {
            if (board[luigi->getX()][i].getType() == 'O ')
            {
                board[luigi->getX()][i] = '. ';
            }
        }
        for (int j = 0; j < 10; j++)
        {
            if (board[j][luigi->getX()].getType() == 'O ')
            {
                board[j][luigi->getY()] = '. ';
            }
        }
    }
};
#endif