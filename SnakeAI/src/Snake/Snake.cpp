#include "Snake.h"
#include"../../main.h"

Snake::Snake():Snake(4)

{
    //Snake(2); // it doesnt have a value (hidden_layers)
}

Snake::Snake(int layers)
{
    headX = HEIGHT / 2;
    headY = WIDTH / 2; // HEIGTH
    food = Food();
    body = std::vector<PVector>();
    vision = std::vector<float>(24);
    decision = std::vector<float>(4);
    foodList = std::vector<Food>();
    foodList.push_back(food.Clone());
    brain = NeuralNet(24, 16/*hidden nodes*/, 4, layers);
    body.push_back(PVector(HEIGHT / 2, WIDTH / 2 + 1 /*SIZE*/));
    body.push_back(PVector(HEIGHT / 2, (WIDTH / 2) + (2 * 1 /*SIZE*/)));
    score += 2;
}

Snake::Snake(std::vector<Food> foods)
{
    replay = true;
    vision = std::vector<float>(24);
    decision = std::vector<float>(4);
    body = std::vector<PVector>();
    foodList = std::vector<Food>(foods.size());
    for (int i = 0; i < foods.size(); i++)
        foodList[i] = foods[i].Clone();
    food = foodList[foodItterate];
    foodItterate++;
    headX = HEIGHT / 2;
    headY = WIDTH / 2; // HEIGTH
    body.push_back(PVector(HEIGHT / 2, WIDTH / 2 + 1 /*SIZE*/));
    body.push_back(PVector(HEIGHT / 2, (WIDTH / 2) + (2 * 1 /*SIZE*/)));
    score += 2;
}

bool Snake::bodyCollide(float x, float y)
{
    for (int i = 0; i < body.size(); i++)
    {
        if (x == body[i].x && y == body[i].y)
            return true;
    }
    return false;
}

bool Snake::foodCollide(float x, float y)
{
    return x == food.y && y == food.x;
}

bool Snake::wallCollide(float x, float y)
{
    return (x >= HEIGHT - (1/*SIZE*/)) || (x < 1/*SIZE*/) || (y >= WIDTH/*SIZE*/ - (1/*SIZE*/)) || (y < 1/*SIZE*/);
}

void Snake::show()
{
    food.Show();
    for (int i = 0; i < body.size(); i++)
        map[body[i].x][body[i].y] = 3;
    map[headX][headY] = 4;
}

void Snake::eat()
{
    int len = body.size() - 1;
    score++;
    if (lifeLeft < 500)
    {
        if (lifeLeft > 400)
            lifeLeft = 500;
        else
            lifeLeft += 100;
    }
    if (len >= 0)
        body.push_back(PVector(body[len].x, body[len].y));
    else
        body.push_back(PVector(headX, headY));
    if (!replay)
    {
        food = Food();
        while (bodyCollide(food.x, food.y))
            food = Food();
        foodList.push_back(food);
    }
    else
    {  //if the snake is a replay, then we dont want to create new random foods, we want to see the positions the best snake had to collect
        food = foodList[foodItterate];
        foodItterate++;
    }
}

void Snake::move()
{
    if (!dead) {
        lifeTime++;
        lifeLeft--;
        if (foodCollide(headX, headY))
            eat();
        shiftBody();
        dead = lifeLeft <= 0 || bodyCollide(headX, headY) || wallCollide(headX, headY);
    }
}

void Snake::shiftBody()
{
    float tempx = headX;
    float tempy = headY;
    headX += xVel;
    headY += yVel;
    float temp2x;
    float temp2y;
    for (int i = 0; i < body.size(); i++) {
        temp2x = body[i].x;
        temp2y = body[i].y;
        body[i].x = tempx;
        body[i].y = tempy;
        tempx = temp2x;
        tempy = temp2y;
    }
}

Snake Snake::cloneForReplay()
{
    Snake clone = Snake(foodList);
    clone.brain = brain.clone();
    return clone;
}

Snake Snake::clone()
{
    Snake clone = Snake(4 /*hidden_layers*/);
    clone.brain = brain.clone();
    return clone;
}

Snake Snake::crossover(Snake parent)
{
    Snake child = Snake(4 /*hidden_layers*/);
    child.brain = brain.crossover(parent.brain);
    return child;
}

void Snake::mutate()
{
    brain.mutate(mutationRate);
}

void Snake::calculateFitness()
{
    if (score < 10) {
        fitness = floor(lifeTime * lifeTime) * pow(2, score);
    }
    else {
        fitness = floor(lifeTime * lifeTime);
        fitness *= pow(2, 10);
        fitness *= (score - 9);
    }
}

void Snake::look()
{
    vision = std::vector<float>(24);
    std::vector<float> temp = lookInDirection(PVector(-1/*SIZE*/, 0));
    vision[0] = temp[0];
    vision[1] = temp[1];
    vision[2] = temp[2];
    temp = lookInDirection(PVector(-1/*SIZE*/, -1/*SIZE*/));
    vision[3] = temp[0];
    vision[4] = temp[1];
    vision[5] = temp[2];
    temp = lookInDirection(PVector(0, -1/*SIZE*/));
    vision[6] = temp[0];
    vision[7] = temp[1];
    vision[8] = temp[2];
    temp = lookInDirection(PVector(1/*SIZE*/, -1/*SIZE*/));
    vision[9] = temp[0];
    vision[10] = temp[1];
    vision[11] = temp[2];
    temp = lookInDirection(PVector(1/*SIZE*/, 0));
    vision[12] = temp[0];
    vision[13] = temp[1];
    vision[14] = temp[2];
    temp = lookInDirection(PVector(1/*SIZE*/, 1/*SIZE*/));
    vision[15] = temp[0];
    vision[16] = temp[1];
    vision[17] = temp[2];
    temp = lookInDirection(PVector(0, 1/*SIZE*/));
    vision[18] = temp[0];
    vision[19] = temp[1];
    vision[20] = temp[2];
    temp = lookInDirection(PVector(-1/*SIZE*/, 1/*SIZE*/));
    vision[21] = temp[0];
    vision[22] = temp[1];
    vision[23] = temp[2];
}

std::vector<float> Snake::lookInDirection(PVector dir)
{
    std::vector<float> look = std::vector <float>(3);
    PVector pos = PVector(headX, headY);
    float distance = 0;
    bool foodFound = false;
    bool bodyFound = false;
    pos.add(dir);
    distance++;
    while (!wallCollide(pos.x, pos.y)) {
        if (!foodFound && foodCollide(pos.x, pos.y)) {
            foodFound = true;
            look[0] = 2;
        }
        if (!bodyFound && bodyCollide(pos.x, pos.y)) {
            bodyFound = true;
            look[1] = 0.1;
        }
        pos.add(dir);
        distance++;
    }
    look[2] = 1 / distance;
    return look;
}

void Snake::moveUp()
{
    if (yVel != 1/*SIZE*/)
        xVel = 0; yVel = -1/*SIZE*/;
}

void Snake::moveDown()
{
    if (yVel != -1/*SIZE*/)
        xVel = 0; yVel = 1/*SIZE*/;
}

void Snake::moveLeft()
{
    if (xVel != 1/*SIZE*/)
        xVel = -1/*SIZE*/; yVel = 0;
}

void Snake::moveRight()
{
    if (xVel != -1/*SIZE*/)
        xVel = 1/*SIZE*/; yVel = 0;
}

void Snake::think()
{
    decision = brain.output(vision);
    int maxIndex = 0;
    float max = 0;

    for (int i = 0; i < decision.size(); i++)
    {
        if (decision[i] > max)
        {
            max = decision[i];
            maxIndex = i;
        }
    }
    switch (maxIndex) {
    case 0:
        moveUp();
        break;
    case 1:
        moveDown();
        break;
    case 2:
        moveLeft();
        break;
    case 3:
        moveRight();
        break;
    }
}