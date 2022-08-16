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

int flag2 = 0;

double r1 = 0.8, g1 = 0.9, b1 = 1.0;
double r2 = 0.6, g2 = 0.27, b2 = 0.0;
double r3 = 1.0, g3 = 0.7, b3 = 0.02;




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
	Scene::SetBackground(ColorF{ r1, g1, b1 });

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
		Rect{ 30, 30, 10+110*4,10+110*4 }.draw(ColorF{ r2,g2,b2 });

		for (int i = 0; i < l; i++) {
			for (int j = 0; j < m; j++) {

				if (mp[i][j] != l*m) {

					text = U"{}"_fmt(mp[i][j]);
					Rect{ 40 + (i) * (440/l), 40 + (j) * (440/m), (440-l*10)/l, (440 - m * 10) / m }.draw(ColorF{ r3,g3,b3 });
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

		if (SimpleGUI::Button(U"back", Vec2{ 20, 500 }, 100))
		{
			flag2 = 1;
			return;
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

void g_option() {

	const Font font{ 30 };

	String text;


	while (System::Update())
	{
		font(text).drawAt(Vec2(400, 150), ColorF{ Palette::Black });

		if (SimpleGUI::Button(U"background", Vec2{ 500, 100 }, 150))
		{
			flag2 = 8;
			return;
		}

		if (SimpleGUI::Button(U"盤面", Vec2{ 500, 200 }, 150))
		{
			flag2 = 9;
			return;
		}

		if (SimpleGUI::Button(U"パネル", Vec2{ 500, 300 }, 150))
		{
			flag2 = 10;
			return;
		}

		if (SimpleGUI::Button(U"リセット", Vec2{ 500, 400 }, 150))
		{
			flag2 = 11;
			return;
		}


		if (SimpleGUI::Button(U"back", Vec2{ 20, 500 }, 100))
		{
			flag2 = 1;
			return;
		}
	}
}

void reset_c() {

	r1 = 0.8, g1 = 0.9, b1 = 1.0;
	r2 = 0.6, g2 = 0.27, b2 = 0.0;
	r3 = 1.0, g3 = 0.7, b3 = 0.02;

	flag2 = 1;

}

void ch_color(double r, double g, double b,int type) {

	const Font font{ 30 };

	String text;

	double x1 = 60 + 600 * r;
	double x2 = 60 + 600 * g;
	double x3 = 60 + 600 * b;

	bool grab = 0;

	while (System::Update())
	{

		int ra = r * 255;
		int ga = g * 255;
		int ba = b * 255;

		text = U"{} {} {}"_fmt(ra,ga,ba);

		font(text).drawAt(Vec2(600, 500), ColorF{ Palette::Black });

		Scene::SetBackground(ColorF{ r, g, b });


		double mx = Cursor::Pos().x;
		double my = Cursor::Pos().y;

		Rect{ 60, 80, 600, 20 }.draw(Palette::Black);

		Rect{ 60, 200, 600, 20 }.draw(Palette::Black);

		Rect{ 60, 320, 600, 20 }.draw(Palette::Black);

		Circle{ x1, 90, 40 }.draw(Palette::Black);

		Circle{ x2, 210, 40 }.draw(Palette::Black);

		Circle{ x3, 330, 40 }.draw(Palette::Black);

		Circle{ x1, 90, 35 }.draw();

		Circle{ x2, 210, 35 }.draw();

		Circle{ x3, 330, 35 }.draw();


		if (MouseL.pressed())  grab = 1;

		else grab = 0;


		if (grab) {

			if ((mx - x1) * (mx - x1) + (my - 90) * (my - 90) <= 1600) {
				if(mx <= 660 && mx >= 60) x1 = mx;
				r = (x1 - 60) / 600;
			}


			if ((mx - x2) * (mx - x2) + (my - 210) * (my - 210) <= 1600) {
				if (mx <= 660 && mx >= 60) x2 = mx;
				g = (x2 - 60) / 600;
			}


			if ((mx - x3) * (mx - x3) + (my - 330) * (my - 330) <= 1600) {
				if (mx <= 660 && mx >= 60) x3 = mx;
				b = (x3 - 60) / 600;
			}

		}

		if (type == 1) {
			r1 = r;
			g1 = g;
			b1 = b;
		}

		if (type == 2) {
			r2 = r;
			g2 = g;
			b2 = b;
		}

		if (type == 3) {
			r3 = r;
			g3 = g;
			b3 = b;
		}

		if (SimpleGUI::Button(U"back", Vec2{ 20, 500 }, 100))
		{
			flag2 = 1;
			return;
		}

	}
}

void Main(){

	Window::SetTitle(U"Slide_Puzzle");

	Scene::SetBackground(Palette::White);

	const Font font{ 100 };
	String text = U"";

	while (System::Update())
	{

		if (flag2 == 2) game(2,2);
		if (flag2 == 3) game(3,3);
		if (flag2 == 4) game(4,4);
		if (flag2 == 5) game(5,5);
		if (flag2 == 6) game(6, 6);
		if (flag2 == 7) g_option();
		if (flag2 == 8) ch_color(r1,g1,b1,1);
		if (flag2 == 9) ch_color(r2, g2, b2,2);
		if (flag2 == 10) ch_color(r3, g3, b3,3);
		if (flag2 == 11) reset_c();

		if (flag2 == 0) {
			text = U"Slide Puzzle";
			font(text).drawAt(Vec2(400, 240), ColorF{ Palette::Black });

			if (SimpleGUI::Button(U"START!!", Vec2{ 300, 340 }, 200))
			{
				flag2 = 1;
			}
		}

		if (flag2 == 1) {

			Scene::SetBackground(Palette::White);

			text = U"Mode Select";
			font(text).drawAt(Vec2(400, 150), ColorF{ Palette::Black });

			if (SimpleGUI::Button(U"2×2", Vec2{ 100, 240 }, 200))
			{
				flag2 = 2;
			}

			if (SimpleGUI::Button(U"3×3", Vec2{ 100, 300 }, 200))
			{
				flag2 = 3;
			}

			if (SimpleGUI::Button(U"4×4", Vec2{ 100, 360 }, 200))
			{
				flag2 = 4;
			}

			if (SimpleGUI::Button(U"5×5", Vec2{ 100, 420 }, 200))
			{
				flag2 = 5;
			}

			if (SimpleGUI::Button(U"6×6", Vec2{ 100, 480 }, 200))
			{
				flag2 = 6;
			}


			if (SimpleGUI::Button(U"option", Vec2{ 500, 480 }, 200))
			{
				flag2 = 7;
			}

		}

	}

}
