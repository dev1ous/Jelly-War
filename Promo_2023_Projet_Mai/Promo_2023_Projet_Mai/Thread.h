#ifndef THREAD_H
#define THREAD_H

#include <vector>
#include <filesystem>
#include <execution>
#include "SFML/Graphics.hpp"
#include <any>
#include "WindowManager.h"

//openGL n'etant pas multi_threadé, je load des images(prefereable) depuis le disque depuis ce thread séparé et je les recupererai sous forme de textures dans le main thread
using images = std::vector<std::unique_ptr<sf::Image>>;

//struct pour les infos essentiels à faire passé dans le thread
struct ThreadInfo 
{
	WindowManager& m_window;
	//mutex pour sf::ContextSettings ( openGL fait chier à nous demander d'en créer un pour chaque threads)
	std::mutex& m_mutex;
	std::string& m_filename;
	//mutex recursif car je compte lock et unlock plusieurs fois le meme mutex dans le meme thread
	//ce mutex est destiné à lock et unlock à chaque fois qu'on affiche le file actuellement en train d'etre load dans l'ecran de chargement
	std::recursive_mutex& m_fileMutex;

	//booléen qui va servir de check quand on va lock et unlock les mutex
	bool& m_Loading;
	//float qui représente la progression du loading
	float& m_Progress;

	images& m_images;
};

//free function pour recup la taille totale des liens vers mes images/textures
template<typename Policy>
std::size_t FilesSize(std::vector<std::filesystem::path>& files, const std::filesystem::path& directory, const std::filesystem::path& extension, Policy policy_execution);
#endif

//le paramètre du template policy va me permettre de specifier à l'algorithme de mon choix comment il va etre executé
template<typename Policy>
inline std::size_t FilesSize(std::vector<std::filesystem::path>& files,const std::filesystem::path& directory, const std::filesystem::path& extension, Policy policy_execution)
{
	using namespace std::filesystem;

	//je l'ai choisis plutot que le directory_iterator car il parcours en + les subdirectory( recursivement du coup) 
	recursive_directory_iterator dirpos{ directory };

	//si rien retourne 0
	if (!exists(directory))
		return 0;

	//je découpe mon algorithme en 2 partie avec copy et foreach car copy ne supporte pas le parallelisme 
	 
	//l'objectif du parallelisme dans ma demarche est qu'il permet d'utiliser plusieurs threads qui s'execute en parallele pour effectuer mon algorithme, ce qui rend l'execution 30 fois
	//plus rapide surtout sur une opération sur celle ci qui consiste à traverser énormement de fichiers
	std::copy(begin(dirpos), end(dirpos), back_inserter(files));

	//mutex pour le push_back des files
	std::mutex m;

	std::for_each(policy_execution, begin(files), end(files), [&files, &m](const path& entry)
		{
			if (is_regular_file(entry) && !is_symlink(entry) && entry.has_extension())//symlink c'est tous les signes bizarres(je les autorise pas)
			{
				//peut etre rajouter des conditions avec le stem tout ça je sais pas ( ca me permet correct moi ) 
				if (entry.extension() == ".png" || entry.extension() == ".jpg")
				{
					std::unique_lock<std::mutex> lock(m);
					// possibilité que ça soit juste "entry" à push_back
					files.push_back(entry.string());
				}
			}
		});
	return std::size(files);
}

//fonction qui rentrera dans le thread avec toutes les infos à passer. (je wrap le tout dans un any pour plus de type safety)
void LoadImages(std::any data)
{
	//Toutes les variables sont créer localement, ce qui m'évite d'avoir recours a des atomic

	//je crée mon any(j'ai essayé d'être évident en utilisant "make_any" mais on peut faire autrement)
	data = std::make_any<ThreadInfo*>();
	//j'accede au type contenu dans mon any avec le any_cast puis je pick up les variables de ma struct
	WindowManager& window = std::any_cast<ThreadInfo*>(data)->m_window;
	std::mutex& mutex = std::any_cast<ThreadInfo*>(data)->m_mutex;
	std::string& filename = std::any_cast<ThreadInfo*>(data)->m_filename;
	std::recursive_mutex& fileMutex = std::any_cast<ThreadInfo*>(data)->m_fileMutex;
	bool& isLoading = std::any_cast<ThreadInfo*>(data)->m_Loading;
	float& progressing = std::any_cast<ThreadInfo*>(data)->m_Progress;
	images& im = std::any_cast<ThreadInfo*>(data)->m_images;

	std::vector<std::filesystem::path> imageFiles;
	FilesSize(imageFiles, "..Ressources/", ".png", std::execution::par);
	std::size_t NumbersOfFiles = std::size(imageFiles);

	//je provide un unsigned long long pour être pile raccord avec le std::size_t présent dans la comparaison du for et les at()
	for (auto i(0uLL); i < NumbersOfFiles; ++i) 
	{
		//scoped_lock car je pense pas avoir besoin des features du unique_lock sur celui la pour l'instant, on verra plus tard si je dois defer(ou autres) avec le mutex de mon algorithme plus haut
		std::scoped_lock<std::mutex> lock(mutex);
		window.setActive();

		fileMutex.lock();
		filename = imageFiles.at(i).string();
		fileMutex.unlock();

		std::unique_ptr<sf::Image> ptr = std::make_unique<sf::Image>();
		if (ptr->loadFromFile(imageFiles.at(i).string()))
			im.push_back(std::move(ptr));
		else
			throw std::runtime_error("didnt find files" + imageFiles.at(i).string());

		progressing = static_cast<float>(i + 1) / static_cast<float>(NumbersOfFiles) * 100.f;
		window.setActive(false);
	}
	isLoading = false;
	fileMutex.lock();
	filename.clear();
	fileMutex.unlock();
}
