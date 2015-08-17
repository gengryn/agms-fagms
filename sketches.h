//
//  sketches.h
//  agms
//
//  Created by admin on 15/8/7.
//  Copyright (c) 2015年 uml. All rights reserved.
//

#ifndef _SKETCH
#define _SKETCH


#include "xis.h"

using namespace std;


/*
 Generic interface for the sketches estimating size of joins and self-join sizes
  */

class Sketch
{
public:
    double Average(double *x, int n);
    double Median(double *x, int n);
    double Min(double *x, int n);
    
    
    virtual ~Sketch();
    
    //reseting the sketch structure
    virtual void Clear_Sketch() = 0;
    
    //updating the sketch with the value corresponding to the given key
    virtual void Update_Sketch(unsigned int key, double func) = 0;
    
    //estimating the size of join of two sketches; the second sketch is passed in as s1
    virtual double Size_Of_Join(Sketch *s1) = 0;
    
    //estimating the self-join size or the second frequency moment
    virtual double Self_Join_Size() = 0;
};



/*
 AGMS sketches
 */

class AGMS_Sketch : public Sketch
{
protected:
    unsigned int rows_no;
    unsigned int cols_no;
    
    double *sketch_elem;
    
    Xi **xi_pm1;
    
    
public:
    AGMS_Sketch(unsigned int cols_no, unsigned int rows_no, Xi **xi_pm1);
    virtual ~AGMS_Sketch();
    
    virtual void Clear_Sketch();
    
    virtual void Update_Sketch(unsigned int key, double func);
    
    virtual double Size_Of_Join(Sketch *s1);
    
    virtual double Self_Join_Size();
};



/*
 Fast-AGMS sketches .
 */

class FAGMS_Sketch : public Sketch
{
protected:
    unsigned int buckets_no;
    unsigned int rows_no;
    
    double *sketch_elem;
    
    Xi **xi_bucket;
    Xi **xi_pm1;
    
    
public:
    FAGMS_Sketch(unsigned int buckets_no, unsigned int rows_no, Xi **xi_bucket, Xi **xi_pm1);
    virtual ~FAGMS_Sketch();
    
    virtual void Clear_Sketch();
    
    virtual void Update_Sketch(unsigned int key, double func);
    
    virtual double Size_Of_Join(Sketch *s1);
    
    virtual double Self_Join_Size();
};




#endif
