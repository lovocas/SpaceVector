/**
 * In 3D space, there is a finite line AB, and a triangle CDE. Create a function that will calculate if line AB
 * penetrates triangle CDE, and if so, calculate penetration point 3D coordinates. Platform independent.
 */
#include<stdio.h>

//judge whether the two vector are the same direction
//if the 0 <= angle <=90 return 1 (true)
//else return 0 (false)
//NOTICE: deprecated
int isSameDirection(float *vector1, float *vector2) {
    float result = vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
    return result >= 0;
}

//perfect!
void CrossProduct(float *resultVector, float *vector1, float *vector2) {
    resultVector[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    resultVector[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    resultVector[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

//perfect!
float DotProduct(float *vector1, float *vector2) {
    return vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
}


//detect whethet C and P point are one the same side of line AB
//implemented after reading this article http://www.blackpawn.com/texts/pointinpoly/default.html
int SameSide(float *aPoint, float *bPoint, float *cPoint, float *pPoint) {
    float vectorAB[] = {bPoint[0] - aPoint[0], bPoint[1] - aPoint[1], bPoint[2] - aPoint[2]};
    float vectorAP[] = {pPoint[0] - aPoint[0], pPoint[1] - aPoint[1], pPoint[2] - aPoint[2]};
    float vectorAC[] = {cPoint[0] - aPoint[0], cPoint[1] - aPoint[1], cPoint[2] - aPoint[2]};
    float vectorABAC[3];
    float vectorABAP[3];
    CrossProduct(vectorABAC, vectorAB, vectorAC); 
    CrossProduct(vectorABAP, vectorAB, vectorAP);
    if (DotProduct(vectorABAC, vectorABAP) >= 0) return 1;
    else return 0;
}

// Same side method
// Determine whether point P in triangle ABC
int IsPointInTriangle(float *aPoint, float * bPoint, float *cPoint, float *pPoint){    
    return SameSide(aPoint, bPoint, cPoint, pPoint) &&SameSide( bPoint, cPoint, aPoint, pPoint) 
        &&SameSide( cPoint, aPoint, bPoint, pPoint) ;
}



//calculate the intersect point of a straight line and a plane
//if the line and the plane are parallel return 0!
//else calculate the intersection point and store in hte result array
//Algrithm:
//a straight line: use a point and a vector to represent [lineVector(v1, v2, v3), linePoint(m1, m2, m3)]
// x = m1 + v1 * t
// y = m2 + v2 * t
// z = m3 + v3 * t  (equation group 1)
//a plane: also use a point and  a vector to represent [planeVector(vp1, vp2, vp3), planePoint(n1, n2, n3)]
//vp1(x - n1) + vp2(y - n2) + vp3(y - n3) = 0 (equation 2)
//combine the equaction group1 and equation2
//we can get the result of t
// t = t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / (v1 * vp1 + v2 * vp2 + v3 * vp3);
//then we can use t to calclate  x, y, z and save them in the result
//end
//
int CalPlaneLineIntersectPoint(float *result, float *planeVector, float *planePoint, float *lineVector, float *linePoint) {

    float vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t,vpt;
    vp1 = planeVector[0];
    vp2 = planeVector[1];
    vp3 = planeVector[2];
    n1 = planePoint[0];
    n2 = planePoint[1];
    n3 = planePoint[2];
    v1 = lineVector[0];
    v2 = lineVector[1];
    v3 = lineVector[2];
    m1 = linePoint[0];
    m2 = linePoint[1];
    m3 = linePoint[2];
    vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;//dot product of the two vectors
    //if the two vectors are vertical, then the line and the plane must be parral, so return false
    if (vpt == 0)
    {
        return 0;
    }
    else
    {
        t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;
        result[0] = m1 + v1 * t;
        result[1] = m2 + v2 * t;
        result[2] = m3 + v3 * t;
        return 1;
    }

}


//calculate the intersect point of a finite straight line and a triangle
//if the line does not penetrate this triangle return 0;
//else return 1 and save the intersection point into the result address
//
int CalTriangleLineIntersectPoint(float *result,  float *triPoint1, float *triPoint2, float *triPoint3, float *linePoint1, float *linePoint2) {
    
    float vector12[] = {triPoint2[0] - triPoint1[0], triPoint2[1] - triPoint1[1], triPoint2[2] - triPoint1[2]};
    float vector13[] = {triPoint3[0] - triPoint1[0], triPoint3[1] - triPoint1[1], triPoint3[2] - triPoint1[2]};
    
    float planeVector[3];
    
    CrossProduct(planeVector, vector12, vector13);

    float *planePoint = triPoint1;
    float lineVector[] = {linePoint2[0] - linePoint1[0], linePoint2[1] - linePoint1[1], linePoint2[2] - linePoint1[2]};
    
    if(CalPlaneLineIntersectPoint(result, planeVector, planePoint, lineVector, linePoint1) != 0) {//if the line does not parallel with the plane
        float vector1[] = {linePoint1[0] - result[0], linePoint1[1] - result[1], linePoint1[2] - result[2]};
        float vector2[] = {linePoint2[0] - result[0], linePoint2[1] - result[1], linePoint2[2] - result[2]};
        
        if(DotProduct(vector1, vector2) > 0) {//if the intersection point is not between the two endpoint of the line, or just be one endpoint
            return 0;
        }
        // the intersection point is between the two end point of the straight line or just be one endpoint
        
        //so judge whether the intersection point is in the triangle
        if(IsPointInTriangle(triPoint1, triPoint2, triPoint3, result) == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }

    //parallel, so not penetrate!
    return 0;    
}

int main(void) {
    
    float triPoint1[] = {0, 0, 1};
    float triPoint2[] = {0, 1, 0};
    float triPoint3[] = {0, 0, 0};

    float linePoint1[] = {1, 0, 0};
    float linePoint2[] = {0, 0, 1};
    float result[3];
    int a = CalTriangleLineIntersectPoint(result, triPoint1, triPoint2, triPoint3, linePoint1, linePoint2);
    if(a != 0) {
        printf("result: %f %f %f\n", result[0], result[1], result[2]);
    }

    float _triPoint1[] = {0, 0, 1};
    float _triPoint2[] = {0, 1, 0};
    float _triPoint3[] = {1, 0, 0};


    float _linePoint1[] = {2, 2, 2};
    float _linePoint2[] = {0, 0, 0};
    float _result[3];
    int _a = CalTriangleLineIntersectPoint(_result, _triPoint1, _triPoint2, _triPoint3, _linePoint1, _linePoint2);
    if(_a != 0) {
        printf("result: %f %f %f\n", _result[0], _result[1], _result[2]);
    }
    getchar();

    
}