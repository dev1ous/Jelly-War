#ifndef CONTAINER_H
#define CONTAINER_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <ranges>
#include <iostream>

template<class T>
class Container
{
public:
	using vec = std::vector<std::pair<std::string_view, T>>;
	using pair = std::pair<std::string_view, T>;

	explicit constexpr Container(T* parent = nullptr)noexcept :_parent{ parent } {}

	template<typename ...Args>
	[[nodiscard]] T& Add(std::string_view, Args&&...args)noexcept;

	[[nodiscard]] T& get(std::string_view)noexcept;

	void remove(std::string_view)noexcept;

	void Children_Clear();

protected:
	~Container() = default;

	[[nodiscard]] vec& getchild()noexcept { return children; }

	[[nodiscard]] T* getParent()noexcept { return _parent; }

	void draw(sf::RenderWindow&) const noexcept;

private:
	T* _parent{ nullptr };
	vec children{ {} };
};

#endif // !Container_H

template<class T>
template<typename ...Args>
inline T& Container<T>::Add(std::string_view id, Args&&...args)noexcept
{
	children.emplace_back(std::make_pair(id, T(static_cast<T*>(this), std::forward<Args>(args)...)));
	return children.back().second;
}

template<class T>
inline T& Container<T>::get(std::string_view id)noexcept
{
	try {
		if (auto x = std::ranges::find_if(children, [id](pair& b) {return b.first == id; }); x != std::ranges::end(children))
			return x->second;
		else
			throw std::runtime_error("didnt find the id of your object");
	}
	catch (std::exception const& e)
	{
		std::cout << "Exception : " << e.what() << "\n";
	}
}

template<class T>
inline void Container<T>::remove(std::string_view id)noexcept
{
	children.erase(std::remove_if(children.begin(), children.end(), [id](pair& k) { return k.first == id; }));
}

template<class T>
inline void Container<T>::Children_Clear()
{
	children.clear();
}

template<class T>
inline void Container<T>::draw(sf::RenderWindow& window) const noexcept
{
	std::ranges::for_each(children, [&window](const pair& v) { v.second.draw(window); });
}