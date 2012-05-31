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

#include <hpp/util/debug.hh>
#include <hpp/constrained/planner/grasping-planner.hh>
#include <hpp/corbaserver/constrained/server.hh>

#include "kpp/constrained-tutorial/tutorial.hh"

namespace kpp {
  namespace constrained {

    Tutorial::Tutorial(Planner * i_planner):
      CkppInterface(i_planner),
      hppPlanner_(i_planner)
    {
      char** argv = (char**) malloc (sizeof (char*));
      argv[0] = strdup ("Kite");
      server_ = new Server (1, argv, false, "child");
      server_->setPlanner (hppPlanner_);
      try {
	startCorbaServer ();
	hppDout (info, "Successfully started hpp-corbaserver.");
      } catch (const std::exception& exc) {
	hppDout (error, "Failed to start hpp-corbaserver");
      }
      try {
	server_->startCorbaServer("hpp", "plannerContext",
				  "hpp", "constrained");
	hppDout (info, "Successfully started constrained corba server.");
      } catch (const std::exception& exc) {
	hppDout (error, "Failed to start constrained corba server.");
      }
    }

    Tutorial::~Tutorial()
    {
    }

    TutorialShPtr
    Tutorial::create()
    {
      Planner * planner = new Planner();

      TutorialShPtr shPtr(new Tutorial(planner));
      TutorialWkPtr wkPtr(shPtr);

      if (shPtr->init (wkPtr) != KD_OK)
	shPtr.reset ();
      return shPtr;
    }

    ktStatus
    Tutorial::init(const TutorialWkPtr & i_wkPtr)
    {
     if (CkppInterface::init (i_wkPtr) != KD_OK)
	return KD_ERROR;
      wkPtr_ = i_wkPtr;
      return KD_OK;
    }

    std::string
    Tutorial::name() const
    {
      return std::string("kpp-constrained-tutorial");
    }

  } // end of namespace constrained-tutorial
} // end of namespace kpp


extern "C"
int
initializeModule (CkppModuleInterfaceShPtr& o_moduleInterface)
{
  using namespace kpp::constrained;
 
  o_moduleInterface = Tutorial::create ();

  if (o_moduleInterface)
    return 0;

  //FIXME: for some reason, a segv happens if the module initialization
  // fails. As the user is doomed anyway, let's exit with a nice error
  // message.

  return 1;
}
