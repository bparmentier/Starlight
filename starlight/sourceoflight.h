#ifndef SOURCEOFLIGHT_H
#define SOURCEOFLIGHT_H

#include "lightmodifier.h"
#include "../o_sdo/sujetdobservation.h"

#include "../geometry/rectangle.h"

#include <ostream>

namespace nvs
{

class Point2Dd;
class LightRay;

/*!
 * \brief The SourceOfLight class
 *
 * émission depuis le centre de la source
 *
 */
class SourceOfLight : public LightModifier, public SujetDObservation
{
    const Rectangle shape_; // c'est un carré => height == width
    const double    emissionAngle_;
    const int       wavelength_;
    bool            on_;

    // TODO (?) : demissionAngle_
    // comme il s'agit d'une constante non issue de calculs,
    // j'estime qu'on peut s'en passer : le demissionAngle_
    // par défaut de nvs::ApproximativeComparison fera l'affaire

  public:

    /*!
     * \brief SourceOfLight
     *
     * \param topLeft
     * \param width c'est un carré => height == width
     * \param emissionAngle normalisé dans [0, 2π[ (ou [0, 2π])
     * \param wavelength si non compris dans [nvs::MIN_WL, nvs::MAX_WL],
     *                   mis à nvs::DFT_WL
     * \param on
     *
     * \throw std::invalid_argument si width <= 0
     *
     * \sa Rectangle::Rectangle(const Point2Dd & topLeft, double width, double height)
     */
    SourceOfLight(Point2Dd topLeft, double width,
                  double emissionAngle, int wavelength, bool on = false);

    /*!
     * \brief SourceOfLight
     *
     * invoque SourceOfLight(Point2Dd topLeft, double width, double emissionAngle, int wavelength, bool on = false)
     * comme :
     *  SourceOfLight {{x, y}, width, emissionAngle, wavelength, on}
     *
     * \param x
     * \param y
     * \param width c'est un carré => height == width
     * \param emissionAngle normalisé dans [0, 2π[ (ou [0, 2π])
     * \param wavelength si non compris dans [nvs::MIN_WL, nvs::MAX_WL],
     *                   mis à nvs::DFT_WL
     * \param on
     *
     * \throw std::invalid_argument si width <= 0
     *
     * \sa SourceOfLight(Point2Dd topLeft, double width, double emissionAngle, int wavelength, bool on = false)
     * \sa Rectangle::Rectangle(double x, double y, double width, double height)
     */
    SourceOfLight(double x, double y, double width,
                  double emissionAngle, int wavelength, bool on = false);

    virtual ~SourceOfLight() = default;

    /*!
     * \brief interaction
     *
     * \param ingoing
     * \param contact
     * \param outgoing une longueur d'onde <= 0 indique l'absence de
     *                 rayon : ce qui est toujours le cas ici
     *                 puisque la source se comporte comme un mur
     *
     * \return true s'il y a un contact entre le rayon incident et
     *         l'objet, false sinon
     *
     * \throw std::domain_error si la source d'ingoing est dans shape_
     *
     * TODO attention donc à ne pas calculer l'interaction d'une
     * source de lumière avec son propre rayon émis !
     *
     * \sa LightModifier::interaction(const LightRay & ingoing, Point2Dd & contact, LightRay & outgoing)
     */
    virtual bool interaction(const LightRay & ingoing,
                             Point2Dd & contact,
                             LightRay & outgoing);

    inline bool state() const;
    inline bool isOn() const;
    inline bool isOff() const;

    inline const Rectangle & shape() const;
    inline int wavelength() const;
    inline double emissionAngle() const;

    /*!
     * \brief setState
     *
     * avertit les Observateur enregistrés si l'état allumé / éteint
     * change
     *
     * \param on
     *
     * \sa SujetDObservation::notifierChangement()
     */
    inline void setState(bool on);

    /*!
     * \brief switchOn
     *
     * avertit les Observateur enregistrés si l'état allumé / éteint
     * change
     *
     * équivalent à setState(true);
     *
     * \sa void setState(bool on)
     * \sa SujetDObservation::notifierChangement()
     */
    inline void switchOn();

    /*!
     * \brief switchOff
     *
     * avertit les Observateur enregistrés si l'état allumé / éteint
     * change
     *
     * équivalent à setState(false);
     *
     * \sa void setState(bool on)
     * \sa SujetDObservation::notifierChangement()
     */
    inline void switchOff();

    /*!
     * \brief toggle
     *
     * avertit les Observateur enregistrés si l'état allumé / éteint
     * change
     *
     * équivalent à setState(!on_);
     *
     * \sa void setState(bool on)
     * \sa SujetDObservation::notifierChangement()
     */
    inline void toggle();

    /*!
     * \brief lightRay
     *
     * \param outgoing le rayon émis. si la source est éteinte
     *                 outgoing n'est pas modifié
     *
     * \return true si un rayon est émis, c.-à-d. si la source est
     *         allumée, false sinon
     */
    bool lightRay(LightRay & outgoing) const;

    /*!
     * \brief lightRay
     *
     * \return le rayon émis. si la source est éteinte sa
     *         longueur d'onde est <= 0
     */
    LightRay lightRay() const;

    /*!
     * \brief lightRay
     * \param visible mis à true si un rayon est émis, c.-à-d. si
     *                la source est allumée, false sinon
     * \return le rayon émis. si la source est éteinte sa
     *         longueur d'onde est <= 0
     */
    LightRay lightRay(bool & visible) const;
};

// prototype

std::ostream & operator<<(std::ostream & out,
                          const SourceOfLight & in);

// méthodes inline

bool SourceOfLight::state() const
{
    return on_;
}

bool SourceOfLight::isOn() const
{
    return on_;
}

bool SourceOfLight::isOff() const
{
    return !on_;
}

inline const Rectangle & SourceOfLight::shape() const
{
    return shape_;
}

inline int SourceOfLight::wavelength() const
{
    return wavelength_;
}

inline double SourceOfLight::emissionAngle() const
{
    return emissionAngle_;
}

void SourceOfLight::setState(bool on)
{
    if (on_ != on)
    {
        on_ = on;
        notifierChangement();
    }
}

void SourceOfLight::switchOn()
{
    setState(true);
}

void SourceOfLight::switchOff()
{
    setState(false);
}

inline void SourceOfLight::toggle()
{
    setState(!on_);
}

} // namespace nvs

#endif // SOURCEOFLIGHT_H
