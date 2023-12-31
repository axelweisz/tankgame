#ifndef TANK_GAME_H
#define TANK_GAME_H

#include "../Framework/Test.h"

#define MAX_PROJECTILE 5

enum eTankCommand
{
    eTankCmd_MoveForward,
    eTankCmd_MoveBackWard,
    eTankCmd_RotateGunUp,
    eTankCmd_RotateGunDown,
    eTankCmd_ChargeGun,
    eTankCmd_FireGun,
};

class Projectile
{
public:

    void Update( float deltaTime );
    void Render( DebugDraw* drawInterface );

protected: 

    enum ProjectileState
    {
        Ready,
        Fired
    };

    float m_lifetime;
    ProjectileState m_state;

};


class TankGun
{
public:
    TankGun( );

    void Init( b2Vec2 pivot, float diameter, float length  );

    void RotateUp();
    void RotateDown();
    void Fire( Projectile& projectile );

    void Render( DebugDraw* drawInterface, b2Vec2 base );

protected:

    b2Vec2 m_pivot;
    float m_impulse;
    float m_angle;
    float m_rotationSpeed;

    b2Vec2  m_gunPoly[4];
};


class TankWheel
{
public:

    TankWheel();
    void Init( b2Vec2 pos, float radius );

    void Render( DebugDraw* drawInterface, b2Vec2 base );
    void Update( float deltaTime);

    void SetSpeed( float speed );

protected:

    b2Vec2 m_position;
    float m_radius;

    float m_angle;
    float m_rotationSpeed;

};

class Tank
{
public:

    Tank();

    void SetPosition( b2Vec2 pos );

    void ProcessCmd( eTankCommand cmd );

    void Render( DebugDraw* drawInterface );

    void Update( float deltaTime );


protected:

    void Move( );
    void RotateGun( );

    b2Vec2 m_position;

    TankGun   m_gun;
    TankWheel m_wheels[4];

    float m_halfLength;
    b2Vec2 m_tankPoly[8];
};

class TankGame : Test 
{
public:

    TankGame();

    virtual void Step(Settings* settings);
	virtual void Keyboard(unsigned char key);
	virtual void KeyboardUp(unsigned char key);

    void UpdateProjectiles( float deltatime );
    void RenderProjectiles( );

    void RenderGround();
    void CheckGroundLimit();

    static Test* Create()
	{
		return new TankGame;
	}

protected:

    Tank m_tank;

    Projectile m_projectiles[MAX_PROJECTILE];

    int m_nextProjectile;

    //Ground
    b2Vec2 m_groundStart;
    b2Vec2 m_groundEnd;
};

#endif