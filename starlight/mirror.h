#ifndef MIRROR_H
#define MIRROR_H

#include "lightmodifier.h"
#include "../o_sdo/sujetdobservation.h"

#include "../geometry/segment.h"

#include <ostream>


namespace nvs
{

class Point2Dd;
class LightRay;

/*!
 * \brief The Mirror class
 *
 *
 * Systéme de coordonnées :
 *
 *      |
 *    --|---------------->
 *      |                 x
 *      |
 *      |
 *    y |
 *      v
 *
 * angle mesuré dans le sens trigonométrique
 * angle entre l'axe horizontal et la surface réfléchissante
 *
 *
 *          angle (α)        |         sens de réflexion
 *                           | orientation de surface réfléchissante
 * --------------------------+-------------------------------
 *          0 ou 2 π         | vers le bas
 *         0 < α < π / 2     | vers le bas et la droite
 *           π / 2           | vers la droite
 *     π / 2 < α < π         | vers le haut et la droite
 *             π             | vers le haut
 *         π < α < 3 π / 2   | vers le haut et la gauche
 *         3 π / 2           | vers la gauche
 *   3 π / 2 < α < 2 π       | vers le bas et la gauche
 *
 */
class Mirror : public LightModifier, public SujetDObservation
{
    const Point2Dd  center_;
    const double    length_2_; // length / 2
    double          angle_;

    Segment         shape_;

    // TODO (?) : dangle_
    // comme il s'agit d'une constante non issue de calculs,
    // j'estime qu'on peut s'en passer : le dangle_
    // par défaut de nvs::ApproximativeComparison fera l'affaire

    /*!
     * \brief hasOnReflectingSide
     *
     * \param point
     *
     * \return true si le point est situé du côté réfléchissant du
     *         miroir, false s'il est de l'autre côté ou dans le
     *         prolongement de sa tranche ou dans le miroir
     */
    bool hasInFrontOfReflectingSide(const Point2Dd & point);

  public:

    /*!
     * \brief Mirror
     *
     * \param center position du centre du miroir
     * \param length
     * \param angle angle entre l'horizontale et la surface
     *              réfléchissante du miroir (voir tableau ci-dessus)
     *
     * \throw invalid_argument si lenght <= 0
     */
    Mirror(const Point2Dd & center, double length, double angle);

    /*!
     * \brief Mirror
     *
     * invoque Mirror(const Point2Dd & center, double length, double angle)
     * comme :
     *  Mirror {{x, y}, length, angle}
     *
     * \param x
     * \param y
     * \param length
     * \param angle
     *
     * \throw invalid_argument si lenght <= 0
     *
     * \sa Mirror(const Point2Dd & center, double length, double angle)
     */
    Mirror(double x, double y, double length, double angle);

    virtual ~Mirror() = default;

    /*!
     * \brief interaction
     *
     * \param ingoing
     *
     * \param contact
     *
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui arrive ici si le rayon
     *                 tombe sur la tranche ou la face non
     *                 réfléchissante du miroir
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

    inline const Point2Dd & center() const;
    inline double length_2() const;
    inline double angle() const;
    inline const Segment & shape() const;

    /*!
     * \brief rotate
     *
     * avertit les Observateur enregistrés si l'angle en paramètre
     * n'est pas nul
     *
     * \param angle
     *
     * \sa SujetDObservation::notifierChangement()
     */
    void rotate(double angle);
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Mirror & in);

// méthodes inline

inline const Point2Dd & Mirror::center() const
{
    return center_;
}

inline double Mirror::length_2() const
{
    return length_2_;
}

inline double Mirror::angle() const
{
    return angle_;
}

inline const Segment & Mirror::shape() const
{
    return shape_;
}

} // namespace nvs

#endif // MIRROR_H
