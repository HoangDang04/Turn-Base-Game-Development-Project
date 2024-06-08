#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType{PHOENIXDOWN1=10, PHOENIXDOWN2, PHOENIXDOWN3, PHOENIXDOWN4, ANTIDOTE, NONE};
enum KnightType { PALADIN = 0, LANCELOT , DRAGON , NORMAL };
class Events;
class BaseKnight;
class ArmyKnights;
class BaseItem;
class BaseBag;
class BaseOpponent;
class KnightAdeventure;

class BaseItem {
public:
    ItemType value;
    BaseItem *next;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    ~BaseItem();
};
class Antidote: public BaseItem
{
    public:
    Antidote();
    virtual bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownI: public BaseItem
{
    public:
    PhoenixDownI();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownII: public BaseItem
{
    public:
    PhoenixDownII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIII: public BaseItem
{
    public:
    PhoenixDownIII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIV: public BaseItem
{
    public:
    PhoenixDownIV();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class BaseBag {
    private:
    int capacity;
    int initial_capacity;
    public:
    BaseItem *head=NULL;
    BaseBag(BaseKnight *knight, int a, int b);
    void setCapacity(int capacity){this->capacity=capacity;}
    int getCapacity(){return capacity;}
    void setInitialCapacity(int initial_capacity){this->initial_capacity=initial_capacity;}
    int getInitialCapacity(){return initial_capacity;}
    virtual bool insertFirst(BaseItem * item);
    virtual int scanPhoenixDown(ItemType itemType);
    virtual ItemType searchPhoenixDown();
    virtual BaseItem * get(ItemType itemType);
    virtual void update(ItemType itemType);
    virtual string toString() const;
    ~BaseBag();
};
class Events {
public:
	Events(const string & file_events);
    int count() const;
    int get(int i) const;
	~Events();    
	int num_event;
	int *list_event;
};

class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    BaseKnight *getLastKnight(){return lastManStanding;}
    void setLastKnight(BaseKnight *lastManStanding){this->lastManStanding=lastManStanding;}

    BaseKnight **getKnightStats(){return knight_stats;}
    void setKnightStats(BaseKnight **knight_stats){this->knight_stats=knight_stats;}
    bool getOmegaWeaponLOL(){return OmegaWeaponLOL;}
    void setOmegaWeaponLOL(bool OmegaWeaponLOL){this->OmegaWeaponLOL=OmegaWeaponLOL;}
    int getNumKnights(){return num_knights;}
    void setNumKnights(int num_knights){this->num_knights=num_knights;}
    bool getSkip(){return Skip;}

    void setShield(bool Shield){this->Shield=Shield;}
    void setSpear(bool Spear){this->Spear=Spear;}
    void setHair(bool Hair){this->Hair=Hair;}
    void setSword(bool Sword){this->Sword=Sword;}
    void setBool(bool Skip){this->Skip=Skip;}

    bool hasPaladinShield() const{return Shield;}
    bool hasLancelotSpear() const{return Spear;}
    bool hasGuinevereHair() const{return Hair;}
    bool hasExcaliburSword() const{return Sword;}

    bool usePhoenixdown2(BaseKnight *knight);
    bool usePhoenixdown3(BaseKnight *knight);
    bool usePhoenixdown4(BaseKnight *knight);
    void printInfo() const;
    void printResult(bool win) const;
protected:
	bool theRealExcalibur = false;
    bool findNormal=false;
    int num_knights;
    int count2;
    int fakecount;
    BaseKnight** knight_stats;
    BaseKnight* lastManStanding;
    bool Haters = false;
    bool OmegaWeaponLOL = false;
    bool Shield = false;
    bool Spear = false;
    bool Hair = false;
    bool Sword = false;
    bool Skip = false;
};
class BaseOpponent
{
    public:
    virtual void fight(int i, BaseKnight *knight)=0;
    virtual void attack(int i, BaseKnight *knight)=0;
    virtual void reward(BaseKnight* knight)=0;
};
class MadBear: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class Bandit: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class LordLupin: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class Elf: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class Troll: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class TornBerry: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class QueenOfCards: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight* knight);
};
class NinaTheRings: public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight *knight);
};
class DurianGarden : public BaseOpponent
{
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight *knight);
};
class OmegaWeapon : public BaseOpponent
{
    bool OmegaLUL;
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight *knight);
    bool getOmegaLUL(){return OmegaLUL;}
};
class Hades : public BaseOpponent
{
    bool death;
    public:
    void fight(int i, BaseKnight *knight);
    void attack(int i, BaseKnight *knight);
    void reward(BaseKnight *knight);
    bool getDeath(){return death;}
};
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;
public:
    BaseKnight();
    ~BaseKnight();
    int getHP(){return hp;}  void setHP(int hp){this->hp=hp;}
    int getID(){return id;} void setID(int ID){this->id=id;}
    int getMaxHP(){return maxhp;} void setMaxHP(int maxhp){this->maxhp=maxhp;}
    int getLevel(){return level;} void setLevel(int level){this->level=level;}
    int getGil(){return gil;} void setGil(int gil){this->gil=gil;}
    int getAntidote(){return antidote;} void setAntidote(int Antidote){this->antidote=antidote;}
    int getPhoenixDownI(){return phoenixdownI;}
    BaseBag *getBag(){return bag;} void setBag(BaseBag *bag){this->bag=bag;}
    KnightType getKnightType(){return knightType;}
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class KnightPaladin : public BaseKnight
{
    public:
    KnightPaladin(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class KnightLancelot: public BaseKnight
{
    public:
    KnightLancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class KnightDragon: public BaseKnight
{
    public:
    KnightDragon(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class KnightNormal: public BaseKnight
{
    public:
    KnightNormal(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__
