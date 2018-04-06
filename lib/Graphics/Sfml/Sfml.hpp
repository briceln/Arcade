//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Definition of SFML Class
//

#ifndef CPP_ARCADE_SFML_HPP
#	define CPP_ARCADE_SFML_HPP

#	include <SFML/Graphics.hpp>
#	include "../../../inc/IDisplay.hpp"

class SfmlDisplay : public IDisplay {
public:
	SfmlDisplay(size_t, size_t);
	~SfmlDisplay() override;
public:
	bool	Display() override;
	bool	isOpen() override;

	bool loadMap(std::vector<std::vector<char>> const &vector) override;

	bool	GetKey(arcade::TypeEvent, std::string const &) override;
	bool	isKey() override;
	void	destroyWindow() override;
	bool	loadTexture(std::map<std::string, Texture> const&) override;
	bool	loadText(std::map<std::string, Texture> const&) override;
	void	changeLibrary(std::string const &) override;
	bool	getChange() const override;
	bool	getSwitchScene() const override;
	void	setSwitchScene(bool) override;
	void	setChange(bool) override;
	std::string const	&getLibraryPath() const override;
	std::string const	&getNewGamePath() const override;
	void	setNewGamePath(std::string const &) override;
	void	setEvent(sf::Event &);
private:
	size_t	width;
	size_t	height;
	bool	alreadyLoad;
	sf::Font	font;
	std::vector<sf::Text>	texts;
	std::vector<sf::Texture>	textures;
	std::map<std::string, sf::Sprite>	sprites;
	std::map<std::string, int> allEvent;
	sf::RenderWindow *window;
	sf::Event event;
};

#endif //CPP_ARCADE_SFML_HPP
