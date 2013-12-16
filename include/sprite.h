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

    virtual void SetImage(Image* image) { this->image = image; }
    virtual const Image* GetImage() const { return image; }

    virtual void SetPosition(double x, double y, double z = 0) { this->x = x; this->y = y; this->z = z; }
    virtual void SetX(double x) { this->x = x; }
    virtual void SetY(double y) { this->y = y; }
    virtual void SetZ(double z) { this->z = z; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }
    virtual double GetZ() const { return z; }
    virtual double GetScreenX() const { return x; }
    virtual double GetScreenY() const { return y; }

    virtual void SetAngle(double angle) { this->angle = angle; }
    virtual double GetAngle() const { return angle; }

    virtual void SetScale(double sx, double sy) { this->scalex = sx; this->scaley = sy; }
    virtual void SetScaleX(double sx) { this->scalex = sx; }
    virtual void SetScaleY(double sy) { this->scaley = sy; }
    virtual double GetScaleX() const { return scalex; }
    virtual double GetScaleY() const { return scaley; }

    virtual void SetFPS(int16 fps) { /* TAREA: Implementar */ }
    //virtual int16 GetFPS() const { /* TAREA: Implementar */ }
    virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { /* TAREA: Implementar */ }
    //virtual uint16 GetFirstFrame() const { /* TAREA: Implementar */ }
    //virtual uint16 GetLastFrame() { /* TAREA: Implementar */ }
    virtual void SetCurrentFrame(uint16 frame) { /* TAREA: Implementar */ }
    //virtual uint16 GetCurrentFrame() const { /* TAREA: Implementar */ }

    virtual void SetBlendMode(Renderer::BlendMode blend) { blendMode = blend; }
    virtual Renderer::BlendMode GetBlendMode() const { return blendMode; }
    virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { this->r = r; this->g = g; this->b = b; this->a = alpha; }
    virtual uint8 GetRed() const { return r; }
    virtual uint8 GetGreen() const { return g; }
    virtual uint8 GetBlue() const { return b; }
    virtual uint8 GetAlpha() const { return a; }

    virtual void SetRadius(double radius) { /* TAREA: Implementar */ }
//    virtual double GetRadius() const { /* TAREA: Implementar */ }

	virtual void SetCollision(CollisionMode mode);
    virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { /* TAREA: Implementar */ }
    //virtual const Collision* GetCollision() const { /* TAREA: Implementar */ }
    //virtual bool CheckCollision(Sprite* sprite);
    //virtual bool CheckCollision(const Map* map);
    //virtual const Sprite* CollisionSprite() const { /* TAREA: Implementar */ }
    //virtual bool DidCollide() const { /* TAREA: Implementar */ }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speedX, double speedY = 0.0);
    virtual bool IsRotating() const { return rotating; }
    virtual bool IsMoving() const { return moving; }

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
