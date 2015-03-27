#ifndef BOMB_H
#define BOMB_H

#include "lightmodifier.h"

#include "../geometry/circle.h"

#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

class Bomb : public LightModifier
{
    const Circle    shape_;
    bool            enlightened_ {false};

  public:

    /*!
     * \brief Bomb
     *
     * toujours créée non éclairée
     *
     * \param topLeft
     * \param radius doit être >= 0
     *
     * \throw std::invalid_argument si radius <= 0
     *
     * \sa Circle(const Point2Dd & center, double radius)
     */
    Bomb(Point2Dd center, double radius);

    /*!
     * \brief Bomb
     *
     * toujours créée non éclairée
     *
     * invoque Bomb(Point2Dd center, double radius) comme :
     *  Bomb {Point2Dd{x, y}, radius}
     *
     * \param x
     * \param y
     * \param radius doit être >= 0
     *
     * \throw std::invalid_argument si radius <= 0
     *
     * \sa Bomb(Point2Dd center, double radius)
     * \sa Circle(const Point2Dd & center, double radius)
     */
    Bomb(double x, double y, double radius);

    virtual ~Bomb() = default;

    /*!
     * \brief interaction
     *
     * \param ingoing
     *
     * \param contact
     *
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui est toujours le cas ici
     *                 puisque la bombe se comporte comme un mur
     *
     * \return true s'il y a un contact entre le rayon incident et
     *         l'objet, false sinon
     *
     * \throw std::domain_error si la source d'ingoing est dans shape_
     *
     * \sa LightModifier::interaction(const LightRay & ingoing, Point2Dd & contact, LightRay & outgoing)
     */
    virtual bool interaction(const LightRay & ingoing,
                             Point2Dd & contact,
                             LightRay & outgoing);

    inline const Circle & shape() const;

    inline bool enlightened() const;
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Bomb & in);

// méthodes inline

inline const Circle & Bomb::shape() const
{
    return shape_;
}

inline bool Bomb::enlightened() const
{
    return enlightened_;
}


} // namespace nvs

#endif // BOMB_H
