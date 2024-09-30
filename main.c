/*******************************************************************************************
*
*   raylib Game Template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

///////////////////////////
//         _____         //
//        |     |        //
//     ___|  1  |___     //
//    |      |      |    //
//    |  4 --+-- 3  |    //
//    |___   |   ___|    //
//        |  2  |        //
//        |_____|        //
//                       //
///////////////////////////

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4



void draw(void);
void drawGrid(Vector2 startPos,Vector2 endPos, Vector2 gridSize,float thick,Color lineColor,Color bgColor);
void drawSqr(Vector2 startPos, Vector2 endPos, Vector2 gridSize, Vector2 position, Color sqrColor);


int edgeSize;
int squareSize;

Vector2 piecesPos[256];
int nPieces = 5;
int headDir = 3;

Vector2 foodPos;

Texture2D mouseTexture;

int main(void)
{
    InitWindow(400, 400, "raylib [core] example - basic window");
    SetWindowState(FLAG_FULLSCREEN_MODE);
    HideCursor();
    SetTargetFPS(60); 
    
    
    mouseTexture = LoadTexture("resources/mouseTexture.png");
    
    ////////////RESET///////////////
    piecesPos[0].x = 3;
    piecesPos[0].y = 8;
    
    foodPos.x = GetRandomValue(0,16); 
    foodPos.y = GetRandomValue(0,16);  
    ////////////////////////////////
    int actualFrame = 0;
    
    
    while (!WindowShouldClose())
    {
        if(GetScreenWidth() > GetScreenHeight())
        {
            squareSize = GetScreenHeight();
            edgeSize = (GetScreenWidth() - squareSize)/2;
        }
        else
        {
            squareSize= GetScreenWidth();
            edgeSize = (GetScreenHeight() - squareSize)/2;
        }
        
        if(IsKeyDown(KEY_W)) { headDir = UP; }
        if(IsKeyDown(KEY_A)) { headDir = LEFT; }
        if(IsKeyDown(KEY_S)) { headDir = DOWN; }
        if(IsKeyDown(KEY_D)) { headDir = RIGHT; }
        actualFrame++;
        
        if (actualFrame >= 30)
        {
            actualFrame=0;
            switch (headDir)
            {
                case UP:
                    piecesPos[0].y--;
                    break;
                case LEFT:
                    piecesPos[0].x--;
                    break;
                case DOWN:
                    piecesPos[0].y++;
                    break;
                case RIGHT:
                    piecesPos[0].x++;
                    break;
                default:
                    headDir=RIGHT;
            }
            
            if(piecesPos[0].x == foodPos.x && piecesPos[0].y == foodPos.y)
            {
                foodPos.x = GetRandomValue(0,16); 
                foodPos.y = GetRandomValue(0,16);
                
                nPieces++;
            }
            
            for(int i=nPieces;i > 0; i--)
            {
                piecesPos[i]=piecesPos[i-1];
            }
        }
        
        BeginDrawing();
            draw();
        EndDrawing();
        
        //////////////DEBUG//////////////////
        DrawText(TextFormat("%d",edgeSize),0, 0,10, BLACK); 
        /////////////////////////////////////
        
        EndDrawing();
    }

    UnloadTexture(mouseTexture);

    CloseWindow();
    
    return 0;
}

void draw()
{
    ClearBackground((Color){8,24,32});
    
    
    for(int i=0; i<nPieces;i++)
    {
        drawSqr((Vector2){edgeSize,0},(Vector2){squareSize + edgeSize , squareSize},(Vector2){16,16},piecesPos[i],WHITE);
    }
    
    drawSqr((Vector2){edgeSize,0},(Vector2){squareSize + edgeSize , squareSize},(Vector2){16,16},foodPos,RED);
    
    drawGrid((Vector2){edgeSize,0},(Vector2){squareSize + edgeSize , squareSize},(Vector2){16,16},2,(Color) {224,248,208,255},(Color) {136,192,112,0});
    
    
    
    DrawTextureEx(mouseTexture,GetMousePosition(),0,0.08, WHITE); 
}

void drawGrid(Vector2 startPos,Vector2 endPos,Vector2 gridSize,float thick,Color lineColor,Color bgColor)
{
    startPos.y += thick/2;
    startPos.x += thick/2;
    endPos.y -= thick/2;
    endPos.x -= thick/2;
    
    Vector2 gap = (Vector2){endPos.x-startPos.x, endPos.y-startPos.y}; //gap are the dimensions of the bg
    
    DrawRectangleV(startPos, gap, bgColor); 
    
    for(int i = 0; i < gridSize.x + 1; i++)
    {
        DrawLineEx((Vector2){startPos.x - (thick/2), (gap.y / gridSize.y) * i + startPos.y}, (Vector2){endPos.x + (thick/2), (gap.y / gridSize.y) * i + startPos.y}, thick, lineColor);
    }
    
    for(int i = 0; i < gridSize.y + 1; i++)
    {
        DrawLineEx((Vector2){(gap.x / gridSize.x) * i + startPos.x, startPos.y}, (Vector2){(gap.x / gridSize.x) * i + startPos.x, endPos.y}, thick, lineColor);
    }
    
}

void drawSqr(Vector2 startPos, Vector2 endPos, Vector2 gridSize, Vector2 pos, Color sqrColor)
{
    /*startPos.y += thick/2;
    startPos.x += thick/2;
    endPos.y -= thick/2;
    endPos.x -= thick/2;*/
    
    Vector2 gap = (Vector2){endPos.x-startPos.x, endPos.y-startPos.y}; //gap are the dimensions of the bg
    
    
    DrawRectangleV((Vector2){(gap.x/gridSize.x) * pos.x + startPos.x,(gap.y/gridSize.y) * pos.y + startPos.y}, (Vector2){gap.x/gridSize.x,gap.y/gridSize.y}, sqrColor);
}
