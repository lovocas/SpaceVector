/** Problem 2:
  *In 3D space, there is a finite line AB, and a point C. Create a function that will calculate shortest line DE
  *from point C to line AB. Platform independent.
  **/
#include<stdio.h>
#include<math.h>
//all float* params are a float[3] array, float[3]==point
//algrithm:
//A(x1, y1, z1) B(x2, y2, z2) C(x0, y0, z0)
//so a point(x, y, z) on the line AB can be represented as
//x = x1 + (x2 - x1) * t
//y = y1 + (y2 - y1) * t
//z = z1 + (z2 - z1) * t   (equation 1)
// and we can assume a surface through C and vertical to line AB
//the surface can be represented as 
//(x2 - x1)*(x - x0) + (y2 - y1) * (y - y0) + (z2 - z1) * (z - z0) = 0;  (equation 2)
// combine both equation1 and equation 2, we can calculate out t
//     (x1 - x0)(x1 - x2) + (y1 - y0)(y1 -y2) + (z1 - z0) (z1 - z2)
// t = ---------------------------------------------------------------------
//      (x1 - x2) ^2 + (y1 - y2) ^ 2 + (z1 - z2) ^ 2
// and then we can get the value of x, y, z
//here we must take the value of t into concern:
//if 0 <= t <= 1. then the point D is between A and B
//else if t < 0. then the point D is on BA(not between), so the shortest path's endpoint should be A
//esle if t > 1. then the point D is on AB(not between), so the shortest path's endpoint should be B


//params:
//pointA: A point, 
//pointB: B point
//pointC: Cpoint
//ret values:
//the shortest distance frome C to AB
//pointD, the point D between AB which makes the CD the shortest path
float dstPntln(float *pointD, float *pointA, float *pointB, float *pointC) {
    float t, x1, y1, z1, x2, y2, z2, x0, y0, z0;
    float xD, yD, zD;
    x1 = pointA[0];
    y1 = pointA[1];
    z1 = pointA[2];

    x2 = pointB[0];
    y2 = pointB[1];
    z2 = pointB[2];

    x0 = pointC[0];
    y0 = pointC[1];
    z0 = pointC[2];

    t = ((x1 - x0) * (x1 - x2) + (y1 - y0) * (y1 - y2) + (z1 - z0) * (z1 - z2)) 
        / ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));

    if(t >= 0 && t <= 1) {
        xD = x1 + t * (x2 - x1);
        yD = y1 + t * (y2 - y1);
        zD = z1 + t * (z2 - z1);


    }
    else if( t < 0) {
        //CA
        xD = x1;
        yD = y1;
        zD = z1;

    } else {
    
        //CB
        xD = x2;
        yD = y2;
        zD = z2;
    }
    pointD[0] = xD;
    pointD[1] = yD;
    pointD[2] = zD;
    return sqrt((xD - x0) * (xD - x0) + (yD - y0 ) * (yD - y0) + (zD - z0) * (zD - z0));
}

void main() {

    float pointA[] = {4, 3, 0};
    float pointB[] = {0, 0, 12};
    float pointC[] = {0, 0 , 0};
    float pointD[3];
    float distance;
    distance = dstPntln(pointD, pointA, pointB, pointC);
    printf("dst is %f\n", distance);
    printf("%f %f %f \n", pointD[0], pointD[1], pointD[2]);
    getchar();

}