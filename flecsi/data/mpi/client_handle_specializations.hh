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

#define POLICY_NAMESPACE mpi
#include <flecsi/data/common/client_handle_specialization.hh>
#undef POLICY_NAMESPACE

#include <flecsi/data/common/client_handle.hh>

namespace flecsi {
namespace data {
namespace mpi {

/*----------------------------------------------------------------------------*
  Global Topology.
 *----------------------------------------------------------------------------*/

template<>
struct client_handle_specialization_u<topology::global_topology_t> {

  using client_t = topology::global_topology_t;

  template<size_t NAMESPACE, size_t NAME>
  static client_handle_u<client_t, 0> get_client_handle() {
    client_handle_u<client_t, 0> h;
    return h;
  } // get_client_handle

}; // client_handle_specialization_u<topology::global_topology_t>

/*----------------------------------------------------------------------------*
  Color Topology.
 *----------------------------------------------------------------------------*/

template<>
struct client_handle_specialization_u<topology::index_topology_t> {

  using client_t = topology::index_topology_t;

  template<size_t NAMESPACE, size_t NAME>
  static client_handle_u<client_t, 0> get_client_handle() {
    client_handle_u<client_t, 0> h;
    return h;
  } // get_client_handle

}; // client_handle_specialization_u<topology::index_topology_t>

/*----------------------------------------------------------------------------*
  Mesh Topology.
 *----------------------------------------------------------------------------*/

#if 0
template<typename MESH_POLICY>
struct client_handle_specialization_u<topology::mesh_topology_t<MESH_POLICY>> {

  using client_t = topology::mesh_topology_t<MESH_POLICY>;

  template<size_t NAMESPACE, size_t NAME>
  static client_handle_u<client_t, 0> get_client_handle() {
    client_handle_u<client_t, 0> h;
    return h;
  } // get_client_handle

}; // client_handle_specialization_u<topology::mesh_topology_t<MESH_POLICY>>
#endif

} // namespace mpi
} // namespace data
} // namespace flecsi
