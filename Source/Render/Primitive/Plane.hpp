#pragma once
#include "../RenderingItem.hpp"

class Plane : public RenderingItem
{
public:
	Plane(float width, float depth, bool fixedUV = false);
	void Render() const override;
};