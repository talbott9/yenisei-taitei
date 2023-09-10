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

class Projectile; class Chara;

class Enemy {
	public:
		Enemy();
		SDL_Rect getBox();
		SDL_Rect setBox(int x, int y);
		SDL_Rect* currentClip;
		//void render(SDL_Rect& camera, BattleChara* battleLouis, SDL_Rect& textbox);
		int getCrrPoints();
		void chooseEnemy(int idNumber);
		void takeDamage(int dmg);
		//int attack(BattleChara* battleLouis);
		void moveToXY(int x, int y, int speed);
		void doThings(Projectile* projectile, Chara* hildegarde);
	private:
		int enemyIdNumber;
		SDL_Rect mBox;
		int mCurrentHitPoints;
		int mMaxHitPoints;
		LTexture* gEnemyTexture;
		int dx, dy;
};

Enemy enemy1;
