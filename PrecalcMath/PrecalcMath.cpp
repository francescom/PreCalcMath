#ifndef PrecalcMath_cpp
#define PrecalcMath_cpp

/*
  PrecalcMath.cpp - Library for sin cos and linearizing led light
  using integer math using precomputed tables.
  Created by Francesco Munafò, November 8, 2018.
  Released into the public domain.
*/

#include "PrecalcMath.h"


#if LINERIZE_TABLE_SIZE == 256
const uint8_t PrecalcMath::ledLights256[]={0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,8,8,8,9,9,10,10,11,11,12,12,13,13,14,15,15,16,17,18,18,19,20,21,22,23,24,25,26,27,29,30,31,33,34,35,37,38,40,42,43,45,47,49,51,53,55,57,59,61,63,66,68,70,73,75,78,81,83,86,89,92,94,97,100,103,106,109,112,115,118,121,124,127,130,133,136,139,142,145,148,151,154,157,160,162,165,168,171,173,176,179,181,184,186,188,191,193,195,197,199,201,203,205,207,209,211,212,214,216,217,219,220,221,223,224,225,227,228,229,230,231,232,233,234,235,236,236,237,238,239,239,240,241,241,242,242,243,243,244,244,245,245,246,246,246,247,247,248,248,248,248,249,249,249,249,250,250,250,250,251,251,251,251,251,251,251,252,252,252,252,252,252,252,252,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,254,254,254,254,254,254,254,254,254,254,254,254,254};
#elif LINERIZE_TABLE_SIZE == 32
const uint8_t PrecalcMath::ledLights32[]={0,0,1,1,2,4,6,8,12,18,25,35,49,66,86,109,133,157,179,197,212,224,233,239,244,247,249,251,252,253,253,254};
#elif LINERIZE_TABLE_SIZE == 16
const uint8_t PrecalcMath::ledLights16[]={0,1,2,6,12,25,49,86,133,179,212,233,244,249,252,253};
#elif LINERIZE_TABLE_SIZE == 8
const uint8_t PrecalcMath::ledLights8[]={0,2,12,49,133,212,244,252};
#else
const uint8_t PrecalcMath::ledLights16[]={0,1,2,6,12,25,49,86,133,179,212,233,244,249,252,253};
#endif

#if SIN_TABLE_SIZE == 256
const int8_t PrecalcMath::sinVals256[]={0,3,6,9,12,16,19,22,25,28,31,34,37,40,43,46,49,51,54,57,60,63,65,68,71,73,76,78,81,83,85,88,90,92,94,96,98,100,102,104,106,107,109,111,112,113,115,116,117,118,120,121,122,122,123,124,125,125,126,126,126,127,127,127,127,127,127,127,126,126,126,125,125,124,123,122,122,121,120,118,117,116,115,113,112,111,109,107,106,104,102,100,98,96,94,92,90,88,85,83,81,78,76,73,71,68,65,63,60,57,54,51,49,46,43,40,37,34,31,28,25,22,19,16,12,9,6,3,0,-3,-6,-9,-12,-16,-19,-22,-25,-28,-31,-34,-37,-40,-43,-46,-49,-51,-54,-57,-60,-63,-65,-68,-71,-73,-76,-78,-81,-83,-85,-88,-90,-92,-94,-96,-98,-100,-102,-104,-106,-107,-109,-111,-112,-113,-115,-116,-117,-118,-120,-121,-122,-122,-123,-124,-125,-125,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-125,-125,-124,-123,-122,-122,-121,-120,-118,-117,-116,-115,-113,-112,-111,-109,-107,-106,-104,-102,-100,-98,-96,-94,-92,-90,-88,-85,-83,-81,-78,-76,-73,-71,-68,-65,-63,-60,-57,-54,-51,-49,-46,-43,-40,-37,-34,-31,-28,-25,-22,-19,-16,-12,-9,-6,-3};
#elif SIN_TABLE_SIZE == 32
const int8_t PrecalcMath::sinVals32[]={0,25,49,71,90,106,117,125,127,125,117,106,90,71,49,25,0,-25,-49,-71,-90,-106,-117,-125,-127,-125,-117,-106,-90,-71,-49,-25};
#elif SIN_TABLE_SIZE == 16
const int8_t PrecalcMath::sinVals16[]={0,49,90,117,127,117,90,49,0,-49,-90,-117,-127,-117,-90,-49};
#elif SIN_TABLE_SIZE == 8
const int8_t PrecalcMath::sinVals8[]={0,90,127,90,0,-90,-127,-90};
#else
const int8_t PrecalcMath::sinVals16[]={0,49,90,117,127,117,90,49,0,-49,-90,-117,-127,-117,-90,-49};
#endif

int8_t PrecalcMath::sin360(int32_t l) { // l positive or negative, in 1/360
    l=l*255L/360L;
    return (l>=0)?_sin(l%256):-_sin((-l)%256);
}

int8_t PrecalcMath::cos360(int32_t l) { // l positive or negative, in 1/360
    l=l*255L/360L;
    return (l>=0)?_sin((l+64)%256):-_sin((-l-64)%256);
}

int8_t PrecalcMath::sin255(int32_t l) { // l positive or negative, in 1/256
     return (l>=0)?_sin(l%256):-_sin((-l)%256);
}

inline int8_t PrecalcMath::sin255small(uint8_t l) { // l positive, in 1/256 must be bteween 0 and 255
     return _sin(l);
}

int8_t PrecalcMath::cos255(int32_t l) { // l positive or negative, in 1/256
     return (l>=0)?_sin((l+64)%256):-_sin((-l-64)%256);
}

inline int8_t PrecalcMath::cos255small(uint8_t l) { // l positive, in 1/256 must be bteween 0 and 255
     return _sin(l+64); // should wrap around and auto %256
}

int8_t PrecalcMath::sin1024(int32_t l) { // l positive or negative, in 1/1024
    return (l>=0)?_sin((l>>2)%256):-_sin(((-l)>>2)%256);
}

int8_t PrecalcMath::cos1024(int32_t l) { // l positive or negative, in 1/1024
    return (l>=0)?_sin(((l>>2)+64)%256):-_sin((((-l)>>2)-64)%256);
}

int8_t PrecalcMath::_sin(uint8_t l) {
#if SIN_TABLE_SIZE == 256
    return sinVals256[l];
#elif SIN_TABLE_SIZE == 32
    return PrecalcMath::sInterpolateFromTable(l,sinVals32, 32);
#elif SIN_TABLE_SIZE == 16
    return PrecalcMath::sInterpolateFromTable(l,sinVals16, 16);
#elif SIN_TABLE_SIZE == 8
    return PrecalcMath::sInterpolateFromTable(l,sinVals8, 8);
#else
    return PrecalcMath::sInterpolateFromTable(l,sinVals16, 16);
#endif
}

uint8_t PrecalcMath::linearizeLight(uint8_t l) {
#if LINERIZE_TABLE_SIZE == 256
	return PrecalcMath::uInterpolateFromTable(l,ledLights256, 256);
#elif LINERIZE_TABLE_SIZE == 32
	return PrecalcMath::uInterpolateFromTable(l,ledLights32, 32);
#elif LINERIZE_TABLE_SIZE == 16
	return PrecalcMath::uInterpolateFromTable(l,ledLights16, 16);
#elif LINERIZE_TABLE_SIZE == 8
	return PrecalcMath::uInterpolateFromTable(l,ledLights8, 8);
#else
	return PrecalcMath::uInterpolateFromTable(l,ledLights16, 16);
#endif
}

uint8_t PrecalcMath::uInterpolateFromTable(uint16_t x,const uint8_t *table, uint8_t tableSize) {
  
 	uint8_t inFact=256/tableSize;
 	uint8_t
      	div=x/inFact,
  		rest=x%inFact,
  		v1=table[div];
  	uint16_t v2=((div+1>=tableSize)?256:table[div+1]);

  	return ( (uint16_t)rest * (uint16_t)(v2) + ( (uint16_t)inFact - (uint16_t)rest ) * v1 ) / inFact;
}

int8_t PrecalcMath::sInterpolateFromTable(uint16_t x,const int8_t *table, uint8_t tableSize) {
  
 	uint8_t inFact=256/tableSize;
 	uint8_t
      	div=x/inFact,
  		rest=x%inFact;
 	int8_t
  		v1=table[div];
  	int16_t v2=((div+1>=tableSize)?table[0]:table[div+1]); // looped.

  	return ( (int16_t)rest * (int16_t)(v2) + ( (int16_t)inFact - (int16_t)rest ) * v1 ) / inFact;
}





/* PHP CODE FOR SIN AND COS TABLE GENERATION

<?php

$TABLE_SIZE=32; // Change this to 16 or 32 or whatever<=256



function functionValue($x) { return round(127*sin($x*M_PI/128.0)); }

function getPrecalcValues($number) {
    $div=256/$number;
    $vals=array();
    for($i=0;$i<$number;$i++) $vals[]=functionValue($i*$div);
    return $vals;
}

function generateTable($size) {
    return ('int8_t sinVals'.$size.'[]={'.implode(',',getPrecalcValues($size)).'};'."\n");
}

	echo("\n\n");
	echo(generateTable($TABLE_SIZE));
	echo("\n\n");

    echo('int8_t precalcSin360(int32_t l) { // l positive or negative, in 1/360
    
    l=l*255L/360L;
    
    return (l>=0)?_precalcSin(l%256):-_precalcSin((-l)%256);
}'."\n\n");

    echo('int8_t precalcCos360(int32_t l) { // l positive or negative, in 1/360
    
    l=l*255L/360L;
    
    return (l>=0)?_precalcSin((l+64)%256):-_precalcSin((-l+64)%256);
}'."\n\n");

    echo('int8_t precalcSin255(int32_t l) { // l positive or negative, in 1/256
    
     return (l>=0)?_precalcSin(l%256):-_precalcSin((-l)%256);
}'."\n\n");

    echo('int8_t precalcCos255(int32_t l) { // l positive or negative, in 1/256
    
     return (l>=0)?_precalcSin((l+64)%256):-_precalcSin((-l+64)%256);
}'."\n\n");

    echo('int8_t precalcSin1024(int32_t l) { // l positive or negative, in 1/1024
    
    return (l>=0)?_precalcSin((l>>2)%256):-_precalcSin(((-l)>>2)%256);
}'."\n\n");

    echo('int8_t precalcCos1024(int32_t l) { // l positive or negative, in 1/1024
    return (l>=0)?_precalcSin((l>>2+64)%256):-_precalcSin(((-l)>>2+64)%256);
}'."\n\n");


if($TABLE_SIZE<256) {
    echo('int8_t _precalcSin(uint8_t l) {
    return interpolateFromTable(l,sinVals'.$TABLE_SIZE.', '.$TABLE_SIZE.');
}'."\n\n");

    echo('
int8_t interpolateFromTable(uint16_t x,int8_t *table, uint8_t tableSize) {
  
 	uint8_t inFact=256/tableSize;
 	uint8_t
      	div=x/inFact,
  		rest=x%inFact;
 	int8_t
  		v1=table[div];
  	int16_t v2=((div+1>=tableSize)?table[0]:table[div+1]); // looped.

  	return ( (int16_t)rest * (int16_t)(v2) + ( (int16_t)inFact - (int16_t)rest ) * v1 ) / inFact;
}
    
    ');
    
    
} else {
    echo('int8_t _precalcSin(uint8_t l) {
	return sinVals'.$TABLE_SIZE.'[l];
}'."\n\n");
}




// PHP ends here, from now on it's plain text (C code)

?>


*/






/* PHP CODE FOR LINEARIZE TABLE GENERATION

<?php

$TABLE_SIZE=32; // Change this to 16 or 32 or whatever<=256



function linearizeLed($x) { return floor(255/(1+exp(-(($x/21)-6)))); }

function getLinearizedValues($number) {
    $div=256/$number;
    $vals=array();
    for($i=0;$i<$number;$i++) $vals[]=linearizeLed($i*$div);
    return $vals;
}

function generateTable($size) {
    return ('uint8_t ledLights'.$size.'[]={'.implode(',',getLinearizedValues($size)).'};'."\n");
}

echo("\n\n");
echo(generateTable($TABLE_SIZE));
echo("\n\n");

if($TABLE_SIZE<256) {
    echo('uint8_t linearizeLight(uint8_t l) {
    return interpolateFromTable(l,ledLights'.$TABLE_SIZE.', '.$TABLE_SIZE.');
}'."\n\n");

    echo('
uint8_t interpolateFromTable(uint16_t x,uint8_t *table, uint8_t tableSize) {
  
 	uint8_t inFact=256/tableSize;
 	uint8_t
      	div=x/inFact,
  		rest=x%inFact,
  		v1=table[div];
  	uint16_t v2=((div+1>=tableSize)?256:table[div+1]);

  	return ( (uint16_t)rest * (uint16_t)(v2) + ( (uint16_t)inFact - (uint16_t)rest ) * v1 ) / inFact;
}
    
    ');
    
    
} else {
    echo('uint8_t linearizeLight(uint8_t l) {
	return ledLights'.$TABLE_SIZE.'[l];
}'."\n\n");
}




// PHP ends here, from now on it's plain text (C code)

?>


*/


#endif