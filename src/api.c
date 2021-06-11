#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "material.h"
#include "truck.h"

void appDataInit(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the material table */
	materialTableInit(&(object->materials));
	
	/* Initialize the trucks table */
	trucksTableInit(&(object->trucks));
	
}

void appDataLoad(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of trucks */
	sprintf(path,"%strucks.txt", object->path);
	trucksTableLoad(&(object->trucks), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of trucks\n");
	}

	/* Load the table of materials */
	sprintf(path,"%smaterials.txt", object->path);
	materialTableLoad(&(object->materials), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of materials\n");
	}
}

void appDataSave(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of trucks */
	snprintf(path,MAX_PATHNAME,"%strucks.txt", object.path);
	trucksTableSave(object.trucks, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of trucks\n");
	}
	
	/* Save the table of materials */
	snprintf(path,MAX_PATHNAME,"%smaterials.txt", object.path);
	materialTableSave(object.materials, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of materials\n");
	}
}

void appDataSetPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, MAX_PATHNAME);	
}


/*********************** 
 *        API
 **********************/

void getTrucks(tAppData object, tTruckTable *result) {
	*result = object.trucks;	
}

void getTruck(tAppData object, tTruckId truckId, tTruck *truck, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a truck with this id */
	i = trucksTableFind(object.trucks, truckId);
	if (i!=NO_TRUCK) {
		truckCpy(truck,object.trucks.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addTruck(tAppData *object, tTruck truck, tError *retVal) {
	*retVal = OK;
	tTruck tmp;

	/* Check if there is another truck with the same id */
	getTruck(*object, truck.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new truck using the truck table method */
		trucksTableAdd(&(object->trucks), truck, retVal);
	}
}

void getMaterials(tAppData object, tMaterialTable *result) {
	*result = object.materials;	
}

void getMaterial(tAppData object, tMaterialId id, tMaterial *material, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a material with this id */
	i = materialTableFind(object.materials, id);
	if (i!=NO_MATERIAL) {
		materialCpy(material,object.materials.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addMaterial(tAppData *object, tMaterial material, tError *retVal) {
	*retVal = OK;
	tMaterial tmpMaterial;
    
	/* Check if there is another material with the same id */
	getMaterial(*object, material.id, &tmpMaterial, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new material using the material table method */
		materialTableAdd(&(object->materials), material, retVal);
	}

}

void removeMaterial(tAppData *object, tMaterial material) {
	
	/* Call the method from the materials table*/
	materialTableDel(&(object->materials), material);

}
