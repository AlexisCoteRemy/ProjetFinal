#include "mesFonctions.h"

void centerText(sf::Text& text, float x, float y)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top);
    text.setPosition(x, y);
}
