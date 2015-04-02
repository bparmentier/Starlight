#ifndef LENS_H
#define LENS_H

#include "lightmodifier.h"
//#include "../o_sdo/sujetdobservation.h"

#include "../geometry/rectangle.h"

#include <limits>
#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

class Lens : public LightModifier//, public SujetDObservation
{
    Rectangle   shape_ {Rectangle{{0., 0.}, {1., 1.}}};

    int         minWavelength_ {1};
    int         maxWavelength_ {std::numeric_limits<int>::max()};

  public:

    Lens() = default;

    /*!
     * \brief Lens
     *
     * \param topLeft
     * \param width
     * \param height
     * \param maxWavelength
     * \param minWavelength
     *
     * \throw std::invalid_argument si width <= 0 ou height <=0
     * \throw std::invalid_argument si maxWavelength < minWavelength
     *
     * \sa Rectangle::Rectangle(const Point2Dd & topLeft, double width, double height)
     */
    Lens(Point2Dd topLeft, double width, double height,
         int maxWavelength = std::numeric_limits<int>::max(),
         int minWavelength = 1);

    /*!
     * \brief Lens
     *
     * invoque Lens(Point2Dd topLeft, double width, double height, int maxWavelength, int minWavelength)
     * comme :
     *  Lens {{x, y}, width, height, maxWavelength, minWavelength}
     *
     * \param x
     * \param y
     * \param width
     * \param height
     * \param maxWavelength
     * \param minWavelength
     *
     * \throw std::invalid_argument si width <= 0 ou height <=0
     * \throw std::invalid_argument si maxWavelength < minWavelength
     *
     * \sa Rectangle::Rectangle(const Point2Dd & topLeft, double width, double height)
     * \sa Lens(Point2Dd topLeft, double width, double height, int maxWavelength, int minWavelength)
     */
    Lens(double x, double y, double width, double height,
         int maxWavelength = std::numeric_limits<int>::max(),
         int minWavelength = 1);

    virtual ~Lens() = default;

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
     *                 rayon sortant : ce qui n'est pas toujours le cas
     *                 ici puisque la lentille ne se comporte comme un
     *                 mur qu'à l'extérieur de
     *                 [minWavelength_, maxWavelength_]
     *                 s'il y a contact (true retourné), il est
     *                 important de checker
     *                 outgoing.wavelength() pour savoir s'il y a
     *                 effectivement un rayon sortant
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

    inline int minWavelength() const;

    inline int maxWavelength() const;
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Lens & in);

// méthodes inline

inline const Rectangle & Lens::shape() const
{
    return shape_;
}

inline int Lens::minWavelength() const
{
    return minWavelength_;
}

inline int Lens::maxWavelength() const
{
    return maxWavelength_;
}

} // namespace nvs

#endif // LENS_H
