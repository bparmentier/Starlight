#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point2dd.h"

#include <ostream>
#include <vector>

namespace nvs
{

class Segment;
class Line;

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
 *
 *  la largeur : selon axe x
 *  la hauteur : selon axe y
 *
 * ATTENTION ! les côtés du rectangle sont toujours parallèles
 *             aux axes !
 *
 */
class Rectangle
{
    Point2Dd  topLeft_ {0., 0.};
    Point2Dd  bottomRight_ {1., 1.};

  public:
    /*!
     * \brief Rectangle
     */
    Rectangle() = default;

    Rectangle(const Rectangle &) = default;

    /*!
     * \brief Rectangle
     *
     * \param topLeft
     * \param bottomRight
     *
     * \throw std::invalid_argument si !(topLeft < bottomRight)
     */
    Rectangle(const Point2Dd & topLeft, const Point2Dd & bottomRight);

    /*!
     * \brief Rectangle
     *
     * bottomRight_ est construit comme :
     *      topLeft + Point2Dd{width, height}
     *
     * et le constructeur Rectangle(const Point2Dd & topLeft, const Point2Dd & bottomRight)
     * est invoqué comme :
     *  Rectangle{topLeft, topLeft + Point2Dd{width, height}}
     *
     * donc bottomRight_.dx_ est mis à :
     * topLeft_.dx() + max(std::numeric_limits<double>::min(),
     *                     abs(width) * std::numeric_limits<double>::epsilon())
     *
     * bottomRight_.dy_ est mis à :
     * topLeft_.dy() + max(std::numeric_limits<double>::min(),
     *                     abs(height) * std::numeric_limits<double>::epsilon())
     *
     * \param topLeft
     * \param width
     * \param height
     *
     * \throw std::invalid_argument si !(topLeft_ < bottomRight_)
     *
     * \sa Rectangle(const Point2Dd & topLeft, const Point2Dd & bottomRight)
     * \sa Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
     */
    Rectangle(const Point2Dd & topLeft, double width, double height);

    /*!
     * \brief Rectangle
     *
     * bottomRight_ est construit comme :
     *      topLeft + Point2Dd{width, height, dwidth, dheight}
     *
     * et le constructeur Rectangle(const Point2Dd & topLeft, const Point2Dd & bottomRight)
     * est invoqué comme :
     *  Rectangle{topLeft, topLeft + Point2Dd{width, height, dwidth, dheight}}
     *
     * les imprécisions sur topLeft_ et bottomRight_ en résultent
     *
     * \param topLeft
     * \param width
     * \param height
     * \param dwidth
     * \param dheight
     *
     * \throw std::invalid_argument si !(topLeft_ < bottomRight_)
     *
     * \sa Rectangle(const Point2Dd & topLeft, const Point2Dd & bottomRight)
     * \sa Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
     */
    Rectangle(const Point2Dd & topLeft, double width, double height,
              double dwidth, double dheight);

    /*!
     * \brief Rectangle
     *
     * invoque Rectangle(const Point2Dd & topLeft, double width, double height)
     * comme Rectangle(Point2Dd{x, y}, double width, double height)
     *
     * les valeurs des dx_ et dy_ et de dwidth_ et dheight_ en résultent
     *
     * \param x
     * \param y
     * \param width
     * \param height
     *
     * \throw std::invalid_argument si !(topLeft_ < bottomRight_)
     *
     * \sa Rectangle(const Point2Dd & topLeft, double width, double height)
     * \sa Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
     */
    Rectangle(double x, double y, double width, double height);

    /*!
     * \brief Rectangle
     *
     * invoque Rectangle(const Point2Dd & topLeft, double width, double height)
     * comme : Rectangle(Point2Dd{x, y, dx, dy}, width, height)
     *
     * les imprécisions sur topLeft_ et bottomRight_ en résultent
     *
     * \param x
     * \param y
     * \param width
     * \param height
     * \param dx
     * \param dy
     *
     * \throw std::invalid_argument si !(topLeft < bottomRight)
     *
     * \sa Rectangle(const Point2Dd & topLeft, double width, double height)
     * \sa Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
     */
    Rectangle(double x, double y, double width, double height, double dx,
              double dy);

    /*!
     * \brief Rectangle
     *
     * invoque Rectangle(const Point2Dd & topLeft, double width, double height,
     *                   double dwidth, double dheight)
     * comme :
     *  Rectangle {Point2Dd{x, y, dx, dy}, width, height, dwidth, dheigth}
     *
     * les imprécisions sur topLeft_ et bottomRight_ en résultent
     *
     * \param x
     * \param y
     * \param width
     * \param height
     * \param dx
     * \param dy
     * \param dwidth
     * \param dheigth
     *
     * \throw std::invalid_argument si !(topLeft < bottomRight)
     *
     * \sa Rectangle(const Point2Dd & topLeft, double width, double height, double dwidth, double dheight)
     * \sa Point2Dd operator+(const Point2Dd & lhs, const Point2Dd & rhs)
     */
    Rectangle(double x, double y, double width, double height, double dx,
              double dy, double dwidth, double dheigth);

    // accesseurs en lecture

    inline const Point2Dd & topLeft() const;
    inline const Point2Dd & bottomRight() const;

    inline double x() const;
    inline double y() const;
    inline double width() const;
    inline double height() const;

    inline double dx() const;
    inline double dy() const;
    inline double dwidth() const;
    inline double dheight() const;

    inline Point2Dd topRight() const;
    inline Point2Dd bottomLeft() const;

    Point2Dd center() const;

    bool contains(const Point2Dd & point) const;

    Segment top() const;
    Segment bottom() const;
    Segment left() const;
    Segment right() const;

    bool hasOnSide(const Point2Dd & point) const;

    bool hasOnTopSide(const Point2Dd & point) const;
    bool hasOnBottomSide(const Point2Dd & point) const;
    bool hasOnLeftSide(const Point2Dd & point) const;
    bool hasOnRightSide(const Point2Dd & point) const;

    /*!
     * \brief intersection intersection d'un rectangle et d'une ligne
     *
     * \param line la droite dont on calcule l'intersection avec
     *                le rectangle *this
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
     */
    bool intersection(const Line & line, std::vector<Point2Dd> & points,
                      Segment & result) const;

    /*!
     * \brief intersection intersection d'un rectangle et d'un segment
     *
     * result peut être modifié même si l'intersection n'est pas un
     * segment
     *
     * \param segment le segment dont on calcule l'intersection avec
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
     */
    bool intersection(const Segment & segment,
                      std::vector<Point2Dd> & points,
                      Segment & result) const;

    // amis
    friend std::ostream & operator<<(std::ostream & out,
                                     const Rectangle & in);
};

// prototypes

inline std::ostream & operator<<(std::ostream & out,
                                 const Rectangle & in);

/*!
 * \brief intersection
 *
 * \param rectangle
 * \param line
 * \param points
 * \param result
 * \return
 *
 * \sa bool Rectangle::intersection(const Line & line, std::vector<Point2Dd> & points, Segment & result) const
 */
bool intersection(const Rectangle & rectangle, const Line & line,
                  std::vector<Point2Dd> & points, Segment & result);

/*!
 * \brief intersection
 * \param line
 * \param rectangle
 * \param points
 * \param result
 * \return
 *
 * \sa bool Rectangle::intersection(const Line & line, std::vector<Point2Dd> & points, Segment & result) const
 */
bool intersection(const Line & line, const Rectangle & rectangle,
                  std::vector<Point2Dd> & points, Segment & result);

/*!
 * \brief intersection
 * \param rectangle
 * \param segment
 * \param points
 * \param result
 * \return
 *
 * \sa bool Rectangle::intersection(const Segment & segment, std::vector<Point2Dd> & points, Segment & result) const
 */
bool intersection(const Rectangle & rectangle,
                  const Segment & segment,
                  std::vector<Point2Dd> & points, Segment & result);

/*!
 * \brief intersection
 * \param segment
 * \param rectangle
 * \param points
 * \param result
 * \return
 *
 * \sa bool Rectangle::intersection(const Segment & segment, std::vector<Point2Dd> & points, Segment & result) const
 */
bool intersection(const Segment & segment,
                  const Rectangle & rectangle,
                  std::vector<Point2Dd> & points, Segment & result);

// méthodes inline

inline const Point2Dd & Rectangle::topLeft() const
{
    return topLeft_;
}

inline const Point2Dd & Rectangle::bottomRight() const
{
    return bottomRight_;
}

inline double Rectangle::x() const
{
    return topLeft_.x();
}

inline double Rectangle::y() const
{
    return topLeft_.y();
}

inline double Rectangle::dx() const
{
    return topLeft_.dx();
}

inline double Rectangle::dy() const
{
    return topLeft_.dy();
}

inline double Rectangle::width() const
{
    return bottomRight_.x() - topLeft_.x();
}

inline double Rectangle::height() const
{
    return bottomRight_.y() - topLeft_.y();
}

inline double Rectangle::dwidth() const
{
    return bottomRight_.dx() + topLeft_.dx();
}

inline double Rectangle::dheight() const
{
    return bottomRight_.dy() + topLeft_.dy();
}

inline Point2Dd Rectangle::topRight() const
{
    // pour ce qui concerne les incertitudes, on privilégie ici la
    // verticalité et l'horizontalité des côtés du rectangle.
    // d'autres choix sont possibles... et meilleurs (?)

    return {bottomRight_.x(), topLeft_.y(),
            bottomRight_.dx(), topLeft_.dy()
           };
}

inline Point2Dd Rectangle::bottomLeft() const
{
    // pour ce qui concerne les incertitudes, on privilégie ici la
    // verticalité et l'horizontalité des côtés du rectangle.
    // d'autres choix sont possibles... et meilleurs (?)

    return {topLeft_.x(), bottomRight_.y(),
            topLeft_.dx(), bottomRight_.dy()
           };
}

// fonctions inline

inline std::ostream & operator<<(std::ostream & out,
                                 const Rectangle & in)
{
    return out << "[" << in.topLeft_ << " -> " << in.bottomRight_
           << "], w : "  << in.width() << ", h : " << in.height();
}

}

#endif // RECTANGLE_H

