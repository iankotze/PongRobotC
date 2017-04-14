struct Shape{
	int x; //xpos
	int y; //ypos
	int width; //width for noncircle
	int length; // length for noncircle
	int dia; //diameter of circle shape
	int xspeed;	// xmove speed
	int yspeed; //ymove speed
};

task main()
{
	// create shapes and game flag
	Shape leftPaddle;
	Shape rightPaddle;
	Shape ball;
	bool playGame = true;

	// initialize ball
	ball.x = 5;
	ball.y = 5;
	ball.dia = 7;
	ball.xspeed = 1;
	ball.yspeed = 1;

	// initialize left paddle
	leftPaddle.x = 1;
	leftPaddle.y = 20;
	leftPaddle.width = 3;
	leftPaddle.length = 15;

	// initialize right paddle
	rightPaddle.x = 96;
	rightPaddle.y = 20;
	rightPaddle.width = 2;
	rightPaddle.length = 15;

	while (playGame)
	{
		// clear the screen
		eraseDisplay();

		// game ends if it hits the wall
		if (ball.x <= 0)
		{
			playGame = false;
		}

	  // move left paddle up
		if (nNxtButtonPressed == kLeftButton && leftPaddle.y+leftPaddle.length < 63)
		{
			leftPaddle.y++;
		}
		// move left paddle down
		if (nNxtButtonPressed == kRightButton && leftPaddle.y > 0)
		{
			leftPaddle.y--;
		}

		// start reflection for side to side
		if (ball.x + ball.dia > rightPaddle.x)
		{
			ball.xspeed = -ball.xspeed;
		}
		if (((ball.y < (leftPaddle.y+leftPaddle.length)) && (ball.y+ball.dia > leftPaddle.y)) && (ball.x == (leftPaddle.x + leftPaddle.width )))
		{
			ball.xspeed = -ball.xspeed;
		}
		// end reflection

		// ball bounces if it hits top or bottom wall
		if (ball.y+ball.dia > 63 || ball.y < 0)
		{
			ball.yspeed = -ball.yspeed;
		}

		// have right paddle follow the ball
		if (rightPaddle.y + rightPaddle.length  < 63 || rightPaddle.y > 0)
		{
			rightPaddle.y = (ball.y + ball.dia) / 2;

		}

		//draw ball
		fillEllipse(ball.x,ball.y,ball.x+ball.dia, ball.y+ball.dia);
		//draw left paddle
		fillRect(leftPaddle.x,leftPaddle.y,leftPaddle.x+leftPaddle.width,leftPaddle.y+leftPaddle.length);
		//draw right paddle
		fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.x+rightPaddle.width,rightPaddle.y+rightPaddle.length);

		// move ball
		ball.x += ball.xspeed;
		ball.y += ball.yspeed;

		// draw every 17ms
		wait1Msec(17);
	}

	drawTextAt(25,35,"%s","Game Over");
}
