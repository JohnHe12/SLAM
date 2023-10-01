# Visual Odometry

The SLAM systems is devided into a front-end and back-end, where the front-end is also called the visual odometer, visual odometry estimates the rough camera motion based on imformation from neighboring images. The algorithms of visual odometry fall into two main categories: **characteristic point method** and **direct method**.

## [caracteristic method](./charateristic%20point%20method/)

The core of the visual odometry is based on the imformation from neighboring images to calculate the rough camera motion.

so the simple flowchart of the caracteristic method:

- Extract the imformation or feature from the image, which is called keypoint here.*
- Gives every keypoint a descriptor in order to match the same point, if the descriptor of two keypoin is similar, we match this two keypoints.
- After match the kepoints, then we can determianate the motion of the camera through the mathmatic mmethod.

*keypoint from the image is not enough to calculate the motion of the camera, so we need to match the same point in the neighboring images.

## Example

Here use the example of ORB.

1. ORB use the Fast as the feature extractor. [Fast](https://docs.opencv.org/3.4/df/d0c/tutorial_py_fast.html) is a corner detector, in orb optimizes the traditional Fast algorithms, first is oritated, because the camera can be rotated and scale invariant.

2. ORB use the BRIEF as the descriptor.the BRIEF in ORB can be rotated.

$$R =\begin{pmatrix}
cos\theta & -sin\theta\\
sin\theta & cos\theta
\end{pmatrix}
 $$

$$
m_{pq} = \sum_{_x,y \in B}x^py^qI(x,y),p,q = \left\{1,0\right\}
$$

$$
C = (\frac{m_{10}}{m_{00}},\frac{m_{01}}{m_{00}})
$$

so can mutiple the rotation matric, and the BRIEF can be designed the random points.

last is to calculate the motion according to the matched points.
After match the points, it can become the pixel coordiate point1 p1(u1,v1,1) and point2 p2(u2,v2,1).

$$
P = [X,Y,Z]^T
$$

$$
s_1p_1 = KP
$$

$$
s_2p_2 = K(RP+t)
$$

$$
x_1 = K^{-1}p_1, x_1 = \frac{P}{s_1}
$$

$$
x_2 = K^{-1}p_2,x_2 = \frac{P}{s_2}
$$
