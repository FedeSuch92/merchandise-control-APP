#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInit(tAppData *object);

/* Load the application data from file */
void appDataLoad(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSave(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the materials */
void getMaterials(tAppData object, tMaterialTable *result);

/* Get the material information */
void getMaterial(tAppData object, tMaterialId materialId, tMaterial *material, tError *retVal);

/* Add a new material */
void addMaterial(tAppData *object, tMaterial material, tError *retVal);

/* Remove a certain material */
void removeMaterial(tAppData *object, tMaterial material);

/* Return the table of trucks */
void getTrucks(tAppData object, tTruckTable *result);

/* Get the truck information */
void getTruck(tAppData object, tTruckId truckId, tTruck *truck, tError *retVal);

/* Add a new truck */
void addTruck(tAppData *object, tTruck truck, tError *retVal);
