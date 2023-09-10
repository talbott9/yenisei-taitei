const int ENEMY_BATTLE_ANIM_FRAMES = 1;
SDL_Rect gEnemyBattleClips[ENEMY_BATTLE_ANIM_FRAMES];

class Ability {
	public:
		void setValues(int dmg, std::string name, std::string msg);
	private:
		int mDamage;
		std::string mName;
		std::string mMessage;
};

class Enemy {
	public:
		static const int DOT_WIDTH = 130;
		static const int DOT_HEIGHT = 200;
		Enemy();
		SDL_Rect getBox();
		SDL_Rect setBox(int x, int y);
		SDL_Rect* currentClip;
		//void render(SDL_Rect& camera, BattleChara* battleLouis, SDL_Rect& textbox);
		int getCrrPoints();
		int getAttack();
		int getSwordResistance();
		int getGunResistance();
		std::string getName();
		std::string getDesc();
		std::string getDeathMessage();
		void setAttributes(int crrhp, int maxhp, int att, int swr, int gunr, std::string name, std::string desc, std::string deathMessage, LTexture* gTexture);
		void setSkills(int dmg1, int dmg2, int dmg3, int dmg4, std::string name1, std::string name2, std::string name3, std::string name4, std::string msg1, std::string msg2, std::string msg3, std::string msg4);
		void chooseEnemy(int idNumber);
		void takeDamage(int dmg);
		//int attack(BattleChara* battleLouis);
		void moveToXY(int x, int y, int speed);
	private:
		int enemyIdNumber;
		SDL_Rect mBox;
		int mCurrentHitPoints;
		int mMaxHitPoints;
		int mAttack;
		int mSwordResistance;
		int mGunResistance;
		std::string mName;
		std::string mDescription;
		std::string mDeathMessage;
		LTexture* gEnemyTexture;
		Ability ability1;
		Ability ability2;
		Ability ability3;
		Ability ability4;
};


