#ifndef POINT2DD_H
#define POINT2DD_H

#include "../misc/approximativecomparison.h"

#include <limits>
#include <algorithm>
#include <ostream>
#include <cmath>

namespace nvs
{

/*!
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
 *  donc m à gauche de n si m.x() < n.x()   (comme d'habitude)
 *    et m en bas de n si m.y() > n.y()     (car y croît vers le bas)
 *
 */

class Point2Dd
{
    double x_ {0.};
    double y_ {0.};

    // incertitudes absolues sur x_ et y_ : doit toujours être > 0 !
    double dx_ {std::numeric_limits<double>::min()};
    double dy_ {std::numeric_limits<double>::min()};

  public:
    /*!
     * \brief Point2Dd
     */
    Point2Dd() = default;

    Point2Dd(const Point2Dd &) = default;

    virtual ~Point2Dd() = default;

    /*!
     * \brief Point2Dd
     *
     * dx_ est mis à :
     *    max(std::numeric_limits<double>::min(),
     *      abs(x) * std::numeric_limits<double>::epsilon())
     * (idem pour dy_)
     *
     * \param x
     * \param y
     */
    inline Point2Dd(double x, double y);

    /*!
     * \brief Point2Dd
     *
     * dx_ est mis à :
     *    max({std::numeric_limits<double>::min(),
     *          abs(x) * std::numeric_limits<double>::epsilon(),
     *          abs(dx)})
     * (idem pour dy_)
     *
     * \param x
     * \param y
     * \param dx
     * \param dy
     */
    inline Point2Dd(double x, double y, double dx, double dy);

    /*!
     * \brief x
     * \return
     */
    inline double x() const;

    /*!
     * \brief y
     * \return
     */
    inline double y() const;

    /*!
     * \brief dx
     *
     * getter pour dx_
     *
     * \return
     */
    inline double dx() const;

    /*!
     * \brief dy
     *
     * getter pour dy_
     *
     * \return
     */
    inline double dy() const;


    /*!
     * \brief setX
     *
     * dx_ est mis à :
     * max(std::numeric_limits<double>::min(),
     *      abs(x) * std::numeric_limits<double>::epsilon())
     *
     * \param x
     */
    inline void setX(double x);

    /*!
     * \brief setX
     *
     * dx_ est mis à :
     *  max({std::numeric_limits<double>::min(),
     *          abs(x) * std::numeric_limits<double>::epsilon(),
     *          abs(dx)})
     *
     * \param x
     * \param dx
     */
    inline void setX(double x, double dx);

    /*!
     * \brief setY
     *
     * dy_ est mis à :
     * max(std::numeric_limits<double>::min(),
     *      abs(y) * std::numeric_limits<double>::epsilon())
     *
     * \param y
     */
    inline void setY(double y);

    /*!
     * \brief setY
     *
     * dy_ est mis à :
     *  max({std::numeric_limits<double>::min(),
     *          abs(y) * std::numeric_limits<double>::epsilon(),
     *          abs(dy)})
     *
     * \param x
     * \param dx
     */
    inline void setY(double y, double dy);

    /*!
     * \brief setDx
     *
     * setter pour dx_ : il est mis à :
     *  max({std::numeric_limits<double>::min(),
     *          abs(x_) * std::numeric_limits<double>::epsilon(),
     *          abs(dx)})
     *
     * \return
     */
    inline void setDx(double dx);

    /*!
     * \brief setDy
     *
     * setter pour dy_ : il est mis à :
     *  max({std::numeric_limits<double>::min(),
     *          abs(y_) * std::numeric_limits<double>::epsilon(),
     *          abs(dy)})
     *
     * \return
     */
    inline void setDy(double dy);

    /*!
     * \brief left
     *
     * this à gauche de other : this->x <= other.x
     * à dx_ et dy_ près
     *
     * \param other
     * \param strict
     * \return
     */
    inline bool left(const Point2Dd & other, bool strict = false) const;

    /*!
     * \brief right
     *
     * this à droite de other : this->x >= other.x
     * à dx_ et dy_ près
     *
     * \param other
     * \param strict
     * \return
     */
    inline bool right(const Point2Dd & other, bool strict = false) const;

    /*!
     * \brief above
     *
     * this au-dessus de other : this->y <= other.y
     *                              (car y croit vers le bas)
     * à dx_ et dy_ près
     *
     * \param other
     * \param strict
     * \return
     */
    inline bool above(const Point2Dd & other, bool strict = false) const;

    /*!
     * \brief below
     *
     * this en-dessous de other : this->y >= other.y (car y croit vers le bas)
     * à dx_ et dy_ près
     *
     * \param other
     * \param strict
     * \return
     */
    inline bool below(const Point2Dd & other, bool strict = false) const;

    /*!
     * \brief distance
     *
     * dx_ et dy_ ne sont pas utilisés ici
     *
     * \param p
     * \return
     */
    inline double distance(const Point2Dd & p) const;

    /*!
     * \brief distance
     *
     * rem. : l'incertitude sue la distance peut être supérieure
     *        à la distance. p. ex. si on a distance == 3 et
     *        ddistance == 4, on a distance \in [0, 7]
     *
     * \param p
     * \param ddistance pour stocker l'incertitude sur la distance
     * \return
     */
    double distance(const Point2Dd & p, double & ddistance) const;

    // amitié
    friend std::ostream & operator<<(std::ostream & out,
                                     const Point2Dd & in);

    friend bool operator==(const Point2Dd & lhs, const Point2Dd & rhs);

    friend bool operator<(const Point2Dd & lhs, const Point2Dd & rhs);

    friend Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs);
};

// prototypes

/*!
 * \brief operator <<
 * \param out
 * \param in
 * \return
 */
inline std::ostream & operator<<(std::ostream & out,
                                 const Point2Dd & in);

/*!
 * \brief operator ==
 *
 * à dx_ et dy_ près
 *
 * \param lhs
 * \param rhs
 * \return
 */
inline bool operator==(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator !=
 *
 * implémenté comme : return !(lhs == rhs);
 *
 * \param lhs
 * \param rhs
 * \return
 *
 * \sa bool operator==(const Point2Dd & lhs, const Point2Dd & rhs)
 */
inline bool operator!=(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator <
 *
 * à dx_ et dy_ près
 *
 * habituellement vrai si lhs en bas à gauche de rhs : dans le
 * système de coordonnées ici : vrai si lhs en haut à gauche de rhs
 *
 * dans tous les cas, vrai si lhs dans le rectangle de
 * coins (-∞, -∞) et rhs
 *
 * \param lhs
 * \param rhs
 * \return
 */
inline bool operator<(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator <=
 *
 * implémenté comme : return !(rhs < lhs);
 *
 * \param lhs
 * \param rhs
 * \return
 *
 * \sa bool operator==(const Point2Dd & lhs, const Point2Dd & rhs)
 */
inline bool operator<=(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator >
 *
 * implémenté comme : return rhs < lhs;
 *
 * \param lhs
 * \param rhs
 * \return
 *
 * \sa bool operator==(const Point2Dd & lhs, const Point2Dd & rhs)
 */
inline bool operator>(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator >=
 *
 * implémenté comme : return !(lhs < rhs);
 *
 * \param lhs
 * \param rhs
 * \return
 *
 * \sa bool operator==(const Point2Dd & lhs, const Point2Dd & rhs)
 */
inline bool operator>=(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief operator +
 *
 * les coordonnées et les incertitudes sont additionnées
 *
 * \param lhs
 * \param rhs
 * \return
 */
inline Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs);

/*!
 * \brief distance
 *
 * dx_ et dy_ ne sont pas utilisés ici
 *
 * \param p1
 * \param p2
 * \return
 */
inline double distance(const Point2Dd & p1, const Point2Dd & p2);

/*!
 * \brief distance
 * \param p1
 * \param p2
 * \param ddistance pour stocker l'incertitude sur la distance
 * \return
 */
inline double distance(const Point2Dd & p1, const Point2Dd & p2,
                       double & ddistance);

// méthodes inline

inline Point2Dd::Point2Dd(double x, double y) : x_ {x}, y_ {y},
       dx_ {std::max(std::numeric_limits<double>::min(),
                     std::abs(x_) * std::numeric_limits<double>::epsilon())
           },
       dy_ {std::max(std::numeric_limits<double>::min(),
                     std::abs(y_) * std::numeric_limits<double>::epsilon())
           }
{}

inline Point2Dd::Point2Dd(double x, double y, double dx, double dy) :
    Point2Dd {x, y}
{
    dx_ = std::max(dx_, std::abs(dx));
    dy_ = std::max(dy_, std::abs(dy));
}

inline double Point2Dd::x() const
{
    return x_;
}

inline double Point2Dd::y() const
{
    return y_;
}

inline double Point2Dd::dx() const
{
    return dx_;
}

inline double Point2Dd::dy() const
{
    return dy_;
}

inline void Point2Dd::setX(double x)
{
    x_ = x;
    dx_ = std::max(std::numeric_limits<double>::min(),
                   std::abs(x_) * std::numeric_limits<double>::epsilon());
}

inline void Point2Dd::setX(double x, double dx)
{
    x_ = x;
    dx_ = std::max({std::numeric_limits<double>::min(),
                    std::abs(x_) * std::numeric_limits<double>::epsilon(),
                    std::abs(dx)
                   });
}

inline void Point2Dd::setY(double y)
{
    y_ = y;
    dy_ = std::max(std::numeric_limits<double>::min(),
                   std::abs(y_) * std::numeric_limits<double>::epsilon());
}

inline void Point2Dd::setY(double y, double dy)
{
    y_ = y;
    dy_ = std::max({std::numeric_limits<double>::min(),
                    std::abs(y_) * std::numeric_limits<double>::epsilon(),
                    std::abs(dy)
                   });
}

inline void Point2Dd::setDx(double dx)
{
    dx_ = std::max({std::numeric_limits<double>::min(),
                    std::abs(x_) * std::numeric_limits<double>::epsilon(),
                    std::abs(dx)
                   });
}

inline void Point2Dd::setDy(double dy)
{
    dy_ = std::max({std::numeric_limits<double>::min(),
                    std::abs(x_) * std::numeric_limits<double>::epsilon(),
                    std::abs(dy)
                   });
}

inline bool Point2Dd::left(const Point2Dd & other, bool strict) const
{
    if (strict)
    {
        return ApproximativeComparison {dx_, other.dx_} .less(x_,
                other.x_);
    }
    else
    {
        return ApproximativeComparison {dx_, other.dx_} .less_equal(
                   x_, other.x_);
    }
}

inline bool Point2Dd::right(const Point2Dd & other, bool strict) const
{
    return other.left(*this, strict);
}

inline bool Point2Dd::above(const Point2Dd & other, bool strict) const
{
    if (strict)
    {
        return ApproximativeComparison {dy_, other.dy_} .less(y_,
                other.y_);
    }
    else
    {
        return ApproximativeComparison {dy_, other.dy_} .less_equal(
                   y_, other.y_);
    }
}

inline bool Point2Dd::below(const Point2Dd & other, bool strict) const
{
    return !above(other, !strict);
}

inline double Point2Dd::distance(const Point2Dd & p) const
{
    return std::hypot(x_ - p.x_, y_ - p.y_);
}

// fonctions inline

inline std::ostream & operator<<(std::ostream & out,
                                 const Point2Dd & in)
{
    return out << "(" << in.x_ << ", " << in.y_ << ")";
}

inline bool operator==(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return ApproximativeComparison {lhs.dx_, rhs.dx_} .equal(
               lhs.x_, rhs.x_) &&
           ApproximativeComparison {lhs.dy_, rhs.dy_} .equal(
               lhs.y_, rhs.y_);
}

inline bool operator!=(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return ApproximativeComparison {lhs.dx_, rhs.dx_} .less(
               lhs.x_, rhs.x_) &&
           ApproximativeComparison {lhs.dy_, rhs.dy_} .less(
               lhs.y_, rhs.y_);
}

inline bool operator<=(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return !(rhs < lhs);
}

inline bool operator>(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return rhs < lhs;
}

inline bool operator>=(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return !(lhs < rhs);
}

inline Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
{
    return {lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.dx_ + rhs.dx_,
            lhs.dy_ + rhs.dy_
           };
}

inline double distance(const Point2Dd & p1, const Point2Dd & p2)
{
    return p1.distance(p2);
}

inline double distance(const Point2Dd & p1, const Point2Dd & p2,
                       double & ddistance)
{
    return p1.distance(p2, ddistance);
}

} // namespace nvs

#endif // POINT2DD_H
