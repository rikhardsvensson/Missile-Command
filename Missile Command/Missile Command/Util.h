#pragma once
#include "SettingsParser.h"

enum ProjectileType
{
	MISSILE, METEOR
};

struct ProjectileParameters
{
	ProjectileType projectileType;
	sf::Vector2f origin;
	sf::Vector2f destination;
	sf::Color projectileColor;
	sf::Color explosionColor;
	float projectileSpeed;
	float explosionMaximumRadius;
	float explosionPropagationSpeed;
	bool isWaveSpawner;
};

inline sf::Vector2f getCircleCenter(const sf::CircleShape& circle)
{
	float circleRadius = circle.getRadius();
	sf::Vector2f circleCenter = circle.getPosition();
	circleCenter.x += circleRadius;
	circleCenter.y += circleRadius;
	return circleCenter;
}

//Returns true if the point is within the circle.
inline bool pointCircleCollision(const sf::Vector2f& point, const sf::CircleShape& circle)
{
	sf::Vector2f circleCenter = getCircleCenter(circle);
	
	sf::Vector2f pointToCircle = point - circleCenter;
	float pointToCircleDist = std::sqrt(pointToCircle.x * pointToCircle.x + pointToCircle.y * pointToCircle.y);

	if (pointToCircleDist <= circle.getRadius())
	{
		return true;
	}
	return false;
}

//Returns val within the boundaries of minVal and maxVal.
inline float clamp(float val, float minVal, float maxVal) 
{
	float clampedToMin = std::min(maxVal, val);
	float clampedToMax = std::max(minVal, clampedToMin);
	return clampedToMax;
}

inline float getVectorLength(const sf::Vector2f& vec)
{
	return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
}

//Returns true if the circle and the rectangle overlap.
inline bool rectangleCircleCollision(const sf::RectangleShape& rectangle, const sf::CircleShape& circle)
{
	sf::Vector2f circleCenter = getCircleCenter(circle);
	float circleRadius = circle.getRadius();
	sf::Vector2f rectangleTopLeft = rectangle.getPosition();
	sf::Vector2f rectangleSize = rectangle.getSize();

	//Calculate the nearest point to the circle's center from within the rectangle.
	sf::Vector2f nearestPointInRectangle;
	nearestPointInRectangle.x = clamp(circleCenter.x, rectangleTopLeft.x, rectangleTopLeft.x + rectangleSize.x);
	nearestPointInRectangle.y = clamp(circleCenter.y, rectangleTopLeft.y, rectangleTopLeft.y + rectangleSize.y);

	//Calculate the distance from the the nearest point to the circle's center.
	sf::Vector2f nearestToCircleVec;
	nearestToCircleVec.x = circleCenter.x - nearestPointInRectangle.x;
	nearestToCircleVec.y = circleCenter.y - nearestPointInRectangle.y;
	float nearestToCircleDist = getVectorLength(nearestToCircleVec);

	if (nearestToCircleDist < circleRadius)
	{
		return true;
	}
	return false;
}

//Returns true if the point is within the rectangle.
inline bool rectanglePointCollision(const sf::RectangleShape& rectangle, const sf::Vector2i& point)
{
	sf::Vector2f rectangleTopLeft = rectangle.getPosition();
	sf::Vector2f rectangleBottomRight = rectangleTopLeft + rectangle.getSize();

	if (point.x > rectangleTopLeft.x && point.x < rectangleBottomRight.x && 
		point.y > rectangleTopLeft.y && point.y < rectangleBottomRight.y)
	{
		return true;
	}

	return false;
}

//Scales mouse coordinates to the render resolution when the view port has been scaled.
inline sf::Vector2i getScaledMouseCoords(const sf::RenderWindow* window, const Settings* settings)
{
	sf::Vector2i mouseCoords = sf::Mouse::getPosition(*window);
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(window->getSize());
	sf::Vector2f scalingFactor
		(
			windowSize.x / settings->resolution.x,
			windowSize.y / settings->resolution.y
		);
	sf::Vector2i scaledMouseCoords
		(
			static_cast<int>(mouseCoords.x / scalingFactor.x), 
			static_cast<int>(mouseCoords.y / scalingFactor.y)
		);
	return scaledMouseCoords;
}

inline sf::Vector2f getRectangleCenterPosition(const sf::RectangleShape& rectangle)
{
	sf::Vector2f centerPos = rectangle.getPosition();
	sf::Vector2f rectangleSize = rectangle.getSize();
	centerPos.x += rectangleSize.x / 2;
	centerPos.y += rectangleSize.y / 2;
	return centerPos;
}