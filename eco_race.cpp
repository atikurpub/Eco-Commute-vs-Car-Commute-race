#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct Vehicle {
    int x, y;
    int speed;
    int pauseCounter;
    int colorBody;
    int colorWheels;
    bool paused;
    const char* type; // "Car" or "Bike"
};

// Draw sky with blue background and clouds
void drawSkyWithClouds() {
    int maxX = getmaxx();
    int maxY = getmaxy();

    // Sky background
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, maxX, maxY / 2);

    // Draw some clouds (simple white ellipses)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    // Cloud 1
    fillellipse(100, 80, 30, 20);
    fillellipse(130, 70, 35, 25);
    fillellipse(160, 80, 30, 20);

    // Cloud 2
    fillellipse(300, 50, 25, 15);
    fillellipse(330, 45, 30, 20);
    fillellipse(360, 50, 25, 15);

    // Cloud 3
    fillellipse(550, 90, 40, 25);
    fillellipse(590, 80, 45, 30);
    fillellipse(630, 90, 40, 25);
}

// Draw city buildings skyline
void drawCityBuildings() {
    int maxX = getmaxx();
    int maxY = getmaxy();

    int buildingWidths[] = {70, 50, 60, 80, 40, 90, 60};
    int buildingHeights[] = {150, 180, 130, 200, 120, 170, 160};
    int colors[] = {BLUE, CYAN, MAGENTA, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTMAGENTA};

    int xPos = 0;
    for(int i = 0; i < 7; i++) {
        setfillstyle(SOLID_FILL, colors[i]);
        bar(xPos, maxY/2 - buildingHeights[i], xPos + buildingWidths[i], maxY/2);
        xPos += buildingWidths[i] + 10;
    }
}

// Draw detailed road with lanes, zebra crossing, and side lines
void drawRoad() {
    int maxX = getmaxx();
    int maxY = getmaxy();

    // Road base
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, maxY / 2, maxX, maxY);

    // Lane dividers (dashed lines)
    setcolor(WHITE);
    for (int i = 0; i < maxX; i += 40) {
        line(i, maxY / 2 + 30, i + 20, maxY / 2 + 30);
    }
    for (int i = 0; i < maxX; i += 40) {
        line(i, maxY / 2 + 70, i + 20, maxY / 2 + 70);
    }

    // Side road lines (solid)
    setcolor(WHITE);
    line(0, maxY / 2 + 10, maxX, maxY / 2 + 10);
    line(0, maxY / 2 + 90, maxX, maxY / 2 + 90);

    // Zebra crossing at traffic light area
    int zebraStartX = maxX / 2 - 40;
    int zebraStartY = maxY / 2 + 10;
    int stripeWidth = 10;
    setfillstyle(SOLID_FILL, WHITE);
    for (int i = 0; i < 8; i++) {
        bar(zebraStartX + i*2*stripeWidth, zebraStartY, zebraStartX + i*2*stripeWidth + stripeWidth, zebraStartY + 80);
    }
}

// Draw a traffic light (red or green)
void drawTrafficLight(bool redLight) {
    int cx = getmaxx() / 2 + 20;
    int cy = getmaxy() / 2 + 50;

    setfillstyle(SOLID_FILL, BLACK);
    bar(cx - 15, cy - 50, cx + 15, cy + 50);

    // Red light
    setcolor(RED);
    setfillstyle(SOLID_FILL, redLight ? RED : DARKGRAY);
    fillellipse(cx, cy - 25, 10, 10);

    // Green light
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, redLight ? DARKGRAY : GREEN);
    fillellipse(cx, cy + 25, 10, 10);
}

// Draw detailed bike with frame and wheels
void drawBike(Vehicle &v) {
    setcolor(v.colorBody);
    // Frame (triangle)
    line(v.x - 10, v.y + 35, v.x, v.y + 10);
    line(v.x, v.y + 10, v.x + 10, v.y + 35);
    line(v.x - 10, v.y + 35, v.x + 10, v.y + 35);

    // Wheels
    setcolor(v.colorWheels);
    circle(v.x - 10, v.y + 35, 10);
    circle(v.x + 10, v.y + 35, 10);

    // Rider head
    setcolor(v.colorBody);
    circle(v.x, v.y, 8);
}

// Draw detailed car with windows, body, and wheels
void drawCar(Vehicle &v) {
    // Body
    setfillstyle(SOLID_FILL, v.colorBody);
    bar(v.x, v.y - 25, v.x + 70, v.y);

    // Windows
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(v.x + 10, v.y - 40, v.x + 60, v.y - 25);

    // Wheels
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(v.x + 15, v.y, 12, 12);
    fillellipse(v.x + 55, v.y, 12, 12);
}

// Draw traffic obstacle (red box) on road lane
void drawTrafficObstacle(int x, int y) {
    setfillstyle(SOLID_FILL, RED);
    bar(x, y - 40, x + 40, y);
    setcolor(WHITE);
    rectangle(x, y - 40, x + 40, y);
    outtextxy(x + 5, y - 30, (char*)"STOP");
}

// Draw scoreboard with stats
void drawScoreboard(Vehicle bikes[], Vehicle cars[], int count, int pollution, int time) {
    int sx = getmaxx() - 260;
    int sy = 20;
    setfillstyle(SOLID_FILL, BLACK);
    bar(sx, sy, sx + 240, sy + 320);

    setcolor(WHITE);
    rectangle(sx, sy, sx + 240, sy + 320);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(sx + 20, sy + 10, (char*)"ECO COMMUTE RACE STATS");

    char line[80];
    sprintf(line, "Time: %d seconds", time / 50);
    outtextxy(sx + 10, sy + 40, line);

    sprintf(line, "Pollution: %d", pollution);
    outtextxy(sx + 10, sy + 70, line);

    for(int i = 0; i < count; i++) {
        sprintf(line, "Bike %d Pos: %d", i+1, bikes[i].x);
        outtextxy(sx + 10, sy + 100 + i*25, line);
    }
    for(int i = 0; i < count; i++) {
        sprintf(line, "Car %d Pos: %d", i+1, cars[i].x);
        outtextxy(sx + 10, sy + 100 + (count + i)*25, line);
    }
}

int main() {
    srand(time(NULL));
    initwindow(1100, 600, "Advanced Eco Commute vs City Traffic");

    const int racersCount = 3;
    Vehicle bikes[racersCount];
    Vehicle cars[racersCount];

    int baseY = getmaxy()/2 + 60;
    int laneGap = 60;

    // Initialize bikes
    int bikeColorsBody[] = {YELLOW, LIGHTMAGENTA, LIGHTCYAN};
    int bikeColorsWheels[] = {LIGHTGREEN, LIGHTGREEN, LIGHTGREEN};
    for(int i=0; i < racersCount; i++) {
        bikes[i].x = 50;
        bikes[i].y = baseY + i * laneGap;
        bikes[i].speed = 4 + rand() % 2; // 4 or 5 (faster)
        bikes[i].colorBody = bikeColorsBody[i];
        bikes[i].colorWheels = bikeColorsWheels[i];
        bikes[i].paused = false;
        bikes[i].pauseCounter = 0;
        bikes[i].type = "Bike";
    }

    // Initialize cars
    int carColors[] = {RED, LIGHTRED, BROWN};
    for(int i=0; i < racersCount; i++) {
        cars[i].x = 50;
        cars[i].y = baseY + i * laneGap + 30;
        cars[i].speed = 3 + rand() % 2; // 3 or 4 (start faster than bikes)
        cars[i].colorBody = carColors[i];
        cars[i].colorWheels = BLACK;
        cars[i].paused = false;
        cars[i].pauseCounter = 0;
        cars[i].type = "Car";
    }

    int pollution = 0;
    int time = 0;
    bool raceFinished = false;
    int finishLine = getmaxx() - 300;

    int page = 0;

    // Traffic light cycle (red/green)
    bool redLight = true;
    int lightTimer = 0;
    int lightDuration = 200;

    while(!raceFinished) {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        // Draw sky with clouds
        drawSkyWithClouds();

        // Draw city and road
        drawCityBuildings();
        drawRoad();

        // Draw traffic light and cycle
        drawTrafficLight(redLight);
        lightTimer++;
        if (lightTimer > lightDuration) {
            redLight = !redLight;
            lightTimer = 0;
        }

        // Draw traffic obstacles near traffic light for cars
        int obstacleX = getmaxx() / 2 + 30;
        for(int i=0; i < racersCount; i++) {
            drawTrafficObstacle(obstacleX, cars[i].y + 25);
        }

        // Update bikes (pause at red light if near traffic light)
        for(int i=0; i < racersCount; i++) {
            if(redLight && bikes[i].x + bikes[i].speed >= obstacleX - 20 && bikes[i].x <= obstacleX + 50) {
                bikes[i].paused = true;
                bikes[i].pauseCounter = 20;
            }

            if(bikes[i].paused) {
                bikes[i].pauseCounter--;
                if(bikes[i].pauseCounter <= 0) bikes[i].paused = false;
            } else {
                bikes[i].x += bikes[i].speed;
                if(bikes[i].x > finishLine)
                    raceFinished = true;
            }
        }

        // Update cars (pause at red light or random traffic jam)
        for(int i=0; i < racersCount; i++) {
            if(redLight && cars[i].x + cars[i].speed >= obstacleX - 10 && cars[i].x <= obstacleX + 50) {
                cars[i].paused = true;
                cars[i].pauseCounter = 40;
            }

            if(!cars[i].paused && cars[i].x > obstacleX + 60 && cars[i].x < obstacleX + 300) {
                if(rand() % 100 < 15) { // 15% chance to pause per frame (more frequent jams)
                    cars[i].paused = true;
                    cars[i].pauseCounter = 60 + rand() % 60; // longer pause
                }
            }

            if(cars[i].paused) {
                cars[i].pauseCounter--;
                if(cars[i].pauseCounter <= 0) cars[i].paused = false;
            } else {
                cars[i].x += cars[i].speed;
                pollution++; // Car pollution while moving
                if(cars[i].x > finishLine)
                    raceFinished = true;
            }
        }

        // Draw bikes and cars
        for(int i=0; i < racersCount; i++) {
            drawBike(bikes[i]);
            drawCar(cars[i]);
        }

        // Draw scoreboard
        drawScoreboard(bikes, cars, racersCount, pollution, time);

        delay(20);
        page = 1 - page;
        time++;

        // Check race finished
        for(int i=0; i < racersCount; i++) {
            if(bikes[i].x >= finishLine || cars[i].x >= finishLine) {
                raceFinished = true;
                break;
            }
        }
    }

    // Show race results
    setactivepage(page);
    setvisualpage(page);
    cleardevice();

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 200, getmaxy()/2 - 80, (char*)"Race Finished!");

    int bestBike = 0, bestCar = 0;
    for(int i=1; i < racersCount; i++) {
        if(bikes[i].x > bikes[bestBike].x) bestBike = i;
        if(cars[i].x > cars[bestCar].x) bestCar = i;
    }

    char buffer[100];
    sprintf(buffer, "Best Bike (Bike %d) pos: %d", bestBike + 1, bikes[bestBike].x);
    outtextxy(getmaxx()/2 - 200, getmaxy()/2 - 40, buffer);

    sprintf(buffer, "Best Car (Car %d) pos: %d", bestCar + 1, cars[bestCar].x);
    outtextxy(getmaxx()/2 - 200, getmaxy()/2, buffer);

    sprintf(buffer, "Total time: %d seconds", time / 50);
    outtextxy(getmaxx()/2 - 200, getmaxy()/2 + 40, buffer);

    sprintf(buffer, "Total pollution: %d units", pollution);
    outtextxy(getmaxx()/2 - 200, getmaxy()/2 + 80, buffer);

    if (bikes[bestBike].x > cars[bestCar].x)
        outtextxy(getmaxx()/2 - 200, getmaxy()/2 + 120, (char*)"Winner: Cyclist! Eco Friendly Win!");
    else
        outtextxy(getmaxx()/2 - 200, getmaxy()/2 + 120, (char*)"Winner: Car! More Pollution!");

    outtextxy(getmaxx()/2 - 200, getmaxy()/2 + 160, (char*)"Press any key to exit...");
    getch();

    closegraph();
    return 0;
}
