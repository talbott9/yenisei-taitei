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
		void takeDamage();
		//int attack(BattleChara* battleLouis);
		void moveToXY(double x, double y, double speed);
		void doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Chara* hildegarde);
		bool moved; bool changeMove;
		int reachedTarget;
		double distanceX, distanceY, distance;
		int actionTicks; bool enemyDead;
		int randX, randY;
		int shotType;
		int pattern;
		double renderAngle;
		double targetX, targetY;
		double speedMod;
	private:
		int enemyIdNumber;
		SDL_Rect mBox;
		int mCurrentHitPoints;
		int mMaxHitPoints;
		LTexture* gEnemyTexture;
		double dx, dy;
		double posX, posY;
};

Enemy enemy1;
