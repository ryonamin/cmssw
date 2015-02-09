#include "Phase2OTBarrelRodBuilder.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace edm;
using namespace std;

Phase2OTBarrelRod* Phase2OTBarrelRodBuilder::build(const GeometricDet* thePhase2OTBarrelRod,
							   const TrackerGeometry* theGeomDetGeometry)
{  
  vector<const GeometricDet*> allGeometricDets = thePhase2OTBarrelRod->components();

  vector<const GeomDet*> innerGeomDets;
  vector<const GeomDet*> outerGeomDets;
  vector<const GeomDet*> innerGeomDetBrothers;
  vector<const GeomDet*> outerGeomDetBrothers;

  // Compute meanR using the first and the third module because of the pt module pairs
  // -->
  // This strategy doesn't work for a new tracker.xml.
  // We should not assume the order of allGeometricDets.
  // So we will take all module information into account (RefRs).
  /*
  LogDebug("Phase2OTBarrelRodRadii") << "mean computed with " 
				     << allGeometricDets[0]->positionBounds().perp() 
				     << " and " << allGeometricDets[2]->positionBounds().perp() 
				     << " and " << allGeometricDets[1]->positionBounds().perp() 
				     << " and " << allGeometricDets[3]->positionBounds().perp() ;
  */

  RefRs rs(allGeometricDets);
  const double rodR = rs.getRodR();
  const double meanRot = rs.getOuterModuleR();
  const double meanRin = rs.getInnerModuleR();
  LogDebug("Phase2OTBarrelRodRadii") << "rodR = " << rodR
                                     << ", meanRot = " << meanRot 
                                     << ", meanRin = " << meanRin
                                     << " ( should be meanRin < rodR < meanRot )"; 

  for(vector<const GeometricDet*>::iterator it=allGeometricDets.begin();
      it!=allGeometricDets.end(); it++){
    const GeomDet* theGeomDet = theGeomDetGeometry->idToDet( (*it)->geographicalID() );
    double r = (*it)->positionBounds().perp();
    if ( r > rodR ) {
      if ( r > meanRot ) outerGeomDetBrothers.push_back(theGeomDet); 
      else               outerGeomDets.push_back(theGeomDet);
    } else {
      if ( r > meanRin ) innerGeomDetBrothers.push_back(theGeomDet); 
      else               innerGeomDets.push_back(theGeomDet);
    }
  }
  
  //LogDebug("TkDetLayers") << "innerGeomDets.size(): " << innerGeomDets.size() ;
  //LogDebug("TkDetLayers") << "outerGeomDets.size(): " << outerGeomDets.size() ;
  return new Phase2OTBarrelRod(innerGeomDets,outerGeomDets,innerGeomDetBrothers,outerGeomDetBrothers);
}

Phase2OTBarrelRodBuilder::RefRs::RefRs(vector<const GeometricDet*>& modules) : rodR(0.),
                                                                               innerModuleR(0.),
                                                                               outerModuleR(0.)
{
  // Compute radial positions for rod, inner/outer pt-modules using all pt-module information
  // This is needed to clasify each pt-module in correct vectors 
  // (innerGeomDets,outerGeomDets,innerGeomDetsBrothers,outerGeomDetsBrothers).

  // (1) Compute radial postion of the rod
  double nmodules = double(modules.size());
  for(vector<const GeometricDet*>::iterator it=modules.begin();
      it!=modules.end(); it++){
    rodR += (*it)->positionBounds().perp();
  }
  rodR /= nmodules;

  // (2) Compute inner/outer module radial postions
  double nRin = 0.; 
  double nRot = 0.;
  for(vector<const GeometricDet*>::iterator it=modules.begin();
      it!=modules.end(); it++){
    if ( (*it)->positionBounds().perp() > rodR ) {
      outerModuleR += (*it)->positionBounds().perp();
      nRot += 1.;
    } else {
      innerModuleR += (*it)->positionBounds().perp();
      nRin += 1.;
    }
  }
  outerModuleR /= nRot;
  innerModuleR /= nRin;
} 
