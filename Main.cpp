# include <Siv3D.hpp> // OpenSiv3D v0.6.4

Grid<double> mp{
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0}
};


void reset(int l,int m) {

	int s = l, t = m;

	int cnt = Random(10000) + 100;

	for (int i = 0; i < cnt; i++) {
		int p = Random(3);

		if (p == 3) {

			if (t != m) {
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

			if (s != l) {
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


void game(int l,int m){

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	for (int i = 0; i < l;i++) {
		for (int j = 0; j < m; j++) {
			mp[i][j] = l*j + i + 1;
		}
	}


	bool flag = 0;

	const Font font{ 50 };
	const Font f2{ 100 };
	const Font f3{ 80 };
	const Font f5{ 40 };
	const Font f6{ 30 };
	String text = U"";

	reset(l,m);

	int fontsize = 100;

	int x, y;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < m; j++) {
			if (mp[i][j] == l*m) {
				x = i + 1;
				y = j + 1;
			}
		}
	}


	while (System::Update())
	{
		Rect{ 30, 30, 10+110*4,10+110*4 }.draw(Palette::Brown);

		for (int i = 0; i < l; i++) {
			for (int j = 0; j < m; j++) {

				if (mp[i][j] != l*m) {

					text = U"{}"_fmt(mp[i][j]);
					Rect{ 40 + (i) * (440/l), 40 + (j) * (440/m), (440-l*10)/l, (440 - m * 10) / m }.draw(Palette::Orange);
					if(l == 4) font(text).drawAt(Vec2(40+ (440 - l * 10) / l/2 + i * (440/l), 40+(440 - m * 10) / m/2 + j * (440/m)) , ColorF{0.25});
					if(l == 2) f2(text).drawAt(Vec2(40 + (440 - l * 10) / l / 2 + i * (440 / l), 40 + (440 - m * 10) / m / 2 + j * (440 / m)), ColorF{ 0.25 });
					if(l == 3) f3(text).drawAt(Vec2(40 + (440 - l * 10) / l / 2 + i * (440 / l), 40 + (440 - m * 10) / m / 2 + j * (440 / m)), ColorF{ 0.25 });
					if(l == 5) f5(text).drawAt(Vec2(40 + (440 - l * 10) / l / 2 + i * (440 / l), 40 + (440 - m * 10) / m / 2 + j * (440 / m)), ColorF{ 0.25 });
					if(l == 6) f6(text).drawAt(Vec2(40 + (440 - l * 10) / l / 2 + i * (440 / l), 40 + (440 - m * 10) / m / 2 + j * (440 / m)), ColorF{ 0.25 });
				}
			}

		}


		if (SimpleGUI::Button(U"Up", Vec2{ 640, 40 }))
		{

			if (y != m) {
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

			if (x != l) {
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

			if (y != m) {
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

			if (x != l) {
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

		for (int i = 0; i < l; i++) {
			for (int j = 0; j < m; j++) {
				if (mp[i][j] != l * j + i + 1) sflag = 0;
			}
		}

		if (sflag == 1) {

			if (KeyR.pressed() && flag == 0) {

				reset(l,m);

				for (int i = 0; i < l; i++) {
					for (int j = 0; j < m; j++) {
						if (mp[i][j] == l*m) {
							x = i + 1;
							y = j + 1;
						}
					}
				}
			}

			if (SimpleGUI::Button(U"RESTART!!", Vec2{ 640, 240 }))
			{
				reset(l,m);

				for (int i = 0; i < l; i++) {
					for (int j = 0; j < m; j++) {
						if (mp[i][j] == l*m) {
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

		if (flag == 2) game(2,2);
		if (flag == 3) game(3,3);
		if (flag == 4) game(4,4);
		if (flag == 5) game(5,5);
		if (flag == 6) game(6, 6);

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

			if (SimpleGUI::Button(U"2×2", Vec2{ 100, 240 }, 200))
			{
				flag = 2;
			}

			if (SimpleGUI::Button(U"3×3", Vec2{ 100, 300 }, 200))
			{
				flag = 3;
			}

			if (SimpleGUI::Button(U"4×4", Vec2{ 100, 360 }, 200))
			{
				flag = 4;
			}

			if (SimpleGUI::Button(U"5×5", Vec2{ 100, 420 }, 200))
			{
				flag = 5;
			}

			if (SimpleGUI::Button(U"6×6", Vec2{ 100, 480 }, 200))
			{
				flag = 6;
			}

		}

	}

}
