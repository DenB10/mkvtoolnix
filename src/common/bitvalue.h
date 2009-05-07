/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   The "bitvalue_c" class definition

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __MTX_COMMON_MTX_BITVALUE_H
#define __MTX_COMMON_MTX_BITVALUE_H

#include "common/os.h"

#include "common/common.h"

#include <ebml/EbmlBinary.h>

class MTX_DLL_API bitvalue_c {
private:
  unsigned char *m_value;
  int m_bitsize;
public:
  bitvalue_c(int size);
  bitvalue_c(const bitvalue_c &src);
  bitvalue_c(std::string s, int allowed_bitlength = -1);
  bitvalue_c(const EbmlBinary &elt);
  virtual ~bitvalue_c();

  bitvalue_c &operator =(const bitvalue_c &src);
  bool operator ==(const bitvalue_c &cmp) const;
  unsigned char operator [](int index) const;

  inline bool empty() const {
    return 0 == m_bitsize;
  }
  inline int size() const {
    return m_bitsize;
  }
  void generate_random();
  unsigned char *data() const {
    return m_value;
  }
};
typedef counted_ptr<bitvalue_c> bitvalue_cptr;

#endif  // __MTX_COMMON_MTX_BITVALUE_H