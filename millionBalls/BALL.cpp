#include"BALL.h"
#define V 4
#define x 2
#define limit 20            //单个节点存放ball数量



Ball::Ball()
{

}

void Ball::setspeed()
{
	//if (this->vel.velx == 0 && this->vel.vely == 0)
	//{
	//	vel.velx = rand() % V - V / 2;
	//	vel.vely = rand() % V - V / 2;
	//}
	//if (this->vel.velx > V)
	//{
	//	vel.velx = rand() % V - V / 2;
	//}
	//if (this->vel.velx > V)
	//{
	//	vel.vely = rand() % V - V / 2;
	//}
}

void Ball::action(float t, int width, int height,  Ball* spriteList, int i, int& c)
{
	spriteList[i].pos.posx += spriteList[i].vel.velx * t;
	spriteList[i].pos.posy += spriteList[i].vel.vely * t;
	if (spriteList[i].pos.posx + spriteList[i].vel.velx * t * x <= 0.0f + spriteList[i].r || spriteList[i].pos.posx + spriteList[i].vel.velx * t * x >= width - spriteList[i].r) { spriteList[i].vel.velx = -spriteList[i].vel.velx; if(spriteList[i].pos.posx + spriteList[i].vel.velx * t * (x+1) > 0.0f + spriteList[i].r && spriteList[i].pos.posx + spriteList[i].vel.velx * t * (x+1) < width - spriteList[i].r)++c; }
	if (spriteList[i].pos.posy + spriteList[i].vel.vely * t * x <= 0.0f + spriteList[i].r || spriteList[i].pos.posy + spriteList[i].vel.vely * t * x >= height - spriteList[i].r) { spriteList[i].vel.vely = -spriteList[i].vel.vely; if (spriteList[i].pos.posy + spriteList[i].vel.vely * t * (x + 1) > 0.0f + spriteList[i].r && spriteList[i].pos.posy + spriteList[i].vel.vely * t * (x + 1) < width - spriteList[i].r)++c; }
	//判断下一位置是否会碰边
	//并且防止小球在某一方向速度为0时刷碰撞数据
	for (int j = 0; j != i; ++j) {
		spriteList[i].collisionjudge(&spriteList[j], c, t);
	}
}

void Ball::collision(Ball* anotherball)
{
	float sin = (anotherball->pos.posy - this->pos.posy) / 
		sqrt(pow(anotherball->pos.posy - this->pos.posy, 2) + pow(anotherball->pos.posx - this->pos.posx, 2));
	float cos = (anotherball->pos.posx - this->pos.posx) /
		sqrt(pow(anotherball->pos.posy - this->pos.posy, 2) + pow(anotherball->pos.posx - this->pos.posx, 2));
	Ball temp = *anotherball;
	anotherball->vel.velx = cos * (this->vel.velx * cos + this->vel.vely * sin);
	anotherball->vel.vely = cos * (anotherball->vel.vely * cos - anotherball->vel.velx * sin) + 
		sin * (this->vel.velx * cos + this->vel.vely * sin);
	this->vel.velx = cos * (temp.vel.velx * cos + temp.vel.vely * sin);
	this->vel.vely = cos * (temp.vel.vely * cos - temp.vel.velx * sin) +
		sin * (temp.vel.velx * cos + temp.vel.vely * sin);

}

void Ball::collisionjudge(Ball* anotherball, int& c, float t)
{
	float dis2 = pow(this->pos.posx + this->vel.velx * t * x - anotherball->pos.posx - anotherball->vel.velx * t * x, 2)
		+ pow(this->pos.posy + this->vel.vely * t * x - anotherball->pos.posy + anotherball->vel.vely * t * x, 2);//计算对象为下一位置，防止粘连
	if(dis2 < pow(this->r, 2)) {
		++c;
		collision(anotherball);
	};

}

Magnitude::Magnitude()
{
}

Point::Point()
{
}


// Insert a node into the quadtree
void Quad::insert(Ball* ball, vector<Ball>::iterator* del)
{
    if (ball == NULL)
        return;

    // Current quad cannot contain it
    if (!inBoundary(ball->pos))//小球运动后，重塑树会用到
    {
        this->n->vBall.erase(*del);
        this->parent->insert(ball);
    }

    //如果该层未满，则插入，如果该层已满，则分裂
    if (this->n->vBall.size() < limit && flag)//flag为0时该层已满，但已被清空
    {
        this->n->vBall.push_back(*ball);
        return;
    }//该层未满
    else if(topLeftTree == NULL)
    {
        topLeftTree = new Quad(Point(topLeft.posx, (topLeft.posy + botRight.posy) / 2),
            Point((topLeft.posx + botRight.posx) / 2, botRight.posy), this);
        botLeftTree = new Quad(Point(topLeft.posx, (topLeft.posy + botRight.posy) / 2),
            Point((topLeft.posx + botRight.posx) / 2, botRight.posy), this);
        topRightTree = new Quad(Point((topLeft.posx + botRight.posx) / 2, topLeft.posy),
            Point(botRight.posx, (topLeft.posy + botRight.posy) / 2), this);
        botRightTree = new Quad(Point((topLeft.posx + botRight.posx) / 2, (topLeft.posy + botRight.posy) / 2),
            Point(botRight.posx, botRight.posy), this);

        vector<Ball>::iterator it;//声明一个迭代器，来访问vector容器
        for (it = this->n->vBall.begin(); it != this->n->vBall.end(); it++)
        {
            this->insert(&*it);
        }
        this->n->vBall.clear();
        flag = 1;
    }//该层已满

    if ((topLeft.posx + botRight.posx) / 2 >= ball->pos.posx)
    {
        // Indicates topLeftTree
        if ((topLeft.posy + botRight.posy) / 2 >= ball->pos.posy)
        {
            topLeftTree->insert(ball);
        }

        // Indicates botLeftTree
        else
        {
            botLeftTree->insert(ball);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.posy + botRight.posy) / 2 >= ball->pos.posy)
        {
            topLeftTree->insert(ball);
        }

        // Indicates botRightTree
        else
        {
            botRightTree->insert(ball);
        }
    }
}

//// Find a node in a quadtree
//Ball* Quad::search(Point p)
//{
//    // Current quad cannot contain it
//    if (!inBoundary(p))
//        return NULL;
//
//    // We are at a quad of unit length
//    // We cannot subdivide this quad further
//    if (n != NULL)
//        return n;
//
//    if ((topLeft.posx + botRight.posx) / 2 >= p.posx)
//    {
//        // Indicates topLeftTree
//        if ((topLeft.posy + botRight.posy) / 2 >= p.posy)
//        {
//            if (topLeftTree == NULL)
//                return NULL;
//            return topLeftTree->search(p);
//        }
//
//        // Indicates botLeftTree
//        else
//        {
//            if (botLeftTree == NULL)
//                return NULL;
//            return botLeftTree->search(p);
//        }
//    }
//    else
//    {
//        // Indicates topRightTree
//        if ((topLeft.posy + botRight.posy) / 2 >= p.posy)
//        {
//            if (topRightTree == NULL)
//                return NULL;
//            return topRightTree->search(p);
//        }
//
//        // Indicates botRightTree
//        else
//        {
//            if (botRightTree == NULL)
//                return NULL;
//            return botRightTree->search(p);
//        }
//    }
//};

// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)//松散四叉树
{
    return (p.posx >= (3.0 / 2 * topLeft.posx - botRight.posx / 2) &&
        p.posx <= (3.0 / 2 * botRight.posx - topLeft.posx / 2) &&
        p.posy >= (3.0 / 2 * topLeft.posy - botRight.posy / 2) &&
        p.posy <= (3.0 / 2 * botRight.posy - topLeft.posy / 2));
}

void Quad::treecollisionjudge(Ball* b, int c, float t)
{
    vector<Ball>::iterator it;//声明一个迭代器，来访问vector容器
    for (it = this->n->vBall.begin(); it != this->n->vBall.end(); it++)
    {
        if (*it == *b)continue;
        b->collisionjudge(&*it, c, t);
    }
}
