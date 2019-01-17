
#include <limits>
#include "vmath.h"

class PhysicsObject
{
private:
	Vector2f _acceleration;
	Vector2f _force;
	Vector2f _velocity;
	Vector2f _position;
	
	float _topSpeed;
	float _mass;
	float _friction;
	
public:
	PhysicsObject(float mass, Vector2f pos, Vector2f force = Vector2f(0.0f, 0.0f), Vector2f vel = Vector2f(0.0f, 0.0f), float max = std::numeric_limits<double>::infinity(), float friction = 0.0f)
	{
		_mass = mass;
		_force = force;
		_acceleration = _force / _mass;
		_velocity = vel;
		_position = pos;
		
		_topSpeed = max;
		_friction = friction;
		
	}
	
	void setForce(const Vector2f &force)
	{
		_force = force;
	}
	
	void addForce(const Vector2f &force)
	{
		_force += force;
	}
	
	void setVelocity(const Vector2f &vel)
	{
		_velocity = vel;
	}
	
	void setFriction(float friction)
	{
		_friction = friction;
	}
	
	void update(int elapsed)
	{
		_acceleration = _force / _mass;
		_velocity += _acceleration * elapsed / 1000.0f;
		_position += _velocity * elapsed / 1000.0f;
	}
	
	float getMass() const { return _mass; }
	float getXPos() const { return _position.x; }
	float getYPos() const { return _position.y; }
	
	
};
