//
// $Id$
//
/*!

  \file
  \ingroup buildblock
  \brief Declaration of class ArrayFunctionObject_1ArgumentImplementation

  \author Kris Thielemans
  
  \date $Date$
  \version $Revision$
*/

#ifndef __Tomo_ArrayFunctionObject_1ArgumentImplementation_H__
#define __Tomo_ArrayFunctionObject_1ArgumentImplementation_H__


#include "tomo/ArrayFunctionObject.h"


START_NAMESPACE_TOMO

/*!
  \ingroup buildblock
  \brief A convenience class for children of ArrayFunctionObject. It
  implements the 2 argument operator() in terms of the in-place version.

  Sadly, we need to introduce another virtual function for this, as 
  redefining an overloaded function in a derived class, hides all other
  overladed versions. So, we cannot simply leave the 1 arg operator() 
  undefined here. Similarly, we could not only define the 1 arg operator()
  in a derived class.

  \see ArrayFunctionObject_2ArgumentImplementation
*/
template <int num_dimensions, typename elemT>
class ArrayFunctionObject_1ArgumentImplementation :
  public ArrayFunctionObject<num_dimensions,elemT>
{
public:
  virtual void operator() (Array<num_dimensions,elemT>& array) const
  {
    do_it(array);
  }

  //! result stored in another array, implemented inline
  virtual void inline operator() (Array<num_dimensions,elemT>& out_array, 
                           const Array<num_dimensions,elemT>& in_array) const
  {
   out_array = in_array;
   do_it(out_array);
  }
protected:
  virtual void do_it(Array<num_dimensions,elemT>& array) const = 0;
};



END_NAMESPACE_TOMO 

#endif 
