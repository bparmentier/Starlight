#ifndef SEGMENT_H
#define SEGMENT_H

#include "line.h"
#include "point2dd.h"

#include <ostream>
#include <vector>

// composition plutôt qu'héritage car un segment n'est pas une ligne
// mais plutôt une ligne est un segment sans limites !

namespace nvs
{

class Circle;
class Rectangle;

class Segment
{
    Point2Dd first_ {0, 0};
    Point2Dd second_ {1, 1};
    // en fait, l'ordre des points n'a pas d'importance dans un segment

  public:

    Segment() = default;

    /*!
     * \brief Segment
     * \param p1
     * \param p2
     *
     * \throw invalid_argument si p1 == p2
     *
     * \sa Line(const Point2Dd & p1, const Point2Dd & p2)
     */
    Segment(const Point2Dd & first, const Point2Dd & second);

    // TODO (?) : constructeur avec angle et 1 point et longueur...

    inline Line line() const;

    inline const Point2Dd first() const;
    inline const Point2Dd second() const;

    double lenght() const;

    bool contains(const Point2Dd & point) const;

    /*!
     * \brief intersection intersection d'un segment avec une ligne
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
     * \param line
     * \param point
     * \param isPoint
     * \return
     */
    bool intersection(const Line & line, Point2Dd & point,
                      bool & isPoint) const;

    /*!
     * \brief intersection intersection de deux segments
     *
     * retourne false si l'intersection est vide
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, met isPoint à true si l'intersection est un point
     *                          (segments sécants)
     *            ou met isPoint à false si l'intersection est un segment
     *                  (les segments sont (partiellement) confondus)
     *
     * attention : point peut être modifié même s'il n'y a pas
     *             d'intersection !
     *
     * \param other
     * \param point
     * \param isPoint
     * \param result
     * \return
     */
    bool intersection(const Segment & other, Point2Dd & point,
                      bool & isPoint, Segment & result) const;

    /*!
     * \brief intersection intersection d'un segment et d'un cercle
     *
     * retourne false si l'intersection est vide
     *  dans ce cas, points est vidé
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, points est garni du ou des deux points
     *      d'intersection
     *
     * \param line
     * \param points
     * \return
     *
     * \sa Circle::intersection(const Segment & segment, std::vector<Point2Dd> & points) const
     */
    bool intersection(const Circle & circle,
                      std::vector<Point2Dd> & points) const;

    /*!
     * \brief intersection intersection d'un segment et d'un rectangle
     *
     * result peut être modifié même si l'intersection n'est pas un
     * segment
     *
     * \param rectangle le rectangle dont on calcule l'intersection avec
     *                le rectangle *this
     *
     * \param points s'il y a intersection et que cette intesection
     *               n'est pas une partie (segment) de côté du
     *               rectangle, alors il y a 1 ou 2 points
     *               d'intersection ; s'il y a une intersection mais
     *               pas d'1 ou 2 points, points est vide alors que
     *               true est retourné
     *
     * \param result le bout de côté du rectangle qui correspond à
     *               l'intersection quand celle-ce ne se réduit pas
     *               à 1 ou 2 points
     *
     * \return true s'il existe une intersection, false si
     *         l'intersection est vide
     *
     * \sa Rectangle::intersection(const Segment & segment, std::vector<Point2Dd> & points, Segment & result) const
     */
    bool intersection(const Rectangle & rectangle,
                      std::vector<Point2Dd> & points,
                      Segment & result) const;

    // amis

    friend std::ostream & operator<<(std::ostream & out,
                                     const Segment & in);

    friend bool operator==(const Segment & segment1,
                           const Segment & segment2);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out,
                                 const Segment & in);

bool operator==(const Segment & segment1, const Segment & segment2);

inline bool operator!=(const Segment & segment1,
                       const Segment & segment2);

/*!
 * \brief intersection
 *
 * attention : point peut être modifié même s'il n'y a pas
 *             d'intersection !
 *
 * \param line
 * \param segment
 * \param point
 * \param isPoint
 * \return
 *
 * \sa Segment::intersection(const Line & line, Point2Dd & point, bool & isPoint) const
 */
bool intersection(const Line & line, const Segment & segment,
                  Point2Dd & point, bool & isPoint);

/*!
 * \brief intersection
 * \param segment
 * \param line
 * \param point
 * \param isPoint
 * \return
 *
 * \sa Segment::intersection(const Line & line, Point2Dd & point, bool & isPoint) const
 */
bool intersection(const Segment & segment, const Line & line,
                  Point2Dd & point, bool & isPoint);

/*!
 * \brief intersection
 * \param segment1
 * \param segment2
 * \param point
 * \param segment en cas de segment en intersection !
 * \param isPoint
 * \return
 *
 * \sa Segment::intersection(const Segment & other, Point2Dd & point, bool & isPoint, Segment & result) const
 */
bool intersection(const Segment & segment1, const Segment & segment2,
                  Point2Dd & point, bool & isPoint, Segment & segment);

// méthodes inline

inline Line Segment::line() const
{
    return {first_, second_};
}

inline const Point2Dd Segment::first() const
{
    return first_;
}

inline const Point2Dd Segment::second() const
{
    return second_;
}

// fonctions inline

std::ostream & operator<<(std::ostream & out, const Segment & in)
{
    return out << "[" << in.first_ << " -- " << in.second_ <<
           "], length = " << in.lenght();
}

inline bool operator!=(const Segment & segment1,
                       const Segment & segment2)
{
    return !(segment1 == segment2);
}

} // namespace nvs

#endif // SEGMENT_H
