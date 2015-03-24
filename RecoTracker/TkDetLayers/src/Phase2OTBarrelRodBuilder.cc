#include "Phase2OTBarrelRodBuilder.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <set>

using namespace edm;
using namespace std;

Phase2OTBarrelRod* Phase2OTBarrelRodBuilder::build(const GeometricDet* thePhase2OTBarrelRod,
						   const TrackerGeometry* theGeomDetGeometry)
{  
  // collection of sensors
  vector<const GeometricDet*> allGeometricDets = thePhase2OTBarrelRod->components();
 
  // find four radii to assign sensors to correct categories
  set<float> radii_list;
  for(vector<const GeometricDet*>::iterator it=allGeometricDets.begin();
      it!=allGeometricDets.end(); it++){
    radii_list.insert((*it)->positionBounds().perp());
  }

  // pick up the four radii
  float r_inner = 0.;
  float r_outer = 0.;
  float r_innerBrother = 0.;
  float r_outerBrother = 0.;
  unsigned int counter = 0;
  for ( set<float>::iterator it = radii_list.begin(); it != radii_list.end(); it++,counter++ ) {
    if      ( counter == 0 ) r_inner = *it;
    else if ( counter == 1 ) r_innerBrother = *it;
    else if ( counter == 2 ) r_outer = *it;
    else if ( counter == 3 ) r_outerBrother = *it;
    else {
     std::cerr << "Unexpected number of radii in Phase2OTBarrelRodBuilder::build." << std::endl;
     std::cerr << "Expect 4 but it is " << radii_list.size() << std::endl;
    }
  }

  // Four categories to which we assign sensors
  vector<const GeomDet*> innerGeomDets;
  vector<const GeomDet*> outerGeomDets;
  vector<const GeomDet*> innerGeomDetBrothers;
  vector<const GeomDet*> outerGeomDetBrothers;

  // compute meanR using the first and the third module because of the pt module pairs
  LogDebug("Phase2OTBarrelRodRadii") << "mean computed with " 
				     << r_inner 
				     << " and " << r_innerBrother 
				     << " and " << r_outer 
				     << " and " << r_outerBrother ;


  for(vector<const GeometricDet*>::iterator it=allGeometricDets.begin();
      it!=allGeometricDets.end(); it++){
    const GeomDet* theGeomDet = theGeomDetGeometry->idToDet( (*it)->geographicalID() );

    float radius = (*it)->positionBounds().perp();
    if      ( radius == r_inner ) innerGeomDets.push_back(theGeomDet);
    else if ( radius == r_innerBrother ) innerGeomDetBrothers.push_back(theGeomDet); 
    else if ( radius == r_outer ) outerGeomDets.push_back(theGeomDet);
    else if ( radius == r_outerBrother ) outerGeomDetBrothers.push_back(theGeomDet);
  }
  
  //LogDebug("TkDetLayers") << "innerGeomDets.size(): " << innerGeomDets.size() ;
  //LogDebug("TkDetLayers") << "outerGeomDets.size(): " << outerGeomDets.size() ;
  return new Phase2OTBarrelRod(innerGeomDets,outerGeomDets,innerGeomDetBrothers,outerGeomDetBrothers);
}
