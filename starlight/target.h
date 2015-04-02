#ifndef TARGET_H
#define TARGET_H

#include "lightmodifier.h"
//#include "../o_sdo/sujetdobservation.h"

#include "../geometry/rectangle.h"

#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

class Target : public LightModifier//, public SujetDObservation
{
    Rectangle   shape_ {Rectangle{{0., 0.}, {1., 1.}}}; // c'est un carré => height == width
    bool        enlightened_ {false};

  public:

    Target() = default;

    /*!
     * \brief Target
     *
     * toujours créée non éclairée
     *
     * \param topLeft
     * \param width c'est un carré => height == width
     *
     * \throw std::invalid_argument si width <= 0
     *
     * \sa Rectangle::Rectangle(const Point2Dd & topLeft, double width, double height)
     */
    Target(Point2Dd topLeft, double width);

    /*!
     * \brief Target
     *
     * toujours créée non éclairée
     *
     * invoque Target(Point2Dd topLeft, double width) comme :
     *  Target(Point2Dd{x, y}, width)
     *
     * \param x
     * \param y
     * \param width c'est un carré => height == width
     *
     * \throw std::invalid_argument si width <= 0
     *
     * \sa Target(Point2Dd topLeft, double width)
     * \sa Rectangle::Rectangle(const Point2Dd & topLeft, double width, double height)
     */
    Target(double x, double y, double width);

    virtual ~Target() = default;

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
     * \param contact
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui est toujours le cas ici
     *                 puisque la cible se comporte comme un mur
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

    inline const Rectangle & shape() const;

    inline bool enlightened() const;

};

// prototypes

std::ostream & operator<<(std::ostream & out, const Target & in);

// méthodes inline

inline const Rectangle & Target::shape() const
{
    return shape_;
}

inline bool Target::enlightened() const
{
    return enlightened_;
}


} // namespace nvs

#endif // TARGET_H
