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

  RadiiHandler rh(allGeometricDets); 
  // This class takes care of finding 3 reference radii in a rod building.
  // 1: center raidus of the rod position
  // 2: center raidus of Pt modules position ( inner side in the rod )
  // 3: center radius of Pt modules position ( outer side in the rod )
  const double rodCenterR   = rh.getRodCenterR();
  const double inModCenterR = rh.getInnerModuleCenterR();
  const double otModCenterR = rh.getOuterModuleCenterR();
  LogDebug("Phase2OTBarrelRodRadii") << "  (1) Rod position R = "               << rodCenterR
                                     << ", (2) Inner Pt-module position R = " << inModCenterR
                                     << ", (3) Outer Pt-module position R = " << otModCenterR
                                     << "( should be (2) < (1) < (3). )";

  // Now we will classify all GeomDets into 4 categories..
  for(vector<const GeometricDet*>::iterator it=allGeometricDets.begin();
      it!=allGeometricDets.end(); it++){
    const GeomDet* theGeomDet = theGeomDetGeometry->idToDet( (*it)->geographicalID() );

    const double sensorPositionR = (*it)->positionBounds().perp();
    
    if ( sensorPositionR < rodCenterR ) {

       // Inner module case

       if ( sensorPositionR < inModCenterR ) {
         // This is an inner sensor in inner modules
         innerGeomDets.push_back(theGeomDet);
       } else {
         // This is an outer sensor in inner modules
         innerGeomDetBrothers.push_back(theGeomDet);
       }

    } else {

       // Outer module case

       if ( sensorPositionR < otModCenterR ) {
         // This is an inner sensor in outer modules
         outerGeomDets.push_back(theGeomDet);
       } else {
         // This is an outer sensor in outer modules
         outerGeomDetBrothers.push_back(theGeomDet);
       }
        
    }

  }
  
  //LogDebug("TkDetLayers") << "innerGeomDets.size(): " << innerGeomDets.size() ;
  //LogDebug("TkDetLayers") << "outerGeomDets.size(): " << outerGeomDets.size() ;
  return new Phase2OTBarrelRod(innerGeomDets,outerGeomDets,innerGeomDetBrothers,outerGeomDetBrothers);
}

Phase2OTBarrelRodBuilder::RadiiHandler::RadiiHandler(const vector<const GeometricDet*>& sensors) : rodR(0.),
                                                                                                   inModR(0.), 
                                                                                                   otModR(0.) 
{
   // Compute radial positions for rod, inner/outer pt-modules using all sensor information

   // Step 1. Comupute radial position of the rod by averaging all sensor radii.
   for (vector<const GeometricDet*>::const_iterator it=sensors.begin(); it!=sensors.end(); it++) {
     rodR += (*it)->positionBounds().perp();
   }
   double nmodules = double(sensors.size());
   rodR /= nmodules;

   // Step 2. Compute radial postions of inner/outer modules as well.
   double nRin = 0.;
   double nRot = 0.;
   for (vector<const GeometricDet*>::const_iterator it=sensors.begin(); it!=sensors.end(); it++) {
     double sensorR = (*it)->positionBounds().perp();
     if ( sensorR < rodR ) {
       // Inner modules case.
       // Find a center radius by averaging sensor radii within inner module sensors
       inModR += sensorR;
       nRin += 1.;
     } else {
       // Outer modules case.
       // Find a center radius by averaging sensor radii within outer module sensors
       otModR += sensorR;
       nRot += 1.;
     }
   }
   inModR /= nRin;
   otModR /= nRot;
}
