# include <Siv3D.hpp> // OpenSiv3D v0.6.4

Grid<double> mp{
		{ 1, 5, 9, 13},
		{ 2, 6, 10, 14},
		{ 3, 7, 11, 15},
		{ 4, 8, 12, 16}
};


void reset() {

	int s = 4, t = 4;

	int cnt = Random(10000) + 100;

	for (int i = 0; i < cnt; i++) {
		int p = Random(3);

		if (p == 3) {

			if (t != 4) {
				int tmp = mp[s - 1][t - 1];
				mp[s - 1][t - 1] = mp[s - 1][t];
				mp[s - 1][t] = tmp;
				t++;
			}
		}

		if (p == 2) {

			if (t != 1) {
				int tmp = mp[s - 1][t - 1];
				mp[s - 1][t - 1] = mp[s - 1][t - 2];
				mp[s - 1][t - 2] = tmp;
				t--;
			}
		}

		if (p == 1) {

			if (s != 4) {
				int tmp = mp[s - 1][t - 1];
				mp[s - 1][t - 1] = mp[s][t - 1];
				mp[s][t - 1] = tmp;
				s++;
			}
		}

		if (p == 0) {

			if (s != 1) {
				int tmp = mp[s - 1][t - 1];
				mp[s - 1][t - 1] = mp[s - 2][t - 1];
				mp[s - 2][t - 1] = tmp;
				s--;
			}
		}
	}

}


void game(){

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });


	bool flag = 0;

	const Font font{ 50 };
	String text = U"";

	reset();

	int x, y;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (mp[i][j] == 16) {
				x = i + 1;
				y = j + 1;
			}
		}
	}


	while (System::Update())
	{
		Rect{ 30, 30, 450, 450 }.draw(Palette::Brown);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				if (mp[i][j] != 16) {

					text = U"{}"_fmt(mp[i][j]);
					Rect{ 40 + (i) * 110, 40 + (j) * 110, 100, 100 }.draw(Palette::Orange);
					font(text).drawAt(Vec2(90 + i * 110, 90 + j * 110), ColorF{ 0.25 });

				}
			}

		}


		if (SimpleGUI::Button(U"Up", Vec2{ 640, 40 }))
		{

			if (y != 4) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 1][y];
				mp[x - 1][y] = tmp;
				y++;
			}

		}

		if (SimpleGUI::Button(U"Down", Vec2{ 640, 90 }))
		{

			if (y != 1) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 1][y - 2];
				mp[x - 1][y - 2] = tmp;
				y--;
			}


		}

		if (SimpleGUI::Button(U"Left", Vec2{ 640, 140 }))
		{

			if (x != 4) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x][y - 1];
				mp[x][y - 1] = tmp;
				x++;
			}

		}

		if (SimpleGUI::Button(U"Right", Vec2{ 640, 190 }))
		{

			if (x != 1) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 2][y - 1];
				mp[x - 2][y - 1] = tmp;
				x--;
			}

		}

		if (KeyUp.pressed() && flag == 0) {

			if (y != 4) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 1][y];
				mp[x - 1][y] = tmp;
				y++;

				flag = 1;
			}

		}

		if (KeyDown.pressed() && flag == 0) {

			if (y != 1) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 1][y - 2];
				mp[x - 1][y - 2] = tmp;
				y--;

				flag = 1;
			}

		}

		if (KeyLeft.pressed() && flag == 0) {

			if (x != 4) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x][y - 1];
				mp[x][y - 1] = tmp;
				x++;

				flag = 1;
			}

		}

		if (KeyRight.pressed() && flag == 0) {

			if (x != 1) {
				int tmp = mp[x - 1][y - 1];
				mp[x - 1][y - 1] = mp[x - 2][y - 1];
				mp[x - 2][y - 1] = tmp;
				x--;

				flag = 1;

			}

		}

		if (KeyUp.up()) flag = 0;
		if (KeyDown.up()) flag = 0;
		if (KeyRight.up()) flag = 0;
		if (KeyLeft.up()) flag = 0;

		int sflag = 1;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (mp[i][j] != 4 * j + i + 1) sflag = 0;
			}
		}

		if (sflag == 1) {

			if (KeyR.pressed() && flag == 0) {

				reset();

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (mp[i][j] == 16) {
							x = i + 1;
							y = j + 1;
						}
					}
				}
			}

			if (SimpleGUI::Button(U"RESTART!!", Vec2{ 640, 240 }))
			{
				reset();

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (mp[i][j] == 16) {
							x = i + 1;
							y = j + 1;
						}
					}
				}
			}

			text = U"CLEAR!!";
			font(text).drawAt(Vec2(640, 320), ColorF{ 0.25 });
		}

	}

}


void Main(){

	Scene::SetBackground(Palette::White);

	const Font font{ 100 };
	String text = U"";

	int flag = 0;

	while (System::Update())
	{

		if (flag == 2) game();
		if (flag == 3) game();
		if (flag == 4) game();

		if (flag == 0) {
			text = U"Slide Puzzle";
			font(text).drawAt(Vec2(400, 240), ColorF{ Palette::Black });

			if (SimpleGUI::Button(U"START!!", Vec2{ 300, 340 }, 200))
			{
				flag = 1;
			}
		}

		if (flag == 1) {

			text = U"Mode Select";
			font(text).drawAt(Vec2(400, 150), ColorF{ Palette::Black });

			if (SimpleGUI::Button(U"3×3", Vec2{ 300, 240 }, 200))
			{
				flag = 2;
			}

			if (SimpleGUI::Button(U"4×4", Vec2{ 300, 300 }, 200))
			{
				flag = 3;
			}

			if (SimpleGUI::Button(U"5×5", Vec2{ 300, 360 }, 200))
			{
				flag = 4;
			}

		}

	}

}
