#ifndef LEVEL_H
#define LEVEL_H

#include "../o_sdo/observateur.h"
#include "../o_sdo/sujetdobservation.h"

#include "sourceoflight.h"
#include "target.h"
#include "wall.h"
#include "mirror.h"
#include "lens.h"
#include "crystal.h"
#include "bomb.h"

#include "../geometry/segment.h"

#include <vector>
#include <ostream>
#include <utility>

namespace nvs
{

// TODO : utiliser le polymorphisme (!)

/*!
 * \brief The Level class
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
 * angles : mesurés entre la droite et ox mesuré comme dans le cercle
 *          trigonométrique
 *
 */
class Level : public Observateur, public SujetDObservation
{
    const int               width_;
    const int               height_;

    SourceOfLight           source_;
    Target                  target_;

    std::vector<Wall>       walls_;
    std::vector<Mirror>     mirrors_;
    std::vector<Lens>       lenses_;
    std::vector<Crystal>    crystals_;
    std::vector<Bomb>       bombs_;

    // les rayons lumineux finis
    // Segment::first_ correspond à l'origine du rayon
    // Segment::second_ correspond à la fin du rayon
    // TODO : class BounderdLightRay : Segment + wavelength_
    std::vector<std::pair<Segment,int>>    boundedRays_;

    /*!
     * \brief updateBoundedRays
     *
     * \throw std::logic_error si la source est éteinte
     */
    void updateBoundedRays();

  public:

    Level(int width, int height, const SourceOfLight & source,
          const Target & target, const std::vector<Wall> & vWall,
          const std::vector<Mirror> & vMirror,
          const std::vector<Lens> & vLens,
          const std::vector<Crystal> & vCrystal,
          const std::vector<Bomb> & vBomb);

    virtual ~Level();

    Level(const Level & original) = delete;
    Level & operator=(const Level & rhs) = delete;

    /*!
     * \brief rafraichir
     *
     * avertit les Observateur enregistrés si nécessaire, c.-à-d.
     * quand la source a changé d'état ou qu'un miroir a été
     * bougé... et que donc les unbounded rays ont été modifiés
     *
     * \param sdo
     *
     * \sa SujetDObservation::notifierChangement()
     */
    void rafraichir(SujetDObservation * sdo);

    inline int width() const;
    inline int height() const;
    inline const SourceOfLight & source() const;
    inline const Target & target() const;
    inline const std::vector<Wall> & walls() const;
    inline const std::vector<Mirror> & mirrors() const;
    inline const std::vector<Lens> & lenses() const;
    inline const std::vector<Crystal> & crystals() const;
    inline const std::vector<Bomb> & bombs() const;
    inline const std::vector<std::pair<Segment,int>> & boundedRays() const;

    inline SourceOfLight & source();
    inline std::vector<Mirror> & mirrors();

    bool finished() const;
    bool won() const;
    bool lost() const;
};

// prototypes

std::ostream & operator<<(std::ostream & out, const Level & in);

// méthodes inline

inline int Level::width() const
{
    return width_;
}

inline int Level::height() const
{
    return height_;
}

inline const SourceOfLight & Level::source() const
{
    return source_;
}

inline const Target & Level::target() const
{
    return target_;
}

inline const std::vector<Wall> & Level::walls() const
{
    return walls_;
}

inline const std::vector<Mirror> & Level::mirrors() const
{
    return mirrors_;
}

inline const std::vector<Lens> & Level::lenses() const
{
    return lenses_;
}

inline const std::vector<Crystal> & Level::crystals() const
{
    return crystals_;
}

inline const std::vector<Bomb> & Level::bombs() const
{
    return bombs_;
}

inline const std::vector<std::pair<Segment, int> > &Level::boundedRays() const
{
    return boundedRays_;
}

inline SourceOfLight & Level::source()
{
    return source_;
}

inline std::vector<Mirror> & Level::mirrors()
{
    return mirrors_;
}

} // namespace nvs

#endif // LEVEL_H
