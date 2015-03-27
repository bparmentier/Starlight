#ifndef CIRCLE_H
#define CIRCLE_H

#include "point2dd.h"
#include "../misc/approximativecomparison.h"

#include <limits>
#include <ostream>
#include <vector>

namespace nvs
{

class Line;
class Segment;

class Circle
{
    Point2Dd    center_ {0., 0.};
    double      radius_ {1.};

    // indéterminations : dcenter_ compris dans center_.dx_ et dy_
    double      dradius_ {std::numeric_limits<double>::epsilon()};

    /*!
     * \brief checkRadius
     *
     * teste si radius_ est bien strictement positif à dradius_ près
     *
     * \return
     */
    inline bool checkRadius() const;

  public:
    /*!
     * \brief Circle
     */
    Circle() = default;

    /*!
     * \brief Circle
     *
     * dradius_ est estimés comme :
     * max(std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon())
     *
     * \param center
     * \param radius
     *
     * \throw std::invalid_argument si radius <= 0
     */
    Circle(const Point2Dd & center, double radius);

    /*!
     * \brief Circle
     *
     * dradius_ est estimés comme :
     * max({std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon(),
     *          std::abs(dradius)})
     *
     * \param center
     * \param radius
     * \param dradius
     *
     * \throw std::invalid_argument si radius <= 0
     */
    Circle(const Point2Dd & center, double radius, double dradius);

    /*!
     * \brief Circle
     *
     * center.dx_ et center.dy_ sont estimés comme :
     * max(std::numeric_limits<double>::min(), std::abs(XXX) *
     *          std::numeric_limits<double>::epsilon())
     *
     * dradius_ est estimés comme :
     * max(std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon())
     *
     * \param x
     * \param y
     * \param radius
     *
     * \throw std::invalid_argument si radius <= 0
     */
    Circle(double x, double y, double radius);

    /*!
     * \brief Circle
     *
     * center.dx_ et center.dy_ sont estimés comme :
     * max(std::numeric_limits<double>::min(), std::abs(XXX) *
     *          std::numeric_limits<double>::epsilon())
     *
     * dradius_ est estimés comme :
     * max({std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon(),
     *          std::abs(dradius)})
     *
     * \param x
     * \param y
     * \param radius
     * \param dradius
     */
    Circle(double x, double y, double radius, double dradius);

    /*!
     * \brief Circle
     *
     * center.dx_ et center.dy_ sont estimés comme :
     * max({std::numeric_limits<double>::min(), std::abs(XXX) *
     *          std::numeric_limits<double>::epsilon(),
     *          abs(dXXX)})
     *
     * dradius_ est estimés comme :
     * max(std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon())
     *
     * \param x
     * \param y
     * \param radius
     * \param dx
     * \param dy
     */
    Circle(double x, double y, double radius, double dx, double dy);

    /*!
     * \brief Circle
     *
     * center.dx_ et center.dy_ sont estimés comme :
     * max({std::numeric_limits<double>::min(), std::abs(XXX) *
     *          std::numeric_limits<double>::epsilon(),
     *          abs(dXXX)})
     *
     * dradius_ est estimés comme :
     * max({std::numeric_limits<double>::min(), std::abs(radius) *
     *          std::numeric_limits<double>::epsilon(),
     *          std::abs(dradius)})
     *
     * \param x
     * \param y
     * \param radius
     * \param dx
     * \param dy
     * \param dradius
     */
    Circle(double x, double y, double radius, double dx, double dy,
           double dradius);

    inline const Point2Dd & center() const;
    inline double x() const;
    inline double y() const;
    inline double radius() const;

    inline double dx() const;
    inline double dy() const;
    inline double dradius() const;

    // TODO (?) setters

    /*!
     * \brief intersection intersection d'un cercle et d'une ligne
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
     */
    bool intersection(const Line & line,
                      std::vector<Point2Dd> & points) const;

    /*!
     * \brief intersection intersection d'un cercle et d'un segment
     *
     * retourne false si l'intersection est vide
     *  dans ce cas, points est vidé
     * retourne true si l'intersection n'est pas vide
     *  dans ce cas, points est garni du ou des deux points
     *      d'intersection
     *
     * \param segment
     * \param points
     * \return
     */
    bool intersection(const Segment & segment,
                      std::vector<Point2Dd> & points) const;

    bool contains(const Point2Dd & point) const;

    bool hasOnSide(const Point2Dd & point) const;

    // TODO (?) intersection de 2 cercles, d'un cercle et d'un rectangle

    // amis

    friend std::ostream & operator<<(std::ostream & out,
                                     const Circle & in);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out,
                                 const Circle & in);

/*!
 * \brief intersection
 * \param circle
 * \param line
 * \param points
 * \return
 *
 * \sa Circle::intersection(const Line & line, std::vector<Point2Dd> & points) const
 */
inline bool intersection(const Circle & circle, const Line & line,
                  std::vector<Point2Dd> & points);

/*!
 * \brief intersection
 * \param line
 * \param circle
 * \param points
 * \return
 *
 * \sa Circle::intersection(const Line & line, std::vector<Point2Dd> & points) const
 */
inline bool intersection(const Line & line, const Circle & circle,
                  std::vector<Point2Dd> & points);
/*!
 * \brief intersection
 * \param circle
 * \param segment
 * \param points
 * \return
 *
 * \sa Circle::intersection(const Segment & segment, std::vector<Point2Dd> & points) const
 */
inline bool intersection(const Circle & circle, const Segment & segment,
                  std::vector<Point2Dd> & points);
/*!
 * \brief intersection
 * \param segment
 * \param circle
 * \param points
 * \return
 *
 * \sa Circle::intersection(const Segment & segment, std::vector<Point2Dd> & points) const
 */
inline bool intersection(const Segment & segment, const Circle & circle,
                  std::vector<Point2Dd> & points);

// méthodes inline

inline bool Circle::checkRadius() const
{
    return ApproximativeComparison {std::numeric_limits<double>::min(), dradius_} .less(
               0, radius_);
}

inline const Point2Dd & Circle::center() const
{
    return center_;
}

inline double Circle::x() const
{
    return center_.x();
}

inline double Circle::y() const
{
    return center_.y();
}

inline double Circle::radius() const
{
    return radius_;
}

inline double Circle::dx() const
{
    return center_.dx();
}

inline double Circle::dy() const
{
    return center_.dy();
}

inline double Circle::dradius() const
{
    return dradius_;
}

// fonctions inline

inline std::ostream & operator<<(std::ostream & out,
                                 const Circle & in)
{
    return out << "[" << in.center_ << ", " << in.radius_ << "]";
}

bool intersection(const Circle & circle, const Line & line,
                  std::vector<Point2Dd> & points)
{
    return circle.intersection(line, points);
}

bool intersection(const Line & line, const Circle & circle,
                  std::vector<Point2Dd> & points)
{
    return circle.intersection(line, points);
}

bool intersection(const Circle & circle, const Segment & segment,
                  std::vector<Point2Dd> & points)
{
    return circle.intersection(segment, points);
}

bool intersection(const Segment & segment, const Circle & circle,
                  std::vector<Point2Dd> & points)
{
    return circle.intersection(segment, points);
}

}

#endif // CIRCLE_H
