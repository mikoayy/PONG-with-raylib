#include <raylib.h>
#include <iostream>

using namespace std;
int main()
{
	const int lenghtScreen = 720;
	const int widthScreen = 1280;
	Vector2 ballPosition;
	ballPosition.x = widthScreen / 2;
	ballPosition.y = lenghtScreen / 2;
	int xbspeed = 10;
	int ybspeed = 10;
	int points = 0;
	int points1 = 0;
	float yPlatform = lenghtScreen / 2;
	float R = 20;
	bool collision2 = false;
	bool collision = false;
	bool collision3 = false;
	bool startGame = false; 
	bool rightUp = false;
	bool rightDown = false;
	bool leftUp = false;
	bool leftDown = false;
	bool player1Start = false;
	bool reset = false;
	const int buttonWidht = 300;
	const int butonHeight = 60;
	Rectangle platform = { widthScreen / 15, yPlatform, 20, 150 };
	Rectangle platform2 = { widthScreen - (widthScreen / 15), yPlatform, 20, 150 };
	Rectangle mouse = { widthScreen - (widthScreen / 15), yPlatform, 1, 1 };
	Rectangle button = { widthScreen / 2 - buttonWidht/2, lenghtScreen / 2 - butonHeight/2, buttonWidht,butonHeight };
	Color green = { 50,150,90, 255 };

	InitWindow(widthScreen, lenghtScreen, "PONG");
	SetTargetFPS(60);
	
	while (WindowShouldClose() == false)
	{	

		if (startGame)
		{


			if (platform.y >= 0)
			{
				if (IsKeyDown(KEY_W))
				{
					platform.y -= 15;
				}
			}
			if (platform.y + platform.height <= lenghtScreen)
				if (IsKeyDown(KEY_S))
				{
					platform.y += 15;
				}

			if (platform2.y >= 0)
			{
				if (IsKeyDown(KEY_UP))
				{
					platform2.y -= 15;
				}
			}
			if (platform2.y + platform2.height <= lenghtScreen)
				if (IsKeyDown(KEY_DOWN))
				{
					platform2.y += 15;
				}
		
			if (reset == false)
			{

				collision = CheckCollisionCircleRec(ballPosition, R, platform);
				collision2 = CheckCollisionCircleRec(ballPosition, R, platform2);

				if (collision)
				{
					xbspeed *= -1;
					ybspeed *= -1;
					xbspeed = 10 + rand() % 10;
					ybspeed = 10 + rand() % 10;
				}



				if (collision2)
				{
					xbspeed = 10 + rand() % 10;
					ybspeed = 10 + rand() % 10;
					xbspeed *= -1;
					ybspeed *= -1;

				}

				if (ballPosition.x + R >= widthScreen || ballPosition.x - R <= 0)
				{
					xbspeed *= -1;
				}

				if (ballPosition.y + R >= lenghtScreen || ballPosition.y - R <= 0)
				{
					ybspeed *= -1;
				}

				if (ballPosition.x + R >= widthScreen)
				{
					points++;
					reset = true;
					player1Start = true; 
					
				}
				if (ballPosition.x - R <= 0)
				{
					points1++;
					reset = true;
				}
				ballPosition.x += xbspeed;
				ballPosition.y += ybspeed;
			}

			if (reset == true)
			{
				if (ballPosition.x + R >= widthScreen / 2 && ballPosition.y <= lenghtScreen / 2) rightUp = true;
				
				
				if (rightUp)
				{
					if (ballPosition.x != widthScreen / 2) ballPosition.x -= 10;
					if (ballPosition.y != lenghtScreen / 2) ballPosition.y += 10;
				}

				if (ballPosition.x >= widthScreen / 2 && ballPosition.y >= lenghtScreen / 2) rightDown = true;

				if (rightDown)
				{
					if (ballPosition.x != widthScreen / 2) ballPosition.x -= 10;
					if (ballPosition.y != lenghtScreen / 2) ballPosition.y -= 10;
				}

				if (ballPosition.x <= widthScreen / 2 && ballPosition.y >= lenghtScreen / 2) leftDown = true;

				if (leftDown)
				{
					if (ballPosition.x != widthScreen / 2) ballPosition.x += 10;
					if (ballPosition.y != lenghtScreen / 2) ballPosition.y -= 10;
				}

				if (ballPosition.x <= widthScreen / 2 && ballPosition.y <= lenghtScreen / 2) leftUp = true;

				if (leftUp)
				{
					if (ballPosition.x != widthScreen / 2) ballPosition.x += 10;
					if (ballPosition.y != lenghtScreen / 2) ballPosition.y += 10;
				}

				if (ballPosition.x <= widthScreen / 2 + 15  && ballPosition.x >= widthScreen / 2 - 15)
				{
					rightUp = false;
					rightDown = false;
					leftUp = false;
					leftDown = false;
					
				}

				if (IsKeyPressed(KEY_SPACE) && rightUp == false && rightDown == false && leftUp == false && leftDown == false)
				{
					if (player1Start)
					{
						xbspeed = (10 + rand() % 10);
						if (rand() % 2 == 0)
						{
							ybspeed = -1 * (10 + rand() % 10);
						}

						else
						{
							ybspeed = (10 + rand() % 10);
						}
					}

					else
					{
						xbspeed = -1 * (10 + rand() % 10);
						if (rand() % 2 == 0)
						{
							ybspeed = -1 * (10 + rand() % 10);
						}

						else
						{
							ybspeed = (10 + rand() % 10);
						}
					}
					
					reset = false;
					player1Start = false;
				}

			}

		}
		if (startGame == false )
		{
			mouse.x = GetMouseX() - mouse.width / 2;
			mouse.y = GetMouseY() - mouse.height / 2;
			
			collision3 = CheckCollisionRecs(button, mouse);
			
			if (collision3 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				startGame = !startGame;
				points = 0;
				points1 = 0;
			}

		}

		if (points >= 10 || points1 >= 10)
		{
			startGame = false;
		}

		BeginDrawing();
		
		ClearBackground(green);
		
		if (startGame)
		{
			DrawCircleV(ballPosition, R, BLUE);
			DrawRectangleRec(platform, RED);
			DrawRectangleRec(platform2, RED);
			DrawText(TextFormat("player 1: %i", (int)points), widthScreen / 30, lenghtScreen / 30, 30, BLACK);
			DrawText(TextFormat("player 2: %i", (int)points1), widthScreen - widthScreen / 30 - MeasureText(TextFormat("player 2: %i", (int)points1), 30), lenghtScreen / 30, 30, BLACK);
		}
		if (startGame == false)
		{
			
			if (points == 0 && points1 == 0)
			{
				DrawText("PONG", widthScreen / 2 - MeasureText("PONG", 100) / 2, 1080 / 10, 100, BLACK);
				DrawRectangleRec(mouse, WHITE);
				DrawRectangleRec(button, WHITE);
				DrawText("PLAY", (int)button.x + 150 - MeasureText("PLAY", 50) / 2, (int)button.y + 30 - 25, 50, BLACK);
			}

			if (points >= 10)
			{
				DrawText("PLAYER 1 WINS!", widthScreen / 2 - MeasureText("PLAYER 1 WINS!", 100) / 2, 1080 / 10, 100, BLACK);
				DrawRectangleRec(mouse, WHITE);
				DrawRectangleRec(button, WHITE);
				DrawText("PLAY", (int)button.x + 150 - MeasureText("PLAY", 50) / 2, (int)button.y + 30 - 25, 50, BLACK);
			}

			if (points1 >= 10)
			{
				DrawText("PLAYER 2 WINS!", widthScreen / 2 - MeasureText("PLAYER 2 WINS!", 100) / 2, 1080 / 10, 100, BLACK);
				DrawRectangleRec(mouse, WHITE);
				DrawRectangleRec(button, WHITE);
				DrawText("PLAY", (int)button.x + 150 - MeasureText("PLAY", 50) / 2, (int)button.y + 30 - 25, 50, BLACK);
			}
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

