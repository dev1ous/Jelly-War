#include "PieceManager.h"
#include "Functions.h"
#include "Cache.h"
#include "Options.h"

PieceManager::PieceManager(int difficult)
	:Difficulté{ difficult }
{
	m_bufferHacking.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Hacking/TuyauPlace.wav");
	m_soundHacking.setBuffer(m_bufferHacking);

	Fond.setTexture(Cache::GetRessources<sf::Texture>("Hacking"));
	Fond.setOrigin(Fond.getGlobalBounds().width / 2, Fond.getGlobalBounds().height / 2);
	Fond.setPosition(960, 540);

	Emplace.setTexture(Cache::GetRessources<sf::Texture>("bouton_éteint"));
	EmplaceStart.setTexture(Cache::GetRessources<sf::Texture>("bouton_debut"));
	EmplaceEnd.setTexture(Cache::GetRessources<sf::Texture>("bouton_fin"));

	Emplace.setOrigin(Emplace.getGlobalBounds().width / 2, Emplace.getGlobalBounds().height / 2);
	EmplaceStart.setOrigin(EmplaceStart.getGlobalBounds().width / 2, EmplaceStart.getGlobalBounds().height / 2);
	EmplaceEnd.setOrigin(EmplaceEnd.getGlobalBounds().width / 2, EmplaceEnd.getGlobalBounds().height / 2);

	Jauge.setTexture(Cache::GetRessources<sf::Texture>("JaugeHacking"));

	Case.setTexture(Cache::GetRessources<sf::Texture>("carré selection"));
	Case.setOrigin({ 269 / 2,269 / 2 });


	Selection.setTexture(Cache::GetRessources<sf::Texture>("carré selection"));
	Selection.setOrigin({ 269 / 2,269 / 2 });


	Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
	Jauge.setPosition(1578, 724);
	Max = (int)Jauge.getGlobalBounds().height;

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Grille[y][x] = { x * Size + Space.x, y * Size + Space.y };
		}
	}
	
	switch (random::RandomInt(0, 4)) {
	case 0:
		One();
		break;
	case 1:
		Two();
		break;
	case 2:
		Three();
		break;
	case 3:
		Four();
		break;
	case 4:
		Five();
		break;
	}

	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][2].x, Grille[4][2].y + Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][3].x, Grille[4][3].y + Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][1].x, Grille[4][1].y + Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][0].x, Grille[4][0].y + Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][4].x, Grille[4][4].y + Size / 2), Emplace));

	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][0].x - Size / 2, Grille[4][0].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[4][4].x + Size / 2, Grille[4][4].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[3][0].x - Size / 2, Grille[3][0].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[3][4].x + Size / 2, Grille[3][4].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[2][0].x - Size / 2, Grille[2][0].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[2][4].x + Size / 2, Grille[2][4].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[1][0].x - Size / 2, Grille[1][0].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[1][4].x + Size / 2, Grille[1][4].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][4].x + Size / 2, Grille[0][4].y), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][0].x - Size / 2, Grille[0][0].y), Emplace));

	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][0].x, Grille[0][0].y - Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][4].x, Grille[0][4].y - Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][1].x, Grille[0][1].y - Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][3].x, Grille[0][3].y - Size / 2), Emplace));
	Light.push_back(std::make_pair(sf::Vector2f(Grille[0][2].x, Grille[0][2].y - Size / 2), Emplace));

	EmplaceStart.setPosition(Start);
	EmplaceEnd.setPosition(End);

	LoadTexture();
}

void PieceManager::Control()
{
	m_soundHacking.setVolume(Options::volumeBruitages);

	Gamepads g;
	if (!debut)
	{
		if (g.is_pressed(0, Xbox::Axis::RightJoystick_Up) && !Switch) {
			Case_Select.y--;
			if (Case_Select.y < 0) {
				Case_Select.y = 4;
			}
			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::RightJoystick_Down) && !Switch) {
			Case_Select.y++;
			if (Case_Select.y > 4) {
				Case_Select.y = 0;
			}

			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::RightJoystick_Left) && !Switch) {
			Case_Select.x--;
			if (Case_Select.x < 0) {
				Case_Select.x = 4;
			}
			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::RightJoystick_Right) && !Switch) {
			Case_Select.x++;
			if (Case_Select.x > 4) {
				Case_Select.x = 0;
			}

			Switch = true;
		}

		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Up) && !Switch) {
			int pre = Piece_Select;

			for (int i = (int)Puzzle.size() - 1; i > -1; i--) {
				if (i < Piece_Select - 1 && !Puzzle[i].Grille) {
					Piece_Select = i;
					break;
				}
			}

			if (Piece_Select == pre) {
				for (int i = 0; i < (int)Puzzle.size(); i++) {
					if (i > Piece_Select && !Puzzle[i].Grille) {
						Piece_Select = i;
					}
				}
			}

			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Down) && !Switch) {
			int pre = Piece_Select;

			for (int i = 0; i < (int)Puzzle.size(); i++) {
				if (i > Piece_Select + 1 && !Puzzle[i].Grille) {
					Piece_Select = i;
					break;
				}
			}

			if (Piece_Select == pre) {
				for (int i = 0; i < (int)Puzzle.size(); i++) {
					if (i < Piece_Select && !Puzzle[i].Grille) {
						Piece_Select = i;
						break;
					}
				}
			}

			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left) && !Switch) {
			int pre = Piece_Select;

			for (int i = (int)Puzzle.size() - 1; i > -1; i--) {
				if (i < Piece_Select && !Puzzle[i].Grille) {
					Piece_Select = i;
					break;
				}
			}

			if (Piece_Select == pre) {
				for (int i = 0; i < (int)Puzzle.size(); i++) {
					if (i > Piece_Select && !Puzzle[i].Grille) {
						Piece_Select = i;
					}
				}
			}

			Switch = true;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right) && !Switch) {
			int pre = Piece_Select;

			for (int i = 0; i < (int)Puzzle.size(); i++) {
				if (i > Piece_Select && !Puzzle[i].Grille) {
					Piece_Select = i;
					break;
				}
			}

			if (Piece_Select == pre) {
				for (int i = 0; i < (int)Puzzle.size(); i++) {
					if (i < Piece_Select && !Puzzle[i].Grille) {
						Piece_Select = i;
						break;
					}
				}
			}

			Switch = true;
		}

		if (g.is_pressed(0, Xbox::A) && !Switch) {
			Switch = true;

			if(m_soundHacking.getStatus() != sf::Sound::Status::Playing)
				m_soundHacking.play();

			bool find2 = false;
			int look = 0;
			for (auto& it : Puzzle) {
				if (sf::Vector2i(it.Position) == sf::Vector2i(Grille[Case_Select.y][Case_Select.x])) {
					it.Position = it.StartPos;
					it.Grille = false;
					Piece_Select = look;
					find2 = true;
					break;
				}
				look++;
			}

			if (!find2 && Piece_Select > -1) {

				Puzzle[Piece_Select].Position = Grille[Case_Select.y][Case_Select.x];
				Puzzle[Piece_Select].Grille = true;

				bool find3 = false;
				int pre = Piece_Select;

				for (int i = 0; i < (int)Puzzle.size(); i++) {
					if (i > Piece_Select && !Puzzle[i].Grille) {
						Piece_Select = i;
						find3 = true;
						break;
					}
				}

				if (Piece_Select == pre) {
					for (int i = 0; i < (int)Puzzle.size(); i++) {
						if (i < Piece_Select && !Puzzle[i].Grille) {
							Piece_Select = i;
							find3 = true;
							break;
						}
					}
				}

				if (!find3) {
					Piece_Select = -1;
				}
			}
		}

		if (!g.is_pressed(0, Xbox::Axis::LeftJoystick_Up) && !g.is_pressed(0, Xbox::Axis::LeftJoystick_Down) &&
			!g.is_pressed(0, Xbox::Axis::LeftJoystick_Left) && !g.is_pressed(0, Xbox::Axis::LeftJoystick_Right) &&
			!g.is_pressed(0, Xbox::Axis::RightJoystick_Up) && !g.is_pressed(0, Xbox::Axis::RightJoystick_Down) &&
			!g.is_pressed(0, Xbox::Axis::RightJoystick_Right) && !g.is_pressed(0, Xbox::Axis::RightJoystick_Left) &&
			!g.is_pressed(0, Xbox::A)) {
			Switch = false;
		}
	}
}

void PieceManager::LoadTexture()
{
	Sprite[0].setTexture(Cache::GetRessources<sf::Texture>("Droite"));
	Sprite[1].setTexture(Cache::GetRessources<sf::Texture>("Gauche"));
	Sprite[2].setTexture(Cache::GetRessources<sf::Texture>("Bas"));
	Sprite[3].setTexture(Cache::GetRessources<sf::Texture>("Haut"));
	Sprite[4].setTexture(Cache::GetRessources<sf::Texture>("Vertical"));
	Sprite[5].setTexture(Cache::GetRessources<sf::Texture>("Horizontal"));

	Sprite[0].setOrigin({ Size / 2,Size / 2 });
	Sprite[1].setOrigin({ Size / 2,Size / 2 });
	Sprite[2].setOrigin({ Size / 2,Size / 2 });
	Sprite[3].setOrigin({ Size / 2,Size / 2 });
	Sprite[4].setOrigin({ Size / 2,Size / 2 });
	Sprite[5].setOrigin({ Size / 2,Size / 2 });

	
}

void PieceManager::One()
{
	Start = { Space.x,Space.y - Size / 2 };
	End = { 4 * Size + Space.x, 4 * Size + Size / 2 + Space.y };

	std::vector<sf::Vector2f> Pos;

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 2; x++) {
			if (x == 1 && y == 4)
				;
			else {
				Pos.push_back(sf::Vector2f((x * Size + 2.f * Size + 50.f + (x * 22.5f)),
					((y + 1.f) * Size + (y * 4.f) - 1.f)));
			}
		}
	}

	std::vector<Piece::Forme> Stock;

	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));

	for (auto& it : Pos) {
		int i = (random::RandomInt(0, static_cast<int>(Stock.size()) - 1));

		Puzzle.push_back(Piece(it, Stock[i]));
		Stock.erase(Stock.begin() + i);
	}
}

void PieceManager::Two()
{
	Start = { Space.x - Size / 2, Size + Space.y };
	End = { 5 * Size + Space.x - Size / 2, 2 * Size + Space.y };

	std::vector<sf::Vector2f> Pos;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 2; x++) {
			Pos.push_back(sf::Vector2f((x * Size + 2.f * Size + 50.f + (x * 22.5f)),
				((y + 1.f) * Size + (y * 4.f) - 1.f)));
		}
	}

	std::vector<Piece::Forme> Stock;

	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleBas));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleHaut));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));

	for (auto& it : Pos) {
		int i = (random::RandomInt(0, static_cast<int>(Stock.size()) - 1));

		Puzzle.push_back(Piece(it, Stock[i]));
		Stock.erase(Stock.begin() + i);
	}
}

void PieceManager::Three()
{
	Start = { Space.x, 4 * Size + Size / 2 + Space.y };
	End = { 4 * Size + Space.x, Space.y - Size / 2 };

	std::vector<sf::Vector2f> Pos;

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 2; x++) {
			if (x == 1 && y == 4)
				;
			else {
				Pos.push_back(sf::Vector2f((x * Size + 2.f * Size + 50.f + (x * 22.5f)),
					((y + 1.f) * Size + (y * 4.f) - 1.f)));
			}
		}
	}

	std::vector<Piece::Forme> Stock;

	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleBas));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleHaut));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleBas));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleHaut));

	for (auto& it : Pos) {
		int i = (random::RandomInt(0, static_cast<int>(Stock.size()) - 1));

		Puzzle.push_back(Piece(it, Stock[i]));
		Stock.erase(Stock.begin() + i);
	}
}

void PieceManager::Four()
{
	Start = { 5 * Size - Size / 2 + Space.x,2 * Size + Space.y };
	End = { Space.x - Size / 2, 2 * Size + Space.y };

	std::vector<sf::Vector2f> Pos;

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 2; x++) {
			if (x == 1 && y == 4)
				;
			else {
				Pos.push_back(sf::Vector2f((x * Size + 2.f * Size + 50.f + (x * 22.5f)),
					((y + 1.f) * Size + (y * 4.f) - 1.f)));
			}
		}
	}

	std::vector<Piece::Forme> Stock;

	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleBas));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleHaut));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleBas));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleHaut));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));

	for (auto& it : Pos) {
		int i = (random::RandomInt(0, static_cast<int>(Stock.size()) - 1));

		Puzzle.push_back(Piece(it, Stock[i]));
		Stock.erase(Stock.begin() + i);
	}
}

void PieceManager::Five()
{
	Start = { Space.x - Size / 2, Size + Space.y };
	End = { 3 * Size + Space.x, 5 * Size - Size / 2 + Space.y };

	std::vector<sf::Vector2f> Pos;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 2; x++) {
			if (x == 1 && y == 3)
				;
			else {
				Pos.push_back(sf::Vector2f((x * Size + 2.f * Size + 50.f + (x * 22.5f)),
					((y + 1.f) * Size + (y * 4.f) - 1.f)));
			}
		}
	}

	std::vector<Piece::Forme> Stock;

	Stock.push_back(Piece::Forme(Piece::Forme::Horizontal));
	Stock.push_back(Piece::Forme(Piece::Forme::Vertical));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleGauche));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));
	Stock.push_back(Piece::Forme(Piece::Forme::AngleDroite));

	for (auto& it : Pos) {
		int i = (random::RandomInt(0, static_cast<int>(Stock.size()) - 1));

		Puzzle.push_back(Piece(it, Stock[i]));
		Stock.erase(Stock.begin() + i);
	}
}

void PieceManager::CheckFind()
{
	Piece* Current = nullptr;
	find = false;

	for (auto& it : Puzzle)
		it.Prec = nullptr;

	for (auto& it : Puzzle) {
		if (Collisions::Between2Circles(it.GetFirstPoint(), Start, 20, 0) ||
			Collisions::Between2Circles(it.GetSecondPoint(), Start, 20, 0)) {
			Current = &it;
		}
	}

	while (Current != nullptr) {

		bool find2 = false;
		for (auto& it : Puzzle) {
			if (it.Grille && *Current != it) {
				if ((Collisions::Between2Circles(Current->GetFirstPoint(), it.GetFirstPoint(), 20, 0) ||
					Collisions::Between2Circles(Current->GetFirstPoint(), it.GetSecondPoint(), 20, 0) ||
					Collisions::Between2Circles(Current->GetSecondPoint(), it.GetFirstPoint(), 20, 0) ||
					Collisions::Between2Circles(Current->GetSecondPoint(), it.GetSecondPoint(), 20, 0))) {
					if (Current->Prec != nullptr) {
						if (it != *Current->Prec) {
							it.Prec = Current;
							Current = &it;
							find2 = true;
							break;
						}
					}
					else {
						it.Prec = Current;
						Current = &it;
						find2 = true;
						break;
					}
				}
			}
		}

		if (Current->GetSecondPoint() == End || Current->GetFirstPoint() == End) {
			find = true;
			Win = true;
			Current = nullptr;
		}

		if (!find2) {
			Current = nullptr;
		}
	}
}

void PieceManager::Victory(const float& dt)
{
	timerVictory += dt;

	if (timerVictory > 0.2f && Phase == 0) {
		Light[0].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 1) {
		Light[1].second = EmplaceStart;
		Light[2].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 2) {
		Light[3].second = EmplaceStart;
		Light[4].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 3) {
		Light[5].second = EmplaceStart;
		Light[6].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 4) {
		Light[7].second = EmplaceStart;
		Light[8].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 5) {
		Light[9].second = EmplaceStart;
		Light[10].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 6) {
		Light[11].second = EmplaceStart;
		Light[12].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 7) {
		Light[13].second = EmplaceStart;
		Light[14].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 8) {
		Light[15].second = EmplaceStart;
		Light[16].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 9) {
		Light[17].second = EmplaceStart;
		Light[18].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (timerVictory > 0.2f && Phase == 10) {
		Light[19].second = EmplaceStart;
		Phase++;
		timerVictory = 0;
	}
	if (Phase == 11 && timerVictory > 0.2f )
	{
		fin = true;
		Go_fin(dt);
	}
}

void PieceManager::Go_debut(const float& dt)
{

	Fond.setPosition(960, 540 - posy);

	Jauge.setPosition(1578, 724 - posy);

	EmplaceStart.setPosition(Start.x,Start.y - posy);
	EmplaceEnd.setPosition(End.x, End.y - posy);


	posy -= 600.f * dt;

	if (posy <= 0)
	{
		posy = 0;
		Fond.setPosition(960, 540 - posy);

		Jauge.setPosition(1578, 724 - posy);

		EmplaceStart.setPosition(Start.x, Start.y - posy);
		EmplaceEnd.setPosition(End.x, End.y - posy);
		debut = false;
	}
}

void PieceManager::Go_fin(const float& dt)
{
	Fond.setPosition(960, 540 - posy);

	Jauge.setPosition(1578, 724 - posy);

	EmplaceStart.setPosition(Start.x, Start.y - posy);
	EmplaceEnd.setPosition(End.x, End.y - posy);

	posy += 600.f * dt;

	if (posy >= 1080)
	{
		posy = 1080;
		Fond.setPosition(960, 540 - posy);

		Jauge.setPosition(1578, 724 - posy);

		EmplaceStart.setPosition(Start.x, Start.y - posy);
		EmplaceEnd.setPosition(End.x, End.y - posy);

		Phase = 12;
	}
	
}

void PieceManager::Update(const float& dt)
{
	m_soundHacking.setVolume(Options::volumeBruitages);

	if (!debut)
	{

		if (Win) {
			Victory(dt);
		}

		if (Piece_Select < 0) {
			Selection.setPosition({ 5000,5000 });
		}

		int i = 0;
		for (auto& it : Puzzle) {
			it.Update();

			if (i == Piece_Select)
				Selection.setPosition(it.Position);

			i++;
		}

		Control();
		CheckFind();
	}
	else
	{
		Go_debut(dt);
	}
}

void PieceManager::Display(WindowManager& window, sf::Font& font)
{
	window.draw(Fond);
	//window.draw(Jauge);

	if (!debut && !fin)
	{


		for (auto& it : Puzzle) {
			it.display(window, Sprite[static_cast<int>(it.type)]);
		}

		for (auto& it : Light) {
			it.second.setPosition(it.first);
			window.draw(it.second);
		}
		window.draw(Case);
		window.draw(Selection);
	}

	Case.setPosition(Grille[Case_Select.y][Case_Select.x]);


	if (!Win) {
		window.draw(EmplaceStart);
		window.draw(EmplaceEnd);
	}

	
	
}