#include "Network.h"
#include "AT_Joueur.h"

const bool Network::isOpen() const
{
    return !closed;
}

void Network::updateInfos(Map& map)
{
    thisInfo.nodes = &map.getNodes();
}

void Network::updateInfos(Map::Nodes* node)
{
    thisInfo.newNode = node;
}

void Network::updateInfos(Projectiles_BR* proj)
{
    thisInfo.br.newProj = proj;
}

void Network::updateInfos(Bonus* bonus[3])
{
    for (int i = 0; i < 3; i++) {
        if (bonus[i] != nullptr) {
            thisInfo.newBonus[i] = bonus[i];
        }
    }
}

void Network::updateInfos(bool Ready, Joueur::Couleur color)
{
    style = NetworkStyle::Waiting;
    thisInfo.ready = Ready;
    thisInfo.color = color;
}

void Network::updateInfos(TC_Joueur* you)
{
    style = NetworkStyle::TC;
    thisInfo.tc.TcPos = you->GetSprite().getPosition();
    thisInfo.tc.tcColor = you->getColor();
    thisInfo.tc.tcScore = you->score;
}

void Network::updateInfos(BR_Joueur* you)
{
    style = NetworkStyle::BR;
    thisInfo.br.pos = you->GetPos();
    thisInfo.br.invincible = you->is_invincible();
    thisInfo.br.score = you->Get_score();
    thisInfo.br.rotation = you->Get_Angle();
}

void Network::updateInfos(AT_Joueur* you)
{
    style = NetworkStyle::AT;
    thisInfo.at.pos = you->GetPosition();
    thisInfo.at.velocity = you->GetVelocity();
    thisInfo.at.alive = you->IsAlive();
    thisInfo.at.rotation = you->Get_Angle();
    thisInfo.at.color = you->GetColor();
    thisInfo.at.score = you->GetScore();
}

void Network::updateInfos(int id, AT_Joueur* you)
{
    style = NetworkStyle::AT;
    thisInfo.at.bumps[id] = you->GetVelocity();
}

void Network::updateInfos(Main_Joueur* you, const float& timer, bool& ready)
{
    style = NetworkStyle::Game;
    thisInfo.GamePos = you->GetPos();
    thisInfo.Anim = you->GetTextureRect();
    thisInfo.XScale = you->GetSprite().getScale().x;
    thisInfo.Tacle = you->GetTacle();
    thisInfo.Check = you->GetCheck();
    thisInfo.UseBonus = you->GetUseBonus();
    thisInfo.CurrentBonus = you->GetFirstBonus().GetType();
    thisInfo.progress = (you->getRessource(0) + you->getRessource(1) + you->getRessource(2)) / 3.f;
    thisInfo.timerbouton = timer;
    thisInfo.MinijeuReady = ready;
}

void Network::updateInfos(Joueur* you)
{
    style = NetworkStyle::Game;
    thisInfo.GamePos = you->GetPos();
    thisInfo.Anim = you->GetTextureRect();
    thisInfo.XScale = you->GetSprite().getScale().x;
}

void Network::updateInfosState(int currentstate, Map::BoutonMG& bouton)
{
    thisInfo.Current_State = currentstate;
}

void Network::updateInfosRemoveTraps(sf::Vector2f pos)
{
    thisInfo.NodeRessourceRemove = pos;
}

void Network::win()
{
    thisInfo.won = true;
}

Network::~Network()
{
    closed = true;
    if (th.joinable()) {
        th.join();
    }
}

void Network::disconnect()
{
    closed = true;
}

const size_t Network::UnprocessedPackets() const
{
    return eventsList.size();
}