#ifndef WALL_H
#define WALL_H

#include "lightmodifier.h"

#include "../geometry/segment.h"

#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

class Wall : public LightModifier
{
    const Segment shape_;

  public:

    /*!
     * \brief Wall
     *
     * p1 doit être != de p2
     *
     * \param p1
     * \param p2
     *
     * \throw invalid_argument si p1 == p2
     *
     * \sa Segment(const Point2Dd & first, const Point2Dd & second)
     */
    Wall(const Point2Dd & p1, const Point2Dd & p2);

    /*!
     * \brief Wall
     *
     * invoque Wall(const Point2Dd & p1, const Point2Dd & p2)
     * comme : Wall{{p1x, p1y}, {p2x, p2y}}
     *
     *
     * p1 doit être != de p2
     *
     * \param p1x
     * \param p1y
     * \param p2x
     * \param p2y
     *
     * \throw invalid_argument si p1 == p2
     *
     * \sa Wall(const Point2Dd & p1, const Point2Dd & p2)
     * \sa Segment(const Point2Dd & first, const Point2Dd & second)
     */
    Wall(double p1x, double p1y, double p2x, double p2y);

    virtual ~Wall() = default;

    /*!
     * \brief interaction
     *
     * \param ingoing
     *
     * \param contact
     *
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui est toujours le cas ici
     *                 avec un mur
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

    inline const Segment & shape() const;
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Wall & in);

// méthodes inline

inline const Segment & Wall::shape() const
{
    return shape_;
}

} // namespace nvs

#endif // WALL_H
