#pragma once

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
};

inline sf::Vector2f getCircleCenter(sf::CircleShape circle)
{
	float circleRadius = circle.getRadius();
	sf::Vector2f circleCenter = circle.getPosition();
	circleCenter.x += circleRadius;
	circleCenter.y += circleRadius;
	return circleCenter;
}

inline bool pointCircleCollision(sf::Vector2f point, sf::CircleShape circle)
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

inline bool pointRectangleCollision(sf::Vector2f point, sf::RectangleShape rectangle)
{
	sf::Vector2f rectangleTopLeft = rectangle.getPosition();
	sf::Vector2f rectangleBottomRight = rectangle.getPosition() + rectangle.getPoint(2);
	if (point.x < rectangleTopLeft.x)
	{
		return false;
	}
	if (point.x > rectangleBottomRight.x)
	{
		return false;
	}
	if (point.y < rectangleTopLeft.y)
	{
		return false;
	}
	if (point.y > rectangleTopLeft.y)
	{
		return false;
	}
	return true;
}

inline bool rectangleSphereCollision(sf::RectangleShape rectangle, sf::CircleShape circle)
{
	if (pointRectangleCollision(getCircleCenter(circle), rectangle))
	{
		return true;
	}

	for (int i = 0; i < 4; i++)
	{
		if (pointCircleCollision(rectangle.getPosition() + rectangle.getPoint(i), circle))
		{
			return true;
		}
	}

	return false;
}