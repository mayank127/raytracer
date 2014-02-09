raytracer
=========

CS 775 Ray Tracer in C++ 

***

**Team** 

110050012 - Mayank Meghwanshi (@mayank127)

110050041 - Shivam H Prasad (@shivamh71)

***

**Instructions**

To Compile use > Makefile

To Run > ./ray-tracer scene-file

***

**Code Description**

1. **Main File**
 * It contains parser for input scene file.
 * It first takes the light parameters and makes a list of light objeect with specified color.
 * It then takes camera parameters and transform pixel points from image plane to view coordinate system then using postioon of eye, up vector and look at vector converts to World coordinate system.
 * Now for each such point a ray is shot from camera to pixel and recursive ray tracing is done.
 * For ray tracing we find out nearest intersection.
 * Now if specular object then send refracted and reflected rays, and calculate color.
 * If diffused object or recursion depth reached then check with shadow ray if light is visible to the point of intersection and calculate color according to phong model.

2. **Objects**
 * For each object we find out intersection with a ray from a given origin and direction.
 * We also have a transformation matrix which is used to transform ray to object coordinate system and then use that to find out the intersection.
 * We also have a function which returns normal of the object, which takes as input a point on surface and trasnforms it to object coordinate system and after finding normal at that point transform back to world coordinate space.
 * Different objects made - 
    * **Sphere**
    * **Cylinder**
    * **Cone**
    * **Triangle**

3. **Lights**
 * This contain only position and color of light used for phong model calculation.

4. **Vec3**
 * This contains function needed for a vector with 3 coordinates x,y,z.
 * It contains functions like dot product, length, cross product, normalize, project, *,/,+,- etc.

5. **Matrix**
 * This contains 4x4 matrix used for transformation in 3-d Space.
 * It has different constructors which can make rotation, scale, shear and translate matrices.
 * Also it has usefull functions like inverse, transpose, multiply, transform etc.

***

**Sample Images**
![Sample 1](http://www.cse.iitb.ac.in/~manku/Images/ray-tracer/sample1.jpg)

![Sample 2](http://www.cse.iitb.ac.in/~manku/Images/ray-tracer/sample2.jpg)

![Sample 3](http://www.cse.iitb.ac.in/~manku/Images/ray-tracer/sample3.jpg)

![Sample 4](http://www.cse.iitb.ac.in/~manku/Images/ray-tracer/sample4.jpg)

![Sample 5](http://www.cse.iitb.ac.in/~manku/Images/ray-tracer/sample5.jpg)

***



**Sources**

* [CS475 slides](http://www.cse.iitb.ac.in/~paragc/teaching/2013/cs475/)
* [Ray Tracing Chapter from Shirley](http://www.cs.utah.edu/~shirley/books/fcg2/rt.pdf)
* [Ray Triangle Intersection](http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/)
* [Ray Cone, Ray Cylinder Intersection](http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf)
* [A sample Ray Tracer for reference](http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-1-writing-a-simple-raytracer/)
