#include "hermes2d.h"

using namespace Hermes::Hermes2D::WeakFormsNeutronics::Multigroup::MaterialProperties;
using namespace Hermes::Hermes2D::WeakFormsNeutronics::Multigroup::MaterialProperties::Diffusion;
using namespace Hermes::Hermes2D::WeakFormsNeutronics::Multigroup::MaterialProperties::Definitions;

// Reference k_effective reactor eigenvalue for the material properties below
// and geometry from the file 'reactor.mesh'. For this example, it was obtained
// simplistically by a reference calculation on a 3x uniformly refined mesh
// with uniform distribution of polynomial degrees (=4), with convergence
// tolerance set to 5e-11.
const double REF_K_EFF = 1.1409144;

//////  Geometric parameters.  /////////////////////////////////////////////////////////////////

// File with initial mesh specification.
const std::string mesh_file = "reactor.mesh";

// Element markers.
const std::string reflector = "reflector";
const std::string core = "core";

// Boundary markers.
const std::string bdy_vacuum = "vacuum boundary";
const std::string bdy_symmetry = "symmetry plane";

//////  Physical parameters.  /////////////////////////////////////////////////////////////////

// Number of energy discretization intervals ('groups').
const unsigned int N_GROUPS = 4;

const MaterialPropertyMap1 D = material_property_map<rank1>
(
  reflector, row(0.0164)(0.0085)(0.00832)(0.00821)
)(
  core, row(0.0235)(0.0121)(0.0119)(0.0116)
);

const MaterialPropertyMap1 Sa = material_property_map<rank1>
(
  reflector, row(0.00139)(0.000218)(0.00197)(0.0106)
)(
  core, row(0.00977)(0.162)(0.156)(0.535)
);

const MaterialPropertyMap1 Sr = material_property_map<rank1>
(
  reflector, row(1.77139)(0.533218)(3.31197)(0.0106)
)(
  core, row(1.23977)(0.529)(2.436)(0.535)
);

const MaterialPropertyMap1 Sf = material_property_map<rank1>
(
  reflector, row(0.0)(0.0)(0.0)(0.0)
)(
  core, row(0.00395)(0.0262)(0.0718)(0.346)
);

const MaterialPropertyMap1 nu = material_property_map<rank1>
(
  reflector, row(0.0)(0.0)(0.0)(0.0) 
)(
  core, row(2.49)(2.43)(2.42)(2.42)
);

const MaterialPropertyMap1 chi = material_property_map<rank1>
(
  reflector, row(0.0)(0.0)(0.0)(0.0)
)(
  core, row(0.9675)(0.03250)(0.0)(0.0)
);

const MaterialPropertyMap2 Ss = material_property_map<rank2>
(
  reflector,
  mat
  (
    row(0.0)(0.0)(0.0)(0.0)
  )(
    row(1.77)(0.0)(0.0)(0.0)
  )(
    row(0.0)(0.533)(0.0)(0.0)
  )(
    row(0.0)(0.0)(3.31)(0.0)
  )
)(
  core,
  mat
  (
    row(0.0)(0.0)(0.0)(0.0)
  )(
    row(1.23)(0.0)(0.0)(0.0)
  )(
    row(0.0)(0.367)(0.0)(0.0)
  )(
    row(0.0)(0.0)(2.28)(0.0)
  )
);