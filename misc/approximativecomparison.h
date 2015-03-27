#ifndef APPROXIMATIVECOMPARISON_H
#define APPROXIMATIVECOMPARISON_H

#include <limits>

namespace nvs
{

/*!
 * \brief The ApproximativeComparison class
 *
 *
 * \sa http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 * \sa https://en.wikipedia.org/wiki/Unit_in_the_last_place
 * \sa http://ljk.imag.fr/membres/Carine.Lucas/TPScilab/JMMuller/ulp-toms.pdf
 */
class ApproximativeComparison
{
    double epsilonlhs_ {std::numeric_limits<double>::epsilon()};
    bool epsilonlhsset_ {false};

    double epsilonrhs_ {std::numeric_limits<double>::epsilon()};
    bool epsilonrhsset_ {false};

    /*!
     * \brief effectiveEpsilon
     *
     * calcule le epsilon effectivement utilisé lors des comparaisons :
     *
     * pour chaque epsilonXXXset_ à false, un epsilonXXX est produit
     * selon :
     *  max(numeric_limits<double>::min(),
     *                   abs(XXX) * numeric_limits<double>::epsilon())
     * sinon epsilonXXX = epsilonXXX_
     *
     * puis epsilon est calculé comme :
     *  epsilon = epsilonlhs + epsilonrhs
     *
     * \param lhs
     * \param rhs
     * \return
     */
    double effectiveEpsilon(double lhs, double rhs) const;

  public:

    ApproximativeComparison() = default;

    /*!
     * \brief ApproximativeComparison
     *
     * met epsilonXXX_ à abs(epsilonXXX) et epsilonXXXset_ à true
     * SAUF
     * si abs(epsilonXXX) < numeric_limits<double>::min(), alors
     * epsilonXXX_ est mis à numeric_limits<double>::epsilon() et
     * epsilonXXXset_ à false
     *
     * \param epsilonlhs
     * \param epsilonrhs
     */
    ApproximativeComparison(double epsilonlhs, double epsilonrhs);

    /*!
     * \brief equal
     *
     * calcule si a == b, étant données les précisions epsilonXXX_
     * c.-à-d. si la distance entre a et b est inférieure ou égale à
     * epsilon, |ab| <= epsilonA_ + epsilonB_ <=>
     *      |a - b| < epsilonA_ + epsilonB_
     *                               (car on est ici à 1 dimension)
     *      |a - b| - (epsilonA_ + epsilonB_) < 0
     *
     * voir effectiveEpsilon pour le calcul epsilonA_ + epsilonB_
     *
     * \param a
     * \param b
     * \return
     *
     * \sa effectiveEpsilon
     */
    bool equal(double a, double b);

    /*!
     * \brief less
     *
     * calcule si a < b, étant données les précisions epsilonXXX_
     * c.-à-d. si a < b et si la distance entre a et b est supérieure
     * à (epsilonA_ + epsilonB_), c.-à-d. :
     *      a < b && |ab| > (epsilonA_ + epsilonB_)
     *      a + epsilonA_ < b - epsilonB_
     *      a - b + epsilonA_ + epsilonB_ < 0
     *      a - b + (epsilonA_ + epsilonB_) < 0
     *
     * voir effectiveEpsilon pour le calcul epsilonA_ + epsilonB_
     *
     * \param a
     * \param b
     * \return
     *
     * \sa effectiveEpsilon
     */
    bool less(double a, double b);

    /*!
     * \brief less_equal
     *
     * calcule si a <= b, étant données les précisions epsilonXXX_
     * c.-à-d. si a < b ou si la distance entre a et b est inférieure
     * ou égale à (epsilonA_ + epsilonB_), c.-à-d. :
     *      a < b || |ab| <= (epsilonA_ + epsilonB_) <=>
     *      a - epsilonA_ <= b + epsilonB_
     *      a - b - epsilonA_ - epsilonB_ <= 0
     *      a - b - (epsilonA_ + epsilonB_) <= 0
     *
     * voir effectiveEpsilon pour le calcul epsilonA_ + epsilonB_
     *
     * \param a
     * \param b
     * \return
     *
     * \sa effectiveEpsilon
     */
    bool less_equal(double a, double b);
};

} // namespace nvs

#endif // APPROXIMATIVECOMPARISON_H

