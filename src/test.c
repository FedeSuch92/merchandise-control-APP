#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "material.h"

#define MATERIAL1 "10 WALL 8 0.25 25.00 0.50 0.60 3 0 0"
#define MATERIAL2 "11 ASBESTOS 13 5.00 20.00 0.40 0.40 2 0 1"
#define MATERIAL3 "05 PVC 4 10.50 200.00 0.80 2.00 0 0 0"
#define MATERIAL4 "15 WINDOW 3 30.00 250.00 1.00 2.00 0 1 0"
#define MATERIAL5 "16 GAS 13 3.00 15.00 0.40 1.00 3 0 1"
#define MATERIAL6 "06 BEAM 2 2.50 30.00 0.20 0.50 0 0 0"

void runTests() {	
	int passedTestPR1, passedTestPR2=0;
	int totalTestPR1, totalTestPR2=0;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, (float)passedTestPR1/totalTestPR1*100.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0);
	printf("===================================\n");		
}

void runTestsPR1(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	testSerialization(totalTest, passedTest);
	testCpycmp(totalTest, passedTest);
	testPersistence(totalTest, passedTest);
	testSearch(totalTest, passedTest);
	testCount(totalTest, passedTest);
}

void testSerialization(int *totalTest, int *passedTest) {	

	tMaterial d1, d2;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" MATERIALS SERIALIZATION (Exercise 3)\n");
	printf("=================================================\n");

	printf("\nTest 3.1: Serialitzation");
	(*totalTest)++;
	d1.id = 10;
#ifdef TYPEDEF_COMPLETED
    strcpy(d1.name,"WALL");
	d1.type = PLADUR;
	d1.price = 0.25;
	d1.weight = 25.0;
	d1.height = 0.5;
	d1.volume = 0.6;
	d1.layers = 3;
	d1.isFragile = false;
	d1.isDangerous = false;
#endif
    getMaterialStr(d1,MAX_LINE,str);
	
    if (strcmp(MATERIAL1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.2: Desserialitzation");
	(*totalTest)++;
	getMaterialObject(MATERIAL1, &d2);
#ifdef TYPEDEF_COMPLETED
    if (d1.id==d2.id && strcmp(d1.name,d2.name)==0 && 
		d1.type==d2.type && d1.price==d2.price && d1.weight==d2.weight && d1.height==d2.height &&
		d1.volume==d2.volume && d1.layers==d2.layers && d1.isFragile==d2.isFragile && d1.isDangerous==d2.isDangerous) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} 
    else
#endif 
    {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 3.3: Equal serialization string after conversion to object");
	(*totalTest)++;
	getMaterialObject(MATERIAL1, &d1);
    getMaterialStr(d1,MAX_LINE,str);
    getMaterialObject(str,&d2);
    if (strcmp(MATERIAL1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Equal serialization object after conversion to string - Comparison");
	(*totalTest)++;
    if (materialCmp(d1, d2)==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;        
	} else {
		printf("\n\t-> FAIL\n");
	}
}	

void testCpycmp(int *totalTest, int *passedTest) {	

	tMaterial d1, d2;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" MATERIALS COPY AND COMPARE (Exercise 4)\n");
	printf("=================================================\n");
	
	printf("\nTest 4.1: Copy (check by string comparison)");
	(*totalTest)++;
	getMaterialObject(MATERIAL1, &d1);
    d2.id= 0;
	materialCpy(&d2,d1);
    getMaterialStr(d2,MAX_LINE,str);
    if (strcmp(MATERIAL1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.2: Compare equal materials");
	(*totalTest)++;
    if (materialCmp(d1,d1)==0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 4.3: Comparison, first material greater than second");
	(*totalTest)++;
	getMaterialObject(MATERIAL2, &d2);
    if (materialCmp(d1,d2)>0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.4: Comparison, second material lower than first");
	(*totalTest)++;
    if (materialCmp(d2,d1)<0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.5: Copy (check by structure comparison)");
	(*totalTest)++;
	materialCpy(&d2,d1);
    if (materialCmp(d1,d2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
}	

void testPersistence(int *totalTest, int *passedTest) {
	tMaterialTable materials;
	tMaterial p1, p2;
	tError retVal;
	
	printf("=================================================\n");
	printf(" PERSISTENCE OF MATERIALS (Exercise 5)\n");
	printf("=================================================\n");
	
	printf("\nTest 5.1: Save and load no data");
	(*totalTest)++;
	materialTableInit(&materials);	
	
	materialTableSave(materials, "./testMaterials.csv",&retVal);
	materialTableInit(&materials);		
	materialTableLoad(&materials, "./testMaterials.csv",&retVal);
	
	if(retVal==OK){
		if(materials.nMaterials==0) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, materials.nMaterials);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
		
	printf("\nTest 5.2: Save and load materials");
	(*totalTest)++;
	getMaterialObject(MATERIAL1, &p1);
	getMaterialObject(MATERIAL2, &p2);
    materialTableAdd(&materials,p1,&retVal);
    materialTableAdd(&materials,p2,&retVal);
	materialTableSave(materials, "./testMaterials.csv",&retVal);
	materialTableInit(&materials);		
	materialTableLoad(&materials, "./testMaterials.csv",&retVal);
	
	if(retVal==OK){
		if(materials.nMaterials==2) {
			if(materialCmp(materials.table[0], p1) != 0 || 
			   materialCmp(materials.table[1], p2) != 0) {
				printf("\n\t-> FAIL (Values are not correct)\n");
			} else {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			}
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, materials.nMaterials);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
}

void testSearch(int *totalTest, int *passedTest) {	
	tMaterialTable materials, result;
	tMaterial material1, material2, material3, material4, material5, material6;	
	tError retVal;
		
	printf("=================================================\n");
	printf(" MATERIAL TABLE FILTER (Exercise 6)\n");
	printf("=================================================\n");
	
	printf("\nTest 6.1: Materials of a type in empty table");
	(*totalTest)++;
	materialTableInit(&materials);	
	materialTableInit(&result);
    
	materialTableFilterByType(materials, (tMaterialType)(0), &result); /* concrete */
	if(result.nMaterials==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nMaterials);
	}

	getMaterialObject(MATERIAL1, &material1);
	getMaterialObject(MATERIAL2, &material2);
    getMaterialObject(MATERIAL3, &material3);
    getMaterialObject(MATERIAL4, &material4);
    getMaterialObject(MATERIAL5, &material5);
    getMaterialObject(MATERIAL6, &material6);
    materialTableAdd(&materials,material1,&retVal);
    materialTableAdd(&materials,material2,&retVal);
    materialTableAdd(&materials,material3,&retVal);
    materialTableAdd(&materials,material4,&retVal);
    materialTableAdd(&materials,material5,&retVal);	
    materialTableAdd(&materials,material6,&retVal);	
	
	printf("\nTest 6.2: Materials of a non existent type in non empty table");
	(*totalTest)++;	
	materialTableFilterByType(materials, (tMaterialType)(5), &result); /* aluminium */
	if(result.nMaterials==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nMaterials);
	}

	printf("\nTest 6.3: Materials of an existent type in non empty table");
	(*totalTest)++;	
	materialTableFilterByType(materials, (tMaterialType)(13), &result); /* other materials */
	if(result.nMaterials==2) {
		if((materialCmp(result.table[0], material2)!=0) ||
           (materialCmp(result.table[1], material5)!=0))  {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nMaterials);
	}

	printf("\nTest 6.4: Materials of a weight in empty table");
	(*totalTest)++;
	materialTableInit(&materials);	
	materialTableFilterByWeightInterval(materials, 0.0, 100.0, &result);
	if(result.nMaterials==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nMaterials);
	}
	
	printf("\nTest 6.5: Materials of a weight in a non empty table: null interval");
	(*totalTest)++;
    materialTableAdd(&materials,material1,&retVal);
    materialTableAdd(&materials,material2,&retVal);
    materialTableAdd(&materials,material3,&retVal);
    materialTableAdd(&materials,material4,&retVal);
    materialTableAdd(&materials,material5,&retVal);
    materialTableAdd(&materials,material6,&retVal);
	materialTableFilterByWeightInterval(materials, 100.0, 0.0, &result);
	if(result.nMaterials==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nMaterials);
	}
	
	printf("\nTest 6.6: Materials of a weight in a non empty table: interval includes some materials");
	(*totalTest)++;
	materialTableFilterByWeightInterval(materials, 0.0, 100.0, &result);
	if(result.nMaterials==4) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 4, result.nMaterials);
	}
	
	printf("\nTest 6.7: Materials of a weight in a non empty table: interval includes all materials");
	(*totalTest)++;
	materialTableFilterByWeightInterval(materials, 0.0, 250.0, &result);
	if(result.nMaterials==6) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 6, result.nMaterials);
	}
}
	
void testCount(int *totalTest, int *passedTest) {

    tAppData appData;
    tMaterial material1, material2, material3, material4, material5, material6;
	int count;
	float max;
	tError retVal;
   
    appDataInit(&appData);

	printf("=================================================\n");
	printf(" MATERIALS STATISTICS (Exercise 7)\n");
	printf("=================================================\n");
	
	printf("\nTest 7.1: Number of fragile materials in empty table");
	(*totalTest)++;
	count= materialTableGetNumberOfFragileMaterials(appData.materials);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}
	
	printf("\nTest 7.2: Number of fragile materials in non empty table (without hits)");
	(*totalTest)++;
	getMaterialObject(MATERIAL1, &material1);
	getMaterialObject(MATERIAL2, &material2);
    getMaterialObject(MATERIAL3, &material3);
	addMaterial(&appData,material1,&retVal);
	addMaterial(&appData,material2,&retVal);
	addMaterial(&appData,material3,&retVal);
	count= materialTableGetNumberOfFragileMaterials(appData.materials);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}
	
	printf("\nTest 7.3: Number of fragile materials in non empty table (with hits)");
	(*totalTest)++;
	getMaterialObject(MATERIAL4, &material4);
    getMaterialObject(MATERIAL5, &material5);
    getMaterialObject(MATERIAL6, &material6);
	addMaterial(&appData,material4,&retVal);
	addMaterial(&appData,material5,&retVal);
	addMaterial(&appData,material6,&retVal);
	count= materialTableGetNumberOfFragileMaterials(appData.materials);
	if (count==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, count);
	}
		
	appDataInit(&appData);

	printf("\nTest 7.4: Maximum height for a material in empty table:");
	(*totalTest)++;
	max = materialTableGetMaxMaterialHeight(appData.materials);
	if(max==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 0.0, max);
	}

    addMaterial(&appData,material4,&retVal);
	
	printf("\nTest 7.5: Maximum height for a material - case 1 material:");
	(*totalTest)++;
	max = materialTableGetMaxMaterialHeight(appData.materials);
	if(max==1.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 1.0, max);
	}

    addMaterial(&appData,material1,&retVal);
	
	printf("\nTest 7.6: Maximum height for a material - case 2 materials in descending order:");
	(*totalTest)++;
	max = materialTableGetMaxMaterialHeight(appData.materials);
	if(max==2.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 2.0, max);
	}   

	appDataInit(&appData);
    addMaterial(&appData,material1,&retVal);
    addMaterial(&appData,material4,&retVal);
	
	printf("\nTest 7.7: Maximum height for a material - case 2 materials in ascending order:");
	(*totalTest)++;
	max = materialTableGetMaxMaterialHeight(appData.materials);
	if(max==2.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of materials. Expected %.2f and returned %.2f)\n", 2.0, max);
	}  
}
	