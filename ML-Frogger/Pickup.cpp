#include "Pickup.h"
#include "Category.h"
#include "DataTables.h"
#include "Airplaine.h"
namespace GEX
{
	std::map<Pickup::Type, PickupDate> table = initializePickupDate();

	Pickup::Pickup(Type type) :
		Entity(1),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).location)
	{}

	unsigned int Pickup::getCategory() const
	{
		return Category::Pickup;
	}

	void Pickup::apply(Airplaine & player) const
	{
		table.at(_type).action(player);
	}

	void Pickup::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

	sf::FloatRect Pickup::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

}