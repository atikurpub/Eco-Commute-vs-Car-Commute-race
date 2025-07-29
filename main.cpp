#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

int ecoX = 50, carX = 50;
int finishLine = 550;
int trafficBlock1 = 250;
int trafficBlock2 = 400;

int timeElapsed = 0;
int carDelayCounter = 0;
bool carStopped = false;

void drawRoad() {
    setcolor(WHITE);
    rectangle(30, 100, 600, 200);
    line(30, 150, 600, 150);

    // Traffic blocks
    setcolor(LIGHTRED);
    rectangle(trafficBlock1, 100, trafficBlock1 + 10, 200);
    rectangle(trafficBlock2, 100, trafficBlock2 + 10, 200);

    // Finish Line
    setcolor(YELLOW);
    line(finishLine, 90, finishLine, 210);
}

void drawCyclist(int x) {
    setcolor(GREEN);
    circle(x, 130, 7);           // Wheel 1
    circle(x + 20, 130, 7);      // Wheel 2
    line(x - 3, 120, x + 23, 120); // Frame
    line(x + 10, 120, x + 10, 110); // Body
    circle(x + 10, 105, 3);      // Head
}

void drawCar(int x) {
    setcolor(RED);
    rectangle(x, 170, x + 40, 190);  // Car body
    circle(x + 10, 195, 5);          // Wheels
    circle(x + 30, 195, 5);
}

bool isCarInTraffic(int x) {
    return (x + 40 >= trafficBlock1 && x <= trafficBlock1 + 10) ||
           (x + 40 >= trafficBlock2 && x <= trafficBlock2 + 10);
}

void showStats() {
    setcolor(WHITE);
    char buffer[100];

    sprintf(buffer, "Time: %d sec", timeElapsed);
    outtextxy(10, 230, buffer);

    sprintf(buffer, "Eco Position: %d", ecoX);
    outtextxy(10, 250, buffer);

    sprintf(buffer, "Car Position: %d", carX);
    outtextxy(10, 270, buffer);

    sprintf(buffer, "Pollution: Car = %d, Cycle = 0", timeElapsed * 2);
    outtextxy(10, 290, buffer);
}

void showImpactMessage() {
    setcolor(LIGHTGREEN);
    settextstyle(3, 0, 2);
    outtextxy(130, 330, "Use Eco-Friendly Transport!");
    outtextxy(120, 360, " Say NO to Traffic Jams & Pollution!");
}

void displayWinner() {
    setcolor(WHITE);
    settextstyle(3, 0, 2);
    if (ecoX >= finishLine && ecoX >= carX) {
        outtextxy(200, 300, "Cyclist Wins!");
        showImpactMessage();
    } else if (carX >= finishLine) {
        outtextxy(200, 300, "Car Wins!");
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (ecoX < finishLine && carX < finishLine) {
        cleardevice();

        drawRoad();
        drawCyclist(ecoX);
        drawCar(carX);
        showStats();

        // Cyclist moves slowly but consistently
        ecoX += 3;

        // Car movement with longer traffic jam simulation
        if (isCarInTraffic(carX)) {
            if (!carStopped) {
                carStopped = true;
                carDelayCounter = 0;
            }
            carDelayCounter++;

            if (carDelayCounter >= 5) {  // 🟢 Increased traffic jam time!
                carStopped = false;
            }
        }

        if (!carStopped) {
            carX += 4;
        }

        timeElapsed++;
        delay(400);
    }

    displayWinner();
    getch();
    closegraph();
    return 0;
}

