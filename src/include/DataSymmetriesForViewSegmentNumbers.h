//
// $Id$: $Date$
//
/*!

  \file
  \ingroup buildblock

  \brief Declaration of class DataSymmetriesForViewSegmentNumbers

  \author Kris Thielemans
  \author PARAPET project

  \date $Date$

  \version $Revision$
*/
#ifndef __DataSymmetriesForViewSegmentNumbers_H__
#define __DataSymmetriesForViewSegmentNumbers_H__

#include "SymmetryOperation.h"
#include "ViewSegmentNumbers.h"
#include <vector>
#include <memory>
#include "shared_ptr.h"
#include "ProjDataInfo.h"

#ifndef TOMO_NO_NAMESPACES
using std::vector;
#ifndef TOMO_NO_AUTO_PTR
using std::auto_ptr;
#endif
#endif

START_NAMESPACE_TOMO

#if 0
class ViewSegmentIndexRange;
#endif


/*!
  \brief A class for encoding/find symmetries. Works only on
  ViewSegmentNumbers (instead of Bin).

  TODOdoc

*/
class DataSymmetriesForViewSegmentNumbers
{
public:
  inline DataSymmetriesForViewSegmentNumbers(const shared_ptr<ProjDataInfo>& proj_data_info_ptr/*,
                        const shared_ptr<DiscretisedDensity>& image_info*/);

  virtual ~DataSymmetriesForViewSegmentNumbers() {};

  virtual DataSymmetriesForViewSegmentNumbers * clone() const = 0;

#if 0    
  //??? maybe not needed
  virtual vector<SymmetryOperation * const>
    get_all_symmetry_operations() const = 0;
#endif

#if 0
  // TODO
  //! returns the range of the indices for basic view/segments
  virtual ViewSegmentIndexRange
    get_basic_view_segment_index_range() const = 0;
#endif

  //! fills in a vector with all the view/segments that are related to 'v_s' (including itself)
  virtual void
    get_related_view_segment_numbers(vector<ViewSegmentNumbers>&, const ViewSegmentNumbers&) const = 0;

  //! returns the number of bins related to 'b'
  virtual inline int
    num_related_view_segment_numbers(const ViewSegmentNumbers&) const;

  /*! \brief given an arbitrary view/segment, find the basic view/segment
  
  sets 'v_s' to the corresponding 'basic' view/segment and returns the symmetry 
  transformation from 'basic' to 'v_s'.

  Note that the symmetry operation is not completely defined by giving only view/segment.
  The symmetry operation returned is the one where 'ring' and 'bin' are not changed.
  */
  virtual auto_ptr<SymmetryOperation>
    find_symmetry_operation_to_basic_view_segment_numbers(ViewSegmentNumbers&) const = 0;

  /*! \brief given an arbitrary view/segment, find the basic view/segment
  
  sets 'v_s' to the corresponding 'basic' view/segment and returns true if
  'v_s' is changed (i.e. it was NOT a basic view/segment).
  */  
  virtual inline bool
    find_basic_view_segment_numbers(ViewSegmentNumbers& v_s) const;

protected:
  const shared_ptr<ProjDataInfo> proj_data_info_ptr;
  //shared_ptr<DiscretisedDensity> image_info;
};

END_NAMESPACE_TOMO

#include "DataSymmetriesForViewSegmentNumbers.inl"

#endif

