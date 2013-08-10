/*
 *  major_body.h
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to abstract MajorBody base class for regular
 *  Solar System planets.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_MAJOR_BODY_H
#define PG_ASTRO_MAJOR_BODY_H

#include "astro_common_types.h"
#include "planet.h"
#include "utc_time.h"

namespace astro {

class MajorBody : public Planet {
    public:
        explicit MajorBody(const utctime::UTCTime& ct,
                           const OrbElem& j2000_oes,
                           const OrbElem& century_oes) :
            Planet(ct, calc_orbital_elements(ct, j2000_oes, century_oes)) {}
        virtual ~MajorBody() = 0;

        virtual RectCoords geo_ecl_coords() const;

    private:
        OrbElem calc_orbital_elements(const utctime::UTCTime& ct,
                                      const OrbElem& j2000_oes,
                                      const OrbElem& century_oes) const;
};

}           //  namespace astro

#endif          // PG_ASTRO_MAJOR_BODY_H
