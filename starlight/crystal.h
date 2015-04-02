#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "lightmodifier.h"

#include "../geometry/circle.h"

#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

class Crystal : public LightModifier
{
    Circle  shape_ {Circle{{0., 0.}, 1.}};
    int     modifier_ {0};

  public:

    Crystal() = default;

    /*!
     * \brief Crystal
     *
     * \param topLeft
     * \param radius doit être >= 0
     * \param modifier peut être nul...
     *
     * \throw std::invalid_argument si radius <= 0
     *
     * \sa Circle(const Point2Dd & center, double radius)
     */
    Crystal(Point2Dd center, double radius, int modifier);

    /*!
     * \brief Crystal
     *
     * invoque Crystal(Point2Dd topLeft, double radius, int modifier)
     * comme :
     *  Crystal {Point2Dd{x, y}, radius, modifier}
     *
     * \param x
     * \param y
     * \param radius
     * \param modifier
     *
     * \throw std::invalid_argument si radius <= 0
     *
     * \sa Crystal(Point2Dd center, double radius, int modifier)
     * \sa Circle(const Point2Dd & center, double radius)
     */
    Crystal(double x, double y, double radius, int modifier);

    virtual ~Crystal() = default;

    /*!
     * \brief checkInteraction
     * \param ingoing
     * \param contact
     * \return true si le rayon ingoing frappe l'objet, false sinon
     *
     * \throw std::domain_error si la source d'ingoing est dans shape_
     */
    virtual bool checkInteraction(const LightRay & ingoing,
                                  Point2Dd & contact);

    /*!
     * \brief interaction
     *
     * \param ingoing
     *
     * \param contact
     *
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui est possible ici
     *                 puisque le cristal peut diminuer la longueur
     *                 d'onde
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

    inline int modifier() const;
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Crystal & in);

// méthodes inline

inline const Circle & Crystal::shape() const
{
    return shape_;
}

inline int Crystal::modifier() const
{
    return modifier_;
}

} // namespace nvs

#endif // CRYSTAL_H
