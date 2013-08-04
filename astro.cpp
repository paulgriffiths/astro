/*
 *  astro.cpp
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of astronomical classes.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include "astro.h"
#include "astrofunc.h"

using namespace astro;

namespace {

//  Orbital elements for each planet at J2000

const OrbElem ELEMENTS_J2000[] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0.387009927, 0.20563593, 7.00497902,
     252.25032350, 77.45779628, 48.33076593, 0, 0},
    {0.72333566, 0.00677672, 3.39467605,
     181.97909950, 131.60246718, 76.67984255, 0, 0},
    {1.00000261, 0.01671123, -0.00001531,
     100.46457166, 102.93768193, 0.0, 0, 0},
    {1.52371034, 0.09339410, 1.84969142,
     -4.55343205, -23.94362959, 49.55953891, 0, 0},
    {5.20288700, 0.04838624, 1.30439695,
     34.39644051, 14.72847983, 100.47390909, 0, 0},
    {9.53667594, 0.05386179, 2.48599187,
     49.95424423, 92.59887831, 113.66242448, 0, 0},
    {19.18916464, 0.04725744, 0.77263783,
     313.23810451, 170.95427630, 74.01692503, 0, 0},
    {30.06992276, 0.00859048, 1.77004347,
     -55.12002969, 44.96476227, 131.78422574, 0, 0},
    {39.48211675, 0.24882730, 17.14001206,
     238.92903833, 224.06891629, 110.30393684, 0, 0}
};

//  Change in orbital elements for each planet, per century

const OrbElem ELEMENTS_CENT[] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0.00000037, 0.00001906, -0.00594749,
     149472.67411175, 0.16047689, -0.12534081, 0, 0},
    {0.00000390, -0.00004107, -0.00078890,
     58517.81538729, 0.00268329, -0.27769418, 0, 0},
    {0.00000562, -0.00004392, -0.01294668,
     35999.37244981, 0.32327364, 0.0, 0, 0},
    {0.00001847, 0.00007882, -0.00813131,
     19140.30268499, 0.44441088, -0.29257343, 0, 0},
    {-0.00011607, -0.00013253, -0.00183714,
     3034.74612775, 0.21252668, 0.20469106, 0, 0},
    {-0.00125060, -0.00050991, 0.00193609,
     1222.49362201, -0.41897216, -0.28867794, 0, 0},
    {-0.00196176, -0.00004397, -0.00242939,
     428.48202785, 0.40805281, 0.04240589, 0, 0},
    {0.00026291, 0.00005105, 0.00035372,
     218.45945325, -0.32241464, -0.00508664, 0, 0},
    {-0.00031596, 0.00005170, 0.00004818,
    145.20780515, -0.04062942, -0.01183482, 0, 0}
};

}           //  namespace


/*
 *  Returns orbital elements for the specified time.
 */

OrbElem Planet::calc_orbital_elements(tm * calc_time) const {
    double jdc = (julian_date(calc_time) - EPOCH_J2000) / 36525;

    OrbElem oes;
    oes.sma = ELEMENTS_J2000[m_number].sma + ELEMENTS_CENT[m_number].sma * jdc;
    oes.ecc = ELEMENTS_J2000[m_number].ecc + ELEMENTS_CENT[m_number].ecc * jdc;
    oes.inc = ELEMENTS_J2000[m_number].inc + ELEMENTS_CENT[m_number].inc * jdc;
    oes.ml = ELEMENTS_J2000[m_number].ml + ELEMENTS_CENT[m_number].ml * jdc;
    oes.lp = ELEMENTS_J2000[m_number].lp + ELEMENTS_CENT[m_number].lp * jdc;
    oes.lan = ELEMENTS_J2000[m_number].lan + ELEMENTS_CENT[m_number].lan * jdc;
    oes.man = oes.ml - oes.lp;
    oes.arp = oes.lp - oes.lan;

    return oes;
}


/*
 *  Returns the planet's name.
 */

std::string Mars::name() const {
    return "Mars";
}
