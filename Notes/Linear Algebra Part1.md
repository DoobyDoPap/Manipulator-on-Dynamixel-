# LINEAR ALGEBRA
## VECTORS
In case of Linear Algebra vectors should be viewed as arrows with its tail rooted at the origin.

The computer science perspective is that vectors are ordered lists of numbers.

The coordinates of a vector is a pair of numbers that basically give instructions for how to get from the tail of that vector—at the origin—to its tip.

To distinguish vectors from points, the convention is to write this pair of numbers vertically with square brackets around them.

Every pair of numbers gives you one and only one vector.
![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/03f5c4a0-c1b9-44a2-85c8-208207d2a8b8)

### VECTOR ADDITION

If you take a step along the first vector, then take a step in the direction and distance described by the second vector, the overall effect is just the same as if you moved along the sum of those two vectors to start with.
![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/cbbb53f4-cd72-4ff4-84bb-14d1192b6f19)

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/1d560c99-a73a-4b49-9e75-5392a4e88803)

### SCALAR MULTIPLICATION
If you take the number 2, and multiply it by a given vector, it means you stretch out that vector so that it's 2 times as long as when you started.

The process of stretching or squishing or sometimes reversing the direction of a vector is called "scaling".

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/12de3d7e-89c9-4af1-92a5-254be517632f)

### SPAN
Unit vector along x-axis is known as **i-hat**.
Unit vector along y-axis is known as **j-hat**.
These are known as the basis of the coordinate system.

Scaling of two vectors and adding them to represent a new vector is known as **Linear Combination of those two vectors**.

Set of all possible vectors that one can find with a linear combination of a given pair of vectors is called the **span of those two vectors**.
Span of 2d vectors is all vectors in 2d space except when they are in one line.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/e1049dcf-2197-43f1-aa8e-a0cf6f110fdd)

### SPAN OF 3D VECTORS
Take three scalars and scale 3 vectors.Add them all together then Span is the set of all possible linear combinations.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/8ba610fa-bfac-4930-8aa8-b17f2adda201)

If the third vector sits on the span of first two vectors then it does not change.

If not then the span of the three vectors is all possible 3d vectors in space. Whenever this happens then we can remove a vector without reducing the span or in other words it is said to be **linearly dependent**.

If the vector adds another dimension it is then said to be linearly independent.


![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/eb6d09e1-f7e7-490b-a3f2-5962d6c20725)

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/c61504a4-d8f1-47bd-b0c7-bdea9fdae581)

**Technical defn of basis:**
The basis of a vector space is a set of linearly dependent vectors that span full space.
### LINEAR TRANSFORMATION
Transformation suggests to think using movements.
If a transformation takes some input vector to some output vector, we imagine that input vector moving over to the output vector. Then to understand the transformation as a whole, we might imagine watching every possible input vector move over to its corresponding output vector.
A transformation is linear if it has two properties: 
1. All lines must remain lines, without getting curved, and
2. The origin must remain fixed in place

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/55be5a67-0978-4f1d-982e-a89851aaccd3)

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/61d1e5db-2350-42c3-afa5-286537f93039)

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/5ccfc690-031d-4523-8d61-398131ea63fb)

 In general, you should think of linear transformations as keeping grid lines parallel and evenly spaced.
 
![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/77a4419e-f3d8-4035-81b8-fff6235ee902)

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/d9c735e8-3252-4f3e-a305-44b68c5c189b)

A two dimensional linear transformation is completely described by just four numbers: the two coordinates for where i-hat lands and the two coordinates for where j-hat lands.

It's common to package these coordinates into a two-by-two grid of numbers, called a two-by-two matrix, where you can interpret the columns as the two special vectors where i-hat and j-hat each land

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/6ba119e6-081e-4428-84af-7f360344e92d)

To get the transformed vector, multiply the coordinate of the vector with the column of the matrix.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/e7248cc9-84d4-4a77-b42a-8c61efed28e0)

In Shear Transformation, i hat remains fixed while j-hat varies.

Linear transformations are a way to move around space such that the grid lines remain parallel and evenly spaced and such that the origin remains fixed.












