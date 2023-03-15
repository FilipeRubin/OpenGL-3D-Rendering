#pragma once
#include "../RenderingItem.hpp"

class Cube : public RenderingItem
{
public:
	Cube(float width, float height, float depth);
	void Render() const override;
};