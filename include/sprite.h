#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

    virtual void SetImage(Image* image) { /* TAREA: Implementar */ }
    virtual const Image* GetImage() const { /* TAREA: Implementar */ }

    virtual void SetPosition(double x, double y, double z = 0) { /* TAREA: Implementar */ }
    virtual void SetX(double x) { /* TAREA: Implementar */ }
    virtual void SetY(double y) { /* TAREA: Implementar */ }
    virtual void SetZ(double z) { /* TAREA: Implementar */ }
    virtual double GetX() const { /* TAREA: Implementar */ }
    virtual double GetY() const { /* TAREA: Implementar */ }
    virtual double GetZ() const { /* TAREA: Implementar */ }
    virtual double GetScreenX() const { /* TAREA: Implementar */ }
    virtual double GetScreenY() const { /* TAREA: Implementar */ }

    virtual void SetAngle(double angle) { /* TAREA: Implementar */ }
    virtual double GetAngle() const { /* TAREA: Implementar */ }

    virtual void SetScale(double sx, double sy) { /* TAREA: Implementar */ }
    virtual void SetScaleX(double sx) { /* TAREA: Implementar */ }
    virtual void SetScaleY(double sy) { /* TAREA: Implementar */ }
    virtual double GetScaleX() const { /* TAREA: Implementar */ }
    virtual double GetScaleY() const { /* TAREA: Implementar */ }

    virtual void SetFPS(int16 fps) { /* TAREA: Implementar */ }
    virtual int16 GetFPS() const { /* TAREA: Implementar */ }
    virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { /* TAREA: Implementar */ }
    virtual uint16 GetFirstFrame() const { /* TAREA: Implementar */ }
    virtual uint16 GetLastFrame() { /* TAREA: Implementar */ }
    virtual void SetCurrentFrame(uint16 frame) { /* TAREA: Implementar */ }
    virtual uint16 GetCurrentFrame() const { /* TAREA: Implementar */ }

    virtual void SetBlendMode(Renderer::BlendMode blend) { /* TAREA: Implementar */ }
    virtual Renderer::BlendMode GetBlendMode() const { /* TAREA: Implementar */ }
    virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { /* TAREA: Implementar */ }
    virtual uint8 GetRed() const { /* TAREA: Implementar */ }
    virtual uint8 GetGreen() const { /* TAREA: Implementar */ }
    virtual uint8 GetBlue() const { /* TAREA: Implementar */ }
    virtual uint8 GetAlpha() const { /* TAREA: Implementar */ }

    virtual void SetRadius(double radius) { /* TAREA: Implementar */ }
    virtual double GetRadius() const { /* TAREA: Implementar */ }

	virtual void SetCollision(CollisionMode mode);
    virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { /* TAREA: Implementar */ }
    virtual const Collision* GetCollision() const { /* TAREA: Implementar */ }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
    virtual const Sprite* CollisionSprite() const { /* TAREA: Implementar */ }
    virtual bool DidCollide() const { /* TAREA: Implementar */ }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speedX, double speedY = 0.0);
    virtual bool IsRotating() const { /* TAREA: Implementar */ }
    virtual bool IsMoving() const { /* TAREA: Implementar */ }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* image;
    double x, y, z;
    double colx, coly, colwidth, colheight;
    double angle;
    double scalex, scaley;
    double radius;
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;

    bool rotating;
    uint16 toAngle;
    double rotatingSpeed;
    double anglesToRotate;

    bool moving;
    double toX, toY;
    double movingSpeedX, movingSpeedY;
    double prevX, prevY;
};

#endif
