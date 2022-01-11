#ifndef TC_JOUEUR_H
#define TC_JOUEUR_H

#include "Joueur.h"
#include <random>
#include <array>

class TC_Joueur final : public Joueur
{
public:
    TC_Joueur();
    ~TC_Joueur() = default;

    void Interaction(std::map<int, Joueur*>& joueurs, const float&);
    virtual void Controle(const float& dt);
    virtual void Update(const float& dt, sf::Image& image);
    void update(const float&);
    virtual void Display(WindowManager& window);
    void Display_Victoire(WindowManager& window);
    void SetColor(Couleur color)override;
    void setScore(int _score) { score = _score; }
    void SetFillColor(const sf::Color& colo) { Sprite.setColor(colo); }
    sf::Color getColor()const { return Sprite.getColor(); }
    bool collidesWith(Joueur& j, const float&);
    double getDistanceEuclidean(const sf::Vector2f&,const sf::Vector2f&);
    void AnimUpdate(const float&);
    int Get_Classement() { return classement; }
    void Set_Classement(int c) { classement = c; }

    int GetID()const { return id; }
    template<typename R>
    int RandomColor(R&& r)
    {
        std::uniform_int_distribution<> dist{ 0 ,5 };
        return int(dist(std::forward<R>(r)));
    }
    int score{ 0 };
private:
    const float m_speed{ 500.f };
    const std::array<sf::Color, 6> m_color = { sf::Color::Cyan, sf::Color::Yellow, sf::Color::Red,sf::Color::Magenta, sf::Color::Green, sf::Color::Blue};
    std::mt19937 m_random{ std::random_device{}() };
    Animator anim;
    int id = 0;
    sf::Sprite tete;
    int classement = 0;
    float angle{ 0.f };
};
#endif

