#include "enemy.h"

Enemy::Enemy() {
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = 100;
	mBox.h = 100;
	mCurrentHitPoints = 1517;
	mMaxHitPoints = 1776;
	gEnemyTexture = NULL;
	enemyIdNumber = 0;
}

SDL_Rect Enemy::getBox() {
	return mBox;
}

int Enemy::getCrrPoints() {
	return mCurrentHitPoints;
}

void Enemy::takeDamage(int dmg) {
	mCurrentHitPoints -= dmg;
}

SDL_Rect Enemy::setBox(int x, int y) {
	mBox.x = x; mBox.y = y;
}

void Enemy::moveToXY(int x, int y, int speed) {
	if(mBox.x != x && mBox.y != y) {
		if(mBox.x > x && mBox.y > y) {
			mBox.x -= speed; mBox.y -= speed;
			if(mBox.x < x)
				mBox.x += mBox.x - x;
			if(mBox.y < y)
				mBox.y += mBox.y - y;
		} else if(mBox.x < x && mBox.y > y) {
			mBox.x += speed; mBox.y -= speed;
			if(mBox.x > x)
				mBox.x -= mBox.x - x;
			if(mBox.y < y)
				mBox.y += mBox.y - y;
		} else if(mBox.x > x && mBox.y < y) {
			mBox.x -= speed; mBox.y += speed;
			if(mBox.x < x)
				mBox.x += mBox.x - x;
			if(mBox.y > y)
				mBox.y -= mBox.y - y;
		} else if(mBox.x < x && mBox.y < y) {
			mBox.x += speed; mBox.y += speed;
			if(mBox.x > x)
				mBox.x -= mBox.x - x;
			if(mBox.y > y)
				mBox.y -= mBox.y - y;
		}
	} else if (mBox.x == x && mBox.y != y) {
		if(mBox.y > y) {
			mBox.y -= speed;
			if(mBox.y < y)
				mBox.y += mBox.y - y;
		} else if(mBox.y > y) {
			mBox.y -= speed;
			if(mBox.y < y)
				mBox.y += mBox.y - y;
		} else if(mBox.y < y) {
			mBox.y += speed;
			if(mBox.y > y)
				mBox.y -= mBox.y - y;
		} else if(mBox.y < y) {
			mBox.y += speed;
			if(mBox.y > y)
				mBox.y -= mBox.y - y;
		}
	} else if(mBox.x !=x && mBox.y == y) {
		if(mBox.x > x) {
			mBox.x -= speed;
			if(mBox.x < x)
				mBox.x += mBox.x - x;
		} else if(mBox.x > x) {
			mBox.x -= speed;
			if(mBox.x < x)
				mBox.x += mBox.x - x;
		} else if(mBox.x < x) {
			mBox.x += speed;
			if(mBox.x > x)
				mBox.x -= mBox.x - x;
		} else if(mBox.x < x) {
			mBox.x += speed;
			if(mBox.x > x)
				mBox.x -= mBox.x - x;
		}
	}
}

