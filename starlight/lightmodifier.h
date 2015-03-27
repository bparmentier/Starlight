#ifndef LIGHTMODIFIER_H
#define LIGHTMODIFIER_H

namespace nvs
{

class Point2Dd;
class LightRay;

class LightModifier
{
  public:
    virtual ~LightModifier() = default;

    /*!
     * \brief interaction
     *
     * \param ingoing le rayon incident
     *
     * \param contact le point de contact entre le rayon incident et
     *                l'objet
     *
     * \param outgoing le rayon sortant : son départ n'est pas
     *                 nécessairement le point de contact, p. ex. si
     *                 l'objet n'est pas unidimensionnel
     *                 une longueur d'onde <= 0 indique l'absence de
     *                 rayon
     *
     * \return true s'il y a un contact entre le rayon incident et
     *         l'objet, false sinon
     */
    virtual bool interaction(const LightRay & ingoing,
                             Point2Dd & contact,
                             LightRay & outgoing) = 0;

  protected:
    LightModifier() = default;
};

} // namespace nvs

#endif // LIGHTMODIFIER_H
