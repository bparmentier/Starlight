#ifndef LIGHTRAY_H
#define LIGHTRAY_H

#include "../geometry/point2dd.h"
//#include "../geometry/line.h"

#include <limits>
#include <ostream>

namespace nvs
{

// TODO : il faudrait distinguer les classes
//        Ray : 1/2 droite (geometry)
//     et LightRay : 1/2 droite avec longueur d'onde (starlight)

class Line;

/*!
 * \brief The LightRay class
 *
 * en fait il s'agit d'une demi-droite !
 *
 *  Systéme de coordonnées :
 *
 *      |
 *    --|---------------->
 *      |                 x
 *      |
 *      |
 *    y |
 *      v
 *
 *  angle de propagation (α) | sens de propagation
 * --------------------------+-------------------------------
 *          0 ou 2 π         | vers la droite, ni haut ni bas
 *         0 < α < π / 2     | vers le haut et la droite
 *           π / 2           | vers le haut, ni gauche ni droite
 *     π / 2 < α < π         | vers le haut et la gauche
 *             π             | vers la gauche, ni haut ni bas
 *         π < α < 3 π / 2   | vers le bas et la gauche
 *         3 π / 2           | vers le bas, ni gauche ni droite
 *   3 π / 2 < α < 2 π       | vers le bas et la droite
 *
 */
class LightRay
{
    Point2Dd emission_ {};   // point d'émission
    double propagation_ {};  // angle de propagation

    int wavelength_ {};

    double dpropagation_ {std::numeric_limits<double>::min()};
    // incertitude sur l'angle de propagation

    //    Line line_;

  public:

    LightRay() = default;

    /*!
     * \brief LightRay
     *
     * dpropagation_ est mis à
     *  max(numeric_limits<double>::min(),
     *      abs(angle) * numeric_limits<double>::epsilon())
     *
     * \param point
     * \param angle normalisé dans [0, 2π[ (ou [0, 2π])
     * \param wavelength une valeur négative (ou nulle) indique
     *                   l'absence de photon ;-) donc de lumière !
     */
    LightRay(const Point2Dd & point, double angle, int wavelength = -1);

    /*!
     * \brief LightRay
     *
     * invoque LightRay(const Point2Dd & point, double angle, int wavelength)
     * comme :
     *  LightRay {{x, y}, angle, wavelength}
     *
     * dx et dy sont mis tels que Point2Dd::Point2Dd(double x, double y)
     * le fait
     *
     * dpropagation_ est mis à
     *  max(numeric_limits<double>::min(),
     *      abs(angle) * numeric_limits<double>::epsilon())
     *
     * \param x
     * \param y
     * \param angle normalisé dans [0, 2π[ (ou [0, 2π])
     * \param wavelength une valeur négative (ou nulle) indique
     *                   l'absence de photon ;-) donc de lumière !
     *
     * \sa Point2Dd(double x, double y)
     * \sa LightRay(const Point2Dd & point, double angle, int wavelength)
     */
    LightRay(double x, double y, double angle, int wavelength = -1);

    /*!
     * \brief LightRay
     *
     * invoque LightRay(const Point2Dd & point, double angle, int wavelength)
     * comme :
     *  LightRay {point, angle, wavelength}
     *
     * puis met dpropagation_ à :
     *  max({numeric_limits<double>::min(),
     *       abs(angle) * numeric_limits<double>::epsilon(),
     *       abs(dangle)})
     *
     * \param point
     * \param angle
     * \param dangle
     * \param wavelength
     */
    LightRay(const Point2Dd & point, double angle, double dangle,
             int wavelength = -1);

    virtual ~LightRay() = default;

    LightRay(const LightRay &) = default;
    LightRay & operator=(const LightRay &) = default;

    inline const Point2Dd & emission() const;

    inline double propagation() const;

    inline int wavelength() const;

    inline double dpropagation() const;

    /*!
     * \brief line
     *
     * \return la ligne associée au rayon : attention, seule la
     *         1/2 droite commençant en emission_ constitue le rayon
     */
    Line line() const;

    /*!
     * \brief contains
     *
     * tient compte du sens de propagation du rayon et de la présence
     * de photons : si le rayon est de longueur d'onde négative ou
     * nulle, false est retourné.
     *
     * ATTENTION : si wavelength_ <= 0 retourne toujours false !
     *
     * \param point
     * \return
     */
    bool contains(const Point2Dd & point) const;

    // amis

    friend bool operator==(const LightRay & lhs, const LightRay & rhs);
};

// prototypes

std::ostream & operator<<(std::ostream & out, const LightRay & in);

/*!
 * \brief operator ==
 *
 * compare les points d'émission, les directions de propagation
 * et les longueurs d'ondes
 *
 * \param lhs
 * \param rhs
 * \return
 */
bool operator==(const LightRay & lhs, const LightRay & rhs);

// méthodes inline

inline const Point2Dd & LightRay::emission() const
{
    return emission_;
}

inline double LightRay::propagation() const
{
    return propagation_;
}

inline int LightRay::wavelength() const
{
    return wavelength_;
}

inline double LightRay::dpropagation() const
{
    return dpropagation_;
}

} // namespace nvs

#endif // LIGHTRAY_H
