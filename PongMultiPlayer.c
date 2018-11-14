
struct Shape{
	int x;  //xpos
	int y;  //ypos
	int width; //width of a non circle
	int length; //length of a non circle
	int dia; // diameter of a circular shape
	int xspeed; //xmove speed
	int yspeed; //ymove speed
};
struct Screen{
	int y; //screen height
	int x; //screen width
};


task main()
{
	//create shapes and game flag
	Shape leftPaddle;
	Shape rightPaddle;
	Shape ball;
	bool playGame = true;
	//Screen Dimensions
	Screen thisScreen;
	thisScreen.x = 160;
	thisScreen.y = 120;
	//initialize ball
	ball.x = 5;
	ball.y = 5;
	ball.dia = 7;
	ball.xspeed = 1;
	ball.yspeed = 1;

	//initialize leftpaddle
	leftPaddle.x = 1;
	leftPaddle.y = 20;
	leftPaddle.width = 3;
	leftPaddle.length = 15;

	//initialize rightpaddle
	rightPaddle.x = thisScreen.x;
	rightPaddle.y = 20;
	rightPaddle.width = 3;
	rightPaddle.length = 15;


	while(playGame)
	{
		//clear the screen
		eraseDisplay();

		//game ends if ball hits the wall
		if(ball.x <= 0 || ball.x >= 160)
		{
			playGame = false;
		}

		//move the left paddle up
		if(getButtonPress(buttonUp)==1 && leftPaddle.y+leftPaddle.length < thisScreen.y)
		{
			leftPaddle.y++;
		}
		//move the left paddle down
		if(getButtonPress(buttonDown)==1 && leftPaddle.y > 0)
		{
			leftPaddle.y--;
		}

		//move the right paddle up
		if(getButtonPress(buttonLeft)==1 && rightPaddle.y+rightPaddle.length < thisScreen.y)
		{
			rightPaddle.y++;
		}
		//move the right paddle down
		if(getButtonPress(buttonRight)==1 && rightPaddle.y > 0)
		{
			rightPaddle.y--;
		}



		//start reflection from side to side
		//change direction by changing the value of x speed from negative to positive and vise versa
		//right hand side
		if (((ball.y < (rightPaddle.y + rightPaddle.length)) && (ball.y+ball.dia > rightPaddle.y)) && (ball.x == (rightPaddle.x - rightPaddle.width)))
		{
			ball.xspeed = -ball.xspeed;
		}
		//left hand side
		if (((ball.y < (leftPaddle.y + leftPaddle.length)) && (ball.y+ball.dia > leftPaddle.y)) && (ball.x == (leftPaddle.x + leftPaddle.width)))
		{
			ball.xspeed = -ball.xspeed;
		}

		//end reflection
		//ball bounces if it hits top or bottom wall
		if (ball.y+ball.dia > thisScreen.y || ball.y < 0)
		{
			ball.yspeed = -ball.yspeed;
		}

		//have the right paddle follow the ball
		//if (rightPaddle.y + rightPaddle.length < thisScreen.y || rightPaddle.y > 0)
		//{
		//	rightPaddle.y = (ball.y + ball.dia) / 2;
		//}

		//draw ball
		fillEllipse(ball.x,ball.y,ball.x+ball.dia,ball.y+ball.dia);
		//draw leftPaddle
		fillRect(leftPaddle.x,leftPaddle.y,leftPaddle.x+leftPaddle.width,leftPaddle.y+leftPaddle.length);
		//draw rightPaddle
		fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.x+rightPaddle.width,rightPaddle.y+rightPaddle.length);

		//move ball
		//depending on whether the value of xspeed or yspeed is 1 or -1 if will increment or decrement the
		//x and y coordinates of the ball
		ball.x += ball.xspeed;
		ball.y += ball.yspeed;

		//draw every 17 ms
		wait1Msec(17);
	}
	eraseDisplay();
	drawTextAt(25,35,"%s","Game Over");
	wait10Msec(100);
}
