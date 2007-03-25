#ifndef SPRITE_H
#define SPRITE_H

#include <kgamecanvas.h>
#include "coord.h"

class KBSRenderer;

class Sprite : public KGameCanvasPixmap
{
    Coord m_scale;
    QString m_name;
    bool m_rotated;
public:
    Sprite(KGameCanvasAbstract* parent, KBSRenderer* renderer, 
            const Coord& scale, const QString& name, bool rotated);
            
    ~Sprite();

    void update(KBSRenderer* renderer);
};

#endif // SPRITE_H
