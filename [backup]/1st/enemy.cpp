#include "enemy.h"

Enemy enemy;

Enemy::Enemy() {
	mBox.x = 50;
	mBox.y = 200;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
	mCurrentHitPoints = 1517;
	mMaxHitPoints = 1776;
	mAttack = 1789;
	mSwordResistance = 1917;
	mGunResistance = 1939;
	mName = "Pancakes";
	mDescription = "Description.";
	mDeathMessage = "Fried Onion";
	gEnemyTexture = NULL;
	enemyIdNumber = 0;
}

SDL_Rect Enemy::getBox() {
	return mBox;
}

int Enemy::getCrrPoints() {
	return mCurrentHitPoints;
}

int Enemy::getAttack() {
	return mAttack;
}

int Enemy::getSwordResistance() {
	return mSwordResistance;
}

int Enemy::getGunResistance() {
	return mGunResistance;
}

std::string Enemy::getName() {
	return mName;
}

std::string Enemy::getDesc() {
	return mDescription;
}

std::string Enemy::getDeathMessage() {
	return mDeathMessage;
}

void Enemy::takeDamage(int dmg) {
	mCurrentHitPoints -= dmg;
}

void Enemy::setAttributes(int crrhp, int maxhp, int att, int swr, int gunr, std::string name, std::string desc, std::string deathMessage, LTexture* gTexture) {
	mCurrentHitPoints = crrhp;
	mMaxHitPoints = maxhp;
	mAttack = att;
	mSwordResistance = swr;
	mGunResistance = gunr;
	mName = name;
	mDescription = desc;
	mDeathMessage = deathMessage;
	gEnemyTexture = gTexture;
}

void Ability::setValues(int dmg, std::string name, std::string msg) {
	mDamage = dmg; mName = name; mMessage = msg;
}

void Enemy::setSkills(int dmg1, int dmg2, int dmg3, int dmg4, std::string name1, std::string name2, std::string name3, std::string name4, std::string msg1, std::string msg2, std::string msg3, std::string msg4) {
	ability1.setValues(dmg1, name1, msg1);
	ability2.setValues(dmg2, name2, msg2);
	ability3.setValues(dmg3, name3, msg3);
	ability4.setValues(dmg4, name4, msg4);
}

void Enemy::chooseEnemy(int idNumber) {
	enemyIdNumber = idNumber;
	switch(idNumber) {
	}
}

SDL_Rect Enemy::setBox(int x, int y) {
	mBox.x = x; mBox.y = y;
}

void Enemy::moveToXY(int x, int y, int speed) {
	if(mBox.x != x && mBox.x < x) {
		mBox.x += speed;
		if(mBox.x > x)
			mBox.x -= mBox.x - x;
	} else if(mBox.x != x && mBox.x > x) {
		mBox.x -= speed;
		if(mBox.x < x)
			mBox.x -= mBox.x - x;
	} else if(mBox.y != y && mBox.y < y) {
		mBox.y += speed;
		if(mBox.y > y)
			mBox.y -= mBox.x - x;
	} else if(mBox.y != y && mBox.y > y) {
		mBox.y -= speed;
		if(mBox.y < y)
			mBox.y -= mBox.x - x;
	}

	if(mBox.x == x && mBox.y == y) {
		enemyMove = 0;
		enemyHasMoved = 1;
	}
}
