#pragma once
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib, "Windowscodecs.lib" )
#include <graphics.h>
#include<cmath>
#include<dinput.h>
#include<windows.h>
#include<d2d1.h>
#include<D2d1helper.h>
#include<wincodec.h>
#include<vector>
#include<sstream>
#include<random>
#include<stack>
using namespace std;

class Point
{
public:
	Point(int x, int y):posx(x), posy(y){}
	Point();
	void setpos(int x, int y) { posx = x; posy = y; }
	int getposx() { return posx; }
	int getposy() { return posy; }
	int posx, posy;
	Point operator()(int _x, int _y) { posx = _x; posy = _y; return *this; }
};

class Magnitude
{
public:
	Magnitude(int x, int y):velx(x),vely(y){}
	Magnitude();
	void setpos(int x, int y) { velx = x; vely = y; }
	int getvelx() { return velx; }
	int getvely() { return vely; }
	int velx, vely;
};

class Ball
{
public:
	Ball(Point position, Magnitude velocity, int radius):pos(position), vel(velocity), r(radius){}
	Ball();
	void setpos(int x, int y) { pos.posx = x; pos.posy = y; }
	void setpos(Point postion) { pos = postion; }
	void setvelocity(int x, int y) { vel.velx = x; vel.vely = y; }
	void setvelocity(Magnitude velocity) { vel = velocity; }
	void setradius(int radius) { r = radius; }
	void setspeed();
	void action(float deltatime, int realwidth, int realheight, Ball* b, int i, int& c);
	void collision(Ball* anotherball);
	void collisionjudge(Ball* anotherball, int& c, float t);
	Ball& operator=(const Ball& b) {
		this->pos.posx = b.pos.posx;
		this->pos.posy = b.pos.posy;
		this->vel.velx = b.vel.velx;
		this->vel.vely = b.vel.vely;
		this->r = b.r;
		return *this;
	}
	bool operator==(const Ball& b) {
		if(this->pos.posx == b.pos.posx&&this->pos.posy == b.pos.posy&&this->vel.velx == b.vel.velx&&this->vel.vely == b.vel.vely&&this->r == b.r)
			return true;
		return false;
	}

	Point pos;
	Magnitude vel;
	int r;
};
//
//class QuadTree
//{
//public:
//	void insert(Ball* ball);
//	void reinsert(Ball* ball);
//	void divide();
//	void searchcollisionjudge(Ball* neededBall);
//};

//
//class GameTimer
//{
//public:
//	GameTimer() :mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
//		mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
//	{
//		__int64 countsPerSec;
//		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
//		mSecondsPerCount = 1.0 / (double)countsPerSec;
//	};
//	~GameTimer() {};
//	float GameTime()const;//in seconds
//	float DeltaTime()const//in seconds
//	{
//		return (float)mDeltaTime;
//	}
//	void Reset()//在消息循环之前调用
//	{
//		__int64 currtime;
//		QueryPerformanceCounter((LARGE_INTEGER*)&currtime);
//		mBaseTime = currtime;
//		mPrevTime = currtime;
//		mStopTime = 0;
//		mStopped = false;
//	}
//	void Tick() //每个帧调用一次
//	{
//		if (mStopped)
//		{
//			mDeltaTime = 0.0;
//			return;
//		}
//		__int64	currTime;
//		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
//		mCurrTime = currTime;
//		//计算间隔时间
//		mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;
//		//为下一次计算做准备
//		mPrevTime = mCurrTime;
//		if (mDeltaTime < 0.0)
//		{
//			mDeltaTime = 0.0;
//		}
//	}
//	float TotalTime()const
//	{
//		// If we are stopped, do not count the time that has passed since we stopped.
//		// Moreover, if we previously already had a pause, the distance 
//		// mStopTime - mBaseTime includes paused time, which we do not want to count.
//		// To correct this, we can subtract the paused time from mStopTime:  
//		//
//		//                     |<--paused time-->|
//		// ----*---------------*-----------------*------------*------------*------> time
//		//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime
//
//		if (mStopped)
//		{
//			return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
//		}
//
//		// The distance mCurrTime - mBaseTime includes paused time,
//		// which we do not want to count.  To correct this, we can subtract 
//		// the paused time from mCurrTime:  
//		//
//		//  (mCurrTime - mPausedTime) - mBaseTime 
//		//
//		//                     |<--paused time-->|
//		// ----*---------------*-----------------*------------*------> time
//		//  mBaseTime       mStopTime        startTime     mCurrTime
//
//		else
//		{
//			return (float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
//		}
//	}
//	void Start()//取消暂停时调用
//	{
//		__int64 startTime;
//		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
//
//
//		// Accumulate the time elapsed between stop and start pairs.
//		//
//		//                     |<-------d------->|
//		// ----*---------------*-----------------*------------> time
//		//  mBaseTime       mStopTime        startTime     
//
//		if (mStopped)
//		{
//			mPausedTime += (startTime - mStopTime);
//
//			mPrevTime = startTime;
//			mStopTime = 0;
//			mStopped = false;
//		}
//	}
//	void Stop()//暂停时调用
//	{
//		if (!mStopped)
//		{
//			__int64 currTime;
//			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
//
//			mStopTime = currTime;
//			mStopped = true;
//		}
//	}
//private:
//	double mSecondsPerCount;
//	double mDeltaTime;
//	__int64 mBaseTime;
//	__int64 mPausedTime;
//	__int64 mStopTime;
//	__int64 mPrevTime;
//	__int64 mCurrTime;
//	bool mStopped;
//};





// The objects that we want stored in the quadtree

struct Node
{
	vector<Ball> vBall;
	Node():vBall(20, Ball()){}
	
};

// The main quadtree class
class Quad
{
	// Hold details of the boundary of this node
	Point topLeft;
	Point botRight;

	// Contains details of node
	Node* n;

	// Children of this tree
	Quad* topLeftTree;
	Quad* topRightTree;
	Quad* botLeftTree;
	Quad* botRightTree;

	Quad* parent;

	int flag;//1表示该层未满，0表示该层已满

public:
	Quad() :n(NULL), topLeftTree(NULL), topRightTree(NULL),
		botLeftTree(NULL), botRightTree(NULL), topLeft(Point(0, 0)), botRight(Point(0, 0)), flag(1) ,parent(NULL) {}

	Quad(Point topL, Point botR, Quad* p) :n(NULL), topLeftTree(NULL), topRightTree(NULL), 
		botLeftTree(NULL), botRightTree(NULL), topLeft(topL), botRight(botR), flag(1), parent(p) {}
		
	void insert(Ball* ball, vector<Ball>::iterator* del = NULL );
	/*Node* search(Point);*/
	bool inBoundary(Point p);
	void treecollisionjudge(Ball* b, int c, float t);
	void rebuild();
};
