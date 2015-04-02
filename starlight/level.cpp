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

    do
    {
        vector<tuple<LightModifier *, Point2Dd>> touchedObjects {};

        // source touchée ?
        if (!source_.shape().contains(ingoing.emission()))
        {
            if (source_.checkInteraction(ingoing, contact))
            {
                touchedObjects.emplace_back(make_tuple(&source_, contact));
            }
        }

        // cible touchée ?
        if (target_.checkInteraction(ingoing, contact))
        {
            touchedObjects.emplace_back(make_tuple(&target_, contact));
        }

        // murs touchés ?
        for (Wall & e : walls_)
        {
            if (e.checkInteraction(ingoing, contact))
            {
                touchedObjects.emplace_back(make_tuple(&e, contact));
            }
        }

        // miroirs touchés ?
        for (Mirror & e : mirrors_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.checkInteraction(ingoing, contact))
                {
                    touchedObjects.emplace_back(make_tuple(&e, contact));
                }
            }
        }

        // lentilles touchées ?
        for (Lens & e : lenses_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.checkInteraction(ingoing, contact))
                {
                    touchedObjects.emplace_back(make_tuple(&e, contact));
                }
            }
        }

        // cristaux touchés ?
        for (Crystal & e : crystals_)
        {
            if (!e.shape().contains(ingoing.emission()))
            {
                if (e.checkInteraction(ingoing, contact))
                {
                    touchedObjects.emplace_back(make_tuple(&e, contact));
                }
            }
        }

        // bombes touchées ?
        for (Bomb & e : bombs_)
        {
            if (e.checkInteraction(ingoing, contact))
            {
                touchedObjects.emplace_back(make_tuple(&e, contact));
            }
        }

        // il y a toujours au moins un mur touché
        // objet touché le plus proche ?

        auto it = min_element(begin(touchedObjects), end(touchedObjects),
                              [ingoing](const tuple<LightModifier *, Point2Dd> & lhs,
                                        const tuple<LightModifier *, Point2Dd> & rhs)
        {
            return ingoing.emission().distance(get<1>(lhs)) <
                   ingoing.emission().distance(get<1>(rhs));
        });

        // ici on calcule l'interaction entre le rayon et l'objet le
        // plus proche

        LightRay outgoing;

        get<0>(*it)->interaction(ingoing, contact, outgoing);

        // ajout du rayon à l'ensemble des rayons
        boundedRays_.emplace_back(make_pair(Segment {ingoing.emission(), contact},
                                            ingoing.wavelength()));

        // on prépare la suite
        ingoing = outgoing;

        // ça continue ou arrêt sur surface absorbante ?
    }
    while (ingoing.wavelength() > 0);
    // NOTE : il est possible d'avoir une boucle sans fin...
    // TODO : régler ce problème...
}


void Level::rafraichir(SujetDObservation *)
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
