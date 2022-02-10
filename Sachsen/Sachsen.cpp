// Sachsen.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;
using namespace sf;
////////данные класса///////////
class Coordinates
{
public:
	////1- атака/////
	int X1[7] = { 0,0,0,0,0,0,0 };
	int Y1[7] = { 0,0,0,0,0,20,10 };
	int heigth1[7] = { 130,120,130,30,120,50,60 };
	int width1[7] = { 90,90,100,40,85,60,80 };
	string obj1[7] = { "f1.png","k1.png","b1.png","a4.png","t1.png","m4.png","p4.png" };
	////2- смерть//////
	int X2[7] = { 0,0,0,10,0,0,0 };
	int Y2[7] = { 0,0,0,10,0,0,0 };
	int heigth2[7] = { 120,110,120,110,90,140,120 };
	int width2[7] = { 90,90,90,90,80,140,90 };
	string obj2[7] = { "f2.png","k2.png","b2.png","a2.png","t2.png","m2.png","p2.png" };
	///////3- ранение//////
	int X3[7] = { 0,0,0,0,0,0,0 };
	int Y3[7] = { 0,10,10,10,0,10,10 };
	int heigth3[7] = { 120,130,120,100,100,120,100 };
	int width3[7] = { 110,110,90,75,70,150,75 };
	string obj3[7] = { "f3.png","k3.png","b3.png","a3.png","t3.png","m3.png","p3.png" };
	//////4- движение/////
	int X4[7] = { 40,10,0,0,0,0,0 };
	int Y4[7] = { 0,10,10,0,0,0,0 };
	int heigth4[7] = { 130,110,110,120,100,130,110 };
	int width4[7] = { 120,80,80,80,70,90,80 };
	string obj4[7] = { "f4.png","k4.png","b4.png","a1.png","t4.png","m1.png","p1.png" };
	int num_kadr1[7] = { 7,7,6,1,8,1,1 };
	int num_kadr2[7] = { 6,6,6,5,8,8,6 };
	int num_kadr3[7] = { 6,6,6,6,8,6,5 };
	int num_kadr4[7] = { 12,12,7,8,10,5,6 };
};
class Player :public Coordinates //1-Воин 2-Рыцарь 3-Варвар 4-Лучник 5-Вор 6-Маг 7-Жрец
{
private:
	int Basic_HP[7] = { 10,10,12,8,6,4,8 };		//базоыве жизни
	int Strength;		//сила
	int Dexterity;		//ловкость
	int Constitution;	//конституция
	int Wisdom;			//мудрость
	int Intelligence;	//интеллект
	int Charisma;		//харизма
	int speed[7] = { 6,7,9,8,10,4,5 };	//скорость
	int Thaco[7] = { 13,11,12,16,14,10,10 };			//вероятность попадания
	int level;			//уровень персонажа
	const int ogr_level = 20;	//ограничение уровня
	int elder[5] = { 0,0,0,0,0 };	//уровень заклинаний 
	int mod_elder[5] = { 0,0,0,0,0 };//уровень бонусов заклинаний
	int all_elder[5];	//всего в итоге заклинаний
	int hp_cha;			//определение кол-ва свитков восстановления жизней для рыцаря
	int dam[7] = { 10,8,12,10,7,4,6 };	//диапазон урона
public:
	int HP;				//всего кол-во жизней
	int id;				//идентификатор класса персонажа
	string magic;		//название заклинание
	string name[7] = { "Fighter","Knight","Barbar","Archer","Thief","Mage","Priest" };		//название класса персонажа
	//////////////
	friend void Stat2(RenderWindow &window, Player &p1);
	friend void game1(RenderWindow &window, Player &p1, Player &p2);
	friend void game2(RenderWindow &window, Player &p1, Player &p2);
	Player() {};
	int Dice();				//кубик с 20 гранями
	int mod_str();			//бонус силы для урона
	int mod_dex();			//бонус ловкости для защиты 
	int mod_con();			//бонус телосложения для жизней
	int mod_thaco();		//бонус попадания
	int atack();			//атака
	int defend();			//защита
	int Health(int x);		//кол-во жизней по уровню
	void leveling(int level);//определение уровня
	int damage()
	{
		int x = rand() % dam[id] + mod_str() + 1;
		return x;
	}
	//////особенности///////
	void mod_int()			//бонус интеллекта, важна для магов,т.к. влияет на заклинания
	{
		if (Intelligence == 13 || Intelligence == 14)
			mod_elder[0] = Intelligence - 12;
		if (Intelligence == 15 || Intelligence == 16)
		{
			mod_elder[0] = 2; mod_elder[1] = Intelligence - 14;
		}
		if (Intelligence == 17 || Intelligence == 18)
		{
			mod_elder[0] = 2; mod_elder[1] = 2; mod_elder[2] = 1; mod_elder[3] = Intelligence - 17;
		}
		if (Intelligence == 19 || Intelligence == 20)
		{
			mod_elder[0] = 3; mod_elder[1] = Intelligence - 17; mod_elder[2] = 1; mod_elder[3] = Intelligence - 17;
		}
	}
	void mod_wis()			//бонус мудрости, важна для жрецов,т.к. влияет на заклинания
	{
		if (Wisdom == 13 || Wisdom == 14)
			mod_elder[0] = Wisdom - 12;
		if (Wisdom == 15 || Wisdom == 16)
		{
			mod_elder[0] = 2; mod_elder[1] = Wisdom - 14;
		}
		if (Wisdom == 17 || Wisdom == 18)
		{
			mod_elder[0] = 2; mod_elder[1] = 2; mod_elder[2] = 1; mod_elder[3] = Wisdom - 17;
		}
		if (Wisdom == 19 || Wisdom == 20)
		{
			mod_elder[0] = 3; mod_elder[1] = Wisdom - 17; mod_elder[2] = 1; mod_elder[3] = Wisdom - 17;
		}
	}
	void mod_cha()			//бонус харизмы, важна для рыцарей для возможности восстановления жизней
	{
		if (Charisma > 13)
			hp_cha = Charisma - 13;
		else hp_cha = 0;
	}
	void system_magic()		//функция для определения кол-ва заклинаний
	{
		for (int i = 1; i <= level; i++)
		{
			if (i % 2 == 0)
				elder[0]++;
			if (i % 4 == 0)
			{
				elder[1]++;
			}
			if (i % 6 == 0)
				elder[2]++;
			if (i % 10 == 0)
				elder[3]++;
			if (i % 20 == 0)
				elder[4]++;
		}
	}
	void all_eld()
	{
		for (int i = 0; i < 5; i++)
		{
			all_elder[i] = elder[i] + mod_elder[i];
		}
	}
	int magic_atack(int x)			//атака мага заклинанием 
	{
		int damage;
		if (x == 1)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 4 + 3;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 2)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 5 + 4;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 3)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 5 + 10;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 4)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 5 + 21;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 5)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = 30;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
	}
	int magic_atack_priest(int x)			//атака жреца заклинанием
	{
		int damage;
		if (x == 1)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 4 + 3;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 2)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				speed[id] = 2 * speed[id];
				return speed[id];
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 3)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				int heal = 10;
				return heal;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 4)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = rand() % 5 + 21;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
		if (x == 5)
		{
			if (all_elder[x - 1] > 0)
			{
				all_elder[x - 1]--;
				damage = 30;
				return damage;
			}
			else
			{
				magic_atack(x);
			}
		}
	}
	int heal()			//заклинание восстановление жизней
	{
		if (hp_cha > 0)
		{
			hp_cha--;
			return 10;
		}
		return 0;
	}
	void set(int s, int d, int c, int w, int i, int ch, int hp, int id, int lev)
	{
		Strength = s;
		Dexterity = d;
		Constitution = c;
		Wisdom = w;
		Intelligence = i;
		Charisma = ch;
		HP = hp;
		this->id = id;
		if (id == 5)
		{
			mod_int();
			system_magic();
			all_eld();
		}
		if (id == 6)
		{
			mod_wis();
			system_magic();
			all_eld();
		}
		if (id == 1)
		{
			mod_cha();
		}
	}
};
void menu(RenderWindow &window);
//void game1(RenderWindow &window, Player &p1, Player &p2);
void game2(RenderWindow &window, Player &p1, Player &p2);
void Stat1(RenderWindow &window);
void Stat2(RenderWindow &window, Player &p1);
int gaming;		//режим игры

///////menu//////
int main()
{
	RenderWindow window(VideoMode(1376, 768), "Duel");
	menu(window);
	return 0;
}
int Player::Dice()
{
	srand(time(NULL));
	int x = rand() & 20 + 1;
	return x;
}
int Player::mod_str()
{
	if (Strength > 15 && Strength < 18)
		return 1;
	if (Strength == 18)
		return 2;
	if (Strength == 19)
		return 7;
	if (Strength == 20)
		return 8;
	if (Strength < 6)
		return -1;
	return 0;
}
int Player::mod_dex()
{
	if (Dexterity == 15)
		return 1;
	if (Dexterity == 16)
		return 2;
	if (Dexterity == 17)
		return 3;
	if (Dexterity > 17)
		return 4;
	return 0;
}
int Player::mod_con()
{
	if (Constitution == 15)
		return 1;
	if (Constitution == 16)
		return 2;
	if (Constitution == 17)
		return 3;
	if (Constitution == 18)
		return 4;
	if (Constitution > 19)
		return 5;
	if (Constitution < 8)
		return -1;
	return 0;
}
int Player::Health(int x)
{
	srand(time(NULL));
	if (x == 0)
	{
		HP = Basic_HP[id];
		return HP;
	}
	int h = Basic_HP[id];
	for (int i = 0; i < x; i++)
		h += rand() % Basic_HP[id] + 1 + mod_con();
	HP = h;
	return HP;
}
int Player::atack()
{
	int x = Dice();
	x += mod_thaco() / 3;
	return x;
}
int Player::mod_thaco()
{
	return Thaco[id];
}
int Player::defend()
{
	int x = Dice();
	x += mod_dex();
	return x;
}
void Player::leveling(int level)
{
	if (level <= ogr_level)
		this->level = level;
	else this->level = 10;
}
//////слайды для игры/////
//////меню/////////
void menu(RenderWindow &window)
{
	Music music;
	music.openFromFile("themea.acm");
	music.play();
	music.setLoop(true);
	Font font;
	font.loadFromFile("Gothic.otf");
	Text text("", font, 60);
	text.setPosition(500, 25);
	text.setString("BATTLE");
	text.setFillColor(Color::Color(50, 0, 25));
	Texture menut1, menut2, menut3, menutbg;
	menut1.loadFromFile("Image/Menu/1 player.png");
	menut2.loadFromFile("Image/Menu/2 players.png");
	menut3.loadFromFile("Image/Menu/exit.png");
	menutbg.loadFromFile("Image/Menu/Background.jpg");
	Sprite menu1(menut1), menu2(menut2), menu3(menut3), menubg(menutbg);
	bool isMenu = 1;
	int num_menu = 0;
	menu1.setPosition(1000, 200);
	menu2.setPosition(1000, 400);
	menu3.setPosition(1000, 600);
	menubg.setPosition(0, 0);
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		num_menu = 0;
		if (IntRect(1000, 200, 400, 100).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Black);
			num_menu = 1;
		}
		if (IntRect(1000, 400, 400, 100).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Black);
			num_menu = 2;
		}
		if (IntRect(1000, 600, 400, 100).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Black);
			num_menu = 3;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (num_menu == 1)
			{
				isMenu = false;		//если нажали первую кнопку, то выходим из меню 
				gaming = 1;
				music.stop();
				Stat1(window);
			}

			if (num_menu == 2)
			{
				isMenu = false;
				music.stop();
				gaming = 2;
				Stat1(window);
			}
			if (num_menu == 3)
			{
				window.close();
				music.stop();
				isMenu = false;
			}
		}
		window.draw(menubg);
		window.draw(text);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
}
/////статистика игрока1 ////////
void Stat1(RenderWindow &window)
{
	srand(time(NULL));
	////текст////
	Font f1, f2;
	f1.loadFromFile("Gothic.otf");
	f2.loadFromFile("1.otf");
	Text player("", f1, 60), play("", f1, 50), exit("", f1, 60);
	player.setString("Player 1");
	play.setString("Play");
	exit.setString("Exit");
	player.setPosition(500, 25); player.setFillColor(Color::Color(50, 0, 25));
	play.setPosition(1100, 650); play.setFillColor(Color::Color(50, 0, 25));
	exit.setPosition(100, 650); exit.setFillColor(Color::Color(50, 0, 25));
	Text str("Strength: ", f1, 30), dex("Dexterity: ", f1, 30), con("Constitution: ", f1, 30), wis("Wisdom: ", f1, 30), intel("Intelligence: ", f1, 30), cha("Charisma: ", f1, 30);
	Text lev("Level: ", f1, 30), hp("Health: ", f1, 30), per("Class: ", f1, 50), roll("Die Roll: ", f1, 40);
	per.setPosition(800, 90); per.setFillColor(Color::Color(50, 0, 25));
	roll.setPosition(800, 150); roll.setFillColor(Color::Color(50, 0, 25));
	str.setPosition(800, 202); str.setFillColor(Color::Color(50, 0, 25));
	dex.setPosition(800, 254); dex.setFillColor(Color::Color(50, 0, 25));
	con.setPosition(800, 306); con.setFillColor(Color::Color(50, 0, 25));
	wis.setPosition(800, 358); wis.setFillColor(Color::Color(50, 0, 25));
	intel.setPosition(800, 410); intel.setFillColor(Color::Color(50, 0, 25));
	cha.setPosition(800, 462); cha.setFillColor(Color::Color(50, 0, 25));
	hp.setPosition(800, 514); hp.setFillColor(Color::Color(50, 0, 25));
	lev.setPosition(800, 566); lev.setFillColor(Color::Color(50, 0, 25));
	/////обои/////
	Image bg;
	bg.loadFromFile("Image/Background/Game.jpg");
	Texture bgr, pl, play1;
	bgr.loadFromImage(bg);
	Sprite sbg;
	sbg.setTexture(bgr);
	////стрелки/////
	Texture left, right, left2;
	left.loadFromFile("Image/Background/left.png"); right.loadFromFile("Image/Background/right.png");
	Sprite l1, l2, l3, l4, l5, l6, l7, l8, r1, r2, r3, r4, r5, r6, r7, r8;
	l1.setTexture(left); r1.setTexture(right);
	l2.setTexture(left); r2.setTexture(right);
	l3.setTexture(left); r3.setTexture(right);
	l4.setTexture(left); r4.setTexture(right);
	l5.setTexture(left); r5.setTexture(right);
	l6.setTexture(left); r6.setTexture(right);
	l7.setTexture(left); r7.setTexture(right);
	l8.setTexture(left); r8.setTexture(right);
	l1.setPosition(1100, 90); r1.setPosition(1200, 90);
	l2.setPosition(1100, 202); r2.setPosition(1200, 202);
	l3.setPosition(1100, 254); r3.setPosition(1200, 254);
	l4.setPosition(1100, 306); r4.setPosition(1200, 306);
	l5.setPosition(1100, 358); r5.setPosition(1200, 358);
	l6.setPosition(1100, 410); r6.setPosition(1200, 410);
	l7.setPosition(1100, 462); r7.setPosition(1200, 462);
	l8.setPosition(1100, 566); r8.setPosition(1200, 566);
	Player p;
	p.id = 0;
	/////остальное//////
	Music music;
	music.openFromFile("09 Mirror Mirror.ogg");
	music.play();
	music.setLoop(true);
	ostringstream sdice, sstr, sdex, scon, swis, sint, scha, slev, sclas, shp;
	int nstr = 3, ndex = 3, ncon = 3, nwis = 3, nint = 3, ncha = 3, nlev = 0, nclas = 0, nhp = p.Health(0);
	bool isStat = 1;
	int dice = rand() % 16 + 75;
	int xdice = dice - 18;
	int menu = 0;
	Vector2i localposition = Mouse::getPosition(window);
	Event e;
	while (isStat)
	{

		exit.setFillColor(Color::Color(50, 0, 25));
		play.setFillColor(Color::Color(50, 0, 25));
		roll.setFillColor(Color::Color(50, 0, 25));
		localposition = Mouse::getPosition(window);
		l1.setColor(Color::White);
		r1.setColor(Color::White);
		l2.setColor(Color::White);
		r2.setColor(Color::White);
		l3.setColor(Color::White);
		r3.setColor(Color::White);
		l4.setColor(Color::White);
		r4.setColor(Color::White);
		l5.setColor(Color::White);
		r5.setColor(Color::White);
		l6.setColor(Color::White);
		r6.setColor(Color::White);
		l7.setColor(Color::White);
		r7.setColor(Color::White);
		l8.setColor(Color::White);
		r8.setColor(Color::White);
		slev.str("");
		sdice.str("");
		sclas.str("");
		sstr.str("");
		sdex.str("");
		scon.str("");
		swis.str("");
		shp.str("");
		sint.str("");
		scha.str("");
		////стрелки/////
		if (IntRect(1100, 90, 70, 42).contains(Mouse::getPosition(window)))
		{
			l1.setColor(Color::Black);
		}
		if (IntRect(1200, 90, 70, 42).contains(Mouse::getPosition(window)))
		{
			r1.setColor(Color::Black);
		}
		if (IntRect(1100, 202, 70, 42).contains(Mouse::getPosition(window)))
		{
			l2.setColor(Color::Black);
		}
		if (IntRect(1200, 202, 70, 42).contains(Mouse::getPosition(window)))
		{
			r2.setColor(Color::Black);
		}
		if (IntRect(1100, 254, 70, 42).contains(Mouse::getPosition(window)))
		{
			l3.setColor(Color::Black);
		}
		if (IntRect(1200, 254, 70, 42).contains(Mouse::getPosition(window)))
		{
			r3.setColor(Color::Black);
		}
		if (IntRect(1100, 306, 70, 42).contains(Mouse::getPosition(window)))
		{
			l4.setColor(Color::Black);
		}
		if (IntRect(1200, 306, 70, 42).contains(Mouse::getPosition(window)))
		{
			r4.setColor(Color::Black);
		}
		if (IntRect(1100, 358, 70, 42).contains(Mouse::getPosition(window)))
		{
			l5.setColor(Color::Black);
		}
		if (IntRect(1200, 358, 70, 42).contains(Mouse::getPosition(window)))
		{
			r5.setColor(Color::Black);
		}
		if (IntRect(1100, 410, 70, 42).contains(Mouse::getPosition(window)))
		{
			l6.setColor(Color::Black);
		}
		if (IntRect(1200, 410, 70, 42).contains(Mouse::getPosition(window)))
		{
			r6.setColor(Color::Black);
		}
		if (IntRect(1100, 462, 70, 42).contains(Mouse::getPosition(window)))
		{
			l7.setColor(Color::Black);
		}
		if (IntRect(1200, 462, 70, 42).contains(Mouse::getPosition(window)))
		{
			r7.setColor(Color::Black);
		}
		if (IntRect(1100, 566, 70, 42).contains(Mouse::getPosition(window)))
		{
			l8.setColor(Color::Black);
		}
		if (IntRect(1200, 566, 70, 42).contains(Mouse::getPosition(window)))
		{
			r8.setColor(Color::Black);
		}
		///////остальное/////
		if (IntRect(100, 650, 100, 60).contains(Mouse::getPosition(window)))
		{
			exit.setFillColor(Color::Yellow);
		}
		if (IntRect(1100, 650, 100, 50).contains(Mouse::getPosition(window)))
		{
			play.setFillColor(Color::Yellow);
		}
		if (IntRect(800, 150, 150, 40).contains(Mouse::getPosition(window)))
		{
			roll.setFillColor(Color::Yellow);
		}
		while (window.pollEvent(e))
		{
			////стрелки/////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 202 && localposition.y <= 244)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nstr > 3 && xdice <= dice)
						{
							nstr--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 202 && localposition.y <= 244)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nstr < 20 && xdice > 0 && xdice <= dice)
						{
							nstr++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 254 && localposition.y <= 296)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ndex > 3 && xdice <= dice)
						{
							ndex--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 254 && localposition.y <= 296)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ndex < 20 && xdice > 0 && xdice <= dice)
						{
							ndex++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 306 && localposition.y <= 348)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncon > 3 && xdice <= dice)
						{
							ncon--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 306 && localposition.y <= 348)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncon < 20 && xdice > 0 && xdice <= dice)
						{
							ncon++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 358 && localposition.y <= 400)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nwis > 3 && xdice <= dice)
						{
							nwis--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 358 && localposition.y <= 400)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nwis < 20 && xdice > 0 && xdice <= dice)
						{
							nwis++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 410 && localposition.y <= 452)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nint > 3 && xdice <= dice)
						{
							nint--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 410 && localposition.y <= 452)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nint < 20 && xdice > 0 && xdice <= dice)
						{
							nint++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 462 && localposition.y <= 504)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncha > 3 && xdice <= dice)
						{
							ncha--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 462 && localposition.y <= 504)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncha < 20 && xdice > 0 && xdice <= dice)
						{
							ncha++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 90 && localposition.y <= 132)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nclas > 0)
						{
							nclas--;
							p.id = nclas;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 90 && localposition.y <= 132)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nclas < 6)
						{
							nclas++;
							p.id = nclas;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 566 && localposition.y <= 608)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nlev > 0)
						{
							nlev--;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 566 && localposition.y <= 608)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nlev < 20)
						{
							nlev++;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			///////////////////////
			////остальное/////
			if (localposition.x >= 100 && localposition.x <= 200 && localposition.y >= 650 && localposition.y <= 710)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						isStat = 0;
						music.stop();
						window.close();
						return;
					}
				}
			}
			if (localposition.x >= 1100 && localposition.x <= 1200 && localposition.y >= 650 && localposition.y <= 700)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						isStat = 0;
						music.stop();
					}
				}
			}
			if (localposition.x >= 800 && localposition.x <= 950 && localposition.y >= 150 && localposition.y <= 190)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						dice = rand() % 16 + 75;
						xdice = dice - 18;
						nstr = 3;
						ndex = 3;
						ncon = 3;
						nwis = 3;
						nint = 3;
						ncha = 3;
					}
				}
			}
		}
		//p.id = nclas;
		sdice << dice;
		slev << nlev;
		sclas << p.name[nclas];
		sstr << nstr;
		sdex << ndex;
		scon << ncon;
		swis << nwis;
		shp << nhp;
		sint << nint;
		scha << ncha;
		per.setString("Class: " + sclas.str());
		lev.setString("Level: " + slev.str());
		roll.setString("Die Roll: " + sdice.str());
		str.setString("Strength: " + sstr.str());
		dex.setString("Dexterity: " + sdex.str());
		con.setString("Constitution: " + scon.str());
		wis.setString("Wisdom: " + swis.str());
		hp.setString("Health: " + shp.str());
		intel.setString("Intelligence: " + sint.str());
		cha.setString("Charisma: " + scha.str());
		window.draw(sbg);
		window.draw(player);
		window.draw(play);
		window.draw(exit);
		window.draw(per);
		window.draw(roll);
		window.draw(str);
		window.draw(dex);
		window.draw(con);
		window.draw(wis);
		window.draw(intel);
		window.draw(cha);
		window.draw(hp);
		window.draw(lev);
		window.draw(l1); window.draw(r1);
		window.draw(l2); window.draw(r2);
		window.draw(l3); window.draw(r3);
		window.draw(l4); window.draw(r4);
		window.draw(l5); window.draw(r5);
		window.draw(l6); window.draw(r6);
		window.draw(l7); window.draw(r7);
		window.draw(l8); window.draw(r8);
		window.display();
	}
	p.set(nstr, ndex, ncon, nwis, nint, ncha, nhp, nclas, nlev);
	Stat2(window, p);
}
/////статистика игрока 2///////
void Stat2(RenderWindow &window, Player &p1)
{
	srand(time(NULL));
	////текст////
	Font f1, f2;
	f1.loadFromFile("Gothic.otf");
	f2.loadFromFile("1.otf");
	Text player("", f1, 60), play("", f1, 50), exit("", f1, 60);
	player.setString("Player 2");
	play.setString("Play");
	exit.setString("Exit");
	player.setPosition(500, 25); player.setFillColor(Color::Color(50, 0, 25));
	play.setPosition(1100, 650); play.setFillColor(Color::Color(50, 0, 25));
	exit.setPosition(100, 650); exit.setFillColor(Color::Color(50, 0, 25));
	Text str("Strength: ", f1, 30), dex("Dexterity: ", f1, 30), con("Constitution: ", f1, 30), wis("Wisdom: ", f1, 30), intel("Intelligence: ", f1, 30), cha("Charisma: ", f1, 30);
	Text lev("Level: ", f1, 30), hp("Health: ", f1, 30), per("Class: ", f1, 50), roll("Die Roll: ", f1, 40);
	per.setPosition(800, 90); per.setFillColor(Color::Color(50, 0, 25));
	roll.setPosition(800, 150); roll.setFillColor(Color::Color(50, 0, 25));
	str.setPosition(800, 202); str.setFillColor(Color::Color(50, 0, 25));
	dex.setPosition(800, 254); dex.setFillColor(Color::Color(50, 0, 25));
	con.setPosition(800, 306); con.setFillColor(Color::Color(50, 0, 25));
	wis.setPosition(800, 358); wis.setFillColor(Color::Color(50, 0, 25));
	intel.setPosition(800, 410); intel.setFillColor(Color::Color(50, 0, 25));
	cha.setPosition(800, 462); cha.setFillColor(Color::Color(50, 0, 25));
	hp.setPosition(800, 514); hp.setFillColor(Color::Color(50, 0, 25));
	lev.setPosition(800, 566); lev.setFillColor(Color::Color(50, 0, 25));
	/////обои/////
	Image bg;
	bg.loadFromFile("Image/Background/Game.jpg");
	Texture bgr, pl, play1;
	bgr.loadFromImage(bg);
	Sprite sbg;
	sbg.setTexture(bgr);
	////стрелки/////
	Texture left, right, left2;
	left.loadFromFile("Image/Background/left.png"); right.loadFromFile("Image/Background/right.png");
	Sprite l1, l2, l3, l4, l5, l6, l7, l8, r1, r2, r3, r4, r5, r6, r7, r8;
	l1.setTexture(left); r1.setTexture(right);
	l2.setTexture(left); r2.setTexture(right);
	l3.setTexture(left); r3.setTexture(right);
	l4.setTexture(left); r4.setTexture(right);
	l5.setTexture(left); r5.setTexture(right);
	l6.setTexture(left); r6.setTexture(right);
	l7.setTexture(left); r7.setTexture(right);
	l8.setTexture(left); r8.setTexture(right);
	l1.setPosition(1100, 90); r1.setPosition(1200, 90);
	l2.setPosition(1100, 202); r2.setPosition(1200, 202);
	l3.setPosition(1100, 254); r3.setPosition(1200, 254);
	l4.setPosition(1100, 306); r4.setPosition(1200, 306);
	l5.setPosition(1100, 358); r5.setPosition(1200, 358);
	l6.setPosition(1100, 410); r6.setPosition(1200, 410);
	l7.setPosition(1100, 462); r7.setPosition(1200, 462);
	l8.setPosition(1100, 566); r8.setPosition(1200, 566);
	Player p;
	p.id = 0;
	/////остальное//////
	Music music;
	music.openFromFile("01 Sacred Worlds.ogg");
	music.play();
	music.setLoop(true);
	ostringstream sdice, sstr, sdex, scon, swis, sint, scha, slev, sclas, shp;
	int nstr = 3, ndex = 3, ncon = 3, nwis = 3, nint = 3, ncha = 3, nlev = 0, nclas = 0, nhp = p.Health(0);
	bool isStat = 1;
	int dice = rand() % 16 + 75;
	int xdice = dice - 18;
	Vector2i localposition = Mouse::getPosition(window);
	Event e;
	while (isStat)
	{
		exit.setFillColor(Color::Color(50, 0, 25));
		play.setFillColor(Color::Color(50, 0, 25));
		roll.setFillColor(Color::Color(50, 0, 25));
		localposition = Mouse::getPosition(window);
		l1.setColor(Color::White);
		r1.setColor(Color::White);
		l2.setColor(Color::White);
		r2.setColor(Color::White);
		l3.setColor(Color::White);
		r3.setColor(Color::White);
		l4.setColor(Color::White);
		r4.setColor(Color::White);
		l5.setColor(Color::White);
		r5.setColor(Color::White);
		l6.setColor(Color::White);
		r6.setColor(Color::White);
		l7.setColor(Color::White);
		r7.setColor(Color::White);
		l8.setColor(Color::White);
		r8.setColor(Color::White);
		slev.str("");
		sdice.str("");
		sclas.str("");
		sstr.str("");
		sdex.str("");
		scon.str("");
		swis.str("");
		shp.str("");
		sint.str("");
		scha.str("");
		////стрелки/////
		if (IntRect(1100, 90, 70, 42).contains(Mouse::getPosition(window)))
		{
			l1.setColor(Color::Black);
		}
		if (IntRect(1200, 90, 70, 42).contains(Mouse::getPosition(window)))
		{
			r1.setColor(Color::Black);
		}
		if (IntRect(1100, 202, 70, 42).contains(Mouse::getPosition(window)))
		{
			l2.setColor(Color::Black);
		}
		if (IntRect(1200, 202, 70, 42).contains(Mouse::getPosition(window)))
		{
			r2.setColor(Color::Black);
		}
		if (IntRect(1100, 254, 70, 42).contains(Mouse::getPosition(window)))
		{
			l3.setColor(Color::Black);
		}
		if (IntRect(1200, 254, 70, 42).contains(Mouse::getPosition(window)))
		{
			r3.setColor(Color::Black);
		}
		if (IntRect(1100, 306, 70, 42).contains(Mouse::getPosition(window)))
		{
			l4.setColor(Color::Black);
		}
		if (IntRect(1200, 306, 70, 42).contains(Mouse::getPosition(window)))
		{
			r4.setColor(Color::Black);
		}
		if (IntRect(1100, 358, 70, 42).contains(Mouse::getPosition(window)))
		{
			l5.setColor(Color::Black);
		}
		if (IntRect(1200, 358, 70, 42).contains(Mouse::getPosition(window)))
		{
			r5.setColor(Color::Black);
		}
		if (IntRect(1100, 410, 70, 42).contains(Mouse::getPosition(window)))
		{
			l6.setColor(Color::Black);
		}
		if (IntRect(1200, 410, 70, 42).contains(Mouse::getPosition(window)))
		{
			r6.setColor(Color::Black);
		}
		if (IntRect(1100, 462, 70, 42).contains(Mouse::getPosition(window)))
		{
			l7.setColor(Color::Black);
		}
		if (IntRect(1200, 462, 70, 42).contains(Mouse::getPosition(window)))
		{
			r7.setColor(Color::Black);
		}
		if (IntRect(1100, 566, 70, 42).contains(Mouse::getPosition(window)))
		{
			l8.setColor(Color::Black);
		}
		if (IntRect(1200, 566, 70, 42).contains(Mouse::getPosition(window)))
		{
			r8.setColor(Color::Black);
		}
		///////остальное/////
		if (IntRect(100, 650, 100, 60).contains(Mouse::getPosition(window)))
		{
			exit.setFillColor(Color::Yellow);
		}
		if (IntRect(1100, 650, 100, 50).contains(Mouse::getPosition(window)))
		{
			play.setFillColor(Color::Yellow);
		}
		if (IntRect(800, 150, 150, 40).contains(Mouse::getPosition(window)))
		{
			roll.setFillColor(Color::Yellow);
		}
		while (window.pollEvent(e))
		{
			////стрелки/////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 202 && localposition.y <= 244)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nstr > 3 && xdice <= dice)
						{
							nstr--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 202 && localposition.y <= 244)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nstr < 20 && xdice > 0 && xdice <= dice)
						{
							nstr++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 254 && localposition.y <= 296)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ndex > 3 && xdice <= dice)
						{
							ndex--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 254 && localposition.y <= 296)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ndex < 20 && xdice > 0 && xdice <= dice)
						{
							ndex++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 306 && localposition.y <= 348)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncon > 3 && xdice <= dice)
						{
							ncon--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 306 && localposition.y <= 348)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncon < 20 && xdice > 0 && xdice <= dice)
						{
							ncon++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 358 && localposition.y <= 400)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nwis > 3 && xdice <= dice)
						{
							nwis--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 358 && localposition.y <= 400)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nwis < 20 && xdice > 0 && xdice <= dice)
						{
							nwis++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 410 && localposition.y <= 452)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nint > 3 && xdice <= dice)
						{
							nint--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 410 && localposition.y <= 452)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nint < 20 && xdice > 0 && xdice <= dice)
						{
							nint++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 462 && localposition.y <= 504)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncha > 3 && xdice <= dice)
						{
							ncha--;
							xdice++;
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 462 && localposition.y <= 504)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (ncha < 20 && xdice > 0 && xdice <= dice)
						{
							ncha++;
							xdice--;
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 90 && localposition.y <= 132)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nclas > 0)
						{
							nclas--;
							p.id = nclas;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 90 && localposition.y <= 132)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nclas < 6)
						{
							nclas++;
							p.id = nclas;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			////////////////////
			if (localposition.x >= 1100 && localposition.x <= 1170 && localposition.y >= 566 && localposition.y <= 608)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nlev > 0)
						{
							nlev--;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			if (localposition.x >= 1200 && localposition.x <= 1270 && localposition.y >= 566 && localposition.y <= 608)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						if (nlev < 20)
						{
							nlev++;
							nhp = p.Health(nlev);
						}
					}
				}
			}
			///////////////////////
			////остальное/////
			if (localposition.x >= 100 && localposition.x <= 200 && localposition.y >= 650 && localposition.y <= 710)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						isStat = 0;
						music.stop();
						window.close();
						return;
					}
				}
			}
			if (localposition.x >= 1100 && localposition.x <= 1200 && localposition.y >= 650 && localposition.y <= 700)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						isStat = 0;
						music.stop();
						;
					}
				}
			}
			if (localposition.x >= 800 && localposition.x <= 950 && localposition.y >= 150 && localposition.y <= 190)
			{
				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)
					{
						dice = rand() % 16 + 75;
						xdice = dice - 18;
						nstr = 3;
						ndex = 3;
						ncon = 3;
						nwis = 3;
						nint = 3;
						ncha = 3;
					}
				}
			}
		}
		//p.id = nclas;
		sdice << dice;
		slev << nlev;
		sclas << p.name[nclas];
		sstr << nstr;
		sdex << ndex;
		scon << ncon;
		swis << nwis;
		shp << nhp;
		sint << nint;
		scha << ncha;
		per.setString("Class: " + sclas.str());
		lev.setString("Level: " + slev.str());
		roll.setString("Die Roll: " + sdice.str());
		str.setString("Strength: " + sstr.str());
		dex.setString("Dexterity: " + sdex.str());
		con.setString("Constitution: " + scon.str());
		wis.setString("Wisdom: " + swis.str());
		hp.setString("Health: " + shp.str());
		intel.setString("Intelligence: " + sint.str());
		cha.setString("Charisma: " + scha.str());
		window.draw(sbg);
		window.draw(player);
		window.draw(play);
		window.draw(exit);
		window.draw(per);
		window.draw(roll);
		window.draw(str);
		window.draw(dex);
		window.draw(con);
		window.draw(wis);
		window.draw(intel);
		window.draw(cha);
		window.draw(hp);
		window.draw(lev);
		window.draw(l1); window.draw(r1);
		window.draw(l2); window.draw(r2);
		window.draw(l3); window.draw(r3);
		window.draw(l4); window.draw(r4);
		window.draw(l5); window.draw(r5);
		window.draw(l6); window.draw(r6);
		window.draw(l7); window.draw(r7);
		window.draw(l8); window.draw(r8);
		window.display();
	}
	p.set(nstr, ndex, ncon, nwis, nint, ncha, nhp, nclas, nlev);
	//if (gaming == 1)
		//game1(window, p1, p);
	if (gaming == 2)
		game2(window, p1, p);
}
////игрок пр игрока////
void game2(RenderWindow &window, Player &p1, Player &p2)
{
	////поле битвы////
	srand(time(NULL));
	int x = rand() % 23;
	string s1[23] = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23" };
	string str1, str2;
	Image map_im;
	map_im.loadFromFile("Image/Map/BG" + s1[x] + ".png");
	Texture map;
	map.loadFromImage(map_im);
	Sprite s_map;
	s_map.setTexture(map);
	////текст////
	Font f;
	f.loadFromFile("Gothic.otf");
	Text output("Result: ", f, 30), roun("Round", f, 40);
	output.setPosition(350, 710); output.setFillColor(Color::Color(150, 150, 0));
	roun.setPosition(500, 25); roun.setFillColor(Color::Color(50, 0, 0));
	///////анимация///////
	Texture t1, t2;
	Texture t11, t12, t13, t14, t21, t22, t23, t24;
	t11.loadFromFile("Image/Sprite/" + p1.obj1[p1.id]); t21.loadFromFile("Image/Sprite/" + p2.obj1[p2.id]);
	t12.loadFromFile("Image/Sprite/" + p1.obj2[p1.id]); t22.loadFromFile("Image/Sprite/" + p2.obj2[p2.id]);
	t13.loadFromFile("Image/Sprite/" + p1.obj3[p1.id]); t23.loadFromFile("Image/Sprite/" + p2.obj3[p2.id]);
	t14.loadFromFile("Image/Sprite/" + p1.obj4[p1.id]); t24.loadFromFile("Image/Sprite/" + p2.obj4[p2.id]);
	Sprite a11, a12, a13, a14, a21, a22, a23, a24;
	a11.setTexture(t11); a24.setTexture(t21);
	a14.setTexture(t12); a24.setTexture(t22);
	a14.setTexture(t13); a24.setTexture(t23);
	a14.setTexture(t14); a24.setTexture(t24);
	a11.setTextureRect(IntRect(p1.X1[p1.id], p1.Y1[p1.id], p1.width1[p1.id], p1.heigth1[p1.id])); a11.setPosition(50, 350);
	a21.setTextureRect(IntRect(p2.X1[p2.id], p2.Y1[p2.id], p2.width1[p2.id], p2.heigth1[p2.id])); a21.setPosition(1200, 350); a21.setScale(-1, 1);
	a12.setTextureRect(IntRect(p1.X2[p1.id], p1.Y2[p1.id], p1.width2[p1.id], p1.heigth2[p1.id])); a12.setPosition(50, 350);
	a22.setTextureRect(IntRect(p2.X2[p2.id], p2.Y2[p2.id], p2.width2[p2.id], p2.heigth2[p2.id])); a22.setPosition(1200, 350); a22.setScale(-1, 1);
	a13.setTextureRect(IntRect(p1.X3[p1.id], p1.Y3[p1.id], p1.width3[p1.id], p1.heigth3[p1.id])); a13.setPosition(50, 350);
	a23.setTextureRect(IntRect(p2.X3[p2.id], p2.Y3[p2.id], p2.width3[p2.id], p2.heigth3[p2.id])); a23.setPosition(1200, 350); a23.setScale(-1, 1);
	a14.setTextureRect(IntRect(p1.X4[p1.id], p1.Y4[p1.id], p1.width4[p1.id], p1.heigth4[p1.id])); a14.setPosition(50, 350);
	a24.setTextureRect(IntRect(p2.X4[p2.id], p2.Y4[p2.id], p2.width4[p2.id], p2.heigth4[p2.id])); a24.setPosition(1200, 350); a24.setScale(-1, 1);
	float frame1 = 0, frame2 = 0, frame3 = 0, frame4 = 0;
	float distance12 = 1200, distance21 = 50;
	/////иконки/////
	Texture ata, mag, heal, ic, info, bookt, mt1, mt2, mt3, mt4, mt5, pt2, pt3;
	ata.loadFromFile("Image/Game/Atack.png");
	mag.loadFromFile("Image/Game/Magic.png");
	heal.loadFromFile("Image/Game/Heal.png");
	ic.loadFromFile("Image/Game/list.bmp");
	info.loadFromFile("Image/Game/info.png");
	bookt.loadFromFile("Image/Game/Book.png");
	mt1.loadFromFile("Image/Game/M1.png");
	mt2.loadFromFile("Image/Game/M2.png");
	mt3.loadFromFile("Image/Game/M3.png");
	mt4.loadFromFile("Image/Game/M4.png");
	mt5.loadFromFile("Image/Game/M5.png");
	pt2.loadFromFile("Image/Game/P2.png");
	pt3.loadFromFile("Image/Game/P3.png");
	Sprite a, m, h, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, inf, book, m1, m2, m3, m4, m5, p3, p4;
	a.setTexture(ata); a.setPosition(0, 678);
	m.setTexture(mag); m.setPosition(81, 678);
	h.setTexture(heal); h.setPosition(162, 678);
	inf.setTexture(info); inf.setPosition(243, 678);
	i1.setTexture(ic); i1.setPosition(324, 678);
	i2.setTexture(ic); i2.setPosition(424, 678);
	i3.setTexture(ic); i3.setPosition(524, 678);
	i4.setTexture(ic); i4.setPosition(624, 678);
	i5.setTexture(ic); i5.setPosition(724, 678);
	i6.setTexture(ic); i6.setPosition(824, 678);
	i7.setTexture(ic); i7.setPosition(924, 678);
	i8.setTexture(ic); i8.setPosition(1024, 678);
	i9.setTexture(ic); i9.setPosition(1124, 678);
	i10.setTexture(ic); i10.setPosition(1224, 678);
	i11.setTexture(ic); i11.setPosition(1324, 678);
	book.setTexture(bookt); book.setPosition(395, 190);
	m1.setTexture(mt1); m1.setPosition(475, 220);
	m2.setTexture(mt2); m2.setPosition(553, 220);
	m3.setTexture(mt3); m3.setPosition(631, 220);
	p3.setTexture(pt2); p3.setPosition(553, 220);
	p4.setTexture(pt3); p4.setPosition(631, 220);
	m4.setTexture(mt4); m4.setPosition(475, 280);
	m5.setTexture(mt5); m5.setPosition(553, 280);
	////////остальное////////
	Music music;
	music.openFromFile("03. Herr Mannelig.ogg");
	music.play();
	music.setLoop(true);
	int r = 1, magic = 0, nres = -1;
	bool isGame = 1, isBook = 1, isInf = 1, res;
	ostringstream sr, s;
	Vector2i localposition = Mouse::getPosition(window);
	Event e;
	Clock clock;
	cout << p2.num_kadr3[p2.id];
	cout << p1.num_kadr3[p1.id];
	while (isGame)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		sr.str("");
		s.str("");
		if ((p1.HP > 0) && (p2.HP > 0))
		{
			/////первым атакует игрок 1///
			if (p1.speed[p1.id] >= p2.speed[p2.id])
			{
				while (window.pollEvent(e))
				{
					//////иконки////
					////атака////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::A)
						{
							nres = 0;
							cout << "atacked";
							if (p1.id == 3 || p1.id >= 5)
							{
								while (frame1 <= p1.num_kadr4[p1.id])
								{
									frame1 += 0.001;
									a14.setTextureRect(IntRect(p1.width4[p1.id] * int(frame1), p1.Y4[p1.id], p1.width4[p1.id], p1.heigth4[p1.id]));
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a14);
									window.draw(a24);
									window.display();
								}
								while (distance21 <= 1020)
								{
									frame3 += 0.1;
									if (frame1 > p1.num_kadr1[p1.id])
										frame1 -= p1.num_kadr1[p1.id];
									a11.setTextureRect(IntRect(p1.width1[p1.id] * int(frame3), p1.Y1[p1.id], p1.width1[p1.id], p1.heigth1[p1.id]));
									a11.move(1, 0);
									distance21 += 0.1;
									cout << distance21 << " ";
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a11);
									window.draw(a24);
									window.display();
								}
							}
							else
							{
								while (distance21 <= 1020)
								{
									frame1 += 0.1;
									if (frame1 > p1.num_kadr4[p1.id])
										frame1 -= p1.num_kadr4[p1.id];
									a14.setTextureRect(IntRect(p1.width4[p1.id] * int(frame1), p1.Y4[p1.id], p1.width4[p1.id], p1.heigth4[p1.id]));
									a14.move(1, 0);
									distance21 += 1;
									cout << distance21 << " ";
								}
								window.clear();
								window.draw(s_map);
								window.draw(a);
								window.draw(m);
								window.draw(h);
								window.draw(inf);
								window.draw(i1);
								window.draw(i2);
								window.draw(i3);
								window.draw(i4);
								window.draw(i5);
								window.draw(i6);
								window.draw(i7);
								window.draw(i8);
								window.draw(i9);
								window.draw(i10);
								window.draw(i11);
								window.draw(output);
								window.draw(roun);
								window.draw(a14);
								window.draw(a24);
								window.display();
								while (frame3 <= p1.num_kadr1[p1.id])
								{
									s.str("");
									frame3 += 0.01;
									frame2 += 0.01;
									a11.setTextureRect(IntRect(p1.width1[p1.id] * int(frame3), p1.Y1[p1.id], p1.width1[p1.id], p1.heigth1[p1.id]));
									a23.setTextureRect(IntRect(p2.width3[p2.id] * int(frame2) + p2.width3[p2.id], p2.Y3[p2.id], -p2.width3[p2.id], p2.heigth3[p2.id]));
									a23.setPosition(1200, 350);
									a11.setPosition(distance21, 350);
									cout << frame3 << " ";
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a11);
									window.draw(a23);
									window.display();
								}
							}
							frame1 = 0;
							frame3 = 0;
							frame2 = 0;
							distance12 = 1200; distance21 = 50;
						}
					}
					/////магия////
					if (p1.id == 5 || p1.id == 6)
					{
						if (e.type == Event::KeyPressed)
						{
							if (e.key.code == Keyboard::M)
							{
								cout << "m" << endl;
								while (isBook)
								{
									while (window.pollEvent(e))
									{
										if (e.type == Event::KeyPressed)
										{
											if (e.key.code == Keyboard::M || e.key.code == Keyboard::Escape)
											{
												magic = 0;
												isBook = 0;
											}
											if (e.key.code == Keyboard::Q)
											{
												cout << "q";
												if (p1.all_elder[0] != 0)
												{
													magic = 1;
													nres = 1;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::W)
											{
												cout << "w";
												if (p1.all_elder[1] != 0)
												{
													magic = 2;
													nres = 2;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::E)
											{
												cout << "e";
												if (p1.all_elder[2] != 0)
												{
													magic = 3;
													nres = 3;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::R)
											{
												cout << "r";
												if (p1.all_elder[3] != 0)
												{
													magic = 4;
													nres = 4;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::T)
											{
												cout << "t";
												if (p1.all_elder[4] != 0)
												{
													magic = 5;
													nres = 5;
													isBook = 0;
												}
											}
										}
									}
									window.draw(book);
									window.draw(m1);
									if (p1.id == 5)
									{
										window.draw(m2); window.draw(m3);
									}
									if (p1.id == 6)
									{
										window.draw(p3);
										window.draw(p4);
									}
									window.draw(m4);
									window.draw(m5);
									window.display();
								}
							}
						}
					}
					/////лечение//////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::H)
						{
							nres = 6;
						}
					}
					//////информация//////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::I)
						{
							Texture help; help.loadFromFile("Image/Game/Book.png");
							Sprite hel; hel.setTexture(help); hel.setPosition(395, 190);
							Text hp("", f, 40);
							hp.setPosition(500, 225); hp.setFillColor(Color::Black);
							ostringstream shp1, shp2;
							while (isInf)
							{
								while (window.pollEvent(e))
								{
									if (e.type == Event::KeyPressed)
										if (e.key.code == Keyboard::Escape)
											isInf = 0;
									shp1.str(""); shp2.str("");
									shp1 << p1.HP << "           ";
									shp2 << p2.HP;
									hp.setString("HP: " + shp1.str() + shp2.str());
									window.draw(hel);
									window.draw(hp);
									window.display();
								}
							}
						}
					}
					/////выход/////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::Escape)
						{
							isGame = 0;
							music.stop();
							window.close();
							return;
						}
					}
				}
				if (nres == 0)
				{
					if (p1.atack() > p2.defend())
					{
						x = p1.damage();
						s << "damage is " << x << "to Player 2";
						p2.HP -= x;
					}
					else s << "Player 2 defend";
					nres = -1;
				}
				if (nres > 0 && nres < 6)
				{
					if (p1.id == 5)
					{
						x = p1.magic_atack(nres);
						if (x > p2.defend())
						{
							s << "damage is " << x << "to Player 2";
							p2.HP -= x;
						}
						else s << "Player 2 defend";
					}
					if (p1.id == 6)
					{
						x = p1.magic_atack_priest(nres);
						if (x > p2.defend())
						{
							s << "damage is " << x << "to Player 2";
							p2.HP -= x;
						}
						else s << "Player 2 defend";
					}
					nres = -1;
				}
				if (nres == 6)
				{
					x = p1.heal();
					s << "Player 1 got HP";
					p1.HP += x;
					nres = -1;
				}
				///////игрок 2//////
				while (window.pollEvent(e))
				{
					//////иконки////
					////атака////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::A)
						{
							nres = 0;
							cout << "atacked";
							if (p2.id == 3 || p2.id >= 5)
							{
								while (frame1 <= p2.num_kadr4[p2.id])
								{
									frame1 += 0.001;
									a24.setTextureRect(IntRect(p2.width4[p2.id] * int(frame1) + p2.width4[p2.id], p2.Y4[p2.id], -p2.width4[p2.id], p2.heigth4[p2.id]));
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a14);
									window.draw(a24);
									window.display();
								}
								while (distance12 >=100)
								{
									frame3 += 0.1;
									if (frame1 > p2.num_kadr1[p2.id])
										frame1 -= p2.num_kadr1[p2.id];
									a21.setTextureRect(IntRect(p2.width1[p2.id] * int(frame3) + p2.width1[p2.id], p2.Y1[p2.id], p2.width1[p2.id], p2.heigth1[p2.id]));
									a21.move(-1, 0);
									distance12 -= 0.1;
									cout << distance12 << " ";
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a14);
									window.draw(a21);
									window.display();
								}
							}
							else
							{
								while (distance12 >= 100)
								{
									frame1 += 0.1;
									if (frame1 > p2.num_kadr4[p2.id])
										frame1 -= p2.num_kadr4[p2.id];
									a24.setTextureRect(IntRect(p2.width4[p1.id] * int(frame1) + p2.width4[p2.id], p2.Y4[p2.id], p2.width4[p2.id], p2.heigth4[p2.id]));
									a24.move(-1, 0);
									distance12 -= 1;
									cout << distance12 << " ";
								}
								window.clear();
								window.draw(s_map);
								window.draw(a);
								window.draw(m);
								window.draw(h);
								window.draw(inf);
								window.draw(i1);
								window.draw(i2);
								window.draw(i3);
								window.draw(i4);
								window.draw(i5);
								window.draw(i6);
								window.draw(i7);
								window.draw(i8);
								window.draw(i9);
								window.draw(i10);
								window.draw(i11);
								window.draw(output);
								window.draw(roun);
								window.draw(a14);
								window.draw(a24);
								window.display();
								while (frame3 <= p2.num_kadr1[p2.id])
								{
									s.str("");
									frame3 += 0.01;
									frame2 += 0.01;
									a21.setTextureRect(IntRect(p2.width1[p2.id] * int(frame3) + p2.width1[p2.id], p2.Y1[p2.id], -p2.width1[p2.id], p2.heigth1[p2.id]));
									a13.setTextureRect(IntRect(p1.width3[p1.id] * int(frame2), p1.Y3[p1.id], p1.width3[p1.id], p1.heigth3[p1.id]));
									a13.setPosition(50, 350);
									a21.setPosition(distance12, 350);
									cout << frame3 << " ";
									window.clear();
									window.draw(s_map);
									window.draw(a);
									window.draw(m);
									window.draw(h);
									window.draw(inf);
									window.draw(i1);
									window.draw(i2);
									window.draw(i3);
									window.draw(i4);
									window.draw(i5);
									window.draw(i6);
									window.draw(i7);
									window.draw(i8);
									window.draw(i9);
									window.draw(i10);
									window.draw(i11);
									window.draw(output);
									window.draw(roun);
									window.draw(a13);
									window.draw(a21);
									window.display();
								}
							}
							frame1 = 0;
							frame3 = 0;
							frame2 = 0;
							distance12 = 1200; distance21 = 50;
						}
					}
					/////магия////
					if (p2.id == 5 || p2.id == 6)
					{
						if (e.type == Event::KeyPressed)
						{
							if (e.key.code == Keyboard::M)
							{
								cout << "m" << endl;
								while (isBook)
								{
									while (window.pollEvent(e))
									{
										if (e.type == Event::KeyPressed)
										{
											if (e.key.code == Keyboard::M || e.key.code == Keyboard::Escape)
											{
												magic = 0;
												isBook = 0;
											}
											if (e.key.code == Keyboard::Q)
											{
												cout << "q";
												if (p2.all_elder[0] != 0)
												{
													magic = 1;
													nres = 1;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::W)
											{
												cout << "w";
												if (p2.all_elder[1] != 0)
												{
													magic = 2;
													nres = 2;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::E)
											{
												cout << "e";
												if (p2.all_elder[2] != 0)
												{
													magic = 3;
													nres = 3;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::R)
											{
												cout << "r";
												if (p2.all_elder[3] != 0)
												{
													magic = 4;
													nres = 4;
													isBook = 0;
												}
											}
											if (e.key.code == Keyboard::T)
											{
												cout << "t";
												if (p2.all_elder[4] != 0)
												{
													magic = 5;
													nres = 5;
													isBook = 0;
												}
											}
										}
									}
									window.draw(book);
									window.draw(m1);
									if (p2.id == 5)
									{
										window.draw(m2); window.draw(m3);
									}
									if (p2.id == 6)
									{
										window.draw(p3);
										window.draw(p4);
									}
									window.draw(m4);
									window.draw(m5);
									window.display();
								}
							}
						}
					}
					/////лечение//////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::H)
						{
							nres = 6;
						}
					}
					//////информация//////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::I)
						{
							Texture help; help.loadFromFile("Image/Game/Book.png");
							Sprite hel; hel.setTexture(help); hel.setPosition(395, 190);
							Text hp("", f, 40);
							hp.setPosition(500, 225); hp.setFillColor(Color::Black);
							ostringstream shp1, shp2;
							while (isInf)
							{
								while (window.pollEvent(e))
								{
									if (e.type == Event::KeyPressed)
										if (e.key.code == Keyboard::Escape)
											isInf = 0;
									shp1.str(""); shp2.str("");
									shp1 << p1.HP << "           ";
									shp2 << p2.HP;
									hp.setString("HP: " + shp1.str() + shp2.str());
									window.draw(hel);
									window.draw(hp);
									window.display();
								}
							}
						}
					}
					/////выход/////
					if (e.type == Event::KeyPressed)
					{
						if (e.key.code == Keyboard::Escape)
						{
							isGame = 0;
							music.stop();
							window.close();
							return;
						}
					}
				}
				if (nres == 0)
				{
					if (p2.atack() > p1.defend())
					{
						x = p2.damage();
						s << "damage is " << x << "to Player 1";
						p1.HP -= x;
					}
					else s << "Player 1 defend";
					nres = -1;
				}
				if (nres > 0 && nres < 6)
				{
					if (p2.id == 5)
					{
						x = p2.magic_atack(nres);
						if (x > p1.defend())
						{
							s << "damage is " << x << "to Player 1";
							p1.HP -= x;
						}
						else s << "Player 1 defend";
					}
					if (p2.id == 6)
					{
						x = p2.magic_atack_priest(nres);
						if (x > p1.defend())
						{
							s << "damage is " << x << "to Player 1";
							p1.HP -= x;
						}
						else s << "Player 1 defend";
					}
					nres = -1;
				}
				if (nres == 6)
				{
					x = p2.heal();
					s << "Player 1 got HP";
					p2.HP += x;
					nres = -1;
				}
			}
			else
			{

			}
		}
		if (p1.HP <= 0)
		{
			s.str("");
			s << "Player 1 is dead";
		}
		if (p2.HP <= 0)
		{
			s.str("");
			s << "Player 2 is dead";
		}
		sr << r;
		roun.setString("Round: " + sr.str());
		output.setString("Result: " + s.str());
		//r++;
		window.draw(s_map);
		window.draw(a);
		window.draw(m);
		window.draw(h);
		window.draw(inf);
		window.draw(i1);
		window.draw(i2);
		window.draw(i3);
		window.draw(i4);
		window.draw(i5);
		window.draw(i6);
		window.draw(i7);
		window.draw(i8);
		window.draw(i9);
		window.draw(i10);
		window.draw(i11);
		window.draw(output);
		window.draw(roun);
		window.draw(a14);
		window.draw(a24);
		window.display();
	}
}