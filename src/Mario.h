#ifndef MARIO_H
#define MARIO_H
class Mario : public Champion
{
public:
    //  idea is putting all the move method here seems stupid , cos why the move function then to kill redundancy ?
    // so somehow we put the move function correctly and just +2 in every single direction but only one time
    // and we remove the getting damage line or something and  we make him not see obstacles aslan fa msh far2a m3ah
    // haye3mel eih

    void useAbility(char c);
};

#endif