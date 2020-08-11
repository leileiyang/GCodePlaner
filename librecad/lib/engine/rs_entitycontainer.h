#ifndef RS_ENTITYCONTAINER_H
#define RS_ENTITYCONTAINER_H

/// a fake RS_EntityContainer class for compile success.

class RS_EntityContainer
{
public:
    RS_EntityContainer(RS_EntityContainer *parent=nullptr);

    virtual void clear() {}
};

#endif // RS_ENTITYCONTAINER_H
