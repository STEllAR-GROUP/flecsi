/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Triad National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*! @file */

#if !defined(__FLECSI_PRIVATE__)
#error Do not include this file directly!
#endif

#include "flecsi/runtime/backend.hh"
#include "flecsi/utils/demangle.hh"
#include <flecsi/utils/flog.hh>
#include <flecsi/utils/mpi_type_traits.hh>

#include <type_traits>

flog_register_tag(reduction_wrapper);

namespace flecsi {
namespace execution {

namespace detail {
template<class>
void register_reduction();
}

// NB: The real initialization is in the callback.
template<class R>
inline MPI_Op
  reduction_op = (runtime::context::instance().register_reduction_operation(
                    detail::register_reduction<R>),
    MPI_Op());

/*!
  Register the user-defined reduction operator with the runtime.
 */

template<typename TYPE>
void
detail::register_reduction() {
  using value_type = typename TYPE::LHS;
  // MPI does not have support for mixed-type reductions
  static_assert(std::is_same_v<value_type, typename TYPE::RHS>,
    "type mismatch: LHS != RHS");

  {
    flog_tag_guard(reduction_wrapper);
    flog(info) << "Executing reduction wrapper callback for "
               << utils::type<TYPE>() << std::endl;
  } // scope

  // Create the operator and register it with the runtime
  MPI_Op_create(
    [](void * in, void * inout, int * len, MPI_Datatype *) {
      const auto lhs = static_cast<value_type *>(inout);
      const auto rhs = static_cast<const value_type *>(in);

      for(size_t i{0}; i < *len; ++i) {
        TYPE::template apply<true>(lhs[i], rhs[i]);
      } // for
    },
    true,
    &reduction_op<TYPE>);
}

} // namespace execution
} // namespace flecsi
