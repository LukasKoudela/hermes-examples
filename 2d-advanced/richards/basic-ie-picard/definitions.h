#include "hermes2d.h"

#include "../constitutive.h"

using namespace Hermes;
using namespace Hermes::Hermes2D;
using namespace Hermes::Hermes2D::WeakFormsH1;
using namespace Hermes::Hermes2D::Views;

/* Custom non-constant Dirichlet condition */

class CustomEssentialBCNonConst : public EssentialBoundaryCondition<double>
{
public:
  CustomEssentialBCNonConst(Hermes::vector<std::string>(markers))       
        : EssentialBoundaryCondition<double>(markers) 
  {
  }

  virtual EssentialBCValueType get_value_type() const;

  virtual double value(double x, double y, double n_x, double n_y, 
                       double t_x, double t_y) const;
};

/* Weak forms */

class CustomWeakFormRichardsIEPicard : public WeakForm<double>
{
public:
  CustomWeakFormRichardsIEPicard(double time_step, Solution<double>* h_time_prev, Solution<double>* h_iter_prev, ConstitutiveRelations* constitutive);

private:

  class CustomJacobian : public MatrixFormVol<double>
  {
  public:
    CustomJacobian(int i, int j, double time_step) 
          : MatrixFormVol<double>(i, j), time_step(time_step) {};

    virtual double value(int n, double *wt, Func<double> *u_ext[], Func<double> *u, 
                         Func<double> *v, Geom<double> *e, ExtData<double> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u, 
                    Func<Ord> *v, Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormVol<double>* clone();

    double time_step;
  };

  class CustomResidual : public VectorFormVol<double>
  {
  public:
    CustomResidual(int i, double time_step)
          : VectorFormVol<double>(i), time_step(time_step) 
    {
    }

    virtual double value(int n, double *wt, Func<double> *u_ext[], Func<double> *v, Geom<double> *e,
                         ExtData<double> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v, Geom<Ord> *e, 
                    ExtData<Ord> *ext) const;

    virtual VectorFormVol<double>* clone();

    double time_step;
  };

  ConstitutiveRelations* constitutive;
};