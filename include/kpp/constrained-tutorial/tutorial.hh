// Copyright (C) 2011 by Sebastien Dalibard.
//
// This file is part of the kpp-constrained-tutorial.
//
// kpp-constrained-tutorial is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// kpp-constrained-tutorial is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with kpp-constrained-tutorial.  If not, see <http://www.gnu.org/licenses/>.


#ifndef KPP_CONSTRAINED_TUTORIAL_KPP_CONSTRAINED_TUTORIAL_HH_
#define KPP_CONSTRAINED_TUTORIAL_KPP_CONSTRAINED_TUTORIAL_HH_

#include <string>

#include <KineoUtility/kitDefine.h>

#include <kppInterface/kppInterface.h>

#include <hpp/constrained/planner/fwd.hh>
#include <hpp/corbaserver/constrained/fwd.hh>

namespace kpp {
  namespace constrained {
    KIT_PREDEF_CLASS(Tutorial);
    class Tutorial : public CkppInterface
    {
    public:
      
      typedef hpp::constrained::GraspingPlanner Planner;
      typedef hpp::constrained::Server Server;

      static TutorialShPtr create();

      virtual ~Tutorial();

      virtual std::string name() const;
      
    protected:

      Tutorial(Planner * i_hppPlanner);

      ktStatus init(const TutorialWkPtr & i_wkPtr);

      Planner * hppPlanner_;
      Server* server_;

    private:
      
      TutorialWkPtr wkPtr_;

  };

  } // end of namespace constrained-tutorial
} // end of namespace kpp

extern "C" KPP_ADDON_API int
initializeModule (CkppModuleInterfaceShPtr& o_moduleInterface);

#endif //! KPP_CONSTRAINED_TUTORIAL_KPP_CONSTRAINED_TUTORIAL_HH_
