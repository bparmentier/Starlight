#include "level.h"
#include "lightray.h"

#include "../geometry/point2dd.h"

#include <stdexcept>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

namespace nvs
{

Level::Level(int width, int height, const SourceOfLight & source,
             const Target & target, const std::vector<Wall> & vWall,
             const std::vector<Mirror> & vMirror,
             const std::vector<Lens> & vLens,
             const std::vector<Crystal> & vCrystal,
             const std::vector<Bomb> & vBomb) :
    width_ {width}, height_ {height}, source_ {source}, target_ {target},
       walls_ {vWall}, mirrors_ {vMirror}, lenses_ {vLens},
crystals_ {vCrystal}, bombs_ {vBomb}
{
    // les murs de la pièce
    walls_.emplace_back(Wall{{0., 0.}, {width_ - 1., 0.}});
    walls_.emplace_back(Wall{{width_ - 1., 0.}, {width_ - 1., height_ - 1.}});
    walls_.emplace_back(Wall{{width_ - 1., height_ - 1.}, {0., height_ - 1.}});
    walls_.emplace_back(Wall{{0., height_ - 1.}, {0., 0.}});

    source_.attacher(this);

    for (auto & e : mirrors_)
    {
        e.attacher(this);
    }

    rafraichir(&source_);
}

Level::~Level()
{
    for (auto & e : mirrors_)
    {
        e.detacher(this);
    }

    source_.detacher(this);
}

bool Level::finished() const
{
    return won() || lost();
}

bool Level::won() const
{
    return target_.enlightened() && !lost();
}

bool Level::lost() const
{
    for (const Bomb & e : bombs_)
    {
        if (e.enlightened())
        {
            return true;
        }
    }
    return false;
}

void Level::updateBoundedRays()
{
    // ici on est sûr (cf. rafraichir) que la source est allumée
    if (source_.isOff())
    {
        throw logic_error {__func__};
        // ceci ne devrait jamais arriver
    }

    // ici la source est allumée

    // TODO : avec polymorphisme tout se factorise !
    //        c'est assez laid ce qui suit...

    LightRay ingoing {source_.lightRay()};
    Point2Dd contact;
    LightRay outgoing;

    do
    {
        vector<tuple<Point2Dd, LightRay>> nearestTouchedObjects;
        vector<tuple<Point2Dd, LightRay>> touchedObjects;

        auto tuplecompare = [ingoing](const tuple<Point2Dd, LightRay> & lhs,
                                      const tuple<Point2Dd, LightRay> & rhs)
        {
            return ingoing.emission().distance(get<0>(lhs)) <
                   ingoing.emission().distance(get<0>(rhs));
        };

        // source touchée ?
        if (!source_.shape().contains(ingoing.emission()))
        {
            if (source_.interaction(ingoing, contact, outgoing))
            {
                nearestTouchedObjects.emplace_back(make_tuple(contact, outgoing));
            }
        }

        // cible touchée ?
        if (target_.interaction(ingoing, contact, outgoing))
        {
            nearestTouchedObjects.emplace_back(make_tuple(contact, outgoing));
        }

        // murs touchés ?
        for (Wall & e : walls_)
        {
            if (e.interaction(ingoing, contact, outgoing))
            {
                touchedObjects.emplace_back(make_tuple(contact, outgoing));
            }
        }
        // le mur touché est celui le plus proche de la source
        // rem. : il y a toujours un mur touché : attention, ce
        //        n'est pas vrai pour les autres éléments du décor !
        auto it = min_element(begin(touchedObjects), end(touchedObjects),
                              tuplecompare);
        // ici it pointe sur le mur touché le plus proche du point
        // d'émission
        nearestTouchedObjects.emplace_back(*it);

        // miroirs touchés ?
        touchedObjects.clear();
        for (Mirror & e : mirrors_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.interaction(ingoing, contact, outgoing))
                {
                    touchedObjects.emplace_back(make_tuple(contact, outgoing));
                }
            }
        }
        // le miroir touché est celui le plus proche de la source
        // rem. : il n'y a pas toujours un miroir touché !
        if (!touchedObjects.empty())
        {
            it = min_element(begin(touchedObjects), end(touchedObjects),
                             tuplecompare);
            // ici it pointe sur le miroir touché le plus proche du point
            // d'émission
            nearestTouchedObjects.emplace_back(*it);
        }

        // lentilles touchées ?
        touchedObjects.clear();
        for (Lens & e : lenses_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.interaction(ingoing, contact, outgoing))
                {
                    touchedObjects.emplace_back(make_tuple(contact, outgoing));
                }
            }
        }
        // la lentille touchée est celle la plus proche de la source
        // rem. : il n'y a pas toujours une lentille touchée !
        if (!touchedObjects.empty())
        {
            it = min_element(begin(touchedObjects), end(touchedObjects),
                             tuplecompare);
            // ici it pointe sur la lentille touchée la plus proche du point
            // d'émission
            nearestTouchedObjects.emplace_back(*it);
        }

        // cristaux touchés ?
        touchedObjects.clear();
        for (Crystal & e : crystals_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.interaction(ingoing, contact, outgoing))
                {
                    touchedObjects.emplace_back(make_tuple(contact, outgoing));
                }
            }
        }
        // le cristal touché est celui le plus proche de la source
        // rem. : il n'y a pas toujours un cristal touché !
        if (!touchedObjects.empty())
        {
            it = min_element(begin(touchedObjects), end(touchedObjects),
                             tuplecompare);
            // ici it pointe sur le cristal touché le plus proche du point
            // d'émission
            nearestTouchedObjects.emplace_back(*it);
        }

        // bombes touchées ?
        touchedObjects.clear();
        for (Bomb & e : bombs_)
        {
            if (e.interaction(ingoing, contact, outgoing))
            {
                touchedObjects.emplace_back(make_tuple(contact, outgoing));
            }
        }
        // la bombe touchée est celle la plus proche de la source
        // rem. : il n'y a pas toujours une bombe touchée !
        if (!touchedObjects.empty())
        {
            it = min_element(begin(touchedObjects), end(touchedObjects),
                             tuplecompare);
            // ici it pointe sur la bombe touchée la plus proche du point
            // d'émission
            nearestTouchedObjects.emplace_back(*it);
        }

        // ici tous les objets ont été passés en revue
        // il faut déterminer le plus proche des plus proches

        it = min_element(begin(nearestTouchedObjects),
                         end(nearestTouchedObjects), tuplecompare);

        // ici it pointe sur le tuple<Point2Dd, LightRay> de contact
        // le plus proche de la source

        // ajout du rayon à l'ensemble des rayons
        boundedRays_.emplace_back(make_pair(Segment {ingoing.emission(), get<0>(*it)},
                                            ingoing.wavelength()));

        // on prépare la suite
        ingoing = get<1>(*it);

        // ça continue ou arrêt sur surface absorbante ?
    }
    while (ingoing.wavelength() > 0);
}


void Level::rafraichir(SujetDObservation * sdo)
{
    // TODO : optimiser selon le miroir qui a bougé...
    boundedRays_.clear();

    if (source_.isOn())
    {
        updateBoundedRays();
    }

    notifierChangement();
}

// fonctions

std::ostream & operator<<(std::ostream & out, const Level & in)
{
    out << in.source() << endl;
    out << in.target() << endl;
    for (const auto & e : in.walls())
    {
        out << e << endl;
    }
    for (const auto & e : in.mirrors())
    {
        out << e << endl;
    }
    for (const auto & e : in.lenses())
    {
        out << e << endl;
    }
    for (const auto & e : in.crystals())
    {
        out << e << endl;
    }
    for (const auto & e : in.bombs())
    {
        out << e << endl;
    }
    for (const auto & e : in.boundedRays())
    {
        out << e.first << ", wavelength : " << e.second << endl;
    }

    return out;
}

} // namespace nvs
