#ifndef OSMSCOUT_AREAWAYINDEX_H
#define OSMSCOUT_AREAWAYINDEX_H

/*
  This source is part of the libosmscout library
  Copyright (C) 2011  Tim Teulings

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <memory>
#include <mutex>
#include <unordered_set>
#include <vector>

#include <osmscout/TypeConfig.h>
#include <osmscout/TypeInfoSet.h>

#include <osmscout/util/FileScanner.h>

namespace osmscout {

  /**
    \ingroup Database
    AreaWayIndex allows you to find ways and way relations in
    a given area.

    Ways can be limited by type and result count.
    */
  class OSMSCOUT_API AreaWayIndex
  {
  public:
    static const char* AREA_WAY_IDX;

  private:
    struct TypeData
    {
      TypeInfoRef type;
      uint32_t    indexLevel;

      uint8_t     dataOffsetBytes;
      FileOffset  bitmapOffset;

      uint32_t    cellXStart;
      uint32_t    cellXEnd;
      uint32_t    cellYStart;
      uint32_t    cellYEnd;
      uint32_t    cellXCount;
      uint32_t    cellYCount;

      double      cellWidth;
      double      cellHeight;

      double      minLon;
      double      maxLon;
      double      minLat;
      double      maxLat;

      TypeData();

      FileOffset GetDataOffset() const;
      FileOffset GetCellOffset(size_t x, size_t y) const;
    };

  private:
    std::string           datafilename;   //!< Full path and name of the data file
    mutable FileScanner   scanner;        //!< Scanner instance for reading this file

    std::vector<TypeData> wayTypeData;

    mutable std::mutex    lookupMutex;

  private:
    bool GetOffsets(const TypeData& typeData,
                    const GeoBox& boundingBox,
                    std::unordered_set<FileOffset>& offsets) const;

  public:
    AreaWayIndex();
    virtual ~AreaWayIndex();

    void Close();
    bool Open(const TypeConfigRef& typeConfig,
              const std::string& path,
              bool memoryMappedData);

    inline bool IsOpen() const
    {
      return scanner.IsOpen();
    }

    inline std::string GetFilename() const
    {
      return datafilename;
    }

    bool GetOffsets(const GeoBox& boundingBox,
                    const TypeInfoSet& types,
                    std::vector<FileOffset>& offsets,
                    TypeInfoSet& loadedTypes) const;
  };

  typedef std::shared_ptr<AreaWayIndex> AreaWayIndexRef;
}

#endif
