#pragma once
#include "SFML\Graphics.hpp"
namespace GEX
{
	class Animation :public sf::Drawable, public sf::Transformable
	{
	public:
		Animation();
		explicit			Animation(const sf::Texture& texture);

		void				setTexture(const sf::Texture& texture);
		const sf::Texture*	getTexture()const;

		void				setFrameSize(sf::Vector2i mFrameSize);
		sf::Vector2i		getFrameSize()const;

		void				setNumFrames(std::size_t numFrame);
		std::size_t			getNumFrames()const;

		void				setDuration(sf::Time duration);
		sf::Time			getDuration() const;

		void				setRepeating(bool flag);
		bool				isRepeating() const;

		void				restart();
		bool				isFinished()const;

		sf::FloatRect		getLocalBounds() const;
		sf::FloatRect		getGlobalBounds() const;

		void				update(sf::Time dt);

	private:
		void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite			_sprite;
		sf::Vector2i		_frameSize;
		std::size_t			_numFrames;
		std::size_t			_currentFrame;
		sf::Time			_duration;
		sf::Time			_elapsedTime;
		bool				_repeat;
	};



}