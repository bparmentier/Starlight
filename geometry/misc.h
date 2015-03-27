#ifndef MISC_H
#define MISC_H

namespace nvs {

/*!
 * \brief normalize_q12
 *
 * retourne l'angle équivalent à alpha dans le 1er ou le 2e quadrant
 * c.-à-d. retourne α' = α avec α' \in [0, π[
 *
 * \param alpha
 * \return α' = α avec α' \in [0, π[
 */
double normalize_q12(double alpha);

/*!
 * \brief normalize_q1234
 *
 * retourne l'angle équivalent à alpha dans le 1er, 2e, 3e ou 4e
 * quadrant modulo 2π retourne α' = α avec α' \in [0, 2π[
 *
 * \param alpha
 * \return α' = α avec α' \in [0, 2π[
 */
double normalize_q1234(double alpha);

} // namespace nvs

#endif // MISC_H

