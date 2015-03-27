#ifndef WAVELENGTH_H
#define WAVELENGTH_H

namespace nvs {

enum Wavelength
{
    NO_WL = -1,
    DFT_WL = 600,
    MIN_WL = 360,
    MAX_WL = 830
};

/*!
 * \brief setVisibleLight
 *
 * retourne wl tel quel si MIN_WL <= wl <= MAX_WL
 * sinon retourne DFT_WL
 *
 * \param wl
 * \return
 */
int setVisibleLight(int wl);

} // namespace nvs

#endif // WAVELENGTH_H

