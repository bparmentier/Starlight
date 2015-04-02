#ifndef LINE_H
#define LINE_H

#include "point2dd.h"

#include <ostream>
#include <limits>
#include <cmath>
#include <vector>

// TODO (?) : HalfLine == Ray...

namespace nvs
{

class Segment;
class Circle;
class Rectangle;

/*!
 * \brief The Line class
 *
 * droite d d'équation :
 *      d ≡ a x + b y + c = 0
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
 * alpha : angle entre la droite et ox mesuré comme dans le cercle
 *         trigonométrique => tg(alpha) = a (opposé du coef. ang. std
 *         car ici y croît vers le bas)
 *    par choix : alpha \in [0, pi[
 */
class Line
{
    double a_ { -1.};
    double b_ {1.};
    double c_ {0.};

    double alpha_ {.75 * M_PI};

    // incertitudes absolues sur a_, b_, c_, alpha_ : nécessairement > 0
    double da_ {std::numeric_limits<double>::epsilon()}; // car a_{-1.}
    double db_ {std::numeric_limits<double>::epsilon()};
    double dc_ {std::numeric_limits<double>::min()}; // car c_ {0.}
    double dalpha_ {std::numeric_limits<double>::epsilon()};

    // propagation des incertitudes :
    // https://fr.wikipedia.org/wiki/Propagation_des_incertitudes
    // https://fr.wikipedia.org/wiki/Propagation_des_incertitudes#Incertitude_sur_une_addition_ou_une_soustraction
    // https://fr.wikipedia.org/wiki/Propagation_des_incertitudes#Incertitude_sur_un_produit_ou_un_quotient

  public:

    /*!
     * \brief Line
     *
     * droite passant par (0,0) et (1,1)
     *
     */
    Line() = default;

    /*!
     * \brief Line
     * \param p1
     * \param p2
     *
     * \throw invalid_argument si p1 == p2
     */
    Line(const Point2Dd & p1, const Point2Dd & p2);

    /*!
     * \brief Line
     *
     * dalpha_ est mis à
     *  max({std::numeric_limits<double>::min(),
     *       abs(alpha) * std::numeric_limits<double>::epsilon(),
     *       abs(dalpha)})
     *
     * \param p1
     * \param alpha
     * \param dalpha : incertitude sur alpha
     */
    Line(const Point2Dd & p, double alpha, double dalpha = 0.);

    /*!
     * \brief Line
     *
     * da_, db_ et dc_ sont produits à partir d'incertitudes relatives
     * d'ordre std::numeric_limits<double>::epsilon() et
     * std::numeric_limits<double>::min() selon les cas
     *
     * \param a
     * \param b
     * \param c
     */
    Line(double a, double b, double c);

    /*!
     * \brief Line
     *
     * TODO : expliquer comment da, db et dc sont utilisés
     *
     * \param a
     * \param b
     * \param c
     */
    Line(double a, double b, double c, double da, double db, double dc);

    virtual ~Line() = default;

    inline double a() const;
    inline double b() const;
    inline double c() const;
    inline double alpha() const;
    inline double alpha_PI() const;

    inline double da() const;
    inline double db() const;
    inline double dc() const;
    inline double dalpha() const;

    bool contains(const Point2Dd & point) const;

    bool parallel(const Line & line) const;

    bool perpendicular(const Line & line) const;

    /*!
     * \brief intersection intersection de 2 lignes
     *
     * retourne false si l'intersection est vide
     *                          (lignes parallèles distinctes)
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, met isPoint à true si l'intersection est un point
     *                          (lignes sécantes)
     *            ou met isPoint à false si l'intersection est la ligne
     *                          (lignes confondues)
     *
     * \param line
     * \param point
     * \param isPoint
     * \return
     */
    bool intersection(const Line & line, Point2Dd & point,
                      bool & isPoint) const;

    /*!
     * \brief intersection intersection entre une ligne et un segment
     *
     * retourne false si l'intersection est vide
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, met isPoint à true si l'intersection est un point
     *                          (ligne et segment sécants)
     *            ou met isPoint à false si l'intersection est le segment
     *                          (segment confondu dans la ligne)
     *
     * attention : point peut être modifié même s'il n'y a pas
     *             d'intersection !
     *
     * \param segment
     * \param point
     * \param isPoint
     * \return
     *
     * \sa Segment::intersection(const Line & line, Point2Dd & point, bool & isPoint) const
     */
    bool intersection(const Segment & segment, Point2Dd & point,
                      bool & isPoint) const;

    /*!
     * \brief intersection intersection d'une ligne et d'un cercle
     *
     * retourne false si l'intersection est vide
     *  dans ce cas, points est vidé
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, points est garni du ou des deux points
     *      d'intersection
     *
     *
     * \param circle
     * \param points
     * \return
     *
     * \sa Circle::intersection(const Line & line, std::vector<Point2Dd> & points) const
     */
    bool intersection(const Circle & circle,
                      std::vector<Point2Dd> & points) const;

    /*!
     * \brief intersection intersection d'une ligne et d'un rectangle
     *
     * \param rectangle le rectangle dont on calcule l'intersection avec
     *                la ligne *this
     *
     * \param points s'il y a intersection et que cette intersection
     *               n'est pas un côté du rectangle, alors il y a 1
     *               ou 2 points d'intersection ; s'il y a une
     *               intersection mais pas d'1 ou 2 points, points est
     *               vidé alors que true est retourné
     *
     * \param result le côté du rectangle qui correspond à
     *               l'intersection quand celle-ce ne se réduit pas
     *               à 1 ou 2 points
     *
     * \return true s'il existe une intersection, false si
     *         l'intersection est vide
     *
     * \sa Rectangle::intersection(const Line & line, std::vector<Point2Dd> & points, Segment & result) const
     */
    bool intersection(const Rectangle & rectangle,
                      std::vector<Point2Dd> & points,
                      Segment & result) const;

    /*!
     * \brief normal
     *
     * \param point point par lequel la normale doit passer
     *
     * \param normalLine la normale
     *
     * \return le point à l'intersection entre *this et sa normale
     */
    Point2Dd normal(const Point2Dd & point, Line & normalLine) const;

    // amis
    friend std::ostream & operator<<(std::ostream & out, const Line & in);

    friend bool operator==(const Line & line1, const Line & line2);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out, const Line & in);

bool operator==(const Line & line1, const Line & line2);

inline bool operator!=(const Line & line1, const Line & line2);

inline bool parallel(const Line & line1, const Line & line2);

inline bool perpendicular(const Line & line1, const Line & line2);

/*!
 * \brief intersection
 * \param line1
 * \param line2
 * \param point
 * \param isPoint true si 1 point, false si droite : line1 == line2
 * \return false si intersection vide
 *
 * \sa Line::intersection(const Line & line, Point2Dd & point, bool & isPoint) const
 */
inline bool intersection(const Line & line1, const Line & line2,
                         Point2Dd & point, bool & isPoint);

inline Point2Dd normal(const Line & line, const Point2Dd & point,
                       Line & result);

// méthodes inline

inline double Line::a() const
{
    return a_;
}

inline double Line::b() const
{
    return b_;
}

inline double Line::c() const
{
    return c_;
}

inline double Line::alpha() const
{
    return alpha_;
}

inline double Line::alpha_PI() const
{
    return alpha_ / M_PI;
}

inline double Line::da() const
{
    return da_;
}

inline double Line::db() const
{
    return db_;
}

inline double Line::dc() const
{
    return dc_;
}

inline double Line::dalpha() const
{
    return dalpha_;
}

// fonctions inline

inline std::ostream & operator<<(std::ostream & out, const Line & in)
{
    return out << in.a_ << " x + " << in.b_ << " y + "  << in.c_ <<
           " = 0, (alpha = " << in.alpha_  << " rad = " << in.alpha_PI()
           << " π)";
}

inline bool operator!=(const Line & line1, const Line & line2)
{
    return !(line1 == line2);
}

inline bool intersection(const Line & line1, const Line & line2,
                         Point2Dd & point, bool & isPoint)
{
    return line1.intersection(line2, point, isPoint);
}

inline bool parallel(const Line & line1, const Line & line2)
{
    return line1.parallel(line2);
}

inline bool perpendicular(const Line & line1, const Line & line2)
{
    return line1.perpendicular(line2);
}

inline Point2Dd normal(const Line & line, const Point2Dd & point,
                       Line & result)
{
    return line.normal(point, result);
}

} // namespace nvs

#endif // LINE_H
