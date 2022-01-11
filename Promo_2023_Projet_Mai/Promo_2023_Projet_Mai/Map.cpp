#include "Map.h"
#include "Cache.h"
#include <random>
#include "Main_Joueur.h"
#include <array>
#include "Functions.h"
#include "Gamepad.h"
#include "Network.h"
#include "Game.h"
#include "Battle_Royal.h"
#include "Auto_tamponneuse.h"
#include "TerritoryConquest.h"
#include "FSM_Manager.h"
#include "Transition.h"

Map::Map(AssetManager& assets, Draw& Drawable)
{
	std::array<sf::Vector2f, 8> pos;
	pos[0] = sf::Vector2f(2200, 3475);
	pos[1] = sf::Vector2f(775, 530);
	pos[2] = sf::Vector2f(4130, 3120);
	pos[3] = sf::Vector2f(7490, 1400);
	pos[4] = sf::Vector2f(3170, 4270);
	pos[5] = sf::Vector2f(1840, 7530);
	pos[6] = sf::Vector2f(5535, 5760);
	pos[7] = sf::Vector2f(6815, 7060);

	// node ressources, machine, rayon, OffsetSpawnAnim, OffsetAnim, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset
	std::array<std::tuple<std::string, std::string, std::string, sf::Vector2f, sf::Vector2f, Animator, Animator, Animator, Animator, sf::Vector2f, Animator, Animator, sf::Vector2f>, 3> machines;

	machines[0] = std::make_tuple("sprite_sheet_liquide", "sprite_sheet_anim_récolteur_liquide", "sprite_sheet_fx_liquide", sf::Vector2f(-70, 83), sf::Vector2f(-69, 75),
		Animator(sf::IntRect(0, 265, 200, 281), 11, 0.1f), Animator(sf::IntRect(0, 0, 198, 265), 12, 0.1f),
		Animator(sf::IntRect(0, 56, 40, 230), 11, 0.1f), Animator(sf::IntRect(0, 0, 38, 56), 12, 0.1f), sf::Vector2f(0, -25.5f),
		Animator(sf::IntRect(0, 0, 139, 50), 17, 0.1f, 50, false), Animator(sf::IntRect(0, 0, 152, 244), 17, 0.1f, 244, false), sf::Vector2f(-15, -30));

	machines[1] = std::make_tuple("sprite_sheet_roche", "sprite_sheet_anim_récolteur_drill", "sprite_sheet_fx_roche", sf::Vector2f(-62, 87), sf::Vector2f(-62, 82),
		Animator(sf::IntRect(0, 265, 212, 304), 12, 0.1f), Animator(sf::IntRect(0, 0, 224, 265), 7, 0.1f),
		Animator(sf::IntRect(0, 336, 42, 192), 12, 0.1f), Animator(sf::IntRect(0, 286, 40, 50), 7, 0.1f), sf::Vector2f(2, -44),
		Animator(sf::IntRect(0, 0, 142, 46), 12, 0.1f, 46, false), Animator(sf::IntRect(0, 0, 152, 244), 16, 0.1f, 244, false), sf::Vector2f(-15, -30));

	machines[2] = std::make_tuple("plasma_recolte", "sprite_sheet_anim_récolteur_plasma", "sprite_sheet_plasma", sf::Vector2f(-116, 85), sf::Vector2f(-116, 75),
		Animator(sf::IntRect(0, 265, 264, 265), 12, 0.1f), Animator(sf::IntRect(0, 0, 232, 265), 6, 0.1f),
		Animator(sf::IntRect(0, 582, 40, 221), 12, 0.1f), Animator(sf::IntRect(0, 528, 40, 54), 6, 0.1f), sf::Vector2f(0, -15),
		Animator(sf::IntRect(0, 0, 212, 54), 1, 0.1f, 50, false), Animator(sf::IntRect(0, 0, 212, 249), 21, 0.1f, 249, false), sf::Vector2f(0, -4));

	std::mt19937 Randomizer{ std::random_device{}() };
	std::uniform_int_distribution<> dist{ 0 ,2 };

	std::map<int, int > v;

	for (int i = 0; i < 8; i++)
	{
		int random{ 0 };

		do {
			random = dist(Randomizer);
		} while (v[random] >= 3);

		v[random]++;

		auto [Minerai, Machine, SecMinerai, OffsetSpawn, Offset, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset] = machines.at(random);

		auto& generated = m_nodesGenerated.emplace_back();
		generated.type = random;
		generated.BasePos = pos[i];
		generated.machine_anim_spawn = spawnAnim;
		generated.machine_anim = Anim;
		generated.machine_fx_anim_spawn = fxSpawnanim;
		generated.machine_fx_anim = fxanim;
		generated.offset_anim = Offset;
		generated.offset_anim_spawn = OffsetSpawn;
		generated.offset_fx_anim_spawn = offset_fx;
		generated.Ressources_anim = ressourcesAnim;
		generated.Rayon_anim = ressourcesfxAnim;
		generated.offset_beam = beamoffset;

		generated.Minerais.setTexture(Cache::GetRessources<sf::Texture>(Minerai));
		generated.Beam.setTexture(Cache::GetRessources<sf::Texture>(SecMinerai));
		generated.machine_sprite.setTexture(Cache::GetRessources<sf::Texture>(Machine));

		generated.Minerais.setPosition(generated.BasePos);

		generated.Ressources_anim.Animation(generated.Minerais, 0.f);
		generated.Rayon_anim.Animation(generated.Beam, 0.f);
		generated.machine_anim.Animation(generated.machine_sprite, 0.f);
		generated.machine_fx_anim.Animation(generated.machine_fx_sprite, 0.f);

		Drawable.emplace_back(std::make_pair(false, &generated.machine_sprite));
	}

	BoutonGame.sprite.setTexture(Cache::GetRessources<sf::Texture>("Bouton_minijeu"));
	BoutonGame.sprite.setOrigin(85, BoutonGame.Rect.height - 25.f);
	BoutonGame.sprite.setPosition(4000, 4000);
	BoutonGame.sprite.setTextureRect(BoutonGame.Rect);

	sf::RectangleShape Coliders;
	Coliders.setFillColor(sf::Color::Black);

	sf::RenderTexture rt;
	rt.create(8000, 8000);
	rt.clear(sf::Color::White);

	for (Nodes& node : m_nodesGenerated) {
		Coliders.setSize(sf::Vector2f(node.Minerais.getGlobalBounds().width, node.Minerais.getGlobalBounds().height));
		Coliders.setPosition(node.Minerais.getPosition());

		node.Boost = Feedback("MBoost fb", node.machine_sprite.getPosition() +
			sf::Vector2f(50, 4), { 0,0,70,81 },
			26, 1.2f / 26.f, 0.1f);
		node.Boost.End();
		node.Boost.Animation(node.machine_sprite.getPosition() +
			sf::Vector2f(50, 4), 0.f);

		//rt.draw(Coliders);
	}

	assets.Display(rt);
	Drawable.emplace_back(std::make_pair(false, &BoutonGame.sprite));

	rt.display();

	m_cols = rt.getTexture().copyToImage();

	SBboost.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Bonus - Machine Boost.wav");
	Sboost.setBuffer(SBboost);
}

Map::Nodes* Map::getNode(sf::Vector2f pos)
{
	for (Nodes& node : m_nodesGenerated) {
		if (Collisions::circleRect(pos, 100.f, node.Minerais.getGlobalBounds())) {
			return &node;
		}
	}


	return nullptr;
}

void Map::ResetBouton()
{
	BoutonGame.timer = TimerRestart;
	BoutonGame.Ready = false;
	BoutonGame.start = false;
	BoutonGame.timerminijeu = 0;
	BoutonGame.Rect = { 0,0,170,280 };
}

void Map::AddtrapsRessource(sf::Vector2f pos, Draw& Drawable, Main_Joueur* joueur)
{
	// node ressources, machine, rayon, OffsetSpawnAnim, OffsetAnim, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset
	std::tuple<std::string, std::string, std::string, sf::Vector2f, sf::Vector2f, Animator, Animator, Animator, Animator, sf::Vector2f, Animator, Animator, sf::Vector2f> machines;

	machines = std::make_tuple("sprite_sheet_roche", "sprite_sheet_anim_récolteur_drill", "sprite_sheet_fx_roche", sf::Vector2f(-62, 87), sf::Vector2f(-62, 82),
		Animator(sf::IntRect(0, 265, 212, 304), 12, 0.1f), Animator(sf::IntRect(0, 0, 224, 265), 7, 0.1f),
		Animator(sf::IntRect(0, 336, 42, 192), 12, 0.1f), Animator(sf::IntRect(0, 286, 40, 50), 7, 0.1f), sf::Vector2f(2, -44),
		Animator(sf::IntRect(0, 0, 142, 46), 12, 0.1f, 46, false), Animator(sf::IntRect(0, 0, 152, 244), 16, 0.1f, 244, false), sf::Vector2f(-15, -30));

	std::mt19937 Randomizer{ std::random_device{}() };
	std::uniform_int_distribution<> dist{ 0 ,2 };

	std::map<int, int > v;

	auto [Minerai, Machine, SecMinerai, OffsetSpawn, Offset, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset] = machines;

	auto& generated = m_nodesGenerated.emplace_back();
	generated.type = 4;
	generated.BasePos = pos;
	generated.machine_anim_spawn = spawnAnim;
	generated.machine_anim = Anim;
	generated.machine_fx_anim_spawn = fxSpawnanim;
	generated.machine_fx_anim = fxanim;
	generated.offset_anim = Offset;
	generated.offset_anim_spawn = OffsetSpawn;
	generated.offset_fx_anim_spawn = offset_fx;
	generated.Ressources_anim = ressourcesAnim;
	generated.Rayon_anim = ressourcesfxAnim;
	generated.offset_beam = beamoffset;
	generated.owner = joueur;

	generated.Minerais.setTexture(Cache::GetRessources<sf::Texture>(Minerai));
	generated.Beam.setTexture(Cache::GetRessources<sf::Texture>(SecMinerai));
	generated.machine_sprite.setTexture(Cache::GetRessources<sf::Texture>(Machine));

	generated.Minerais.setPosition(generated.BasePos);

	generated.Ressources_anim.Animation(generated.Minerais, 0.f);
	generated.Rayon_anim.Animation(generated.Beam, 0.f);
	generated.machine_anim.Animation(generated.machine_sprite, 0.f);
	generated.machine_fx_anim.Animation(generated.machine_fx_sprite, 0.f);

	Drawable.emplace_back(std::make_pair(false, &generated.machine_sprite));

	/*sf::RectangleShape Coliders;
	Coliders.setFillColor(sf::Color::Black);

	sf::RenderTexture rt;
	rt.create(8000, 8000);
	rt.clear(sf::Color::White);

	sf::Texture current_col;
	current_col.loadFromImage(m_cols);
	sf::Sprite SCurrent_col(current_col);
	rt.draw(SCurrent_col);

	Coliders.setSize(sf::Vector2f(generated.Minerais.getGlobalBounds().width, generated.Minerais.getGlobalBounds().height));
	Coliders.setPosition(generated.Minerais.getPosition());
	rt.draw(Coliders);

	rt.display();

	m_cols.copy(rt.getTexture().copyToImage(), 8000, 8000);*/
}

void Map::RemoveTrapsRessources(sf::Vector2f pos, Draw& Drawable)
{
	auto it = std::find_if(std::begin(m_nodesGenerated), std::end(m_nodesGenerated), [pos](Map::Nodes& node) {return node.BasePos == pos; });

	if (it != std::end(m_nodesGenerated)) {
		Drawable.erase(std::remove_if(std::begin(Drawable), std::end(Drawable),
			[&it](std::pair<bool, sf::Sprite*> d) {return d.second == &it->machine_sprite; }));

		//sf::RectangleShape Coliders;
		//Coliders.setFillColor(sf::Color::White);

		//sf::RenderTexture rt;
		//rt.create(8000, 8000);
		//rt.clear(sf::Color::White);

		//sf::Texture current_col;
		//current_col.loadFromImage(m_cols);
		//sf::Sprite SCurrent_col(current_col);
		//rt.draw(SCurrent_col);

		//Coliders.setSize(sf::Vector2f(it->Minerais.getGlobalBounds().width, it->Minerais.getGlobalBounds().height));
		//Coliders.setPosition(it->Minerais.getPosition());
		//rt.draw(Coliders);

		//rt.display();

		//m_cols.copy(rt.getTexture().copyToImage(), 8000, 8000);

		m_nodesGenerated.erase(it);
	}
}

void Map::ChangeTexture()
{
	// node ressources, machine, rayon, OffsetSpawnAnim, OffsetAnim, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset
	std::array<std::tuple<std::string, std::string, std::string, sf::Vector2f, sf::Vector2f, Animator, Animator, Animator, Animator, sf::Vector2f, Animator, Animator, sf::Vector2f>, 3> machines;

	machines[0] = std::make_tuple("sprite_sheet_liquide", "sprite_sheet_anim_récolteur_liquide", "sprite_sheet_fx_liquide", sf::Vector2f(-70, 83), sf::Vector2f(-69, 75),
		Animator(sf::IntRect(0, 265, 200, 281), 11, 0.1f), Animator(sf::IntRect(0, 0, 198, 265), 12, 0.1f),
		Animator(sf::IntRect(0, 56, 40, 230), 11, 0.1f), Animator(sf::IntRect(0, 0, 38, 56), 12, 0.1f), sf::Vector2f(0, -25.5f),
		Animator(sf::IntRect(0, 0, 139, 50), 17, 0.1f, 50, false), Animator(sf::IntRect(0, 0, 152, 244), 17, 0.1f, 244, false), sf::Vector2f(-15, -30));

	machines[1] = std::make_tuple("sprite_sheet_roche", "sprite_sheet_anim_récolteur_drill", "sprite_sheet_fx_roche", sf::Vector2f(-62, 87), sf::Vector2f(-62, 82),
		Animator(sf::IntRect(0, 265, 212, 304), 12, 0.1f), Animator(sf::IntRect(0, 0, 224, 265), 7, 0.1f),
		Animator(sf::IntRect(0, 336, 42, 192), 12, 0.1f), Animator(sf::IntRect(0, 286, 40, 50), 7, 0.1f), sf::Vector2f(2, -44),
		Animator(sf::IntRect(0, 0, 142, 46), 12, 0.1f, 46, false), Animator(sf::IntRect(0, 0, 152, 244), 16, 0.1f, 244, false), sf::Vector2f(-15, -30));

	machines[2] = std::make_tuple("plasma_recolte", "sprite_sheet_anim_récolteur_plasma", "sprite_sheet_plasma", sf::Vector2f(-116, 85), sf::Vector2f(-116, 75),
		Animator(sf::IntRect(0, 265, 264, 265), 12, 0.1f), Animator(sf::IntRect(0, 0, 232, 265), 6, 0.1f),
		Animator(sf::IntRect(0, 582, 40, 221), 12, 0.1f), Animator(sf::IntRect(0, 528, 40, 54), 6, 0.1f), sf::Vector2f(0, -15),
		Animator(sf::IntRect(0, 0, 212, 54), 1, 0.1f, 50, false), Animator(sf::IntRect(0, 0, 212, 249), 21, 0.1f, 249, false), sf::Vector2f(0, -4));


	for (Nodes& node : m_nodesGenerated) {
		auto [Minerai, Machine, SecMinerai, OffsetSpawn, Offset, spawnAnim, Anim, fxSpawnanim, fxanim, offset_fx, ressourcesAnim, ressourcesfxAnim, beamoffset] = machines[node.type];

		node.machine_anim_spawn = spawnAnim;
		node.machine_anim = Anim;
		node.machine_fx_anim_spawn = fxSpawnanim;
		node.machine_fx_anim = fxanim;
		node.offset_anim = Offset;
		node.offset_anim_spawn = OffsetSpawn;
		node.offset_fx_anim_spawn = offset_fx;
		node.Ressources_anim = ressourcesAnim;
		node.Rayon_anim = ressourcesfxAnim;
		node.offset_beam = beamoffset;

		node.Minerais.setTexture(Cache::GetRessources<sf::Texture>(Minerai), true);
		node.Beam.setTexture(Cache::GetRessources<sf::Texture>(SecMinerai), true);
		node.machine_sprite.setTexture(Cache::GetRessources<sf::Texture>(Machine), true);

		node.Minerais.setPosition(node.BasePos);

		node.Ressources_anim.Animation(node.Minerais, 0.f);
		node.Rayon_anim.Animation(node.Beam, 0.f);
		node.machine_anim.Animation(node.machine_sprite, 0.f);
		node.machine_fx_anim.Animation(node.machine_fx_sprite, 0.f);
	}
}

void Map::ReceiveBonus(Main_Joueur* joueur, std::map<int, Main_Joueur*> others)
{
	for (Nodes& node : m_nodesGenerated) {

		for (auto& it : others) {
			if (Collisions::Between2Circles(it.second->GetPos(), node.BasePos, 250)) {
				if (it.second->GetUseBonus() &&
					it.second->GetFirstBonus().GetType() == Bonus::Type::MachineBoost) {
					node.Bonus = true;
					Sboost.play();
				}
			}
		}
		if (Collisions::Between2Circles(joueur->GetPos(), node.BasePos, 250)) {
			if (joueur->GetUseBonus() &&
				joueur->GetFirstBonus().GetType() == Bonus::Type::MachineBoost) {
				node.Bonus = true;
				Sboost.play();
			}
		}
	}
}

void Map::UpdateBouton(const float& dt, Main_Joueur* joueur, Network* network, FSM_Manager& fsm, Game& game)
{
	if (!BoutonGame.Ready) {
		if (network != nullptr && network->type() == "Host")
			BoutonGame.timer -= dt;

		if (BoutonGame.timer < 0.f) {
			BoutonGame.Ready = true;
		}
	}
	else {
		BoutonGame.Rect.left = 170;

		if (BoutonGame.start) {
			BoutonGame.timerminijeu += dt;

			if (BoutonGame.timerminijeu > 5.f) {
				ResetBouton();

				if (network->type() == "Host") {
					
					if (Minijeu == 1) {
						fsm.SoftAddTransition<Transition<Battle_Royal>>(fsm, game.GetWindow(), game.GetFont(), true);
						//fsm.AddState(FSM_Manager::create<Battle_Royal>(fsm, game.GetWindow(), game.GetFont(), true));
					}
					if (Minijeu == 2) {
						fsm.SoftAddTransition<Transition<Auto_tamponneuse>>(fsm, game.GetWindow(), game.GetFont(), true);
						//fsm.AddState(FSM_Manager::create<Auto_tamponneuse>(fsm, game.GetWindow(), game.GetFont(), true));
					}
					if (Minijeu == 3) {
						fsm.SoftAddTransition<Transition<TerritoryConquest>>(fsm, game.GetWindow(), game.GetFont(), true);
						//fsm.AddState(FSM_Manager::create<TerritoryConquest>(fsm, game.GetWindow(), game.GetFont(), true));
					}

					if (network != nullptr) {
						network->updateInfosState(Minijeu, BoutonGame);
						Minijeu++;

						if (Minijeu > 3) {
							Minijeu = 1;
						}
					}
				}
			}
		}
	}

	BoutonGame.sprite.setTextureRect(BoutonGame.Rect);

	if (Collisions::Between2Circles(joueur->GetPos(), BoutonGame.sprite.getPosition(), 200)) {
		Gamepads g;
		if (joueur->getRessource(0) >= 100.f && joueur->getRessource(1) >= 100.f && joueur->getRessource(2) >= 100.f) {
			if (g.on_pressed(0, Xbox::A)) {
				network->win();
				game.win();
			}
		}
		else if (BoutonGame.Ready) {
			if (g.on_pressed(0, Xbox::A)) {
				BoutonGame.start = true;
				BoutonGame.Ready = false;
			}
		}
	}
}

void Map::Update(float dt)
{
	for (Nodes& node : m_nodesGenerated) {
		node.Ressources_anim.Animation(node.Minerais, dt);
		node.Rayon_anim.Animation(node.Beam, dt);

		if (node.owner != nullptr) {

			switch (node.owner->getcolor())
			{
			case Joueur::Couleur::One:		node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_cyan"));	break;
			case Joueur::Couleur::Two:		node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_rouge"));	break;
			case Joueur::Couleur::Three:	node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_rose"));	break;
			case Joueur::Couleur::Four:		node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_bleu"));	break;
			case Joueur::Couleur::Five:		node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_orange"));	break;
			case Joueur::Couleur::Six:		node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_jaune"));	break;
			case Joueur::Couleur::Seven:	node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_violet"));	break;
			case Joueur::Couleur::Height:	node.machine_fx_sprite.setTexture(Cache::GetRessources<sf::Texture>("fx_récolteurs_vert"));	break;

			default: break;
			}

			if (!node.machine_anim_spawn.Get_End()) {
				node.machine_anim_spawn.Animation_NoRestart(node.machine_sprite, dt);
				node.machine_fx_anim_spawn.Animation_NoRestart(node.machine_fx_sprite, dt);
			}

			if (node.machine_anim_spawn.Get_End()) {
				node.machine_anim.Animation(node.machine_sprite, dt);
				node.machine_fx_anim.Animation(node.machine_fx_sprite, dt);
			}

			if (node.Bonus) {
				node.TimerBoost += dt;
				node.Boost.Animation(node.machine_sprite.getPosition() +
					sf::Vector2f(50, 4), dt);

				if (node.TimerBoost > 30.f) {
					node.Bonus = false;
					node.Boost.End();
					node.Boost.Animation_NoRestart(node.machine_sprite.getPosition()
						+ sf::Vector2f(50, 4), dt);
					node.TimerBoost = 0;
				}
			}

		}
	}
}

void Map::DisplayTimer(WindowManager& window, sf::Font& font)
{
	if (!BoutonGame.Ready) {
		sf::Text tmp = func::CreateText(std::to_string((int)BoutonGame.timer), font, 50, BoutonGame.sprite.getPosition() - sf::Vector2f(0, 200), sf::Color::White);
		tmp.setOrigin(func::GetMiddle(tmp));
		window.draw(tmp);
	}
}

void Map::display(WindowManager& window)
{
	for (Nodes& node : m_nodesGenerated) {
		node.Minerais.setPosition(node.BasePos);
		window.draw(node.Minerais);

		node.machine_sprite.setPosition(node.BasePos - node.offset_anim_spawn);

		if (node.owner != nullptr) {

			if (!node.machine_anim_spawn.Get_End()) {
				node.machine_sprite.setPosition(node.BasePos - node.offset_anim_spawn);
				node.machine_fx_sprite.setPosition(node.BasePos - node.offset_anim_spawn + node.offset_fx_anim_spawn);
			}

			if (node.machine_anim_spawn.Get_End()) {
				node.machine_sprite.setPosition(node.BasePos - node.offset_anim);
				node.machine_fx_sprite.setPosition(node.BasePos - node.offset_anim - sf::Vector2f(0, 104));
			}

			window.draw(node.machine_fx_sprite);
			node.machine_sprite.setScale(1.f, 1.f);
			//window.draw(node.machine_sprite);
		}
		else {
			node.machine_sprite.setScale(1.f, 0.f);
			node.Beam.setPosition(sf::Vector2f(node.BasePos.x, node.BasePos.y - (node.Beam.getGlobalBounds().height - node.Minerais.getGlobalBounds().height)) + node.offset_beam);
			window.draw(node.Beam);
		}
	}
}

void Map::Nodes::Display(WindowManager& window)
{
	window.draw(Boost.GetSprite());
}