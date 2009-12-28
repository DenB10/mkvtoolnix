/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   IO callback class definitions

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __MTX_COMMON_MM_MULTI_FILE_IO_H
#define __MTX_COMMON_MM_MULTI_FILE_IO_H

#include "common/os.h"

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

#include "common/mm_io.h"

namespace bfs = boost::filesystem;

class mm_multi_file_io_c;
typedef counted_ptr<mm_multi_file_io_c> mm_multi_file_io_cptr;

class MTX_DLL_API mm_multi_file_io_c: public mm_io_c {
  struct file_t {
    bfs::path m_file_name;
    uint64_t m_size, m_global_start;
    mm_file_io_cptr m_file;

    file_t(const bfs::path &file_name, uint64_t global_start, mm_file_io_cptr file);
  };

protected:
  bfs::path m_file_name;
  uint64_t m_total_size, m_current_pos, m_current_local_pos;
  unsigned int m_current_file;
  std::vector<mm_multi_file_io_c::file_t> m_files;

public:
  mm_multi_file_io_c(std::vector<bfs::path> file_names);
  virtual ~mm_multi_file_io_c();

  virtual uint64 getFilePointer();
  virtual void setFilePointer(int64 offset, seek_mode mode = seek_beginning);
  virtual uint32 read(void *buffer, size_t size);
  virtual size_t write(const void *buffer, size_t size);
  virtual void close();
  virtual bool eof();

  virtual std::string get_file_name() const {
    return m_file_name.string();
  }
  virtual std::vector<bfs::path> get_file_names();
  void create_verbose_identification_info(const bfs::path &exclude_file_name, std::vector<std::string> &verbose_info);

  static mm_multi_file_io_cptr open_multi(bfs::path first_file_name);
};

#endif  // __MTX_COMMON_MM_MULTI_FILE_IO_H