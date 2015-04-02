#ifndef LIGHTMODIFIER_H
#define LIGHTMODIFIER_H

namespace nvs
{

class Point2Dd;
class LightRay;

class LightModifier
{
  protected:

    LightRay * lastIngoing_ {nullptr};
    Point2Dd * lastContactIn_ {nullptr};
    LightRay * lastOutgoing_ {nullptr};
    Point2Dd * lastContactOut_ {nullptr};

    /*!
     * \brief checkIngoing
     *
     * les classes filles doivent commencer par appeler cette méthode
     * dans leur surdéfinition de checkInteraction()
     *
     * elle vérifie si ingoing est égal à lastIngoing_. si c'est le cas,
     * elle retourne false, sinon, elle retourne true, assigne à
     * lastIngoing_ un clone de ingoing et détruit et met
     * à nullptr lastOutgoing_, lastContactIn_ et lastContactOut_.
     *
     * \param ingoing
     * \return
     */
    bool checkNewIngoing(const LightRay & ingoing);

  public:

    virtual ~LightModifier();

    // clonage !
    LightModifier(const LightModifier &original);
    LightModifier & operator=(const LightModifier & rhs);

    /*!
     * \brief checkInteraction
     *
     * cette méthode doit être implémentée dans les classes filles
     *
     * \param ingoing le rayon incident
     *
     * \param contact le point de contact en cas d'interaction
     *
     * \return true si le rayon ingoing frappe l'objet, false sinon
     */
    virtual bool checkInteraction(const LightRay & ingoing,
                                  Point2Dd & contact) = 0;

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
