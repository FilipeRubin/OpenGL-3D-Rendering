#pragma once

#include "../RenderingItem.hpp"

class Pyramid : public RenderingItem
{
public:
	Pyramid(float width, float height);
	void Render() const override;
};