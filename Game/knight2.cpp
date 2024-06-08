#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + this->bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */

//===================================Read Events===============================//

Events::Events(const string & file_events) 
{
    ifstream assign;
    assign.open(file_events);
    assign>>num_event;
    list_event=new int[1000];
    for(int i=0; i<num_event; i++)
    {
        assign>>list_event[i];
    }
    assign.close();
}
int Events::count() const
{
	return num_event;
}
int Events::get(int i) const
{
	return list_event[i];
}
Events::~Events()
{
    delete list_event;
}
//=================================BaseKnight===================================//
//check prime
bool CheckPrime(int hp)
{
    if(hp<2) return false;
    for(int i=2;i<=sqrt(hp);i++){
        if(hp%i==0) return false;
    }
    return true;
}
//Pythagore
bool CheckPythagoras(int hp)
{
    int a=hp/100, b=(hp-a*100)/10, c=hp%10;
    return ((a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a)&&a!=0&&b!=0&&c!=0);
}
BaseKnight::BaseKnight(){}
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
	if(CheckPrime(maxhp)) 
        return new KnightPaladin(id, maxhp, level, gil, antidote, phoenixdownI);
    else if(maxhp==888)
        return new KnightLancelot(id, maxhp, level, gil, antidote, phoenixdownI);
    else if(CheckPythagoras(maxhp))
        return new KnightDragon(id, maxhp, level, gil, antidote, phoenixdownI);
    else 
        return new KnightNormal(id,maxhp, level, gil, antidote, phoenixdownI);
}
KnightPaladin::KnightPaladin(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{ 
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->knightType = PALADIN;
}
KnightLancelot::KnightLancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{ 
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->knightType= LANCELOT;
}
KnightDragon::KnightDragon(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{ 
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->knightType = DRAGON;
}
KnightNormal::KnightNormal(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{ 
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->knightType = NORMAL;
}
BaseKnight::~BaseKnight()
{
    delete bag;
}
//============================ArmyKnights======================================//
ArmyKnights::ArmyKnights(const string & file_armyknights)
{
	ifstream assign;
	assign.open(file_armyknights);
    assign>>num_knights;
    knight_stats= new BaseKnight*[1000];
	for(int i=0; i<num_knights; i++)
	{
        int hp, level, gil, antidote, phoenixdownI;
        assign>>hp>>level>>phoenixdownI>>gil>>antidote;
        BaseKnight *knight_temp = BaseKnight::create(i+1, hp, level, gil, antidote, phoenixdownI);
        knight_stats[i] = knight_temp;
        knight_stats[i]->setBag(new BaseBag(knight_stats[i], knight_stats[i]->getPhoenixDownI(), knight_stats[i]->getAntidote()));
	}
    assign.close();
}
bool ArmyKnights::usePhoenixdown2(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    if(temp->get(PHOENIXDOWN2)!=NULL)
    {
        PhoenixDownII *hold = new PhoenixDownII();
        hold->use(knight);
        return true;
    }
    return false;
}
bool ArmyKnights::usePhoenixdown3(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    if(temp->get(PHOENIXDOWN3)!=NULL)
    {
        PhoenixDownIII *hold = new PhoenixDownIII();
        hold->use(knight);
        return true;
    }
    return false;
}
bool ArmyKnights::usePhoenixdown4(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    if(temp->get(PHOENIXDOWN4)!=NULL)
    {
        PhoenixDownIV *hold = new PhoenixDownIV();
        hold->use(lastKnight());
        return true;
    }
    return false;
}
bool ArmyKnights::fight(BaseOpponent *opponent)
{
    if(lastKnight()->getHP()>0)
    {
        if(lastKnight()->getHP()<lastKnight()->getMaxHP()/4)
        {
           if(lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN2)<9999||lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN3)<9999||lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN4)<9999)
            {
                int a=lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN2);
                int b=lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN3);
                int c=lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN4);
                int smallest=a;
                if(b<smallest)
                {
                    smallest=b;
                    if(c<smallest) c=smallest;
                }
                else if(c<smallest) c=smallest;
                if(smallest==a) return usePhoenixdown2(lastKnight());
                else if(smallest==b) return usePhoenixdown3(lastKnight());
                else return usePhoenixdown4(lastKnight());
            } 
        }
        else
        {
            if(lastKnight()->getHP()<lastKnight()->getMaxHP()/3)
            {
                if(lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN4)<9999||lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN3)<9999)
                {
                    int a=lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN4);
                    int b=lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN3);
                    if(a<b) return usePhoenixdown4(lastKnight());
                    else return usePhoenixdown3(lastKnight());
                }
            }
            else
            {
                if(lastKnight()->getHP()<lastKnight()->getMaxHP()/2)
                {
                    if(lastKnight()->getBag()->scanPhoenixDown(PHOENIXDOWN4)<9999) return usePhoenixdown4(lastKnight());
                }
            }
        }
        return true;
    }
    else
    {
        if(lastKnight()->getBag()->searchPhoenixDown()==PHOENIXDOWN1)
        {
            BaseBag *temp=lastKnight()->getBag();
            if(temp->get(PHOENIXDOWN1)!=NULL)
            {
                PhoenixDownI *hold=new PhoenixDownI();
                hold->use(lastKnight());
                // delete hold;
                return true;
            }
            return true;
        }
        else if(lastKnight()->getBag()->searchPhoenixDown()==PHOENIXDOWN2) return usePhoenixdown2(lastKnight());
        else if(lastKnight()->getBag()->searchPhoenixDown()==PHOENIXDOWN3) return usePhoenixdown3(lastKnight());
        else if(lastKnight()->getBag()->searchPhoenixDown()==PHOENIXDOWN4) return usePhoenixdown4(lastKnight());
        else
        {
            if(lastKnight()->getGil()>=100) 
            {
                lastKnight()->setGil(lastKnight()->getGil()-100);
                lastKnight()->setHP(lastKnight()->getMaxHP()/2);
                return true;
            }
            else 
            {
                setNumKnights(getNumKnights()-1);
                return false;
            }
        }
    }
}
bool ArmyKnights::adventure(Events *events)
{
    for(int i=0; i<events->count(); i++)
    {
        if(num_knights<=0)
        {
            return false;
        }
        switch (events->get(i))
        {
        case 1:
        {   
            BaseOpponent *bear_mad= new MadBear();
            bear_mad->fight(i, lastKnight());
            if(!ArmyKnights::fight(bear_mad)) setLastKnight(knight_stats[num_knights-1]);
            else
            {
                if(lastKnight()->getGil()>999)
                {
                    int spare=lastKnight()->getGil()-999;
                    lastKnight()->setGil(999);
                    for(int j=num_knights; j>0; j--)
                    {
                        if(knight_stats[j-1]->getGil()+spare>999)
                        {
                            spare=knight_stats[j-1]->getGil()+spare-999;
                        }
                        else 
                        {
                            knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                            break;
                        }
                    }
                }
            }
            printInfo();
            delete bear_mad;
            break;
        }
        case 2:
        {
            BaseOpponent *dit_ban= new Bandit();
            dit_ban->fight(i, lastKnight());
            if(!ArmyKnights::fight(dit_ban)) setLastKnight(knight_stats[num_knights-1]);
            else
            {
                if(lastKnight()->getGil()>999)
                {
                    int spare=lastKnight()->getGil()-999;
                    lastKnight()->setGil(999);
                    for(int j=num_knights; j>0; j--)
                    {
                        if(knight_stats[j-1]->getGil()+spare>999)
                        {
                            spare=knight_stats[j-1]->getGil()+spare-999;
                        }
                        else 
                        {
                            knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                            break;
                        }
                    }
                }
            }
            printInfo();
            delete dit_ban;
            break;
        }
        case 3:
        {
            BaseOpponent *lupin_lord= new LordLupin();
            lupin_lord->fight(i, lastKnight());
            if(!ArmyKnights::fight(lupin_lord)) setLastKnight(knight_stats[num_knights-1]);
            else
            {
                if(lastKnight()->getGil()>999)
                {
                    int spare=lastKnight()->getGil()-999;
                    lastKnight()->setGil(999);
                    for(int j=num_knights; j>0; j--)
                    {
                        if(knight_stats[j-1]->getGil()+spare>999)
                        {
                            spare=knight_stats[j-1]->getGil()+spare-999;
                        }
                        else 
                        {
                            knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                            break;
                        }
                    }
                }
            }
            printInfo();
            delete lupin_lord;
            break;
        }
        case 4:
        {
            BaseOpponent *eleven= new Elf();
            eleven->fight(i, lastKnight());
            if(!ArmyKnights::fight(eleven)) setLastKnight(knight_stats[num_knights-1]);
            else
            {
                if(lastKnight()->getGil()>999)
                {
                    int spare=lastKnight()->getGil()-999;
                    lastKnight()->setGil(999);
                    for(int j=num_knights; j>0; j--)
                    {
                        if(knight_stats[j-1]->getGil()+spare>999)
                        {
                            spare=knight_stats[j-1]->getGil()+spare-999;
                        }
                        else 
                        {
                            knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                            break;
                        }
                    }
                }
            }
            printInfo();
            delete eleven;
            break;
        }
        case 5:
        {
            BaseOpponent *LOL= new Troll();
            LOL->fight(i, lastKnight());
            if(!ArmyKnights::fight(LOL)) setLastKnight(knight_stats[num_knights-1]);
            else
            {
                if(lastKnight()->getGil()>999)
                {
                    int spare=lastKnight()->getGil()-999;
                    lastKnight()->setGil(999);
                    for(int j=num_knights; j>0; j--)
                    {
                        if(knight_stats[j-1]->getGil()+spare>999)
                        {
                            spare=knight_stats[j-1]->getGil()+spare-999;
                        }
                        else 
                        {
                            knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                            break;
                        }
                    }
                }
            }
            printInfo();
            delete LOL;
            break;
        }
        case 6:
        {
            BaseOpponent *BerryTorn= new TornBerry();
            BerryTorn->fight(i, lastKnight());
            if(!ArmyKnights::fight(BerryTorn)) setLastKnight(knight_stats[num_knights-1]);
            printInfo();
            delete BerryTorn;
            break;
        }
        case 7:
        {
            BaseOpponent *cards_queen= new QueenOfCards();
            cards_queen->fight(i,lastKnight());
            if(lastKnight()->getGil()>999)
            {
                int spare=lastKnight()->getGil()-999;
                lastKnight()->setGil(999);
                for(int j=num_knights; j>0; j--)
                {
                    if(knight_stats[j-1]->getGil()+spare>999)
                    {
                        spare=knight_stats[j-1]->getGil()+spare-999;
                        knight_stats[j-1]->setGil(999);
                    }
                    else 
                    {
                        knight_stats[j-1]->setGil(knight_stats[j-1]->getGil()+spare);
                        break;
                    }
                }
            }
            printInfo();
            delete cards_queen;
            break;
        }
        case 8:
        {
            BaseOpponent *nings= new NinaTheRings();
            nings->fight(i,lastKnight());
            printInfo();
            delete nings;
            break;
        }
        case 9:
        {
            BaseOpponent *Garien= new DurianGarden();
            Garien->fight(i,lastKnight());
            printInfo();
            delete Garien;
            break;
        }
        case 10:
        {
            OmegaWeapon *OmegaLOL= new OmegaWeapon();
            if(!getOmegaWeaponLOL())
            {
                OmegaLOL->fight(i, lastKnight());
                if(!ArmyKnights::fight(OmegaLOL)) setLastKnight(knight_stats[num_knights-1]);
                if (OmegaLOL->getOmegaLUL()) 
                {
                    setOmegaWeaponLOL(true);
                    printInfo();
                    delete OmegaLOL;
                    break;
                }
            }
            printInfo();
            delete OmegaLOL;
            break;
        }
        case 11:
        {
            Hades *sedah= new Hades();
            if(!Haters)
            {
                sedah->fight(i, lastKnight());
                if(!ArmyKnights::fight(sedah)) setLastKnight(knight_stats[num_knights-1]);
                if(sedah->getDeath()) 
                {
                    Haters=true;
                    setShield(true);
                }
            }
            printInfo();
            delete sedah;
            break;
        }
        case 112:
        {
            BaseItem *addon1= new PhoenixDownII();
            if(!lastKnight()->getBag()->insertFirst(addon1))
            {
                for(int j=num_knights; j>0; j--)
                {
                    if(knight_stats[j-1]->getBag()->insertFirst(addon1)) break;
                }
            }
            printInfo();
            // delete addon1;
            break;
        }
        case 113:
        {
            BaseItem *addon2= new PhoenixDownIII();
            if(!lastKnight()->getBag()->insertFirst(addon2))
            {
                for(int j=num_knights; j>0; j--)
                {
                    if(knight_stats[j-1]->getBag()->insertFirst(addon2)) break;
                }
            }
            printInfo();
            // delete addon2;
            break;
        }
        case 114:
        {
            BaseItem *addon3= new PhoenixDownIV();
            if(!lastKnight()->getBag()->insertFirst(addon3))
            {
                for(int j=num_knights; j>0; j--)
                {
                    if(knight_stats[j-1]->getBag()->insertFirst(addon3)) break;
                }
            }
            printInfo();
            // delete addon3;
            break;
        }
        case 95:
        {
            if(!hasPaladinShield()) setShield(true);
            printInfo();
            break;
        }
        case 96:
        {
            if(!hasLancelotSpear()) setSpear(true);
            printInfo();
            break;
        }
        case 97:
        {
            if(!hasGuinevereHair()) setHair(true);
            printInfo();
            break;
        }
        case 98:
        {
            if(hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()) setSword(true);
            printInfo();
            break;
        }
        case 99:
        {
            if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair() || hasExcaliburSword())
            {
                count2=getNumKnights();
                if (hasExcaliburSword())
                {
                    printInfo();
                    return true;
                }
                else
                {
                    fakecount = getNumKnights();
                    theRealExcalibur = true;
                    int BossHP = 5000;
                    for (int i = num_knights - 1; i>-1; i--)
                    {
                        if (knight_stats[i]->getKnightType() == NORMAL)
                        {
                            count2--;
                            findNormal=true;
                            continue;
                        }
                        if (count2 == 0)
                        {
                            setNumKnights(0);
                            printInfo();
                            return false;
                        }
                        else
                        {
                            double baseDam;
                            if (knight_stats[i]->getKnightType() == PALADIN) baseDam = 0.06;
                            else if (knight_stats[i]->getKnightType() == LANCELOT) baseDam = 0.05;
                            else if (knight_stats[i]->getKnightType() == DRAGON) baseDam = 0.075;
                            int damage = knight_stats[i]->getHP() * knight_stats[i]->getLevel() * baseDam;
                            BossHP = BossHP - damage;
                            if (BossHP <= 0)
                            {
                                printInfo();
                                return true;
                            }
                            else
                            {
                                setNumKnights(getNumKnights() - 1);
                                count2--;
                                if(!findNormal) fakecount--;
                            }
                        }
                    }
                    setNumKnights(0);
                    printInfo();
                    return false;
                }
            }
            else
            {
                setNumKnights(0);
                printInfo();
                return false;
            }
        }
        default:
            break;
        }
    }
    return true;
}
int ArmyKnights::count() const
{
    return num_knights;
}
BaseKnight *ArmyKnights::lastKnight() const
{ 
    if (theRealExcalibur&&count2!=num_knights) return knight_stats[fakecount - 1];
    return knight_stats[num_knights - 1];
}
ArmyKnights::~ArmyKnights()
{
    for(int i=0; i<num_knights; i++) delete[] knight_stats[i];
    delete lastManStanding;
}
//===============================BaseOpponent===================================//
void MadBear::fight(int i, BaseKnight *knight)
{
    int levelO=(1+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==1||knight->getKnightType()==0) reward(knight);
    else attack(i, knight);
}
void MadBear::attack(int i, BaseKnight *knight)
{
    int levelO=(1+i)%10+1;
    int temp;
    temp=knight->getHP()-10*(levelO-knight->getLevel());
    knight->setHP(temp);
}
void MadBear::reward(BaseKnight *knight)
{
    int temp;
    temp=knight->getGil()+100;
    knight->setGil(temp);
}
void Bandit::fight(int i, BaseKnight *knight)
{
    int levelO=(2+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==1||knight->getKnightType()==0) reward(knight);
    else attack(i, knight);
}
void Bandit::attack(int i, BaseKnight *knight)
{
    int levelO=(2+i)%10+1;
    int temp;
    temp=knight->getHP()-15*(levelO-knight->getLevel());
    knight->setHP(temp);
}
void Bandit::reward(BaseKnight *knight)
{
    int temp;
    temp=knight->getGil()+150;
    knight->setGil(temp);
}
void LordLupin::fight(int i, BaseKnight *knight)
{
    int levelO=(3+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==1||knight->getKnightType()==0) reward(knight);
    else attack(i, knight);
}
void LordLupin::attack(int i, BaseKnight *knight)
{
    int levelO=(3+i)%10+1;
    int temp;
    temp=knight->getHP()-45*(levelO-knight->getLevel());
    knight->setHP(temp);
}
void LordLupin::reward(BaseKnight *knight)
{
    int temp;
    temp=knight->getGil()+450;
    knight->setGil(temp);
}
void Elf::fight(int i, BaseKnight *knight)
{
    int levelO=(4+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==1||knight->getKnightType()==0) reward(knight);
    else attack(i, knight);
}
void Elf::attack(int i, BaseKnight *knight)
{
    int levelO=(4+i)%10+1;
    int temp;
    temp=knight->getHP()-75*(levelO-knight->getLevel());
    knight->setHP(temp);
}
void Elf::reward(BaseKnight *knight)
{
    int temp;
    temp=knight->getGil()+750;
    knight->setGil(temp);
}
void Troll::fight(int i, BaseKnight *knight)
{
    int levelO=(5+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==1||knight->getKnightType()==0) reward(knight);
    else attack(i, knight);
}
void Troll::attack(int i, BaseKnight *knight)
{
    int levelO=(5+i)%10+1;
    int temp;
    temp=knight->getHP()-95*(levelO-knight->getLevel());
    knight->setHP(temp);
}
void Troll::reward(BaseKnight *knight)
{
    int temp;
    temp=knight->getGil()+800;
    knight->setGil(temp);
}
void TornBerry::fight(int i, BaseKnight *knight)
{
    int levelO=(6+i)%10+1;
    if(knight->getLevel()>=levelO||knight->getKnightType()==2) reward(knight);
    else attack(i,knight);
}
void TornBerry::attack(int i, BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    if(temp->get(ANTIDOTE)!=NULL)
    {
        Antidote *hold= new Antidote();
        hold->use(knight);
    }
    else
    {
        knight->setHP(knight->getHP()-10);
        if(knight->getBag()->getInitialCapacity()-knight->getBag()->getCapacity()<3)
        {
            BaseBag *temp=knight->getBag();
            temp->head=NULL;
            knight->getBag()->setCapacity(knight->getBag()->getInitialCapacity());
        }
        else
        {
            BaseBag *temp=knight->getBag();
            for(int i=0; i<3; i++)
            {
                temp->head=temp->head->next;
                knight->getBag()->setCapacity(knight->getBag()->getCapacity()+1);
            }
        }
    }
}
void TornBerry::reward(BaseKnight *knight)
{
    if(knight->getLevel()+1>10) return;
    else (knight->setLevel(knight->getLevel()+1));
}
void QueenOfCards::fight(int i, BaseKnight *knight)
{
    int levelO=(7+i)%10+1;
    if(knight->getLevel()>=levelO) reward(knight);
    else attack(i,knight);
}
void QueenOfCards::attack(int i, BaseKnight *knight)
{
    if(knight->getKnightType()==0) return;
    knight->setGil(knight->getGil()/2);
}
void QueenOfCards::reward(BaseKnight *knight)
{
    knight->setGil(knight->getGil()*2);
}
void NinaTheRings::fight(int i, BaseKnight *knight)
{
    if(knight->getGil()>=50 && knight->getHP()<knight->getMaxHP()/3 || knight->getKnightType()==0 && knight->getHP()<knight->getMaxHP()/3 ) reward(knight);
    else attack(i,knight);
}
void NinaTheRings::attack(int i, BaseKnight *knight)
{
    return;
}
void NinaTheRings::reward(BaseKnight *knight)
{
    if(knight->getKnightType()!=0) knight->setGil(knight->getGil()-50);
    knight->setHP(knight->getHP()+knight->getMaxHP()/5);
}
void DurianGarden::fight(int i, BaseKnight *knight)
{
    reward(knight);
}
void DurianGarden::reward(BaseKnight *knight)
{
    knight->setHP(knight->getMaxHP());
}
void DurianGarden::attack(int i, BaseKnight *knight)
{
    return;
}
void OmegaWeapon::fight(int i, BaseKnight *knight)
{
    if(knight->getKnightType()==2) reward(knight);
    else if(knight->getHP()==knight->getMaxHP() && knight->getLevel()==10) reward(knight);
    else attack(i, knight);
}
void OmegaWeapon::reward(BaseKnight *knight)
{
    knight->setLevel(10);
    knight->setGil(999);
    OmegaLUL=true;
}
void OmegaWeapon::attack(int i, BaseKnight *knight)
{
    knight->setHP(0);
}
void Hades::fight(int i, BaseKnight *knight)
{
    if(knight->getKnightType()==0 && knight->getLevel()>=8 || knight->getKnightType()!=0 && knight->getLevel()==10) reward(knight);
    else attack(i,knight);
}
void Hades::reward(BaseKnight *knight)
{
    death=true;
}
void Hades::attack(int i, BaseKnight *knight)
{
    knight->setHP(0);
}
//=================================BaseItem=====================================//
Antidote::Antidote()
{
    value=ANTIDOTE;
}
PhoenixDownI::PhoenixDownI()
{
    value=PHOENIXDOWN1;
}
PhoenixDownII::PhoenixDownII()
{
    value=PHOENIXDOWN2;
}
PhoenixDownIII::PhoenixDownIII()
{
    value=PHOENIXDOWN3;
}
PhoenixDownIV::PhoenixDownIV()
{
    value=PHOENIXDOWN4;
}
bool Antidote::canUse(BaseKnight* knight)
{
    if(knight->getBag()->get(ANTIDOTE)!=NULL) return true;
    else return false;
}
void Antidote::use(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    temp->update(ANTIDOTE);
}
bool PhoenixDownI::canUse(BaseKnight * knight)
{
    if(knight->getHP()<=0 && knight->getBag()->get(PHOENIXDOWN1)!=NULL) return true;
    else return false;
}
void PhoenixDownI::use(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    temp->update(PHOENIXDOWN1);
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownII::canUse(BaseKnight* knight)
{
    if(knight->getHP()<knight->getMaxHP()/4 && knight->getBag()->get(PHOENIXDOWN2)!=NULL && knight->getHP()>0) return true;
    else return false;
}
void PhoenixDownII::use(BaseKnight *knight)
{
    BaseBag *temp=knight->getBag();
    temp->update(PHOENIXDOWN2);
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownIII::canUse(BaseKnight * knight)
{
    if(knight->getHP()<knight->getMaxHP()/3 && knight->getHP()>0 && knight->getBag()->get(PHOENIXDOWN3)!=NULL || knight->getHP()<=0 && knight->getBag()->get(PHOENIXDOWN3)!=NULL) return true;
    else return false;
}
void PhoenixDownIII::use(BaseKnight* knight)
{
    if(knight->getHP()<=0) knight->setHP(knight->getMaxHP()/3);
    else knight->setHP(knight->getHP()+knight->getMaxHP()/4);
    BaseBag *temp=knight->getBag();
    temp->update(PHOENIXDOWN3);
}
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    if(knight->getHP()<knight->getMaxHP()/2 && knight->getHP()>0 && knight->getBag()->get(PHOENIXDOWN4)!=NULL|| knight->getHP()<=0 && knight->getBag()->get(PHOENIXDOWN4)!=NULL) return true;
    else return false;
}
void PhoenixDownIV::use(BaseKnight *knight)
{
    if(knight->getHP()<=0) knight->setHP(knight->getMaxHP()/2);
    else knight->setHP(knight->getHP()+knight->getMaxHP()/5);
    BaseBag *temp=knight->getBag();
    temp->update(PHOENIXDOWN4);
}
BaseItem::~BaseItem()
{
    delete next;
}
//==================================BaseBag=====================================//
BaseBag::BaseBag(BaseKnight *knight, int a, int b)
{
    if(knight->getKnightType()==PALADIN) 
    {
        setCapacity(9999);
        setInitialCapacity(9999);
    }
    else if(knight->getKnightType()==LANCELOT) 
    {
        setCapacity(16);
        setInitialCapacity(16);
    }
    else if(knight->getKnightType()==DRAGON) 
    {
        setCapacity(14);
        setInitialCapacity(14);
    }
    else if(knight->getKnightType()==NORMAL) 
    {
        setCapacity(19);
        setInitialCapacity(19);
    }
    for(int i=0; i<a && getCapacity()>0; i++)
    {
        BaseItem* new_node=new PhoenixDownI();
        new_node->value=PHOENIXDOWN1;
        new_node->next=head;
        head=new_node;
        setCapacity(getCapacity()-1);
    }
    for(int i=0; i<b && getCapacity()>0 && knight->getKnightType()!=DRAGON; i++)
    { 
        BaseItem *node_new= new Antidote();
        node_new->value=ANTIDOTE;
        node_new->next=head;
        head=node_new;
        setCapacity(getCapacity()-1);
    }
}
int BaseBag::scanPhoenixDown(ItemType itemType)
{
    int i=getInitialCapacity()-getCapacity();
    int cnt=0;
    if(i==0) return 9999;
    BaseItem *temp=head;
    for(int j=0; j<i; j++)
    {
        if(temp->value==itemType) return cnt;
        temp=temp->next;
        cnt++;
    }
    return 9999;
}
ItemType BaseBag::searchPhoenixDown()
{
    int i=getInitialCapacity()-getCapacity();
    if(i==0) return NONE;
    BaseItem *temp=head;
    for(int j=0; j<i; j++)
    {
        if(temp->value==PHOENIXDOWN1) return PHOENIXDOWN1;
        else if(temp->value==PHOENIXDOWN2) return PHOENIXDOWN2;
        else if(temp->value==PHOENIXDOWN3) return PHOENIXDOWN3;
        else if(temp->value==PHOENIXDOWN4) return PHOENIXDOWN4;
        temp=temp->next;
    }
    return NONE;
}
bool BaseBag::insertFirst(BaseItem *item)
{
    if(getCapacity()>0)
    {
        item->next=head;
        head=item;
        setCapacity(getCapacity()-1);
        return true;
    }
    else return false;
}
BaseItem *BaseBag::get(ItemType itemType)
{
    BaseItem *a=head;
    BaseItem *prevb=NULL; BaseItem *currb=head;
    while(currb&&currb->value!=itemType)
    {
        prevb=currb;
        currb=currb->next;
    }
    if(currb==NULL) return NULL;
    else return currb;
}
void BaseBag::update(ItemType itemType)
{
    if(head->value==itemType) 
    {
        head=head->next;
        setCapacity(getCapacity()+1);
        return;
    }
    BaseItem *test=head;
    if(test->next->value==itemType)
    {
        head->next=head->next->next;
        setCapacity(getCapacity()+1);
        return;
    }
    BaseItem *a=head;
    BaseItem *prevb=NULL; BaseItem *currb=head;
    while(currb&&currb->value!=itemType)
    {
        prevb=currb;
        currb=currb->next;
    }
    head=currb;
    BaseItem* temp=currb->next;
    currb->next=a->next;
    prevb->next = a;
    a->next=temp;
    head=head->next;
    setCapacity(getCapacity()+1);
}
string BaseBag::toString() const
{
    string s="";
    s   += "Bag[count="
        + to_string(initial_capacity-capacity)
        +";";
    BaseItem *temp=head;
    if(initial_capacity-capacity<=0) s+="]";
    else
    {
        for(int i=0; i<initial_capacity-capacity-1; i++)
        {
            if(temp->value==ANTIDOTE) s+="Antidote";
            else if(temp->value==PHOENIXDOWN1) s+="PhoenixI";
            else if(temp->value==PHOENIXDOWN2) s+="PhoenixII";
            else if(temp->value==PHOENIXDOWN3) s+="PhoenixIII";
            else if(temp->value==PHOENIXDOWN4) s+="PhoenixIV";
            s+=",";
            temp=temp->next;
        }
        if(temp->value==ANTIDOTE) s+="Antidote";
        else if(temp->value==PHOENIXDOWN1) s+="PhoenixI";
        else if(temp->value==PHOENIXDOWN2) s+="PhoenixII";
        else if(temp->value==PHOENIXDOWN3) s+="PhoenixIII";
        else if(temp->value==PHOENIXDOWN4) s+="PhoenixIV";
        s+="]";
    }
    return s;
}
BaseBag::~BaseBag()
{
    delete head;
}
//==================================KnightAdventure============================//
void KnightAdventure::loadArmyKnights(const string &s)
{
    armyKnights = new ArmyKnights(s);
}
void KnightAdventure::loadEvents(const string &s)
{
    events = new Events(s);
}
void KnightAdventure::run()
{
    armyKnights->printResult(armyKnights->adventure(events));
}
KnightAdventure::~KnightAdventure()
{
    // delete armyKnights, events;
}

